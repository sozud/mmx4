#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/shot_flight.h"
#include "main/shots/shot_15_turret_laser.h"

#define LASER(st, step, setup) (SHOT_FLIGHT(st, step, setup), turret_laser_update(&sf))
static void laser_init(void) { LASER(0, 0, 0); }
static void laser_destroyed(void) { LASER(1, 2, SHOT_DESTROYED()); }
static void laser_moves(void) { LASER(1, 2, sf.x_vel.val = 0x10000); }
static void laser_waits_off_screen(void) { LASER(1, 1, SHOT_OFF_SCREEN()); }
static void laser_hit_reaction(void) { LASER(1, 0, ((struct MainObj*)&sf)->unk63 = 1); }
static void laser_despawn(void) { LASER(2, 0, 0); }
static void (*const laser_cases[])(void) = {
    laser_init,
    laser_destroyed,
    laser_moves,
    laser_waits_off_screen,
    laser_hit_reaction,
    laser_despawn,
};
static const u32 laser_expected[] = {
    0x201u,
    0xFF000001u,
    0x900000u,
    0x700000u,
    0x20000u,
    0x0u,
    0x0u,
    0x50123u,
    0x0u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x58000u,
    0x0u,
    0x2100u,
    0x201u,
    0x1u,
    0x810000u,
    0x600000u,
    0x10000u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x102u,
    0x1u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x10001u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x58000u,
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
static u32 test_laser(u32 row)
{
    return object_run(laser_cases[row], row, &laser_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "turret_laser_states", 0, 0, COUNT(laser_cases), test_laser },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(laser_cases);
