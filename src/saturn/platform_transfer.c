#include "saturn.h"
#include "saturn/platform.h"
#include <stddef.h>

#define SR_IMASK_CLEAR 0xFF0F
#define SR_IMASK_ALL 0xF0
#define TRANSFER_LOCK_BUSY 2

extern u8 saturn_transfer_lock;

#define SCU_DMA0_READ (*(volatile u32*)0x25FE0000)
#define SCU_DMA0_WRITE (*(volatile u32*)0x25FE0004)
#define SCU_DMA0_COUNT (*(volatile u32*)0x25FE0008)
#define SCU_DMA0_ADD (*(volatile u32*)0x25FE000C)
#define SCU_DMA0_ENABLE (*(volatile u32*)0x25FE0010)
#define SCU_DMA0_MODE (*(volatile u32*)0x25FE0014)
#define SCU_DMA_START 0x101
#define SCU_DMA_MODE_FACTOR 7
#define SCU_DMA_LEVEL0_END 75
#define SCU_MASK_DMA_END (-0x801)
#define TRANSFER_GROUP_END 0x80000000
#define TRANSFER_ADDRESS_MASK 0x7FFFFFFF
#define CS2_FIRST 0x20200000
#define CS2_LAST 0x20300000
#define LOW_RAM_FIRST 0x00200000
#define LOW_RAM_LAST 0x00300000

typedef void (*SaturnScuMaskChange)(s32 mask, s32 bits);
extern SaturnScuMaskChange saturn_bios_change_scu_mask;
extern void* saturn_transfer_saved_handler;
extern u32 saturn_transfer_profiles[];
void* INT_GetScuFunc(s32 vector);
void INT_SetScuFunc(s32 vector, void* function);

const u16 saturn_transfer_attributes[][2] = { { 0, 0 }, { 0, 0x100 }, { 0, 0x100 }, { 0, 0 } };

void saturn_interrupt_timer_0(void)
{
}

void saturn_interrupt_timer_1(void)
{
}

static u32 transfer_skipped(u32 address)
{
    return (address >= CS2_FIRST && address < CS2_LAST) || (address >= LOW_RAM_FIRST && address < LOW_RAM_LAST);
}

void saturn_transfer_flush(void)
{
    u32 mask;
    u8 index;
    u8 profile = 0;
    u32* command;
    u32* settings;
    u32 source;
    if (saturn_transfer_command_count == 0) {
        return;
    }
    mask = (_builtin_get_cr() >> 4) & 15;
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    saturn_transfer_lock = 1;
    saturn_transfer_saved_handler = INT_GetScuFunc(SCU_DMA_LEVEL0_END);
    INT_SetScuFunc(SCU_DMA_LEVEL0_END, (void*)saturn_transfer_unlock);
    saturn_bios_change_scu_mask(SCU_MASK_DMA_END, 0);
    _builtin_set_cr(((mask & 15) << 4) | (_builtin_get_cr() & SR_IMASK_CLEAR));
    for (index = 0; index < saturn_transfer_command_count; index++) {
        command = (u32*)((u8*)&saturn_transfer_primary + (s16)(index * 12));
        if (transfer_skipped(command[1]) || transfer_skipped(command[2])) {
            continue;
        }
        SCU_DMA0_COUNT = command[0];
        SCU_DMA0_WRITE = command[1];
        source = command[2];
        SCU_DMA0_READ = source & TRANSFER_ADDRESS_MASK;
        settings = saturn_transfer_profiles + profile * 4;
        SCU_DMA0_ADD = settings[0] | settings[1];
        SCU_DMA0_MODE = settings[2] | settings[3] | SCU_DMA_MODE_FACTOR;
        if (source & TRANSFER_GROUP_END) {
            profile++;
        }
        SCU_DMA0_ENABLE = SCU_DMA_START;
        while (saturn_transfer_check_busy() == TRANSFER_LOCK_BUSY) {
        }
    }
    saturn_transfer_profile_count = 0;
    saturn_transfer_command_count = 0;
    mask = (_builtin_get_cr() >> 4) & 15;
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    INT_SetScuFunc(SCU_DMA_LEVEL0_END, saturn_transfer_saved_handler);
    _builtin_set_cr(((mask & 15) << 4) | (_builtin_get_cr() & SR_IMASK_CLEAR));
}

static inline void
copy_transfers(volatile SaturnTransferBank* primary, volatile u8* primary_join,
    volatile SaturnTransferBank* secondary, volatile u8* secondary_join)
{
    for (unsigned i = 0; i < secondary->command_count; ++i) {
        primary->commands[i].byte_length = secondary->commands[i].byte_length;
        primary->commands[i].destination = secondary->commands[i].destination;
        primary->commands[i].source_and_group_end = secondary->commands[i].source_and_group_end;
    }
    for (unsigned i = 0; i < secondary->profile_count; ++i) {
        primary->profiles[i].add_a = secondary->profiles[i].add_a;
        primary->profiles[i].add_b = secondary->profiles[i].add_b;
        primary->profiles[i].attribute_a = secondary->profiles[i].attribute_a;
        primary->profiles[i].attribute_b = secondary->profiles[i].attribute_b;
    }
    *primary_join = *secondary_join;
    primary->command_count = secondary->command_count;
    primary->profile_count = secondary->profile_count;
    secondary->command_count = 0;
    secondary->profile_count = 0;
}

void saturn_transfer_copy(volatile SaturnTransferBank* primary, volatile u8* primary_join,
    volatile SaturnTransferBank* secondary, volatile u8* secondary_join)
{
    copy_transfers(primary, primary_join, secondary, secondary_join);
}

static inline void advance_count(volatile u8* count)
{
    *count = (u8)(*count + 1);
    unsigned next = *count;
    while (next >= SATURN_TRANSFER_SLOTS) {
        next -= SATURN_TRANSFER_SLOTS;
    }
    *count = (u8)next;
}

static inline void
append_profile(volatile SaturnTransferBank* bank, volatile u8* join,
    u32 add_a, u32 add_b, const u16 attributes[2])
{
    *join = 0;
    bank->profiles[bank->profile_count].add_a = add_a;
    bank->profiles[bank->profile_count].add_b = add_b;
    bank->profiles[bank->profile_count].attribute_a = attributes[0];
    bank->profiles[bank->profile_count].attribute_b = attributes[1];
    advance_count(&bank->profile_count);
}

void saturn_transfer_add_profile(volatile SaturnTransferBank* bank, volatile u8* join,
    u32 add_a, u32 add_b, const u16 attributes[2])
{
    append_profile(bank, join, add_a, add_b, attributes);
}

static inline void
append_transfer(volatile SaturnTransferBank* bank, volatile u8* join,
    u32 source, u32 destination, u32 byte_length)
{
    bank->commands[bank->command_count].byte_length = byte_length;
    bank->commands[bank->command_count].destination = destination;
    bank->commands[bank->command_count].source_and_group_end = source | 0x80000000U;
    if (bank->command_count && *join) {
        bank->commands[bank->command_count - 1].source_and_group_end &= 0x7FFFFFFFU;
    }
    advance_count(&bank->command_count);
    *join = 1;
}

void saturn_transfer_append(volatile SaturnTransferBank* bank, volatile u8* join,
    u32 source, u32 destination, u32 byte_length)
{
    append_transfer(bank, join, source, destination, byte_length);
}

void saturn_transfer_enqueue(u32 source, u32 destination, u32 byte_length)
{
    append_transfer(&saturn_transfer_primary, &saturn_transfer_join, source, destination, byte_length);
}

void saturn_transfer_profile(u32 add_a, u32 add_b, unsigned attribute_index)
{
    append_profile(&saturn_transfer_primary, &saturn_transfer_join, add_a, add_b,
        saturn_transfer_attributes[attribute_index]);
}

void saturn_transfer_enqueue_secondary(u32 source, u32 destination, u32 byte_length)
{
    append_transfer(&saturn_transfer_secondary, &saturn_transfer_join_secondary, source, destination, byte_length);
}

void saturn_transfer_profile_secondary(u32 add_a, u32 add_b, unsigned attribute_index)
{
    append_profile(&saturn_transfer_secondary, &saturn_transfer_join_secondary, add_a, add_b,
        saturn_transfer_attributes[attribute_index]);
}

void saturn_transfer_use_secondary(void)
{
    copy_transfers(&saturn_transfer_primary, &saturn_transfer_join,
        &saturn_transfer_secondary, &saturn_transfer_join_secondary);
}

u32 saturn_transfer_check_busy(void)
{
    volatile u32 state;
    u32 mask = (_builtin_get_cr() >> 4) & 15;
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    state = saturn_transfer_lock;
    if (state == 1) {
        _builtin_set_cr(((mask & 15) << 4) | (_builtin_get_cr() & SR_IMASK_CLEAR));
        return TRANSFER_LOCK_BUSY;
    }
    _builtin_set_cr(((mask & 15) << 4) | (_builtin_get_cr() & SR_IMASK_CLEAR));
    return 0;
}

void saturn_transfer_unlock(void)
{
    u32 mask = (_builtin_get_cr() >> 4) & 15;
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    saturn_transfer_lock = 0;
    _builtin_set_cr(((mask & 15) << 4) | (_builtin_get_cr() & SR_IMASK_CLEAR));
}
