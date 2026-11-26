#include "test_runtime.h"
#include "main/shots/shot_27_jump_shooter_shot.h"
#include "support/state_cases.h"

#define ss state_room.shot
#define JSS(st, setup) (state_reset(0, 0, 0), memset(&g_Player, 0, sizeof(g_Player)), g_Player.x_pos.i.hi = 0x400, ss.active = 0x41, ss.state = st, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, ss.x_vel.val = 0x10000, ss.y_vel.val = -0x8000, setup, jump_shooter_shot_update(&ss))
static void jss_start_left(void) { JSS(0, 0); }
static void jss_start_right(void) { JSS(0, ss.unk15 = PLAYER_FACING_RIGHT); }
static void jss_gone(void) { JSS(1, ss.x_pos.i.hi = 0x1000); }
static void (*const jump_shooter_shot_steps_cases[])(void) = {
    jss_start_left,
    jss_start_right,
    jss_gone,
};
static const u32 jump_shooter_shot_steps_expected[] = {
    0x1u, 0xFF000041u, 0x820000u, 0x4A0000u, 0x20000u, 0xFFFF0000u, 0u, 0x50000u, 0u, 0u,
    0x1u, 0xFF400041u, 0x7E0000u, 0x4A0000u, 0x20000u, 0xFFFF0000u, 0u, 0x50000u, 0u, 0u,
    0x2u, 0x41u, 0x10010000u, 0x608000u, 0x10000u, 0xFFFF8000u, 0u, 0x40000u, 0u, 0u,
};
static u32 test_jump_shooter_shot_steps(u32 row)
{
    return object_run(jump_shooter_shot_steps_cases[row], row, &jump_shooter_shot_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "jump_shooter_shot_steps", 0, 0, COUNT(jump_shooter_shot_steps_cases), test_jump_shooter_shot_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(jump_shooter_shot_steps_cases);
