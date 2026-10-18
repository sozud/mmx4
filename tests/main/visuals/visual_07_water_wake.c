#include "test_runtime.h"

#include "support/state_cases.h"
s32 water_wake_player_idle(struct PlayerObj*);
s32 water_wake_player_moving(struct PlayerObj*);

static struct PlayerObj wake_player;
#define WAKE(kind, pose) (state_reset(0, 0, 0), memset(&wake_player, 0, sizeof(wake_player)), wake_player.unk2 = kind, wake_player.unk17 = pose, state_extra = water_wake_player_idle(&wake_player) | water_wake_player_moving(&wake_player) << 1)
static void ww_x_still(void)
{
    WAKE(0, 2);
}
static void ww_x_run(void) { WAKE(0, 7); }
static void ww_x_none(void) { WAKE(0, 0); }
static void ww_zero_still(void) { WAKE(1, 3); }
static void ww_zero_run(void) { WAKE(1, 8); }
static void ww_zero_none(void) { WAKE(1, 4); }

static void (*const water_wake_modes_cases[])(void) = {
    ww_x_still,
    ww_x_run,
    ww_x_none,
    ww_zero_still,
    ww_zero_run,
    ww_zero_none,
};
static const u32 water_wake_modes_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_water_wake_modes(u32 row)
{
    return state_run(water_wake_modes_cases[row], row, &water_wake_modes_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "water_wake_modes", 0, 0, COUNT(water_wake_modes_cases), test_water_wake_modes },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(water_wake_modes_cases);
