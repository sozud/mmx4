#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/shot_flight.h"
#include "main/shots/shot_18_aimed_bullet.h"

extern u8 aimed_bullet_hit_box[4];
#define FLY(st, setup) (SHOT_FLIGHT(st, 0, setup), aimed_bullet_update(&sf))
static void aimed_init(void) { FLY(0, (sf.x_vel.val = 0x10000, sf.y_vel.val = -0x8000)); }
static void aimed_destroyed(void) { FLY(1, SHOT_DESTROYED()); }
static void aimed_hits_player(void) { FLY(1, SHOT_PLAYER_HERE(aimed_bullet_hit_box)); }
static void aimed_flies(void) { FLY(1, 0); }
static void aimed_off_screen(void) { FLY(1, SHOT_OFF_SCREEN()); }
static void aimed_despawn(void) { FLY(2, 0); }
static void (*const aimed_cases[])(void) = {
    aimed_init,
    aimed_destroyed,
    aimed_hits_player,
    aimed_flies,
    aimed_off_screen,
    aimed_despawn,
};
static const u32 aimed_expected[] = {
    0x1u, 0xFF000001u, 0x800000u, 0x600000u, 0x20000u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48000u, 0x0u, 0x2100u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x2000000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_aimed(u32 row)
{
    return object_run(aimed_cases[row], row, &aimed_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "aimed_bullet_states", 0, 0, COUNT(aimed_cases), test_aimed },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(aimed_cases);
