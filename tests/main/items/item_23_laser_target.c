#include "test_runtime.h"
#include "main/items/item_23_laser_target.h"
#include "support/state_cases.h"
void laser_target_track(struct ItemObj*);
void func_800C5F90(struct ItemObj*);

#define lt state_room.item
static struct MainObj lt_owner;
#define LT(step) (state_reset(0, 0, 0), memset(&lt_owner, 0, sizeof(lt_owner)), lt.active = 1, lt.state = 1, lt.unk5 = step, lt.x_pos.i.hi = 0x80, lt.y_pos.i.hi = 0x60, lt.unk7C.owner = &lt_owner, lt_owner.state = 1, lt_owner.unk5 = 3)
#define LTX() (state_extra = lt.ext.item_23.unk80 | (u32)lt.ext.item_23.timer << 16)
#define TRACK(dx, dy) (LT(0), lt.ext.item_23.unk80 = 0x100, lt.ext.item_23.timer = 1, g_Player.x_pos.i.hi = 0x80 + (dx), g_Player.y_pos.i.hi = 0x60 + (dy), laser_target_track(&lt), LTX())
static void lt_track_done(void)
{
    LT(0), laser_target_track(&lt), LTX();
}
static void lt_track_wait(void) { LT(0), lt.ext.item_23.unk80 = 0x100, lt.ext.item_23.timer = 3, laser_target_track(&lt), LTX(); }
static void lt_track_far_x(void) { TRACK(20, 0); }
static void lt_track_far_y(void) { TRACK(0, 20); }
static void lt_track_8_x(void) { TRACK(-10, 0); }
static void lt_track_8_y(void) { TRACK(0, -10); }
static void lt_track_4_x(void) { TRACK(6, 0); }
static void lt_track_4_y(void) { TRACK(0, 6); }
static void lt_track_2_x(void) { TRACK(3, 0); }
static void lt_track_2_y(void) { TRACK(0, 3); }
static void lt_track_snap(void) { TRACK(1, 1); }
#define LTMAIN(setup) (LT(1), setup, func_800C5F90(&lt), LTX())
static void lt_main_owner_gone(void)
{
    LTMAIN(lt_owner.state = 2);
}
static void lt_main_owner_busy(void) { LTMAIN(lt_owner.unk5 = 2); }
static void lt_main_owner_firing(void) { LTMAIN((lt_owner.unk5 = 4, lt_owner.unk2 = 2)); }
static void lt_main_owner_firing_held(void) { LTMAIN((lt_owner.unk5 = 4, lt_owner.unk2 = 2, lt.tail_ext.unk1.unk84.previous_value = 1)); }
static void lt_main_lock(void) { LTMAIN(0); }
static void (*const laser_target_states_cases[])(void) = {
    lt_track_done,
    lt_track_wait,
    lt_track_far_x,
    lt_track_far_y,
    lt_track_8_x,
    lt_track_8_y,
    lt_track_4_x,
    lt_track_4_y,
    lt_track_2_x,
    lt_track_2_y,
    lt_track_snap,
    lt_main_owner_gone,
    lt_main_owner_busy,
    lt_main_owner_firing,
    lt_main_owner_firing_held,
    lt_main_lock,
};
static const u32 laser_target_states_expected[] = {
    0x101u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x20100u,
    0x0u,
    0x1u,
    0x1u,
    0x880000u,
    0x600000u,
    0x80000u,
    0x0u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x680000u,
    0x0u,
    0xFFF98000u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x7C0000u,
    0x600000u,
    0xFFFC0000u,
    0x0u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x5C0000u,
    0x0u,
    0x40000u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x820000u,
    0x600000u,
    0x20000u,
    0x0u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x620000u,
    0x0u,
    0xFFFE0000u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x810000u,
    0x600000u,
    0x10000u,
    0x0u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x610000u,
    0x0u,
    0xFFFF0000u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x1u,
    0x1u,
    0x81B505u,
    0x61B505u,
    0xB505u,
    0xFFFF4AFBu,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x30000u,
    0x0u,
    0x0u,
};
static u32 test_laser_target_states(u32 row)
{
    return object_run(laser_target_states_cases[row], row, &laser_target_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "laser_target_states", 0, 0, COUNT(laser_target_states_cases), test_laser_target_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(laser_target_states_cases);
