#include "test_runtime.h"
#include "main/misc/misc_36_item_sparkle.h"
#include "support/state_cases.h"

static struct MiscObj sparkle_owner;
#define sm state_room.misc
#define SPARKLE(st, kind) (state_reset(0, 0, 0), memset(&sparkle_owner, 0, sizeof(sparkle_owner)), sparkle_owner.unk42 = 0x8123, sparkle_owner.animation_table = (void*)state_table, sm.active = 1, sm.state = st, sm.unk2 = kind, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.ext.pointer.unk50 = (void*)&sparkle_owner, cur_random = 0x1234)
static void is_init_slow(void)
{
    SPARKLE(0, 0);
    item_sparkle_update(&sm);
    state_extra = sparkle_owner.unk42;
}
static void is_init_mid(void)
{
    SPARKLE(0, 1);
    item_sparkle_update(&sm);
}
static void is_init_mid_alt(void)
{
    SPARKLE(0, 1);
    cur_random = 0x1235;
    item_sparkle_update(&sm);
}
static void is_init_fast(void)
{
    SPARKLE(0, 2);
    item_sparkle_update(&sm);
}
static void is_init_fast_alt(void)
{
    SPARKLE(0, 2);
    cur_random = 0x1235;
    item_sparkle_update(&sm);
}
static void is_init_other(void)
{
    SPARKLE(0, 3);
    item_sparkle_update(&sm);
}
static void is_move(void)
{
    SPARKLE(1, 0);
    sm.y_vel.val = 0x10000;
    sm.animation_step.fields.relative_step = 1;
    item_sparkle_update(&sm);
}
static void is_move_done(void)
{
    SPARKLE(1, 0);
    sm.animation_step.fields.relative_step = 0;
    item_sparkle_update(&sm);
}
static void is_move_away(void)
{
    SPARKLE(1, 0);
    sm.animation_step.fields.relative_step = 1;
    sm.y_pos.i.hi = 0x1000;
    item_sparkle_update(&sm);
}
static void is_despawn(void)
{
    SPARKLE(2, 0);
    item_sparkle_update(&sm);
}

static void (*const item_sparkle_states_cases[])(void) = {
    is_init_slow,
    is_init_mid,
    is_init_mid_alt,
    is_init_fast,
    is_init_fast_alt,
    is_init_other,
    is_move,
    is_move_done,
    is_move_away,
    is_despawn,
};
static const u32 item_sparkle_states_expected[] = { 1u, 0xFF000001u, 0x800000u, 0x600000u, 0u, 0x8000u, 0u, 0x50123u, 0x123u, 0u, 1u, 0xFF000101u, 0x800000u, 0x600000u, 0u, 0x18000u, 0u, 0x50123u, 0u, 0u, 1u, 0xFF000101u, 0x800000u, 0x600000u, 0u, 0x10000u, 0u, 0x50123u, 0u, 0u, 1u, 0xFF000201u, 0x800000u, 0x600000u, 0u, 0x28000u, 0u, 0x50123u, 0u, 0u, 1u, 0xFF000201u, 0x800000u, 0x600000u, 0u, 0x20000u, 0u, 0x50123u, 0u, 0u, 1u, 0x301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 1u, 1u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x800000u, 0x10000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_item_sparkle_states(u32 row)
{
    return object_run(item_sparkle_states_cases[row], row, &item_sparkle_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "item_sparkle_states", 0, 0, COUNT(item_sparkle_states_cases), test_item_sparkle_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(item_sparkle_states_cases);
