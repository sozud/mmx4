#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_31_slash_beast_crescent.h"

void slash_beast_crescent_fly(struct ShotObj*);
#define sc state_room.shot
#define CRESCENT(st, kind, face, setup) (state_reset(0, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), sc.active = 1, sc.state = st, sc.unk2 = kind, sc.unk15 = face, sc.unk42 = 0x8123, sc.x_pos.i.hi = 0x80, sc.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x400, setup, slash_beast_crescent_update(&sc))
static void crescent_init_level_left(void) { CRESCENT(0, 0, 0, 0); }
static void crescent_init_level_right(void) { CRESCENT(0, 0, PLAYER_FACING_RIGHT, 0); }
static void crescent_init_low_left(void) { CRESCENT(0, 1, 0, 0); }
static void crescent_init_low_right(void) { CRESCENT(0, 1, PLAYER_FACING_RIGHT, 0); }
static void crescent_destroyed(void) { CRESCENT(1, 0, 0, (((struct MainObj*)&sc)->hp = 1, state_hit((struct MainObj*)&sc, 0, 0, 1))); }
static void crescent_off_screen(void) { CRESCENT(1, 0, 0, sc.x_pos.i.hi = 0x200); }
static void crescent_despawn(void) { CRESCENT(2, 0, 0, 0); }
static void (*const crescent_cases[])(void) = {
    crescent_init_level_left,
    crescent_init_level_right,
    crescent_init_low_left,
    crescent_init_low_right,
    crescent_destroyed,
    crescent_off_screen,
    crescent_despawn,
};
static const u32 crescent_expected[] = {
    0x1u, 0xFF000001u, 0x380000u, 0x5A0000u, 0xFFFB0000u, 0x0u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF400001u, 0xC80000u, 0x5A0000u, 0x50000u, 0x0u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000101u, 0x440000u, 0x2D0000u, 0xFFFC76E7u, 0x38919u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF400101u, 0xBC0000u, 0x2D0000u, 0x38919u, 0x38919u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x0u, 0x2100u,
    0x2u, 0x1u, 0x2000000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x58123u, 0x0u, 0x0u,
};
static u32 test_crescent(u32 row)
{
    return object_run(crescent_cases[row], row, &crescent_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "slash_beast_crescent_states", 0, 0, COUNT(crescent_cases), test_crescent },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(crescent_cases);
