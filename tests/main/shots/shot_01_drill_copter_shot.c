#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_01_drill_copter_shot.h"

#define ss state_room.shot
#define DCS(st, side) (state_reset(0, 0, 0), ss.active = 1, ss.state = st, ss.unk2 = side, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
static void dcs_init_left(void)
{
    DCS(0, 1);
    drill_copter_shot_update(&ss);
}
static void dcs_init_right(void)
{
    DCS(0, 0);
    drill_copter_shot_update(&ss);
}
static void dcs_fly(void)
{
    DCS(1, 0);
    ss.x_vel.val = 0x60000;
    drill_copter_shot_update(&ss);
}
static void dcs_fly_hit(void)
{
    DCS(1, 0);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    drill_copter_shot_update(&ss);
}
static void dcs_away(void)
{
    DCS(1, 0);
    ss.x_pos.i.hi = 0x1000;
    drill_copter_shot_update(&ss);
}
static void dcs_despawn(void)
{
    DCS(2, 0);
    drill_copter_shot_update(&ss);
}

static void (*const drill_copter_shot_states_cases[])(void) = {
    dcs_init_left,
    dcs_init_right,
    dcs_fly,
    dcs_fly_hit,
    dcs_away,
    dcs_despawn,
};
static const u32 drill_copter_shot_states_expected[] = { 1u, 0xFF000101u, 0x6E0000u, 0x690000u, 0xFFFA0000u, 0u, 0u, 0x30000u, 0u, 0u, 1u, 0xFF400001u, 0x920000u, 0x690000u, 0x60000u, 0u, 0u, 0x30000u, 0u, 0u, 1u, 1u, 0x860000u, 0x600000u, 0x60000u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x2100u, 2u, 1u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_drill_copter_shot_states(u32 row)
{
    return object_run(drill_copter_shot_states_cases[row], row, &drill_copter_shot_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "drill_copter_shot_states", 0, 0, COUNT(drill_copter_shot_states_cases), test_drill_copter_shot_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(drill_copter_shot_states_cases);
