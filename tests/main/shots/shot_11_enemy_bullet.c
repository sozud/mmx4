#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/shot_flight.h"
#include "main/shots/shot_11_enemy_bullet.h"

extern u8 enemy_bullet_hit_box[4];
#define FLY(st, setup) (SHOT_FLIGHT(st, 0, setup), enemy_bullet_update(&sf))
static void bullet_init(void) { FLY(0, (sf.x_vel.val = 0x10000, sf.y_vel.val = -0x8000)); }
static void bullet_destroyed(void) { FLY(1, SHOT_DESTROYED()); }
static void bullet_hits_player(void) { FLY(1, SHOT_PLAYER_HERE(enemy_bullet_hit_box)); }
static void bullet_flies(void) { FLY(1, 0); }
static void bullet_off_screen(void) { FLY(1, SHOT_OFF_SCREEN()); }
static void bullet_despawn(void) { FLY(2, 0); }
static void (*const bullet_cases[])(void) = {
    bullet_init,
    bullet_destroyed,
    bullet_hits_player,
    bullet_flies,
    bullet_off_screen,
    bullet_despawn,
};
static const u32 bullet_expected[] = {
    0x1u, 0xFF000001u, 0x800000u, 0x600000u, 0x30000u, 0xFFFE8000u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48000u, 0x0u, 0x2100u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x2000000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_bullet(u32 row)
{
    return object_run(bullet_cases[row], row, &bullet_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "enemy_bullet_states", 0, 0, COUNT(bullet_cases), test_bullet },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bullet_cases);
