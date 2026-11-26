#include "test_runtime.h"
#include "main/items/item_14_big_elevator.h"
#include "support/state_cases.h"
void big_elevator_wait_player(struct ItemObj*);
void big_elevator_rise(struct ItemObj*);
void func_800C3BA4(struct ItemObj*);
void big_elevator_restore_camera(struct ItemObj*);

#define be state_room.item
#define BE(setup) (state_reset(0, 0, 0), be.active = 1, be.id = 0xE, be.state = 1, be.x_pos.i.hi = 0x80, be.y_pos.i.hi = 0x900, g_Player.unk5 = 0, setup)
#define BEX() (state_extra = be.unk7C.timer ^ (u32)background_objects[0].unk47 << 24 ^ (u32)(u16)background_objects[0].unk22 << 8)
static void be_wait_boarded(void)
{
    BE(g_Player.unk5 = 1), big_elevator_wait_player(&be), BEX();
}
static void be_wait(void) { BE(0), big_elevator_wait_player(&be), BEX(); }
static void be_rise_held(void) { BE(background_objects[0].unk34 = 1), big_elevator_rise(&be), BEX(); }
static void be_rise_top(void) { BE(be.y_pos.i.hi = 0x8D0), big_elevator_rise(&be), BEX(); }
static void be_rise_speed_up(void) { BE(be.unk7C.timer = 0x4000), big_elevator_rise(&be), BEX(); }
static void be_rise_full_speed(void) { BE(be.unk7C.timer = 0x10000), big_elevator_rise(&be), BEX(); }
static void be_shudder_sink(void) { BE(be.ext.item_2.unk80 = 1), func_800C3BA4(&be), BEX(); }
static void be_shudder_lift(void) { BE(0), func_800C3BA4(&be), BEX(); }
static void be_top_shudder(void) { BE((be.y_pos.i.hi = 0x3B0, background_objects[0].y_pos.i.hi = 0x300)), func_800C3BA4(&be), BEX(); }
static void be_top_shudder_low(void) { BE((be.y_pos.i.hi = 0x3B0, be.ext.item_2.unk80 = 1, background_objects[0].y_pos.i.hi = 0x300)), func_800C3BA4(&be), BEX(); }
static void be_top_stop(void) { BE((be.y_pos.i.hi = 0x3B0, background_objects[0].y_pos.i.hi = 0x2D0, D_80141F50[5] = D_80141F50[6] = state_sound_rows)), func_800C3BA4(&be), BEX(); }
static void be_camera_back(void) { BE(0), big_elevator_restore_camera(&be), BEX(); }
static void be_camera_wait(void) { BE(background_objects[0].unk34 = 1), big_elevator_restore_camera(&be), BEX(); }

static void (*const big_elevator_states_cases[])(void) = {
    be_wait_boarded,
    be_wait,
    be_rise_held,
    be_rise_top,
    be_rise_speed_up,
    be_rise_full_speed,
    be_shudder_sink,
    be_shudder_lift,
    be_top_shudder,
    be_top_shudder_low,
    be_top_stop,
    be_camera_back,
    be_camera_wait,
};
static const u32 big_elevator_states_expected[] = {
    0x10001u,
    0x1u,
    0x800000u,
    0x9000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x4000u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x9000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x9000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x10001u,
    0x1u,
    0x800000u,
    0x8D00000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x8FFB000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x5000u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x8FF0000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10000u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x8FF0000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x9000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1000000u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x3B00000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1000000u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x3B00000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x101u,
    0x1u,
    0x800000u,
    0x3B00000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2D000u,
    0x0u,
    0x101u,
    0x1u,
    0x800000u,
    0x9000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10000u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x9000000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};
static u32 test_big_elevator_states(u32 row)
{
    return object_run(big_elevator_states_cases[row], row, &big_elevator_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "big_elevator_states", 0, 0, COUNT(big_elevator_states_cases), test_big_elevator_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(big_elevator_states_cases);
