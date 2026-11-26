#include "test_runtime.h"
#include "saturn/platform.h"

enum { SATURN_TRANSFER_SLOTS = 80 };
typedef struct {
    u32 byte_length;
    u32 destination;
    u32 source_and_group_end;
} SaturnTransferCommand;
typedef struct {
    u32 add_a;
    u32 add_b;
    u32 attribute_a;
    u32 attribute_b;
} SaturnTransferProfile;
typedef struct {
    SaturnTransferCommand commands[SATURN_TRANSFER_SLOTS];
    SaturnTransferProfile profiles[SATURN_TRANSFER_SLOTS];
    u8 command_count;
    u8 profile_count;
    u8 padding[2];
} SaturnTransferBank;
extern volatile SaturnTransferBank saturn_transfer_primary;
extern volatile SaturnTransferBank saturn_transfer_secondary;
extern volatile u8 saturn_transfer_join;
extern volatile u8 saturn_transfer_join_secondary;
extern u8 saturn_transfer_lock;
void saturn_transfer_enqueue_secondary(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile_secondary(u32 add_a, u32 add_b, unsigned attribute_index);
void saturn_transfer_use_secondary(void);
u32 saturn_transfer_check_busy(void);
void saturn_transfer_unlock(void);

static u32 busy_result;

static void enqueue_joined_wraps(void)
{
    saturn_transfer_primary.command_count = SATURN_TRANSFER_SLOTS - 1;
    saturn_transfer_primary.commands[SATURN_TRANSFER_SLOTS - 2].source_and_group_end = 0x80123456;
    saturn_transfer_join = 1;
    saturn_transfer_enqueue(0x06001000, 0x25C00000, 0x40);
}

static void profile_wraps(void)
{
    saturn_transfer_primary.profile_count = SATURN_TRANSFER_SLOTS - 1;
    saturn_transfer_join = 1;
    saturn_transfer_profile(0x101, 0x202, 1);
}

static void secondary_profile_wraps(void)
{
    saturn_transfer_secondary.profile_count = SATURN_TRANSFER_SLOTS - 1;
    saturn_transfer_profile_secondary(0x505, 0x606, 3);
}

static void use_secondary_copies(void)
{
    saturn_transfer_enqueue_secondary(0x06005000, 0x25C20000, 0x30);
    saturn_transfer_profile_secondary(0x707, 0x808, 1);
    saturn_transfer_enqueue_secondary(0x06006000, 0x25C30000, 0x50);
    saturn_transfer_primary.command_count = 5;
    saturn_transfer_use_secondary();
}

static void busy_while_locked(void)
{
    saturn_transfer_lock = 1;
    busy_result = saturn_transfer_check_busy();
}

static void idle_after_unlock(void)
{
    saturn_transfer_lock = 1;
    saturn_transfer_unlock();
    busy_result = saturn_transfer_check_busy() | 0x100;
}

static void (*const transfer_cases[])(void) = {
    enqueue_joined_wraps,
    profile_wraps,
    secondary_profile_wraps,
    use_secondary_copies,
    busy_while_locked,
    idle_after_unlock,
};

#define WORDS 12
static const u32 transfer_expected[][WORDS] = {
#include "platform_transfer_expected.inc"
};

static u32 transfer_run(u32 row)
{
    volatile SaturnTransferBank* p = &saturn_transfer_primary;
    volatile SaturnTransferBank* s = &saturn_transfer_secondary;
    u32 observed[WORDS];
    busy_result = 0xFFFF;
    transfer_cases[row]();
    observed[0] = p->command_count | p->profile_count << 8 | saturn_transfer_join << 16 | saturn_transfer_lock << 24;
    observed[1] = s->command_count | s->profile_count << 8 | saturn_transfer_join_secondary << 16;
    observed[2] = p->commands[0].byte_length;
    observed[3] = p->commands[0].destination;
    observed[4] = p->commands[0].source_and_group_end;
    observed[5] = p->commands[1].source_and_group_end;
    observed[6] = p->commands[SATURN_TRANSFER_SLOTS - 2].source_and_group_end ^ s->commands[SATURN_TRANSFER_SLOTS - 2].source_and_group_end;
    observed[7] = p->commands[SATURN_TRANSFER_SLOTS - 1].source_and_group_end ^ s->commands[SATURN_TRANSFER_SLOTS - 1].source_and_group_end;
    observed[8] = p->profiles[0].add_a | p->profiles[0].add_b << 16;
    observed[9] = p->profiles[0].attribute_a << 16 | p->profiles[0].attribute_b;
    observed[10] = (p->profiles[SATURN_TRANSFER_SLOTS - 1].add_a | s->profiles[SATURN_TRANSFER_SLOTS - 1].add_a) << 16
        | p->profiles[SATURN_TRANSFER_SLOTS - 1].attribute_b | s->profiles[SATURN_TRANSFER_SLOTS - 1].attribute_b;
    observed[11] = busy_result;
    return c_test_observe(0, row, observed, transfer_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_transfer", 0, 0, COUNT(transfer_cases), transfer_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(transfer_cases);
