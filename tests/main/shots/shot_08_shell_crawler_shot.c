#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_08_shell_crawler_shot.h"

#define cs8 state_room.shot
#define SHELL(st, face, setup) (state_reset(0, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), cs8.active = 1, cs8.state = st, cs8.unk15 = face, cs8.x_pos.i.hi = 0x80, cs8.y_pos.i.hi = 0x60, setup, shell_crawler_shot_update(&cs8))
static void shell_init_right(void) { SHELL(0, PLAYER_FACING_RIGHT, 0); }
static void shell_init_left(void) { SHELL(0, 0, 0); }
static void shell_destroyed(void) { SHELL(1, 0, (((struct MainObj*)&cs8)->hp = 1, state_hit((struct MainObj*)&cs8, 0, 0, 1))); }
static void shell_off_screen(void) { SHELL(1, 0, cs8.x_pos.i.hi = 0x200); }
static void shell_despawn(void) { SHELL(2, 0, 0); }
static void (*const shell_cases[])(void) = {
    shell_init_right,
    shell_init_left,
    shell_destroyed,
    shell_off_screen,
    shell_despawn,
};
static const u32 shell_expected[] = {
    0x1u,
    0xFF400001u,
    0x900000u,
    0x630000u,
    0x28000u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0xFF000001u,
    0x700000u,
    0x630000u,
    0xFFFD8000u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x48000u,
    0x0u,
    0x2100u,
    0x2u,
    0x1u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
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
};
static u32 test_shell(u32 row)
{
    return object_run(shell_cases[row], row, &shell_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "shell_crawler_shot_states", 0, 0, COUNT(shell_cases), test_shell },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(shell_cases);
