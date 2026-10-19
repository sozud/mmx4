#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_49_double_afterimage.h"
void func_800D1A48(struct MiscObj*);

#define sm state_room.misc
#define AFTER(st, kind, t) (state_reset(0, 0, 0), sm.active = 1, sm.state = st, sm.unk2 = kind, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.ext.misc_49.timer = t, state_extra = 0)
static void da_init_spark(void)
{
    AFTER(0, 4, 0);
    func_800D1990(&sm);
    state_extra = sm.ext.misc_49.timer;
}
static void da_init_left(void)
{
    AFTER(0, 0, 0);
    func_800D1990(&sm);
    state_extra = sm.ext.misc_49.timer;
}
static void da_init_right(void)
{
    AFTER(0, 3, 0);
    func_800D1990(&sm);
}
static void da_fly(void)
{
    AFTER(1, 0, 3);
    sm.y_vel.val = 0x10000;
    func_800D1A48(&sm);
    state_extra = sm.ext.misc_49.timer | sm.on_screen << 8;
}
static void da_fly_end(void)
{
    AFTER(1, 0, 1);
    func_800D1A48(&sm);
    state_extra = sm.on_screen;
}
static void da_spark(void)
{
    AFTER(1, 4, 3);
    func_800D1A48(&sm);
    state_extra = sm.ext.misc_49.timer | sm.on_screen << 8;
}
static void da_spark_end(void)
{
    AFTER(1, 4, 1);
    func_800D1A48(&sm);
    state_extra = sm.on_screen;
}

static void (*const double_afterimage_states_cases[])(void) = {
    da_init_spark,
    da_init_left,
    da_init_right,
    da_fly,
    da_fly_end,
    da_spark,
    da_spark_end,
};
static const u32 double_afterimage_states_expected[] = { 1u, 0xFF000401u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x14u, 0u, 1u, 0xFF000001u, 0x800000u, 0x600000u, 0x16A0Au, 0x21F0Fu, 0x400000u, 0x50000u, 0xAu, 0u, 1u, 0xFF000301u, 0x800000u, 0x600000u, 0x1F628u, 0xFFFF6A2Du, 0x400000u, 0x50000u, 0u, 0u, 1u, 1u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x40000u, 0x102u, 0u, 2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0x401u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x102u, 0u, 2u, 0x401u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_double_afterimage_states(u32 row)
{
    return object_run(double_afterimage_states_cases[row], row, &double_afterimage_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "double_afterimage_states", 0, 0, COUNT(double_afterimage_states_cases), test_double_afterimage_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_afterimage_states_cases);
