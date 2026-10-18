#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_52_double_mine_shot.h"

static struct MainObj mine_shot_owner;
#define ss state_room.shot
#define MINESHOT(st) (state_reset(0, 0, 0), memset(&mine_shot_owner, 0, sizeof(mine_shot_owner)), ss.state = st, ss.unk7C = (struct WeaponObj*)&mine_shot_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
static void ms_init(void)
{
    MINESHOT(0);
    double_mine_shot_update(&ss);
}
static void ms_fly(void)
{
    MINESHOT(1);
    ss.y_vel.val = -0x40000;
    double_mine_shot_update(&ss);
}
static void ms_owner_gone(void)
{
    MINESHOT(1);
    mine_shot_owner.state = 2;
    double_mine_shot_update(&ss);
}
static void ms_shot_down(void)
{
    MINESHOT(1);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    double_mine_shot_update(&ss);
}
static void ms_away(void)
{
    MINESHOT(1);
    ss.y_pos.i.hi = 0x1000;
    double_mine_shot_update(&ss);
}

static void (*const double_mine_shot_states_cases[])(void) = {
    ms_init,
    ms_fly,
    ms_owner_gone,
    ms_shot_down,
    ms_away,
};
static const u32 double_mine_shot_states_expected[] = { 1u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0xFFFC0000u, 0u, 0x50000u, 0u, 0u, 1u, 0u, 0x800000u, 0x640000u, 0u, 0xFFFC0000u, 0u, 0x40000u, 0u, 0u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x2100u, 2u, 0u, 0x800000u, 0x10000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_double_mine_shot_states(u32 row)
{
    return object_run(double_mine_shot_states_cases[row], row, &double_mine_shot_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "double_mine_shot_states", 0, 0, COUNT(double_mine_shot_states_cases), test_double_mine_shot_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_mine_shot_states_cases);
