#include "test_runtime.h"
#include "main/effects/effect_09_bg_wind.h"

static const u32 bg_wind_delay_expected[] = { 0u, 0xFFFFFFFFu, 0u, 0u };
static u32 test_bg_wind_delay(u32 row)
{
    u32 observed_values[4];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    bg_wind_delay(&obj);
    observed_values[0] = (u32)obj.ext.effect_9.direction;
    observed_values[1] = (u32)obj.ext.effect_9.transition_timer;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, bg_wind_delay_expected, 4);
}


extern u8 bg_wind_steps_slow[], bg_wind_steps_fast[], bg_wind_steps_medium[];
static struct EffectObj wind;
enum { SLOW = 1,
    FAST,
    MEDIUM,
    STORM };
static void wind_reset(u8 phase, s16 movement, s16 direction, s32 velocity, u8 timer, s32 y)
{
    memset(&wind, 0, sizeof(wind));
    wind.active = 1;
    wind.id = 9;
    wind.state = 2;
    wind.unk5 = phase;
    wind.ext.effect_9.movement_timer = movement;
    wind.ext.effect_9.direction = direction;
    wind.ext.effect_9.velocity = velocity;
    wind.ext.effect_9.movement_table = bg_wind_steps_slow;
    wind.ext.effect_9.timer = timer;
    wind.ext.effect_9.frame = 1;
    wind.ext.effect_9.target_x = 4;
    background_objects[2].x_pos.val = 0x00BFF000;
    background_objects[2].y_pos.val = y;
}
#define LIMIT(phase) ((s32)(phase)*FIXED(1) + FIXED(0.5))
#define END(phase, direction) (wind_reset(phase, 1, direction, 0, 5, FIXED(320)), bg_wind_update(&wind))
#define STEP(phase) (wind_reset(phase, 9, 0, LIMIT(phase) - FIXED(1.0 / 64), 1, FIXED(258)), bg_wind_update(&wind))
#define SLOW_DOWN(phase) (wind_reset(phase, 9, 1, LIMIT(phase) + FIXED(1.0 / 16), 5, FIXED(320)), background_objects[2].x_pos.val = 0, bg_wind_update(&wind))
#define HOLD(phase, direction) (wind_reset(phase, 9, direction, LIMIT(phase), 5, FIXED(320)), background_objects[2].x_pos.val = 0, bg_wind_update(&wind))
static void wind_slow_ends_right(void) { END(SLOW, 0); }
static void wind_slow_ends_left(void) { END(SLOW, 1); }
static void wind_fast_ends_right(void) { END(FAST, 0); }
static void wind_fast_ends_left(void) { END(FAST, 1); }
static void wind_medium_ends_right(void) { END(MEDIUM, 0); }
static void wind_medium_ends_left(void) { END(MEDIUM, 1); }
static void wind_storm_ends(void) { END(STORM, 0); }
static void wind_slow_next_cell(void) { STEP(SLOW); }
static void wind_fast_next_cell(void) { STEP(FAST); }
static void wind_medium_next_cell(void) { STEP(MEDIUM); }
static void wind_storm_next_cell(void) { STEP(STORM); }
static void wind_slow_slows(void) { SLOW_DOWN(SLOW); }
static void wind_fast_slows(void) { SLOW_DOWN(FAST); }
static void wind_medium_slows(void) { SLOW_DOWN(MEDIUM); }
static void wind_slow_holds_right(void) { HOLD(SLOW, 0); }
static void wind_slow_holds_left(void) { HOLD(SLOW, 1); }
static void wind_fast_holds_right(void) { HOLD(FAST, 0); }
static void wind_fast_holds_left(void) { HOLD(FAST, 1); }
static void wind_medium_holds_right(void) { HOLD(MEDIUM, 0); }
static void wind_medium_holds_left(void) { HOLD(MEDIUM, 1); }
static void wind_storm_holds(void) { HOLD(STORM, 0); }
static void wind_calm_ends(void) { wind_reset(0, 0, 1, 0, 0, FIXED(320)), wind.ext.effect_9.frame = 0, wind.ext.effect_9.target_x = 0, wind.ext.effect_9.movement_table = NULL, bg_wind_update(&wind); }
static void wind_calm_gusts(void) { wind_reset(0, 0, 0, 0, 0, FIXED(320)), bg_wind_update(&wind); }
static void wind_delay_done(void) { wind_reset(0, 0, 1, 0, 5, FIXED(320)), wind.state = 1, wind.ext.effect_9.transition_timer = 1, bg_wind_update(&wind); }
static void wind_init(void) { wind_reset(0, 0, 0, 0, 5, FIXED(320)), wind.state = 0, bg_wind_update(&wind); }

static void (*const bg_wind_phase_cases[])(void) = {
    wind_slow_ends_right,
    wind_slow_ends_left,
    wind_fast_ends_right,
    wind_fast_ends_left,
    wind_medium_ends_right,
    wind_medium_ends_left,
    wind_storm_ends,
    wind_slow_next_cell,
    wind_fast_next_cell,
    wind_medium_next_cell,
    wind_storm_next_cell,
    wind_slow_slows,
    wind_fast_slows,
    wind_medium_slows,
    wind_slow_holds_right,
    wind_slow_holds_left,
    wind_fast_holds_right,
    wind_fast_holds_left,
    wind_medium_holds_right,
    wind_medium_holds_left,
    wind_storm_holds,
    wind_calm_ends,
    wind_calm_gusts,
    wind_delay_done,
    wind_init,
};
#define WIND_WORDS 6
static const u32 bg_wind_phase_expected[][WIND_WORDS] = {
    { 0xB40202u, 0x40105u, 0u, 0x1400000u, 0u, 0x100u },
    { 0xB40200u, 0x40105u, 0u, 0x1400000u, 1u, 0x100u },
    { 0x780203u, 0x40105u, 0u, 0x1400000u, 0u, 0x100u },
    { 0x1680201u, 0x70105u, 0u, 0x1400000u, 1u, 0x200u },
    { 0x960204u, 0x105u, 0u, 0x1400000u, 0u, 0x300u },
    { 0xB40202u, 0x40105u, 0u, 0x1400000u, 1u, 0x100u },
    { 0x780203u, 0x40105u, 0u, 0x1400000u, 1u, 0x100u },
    { 0x80201u, 0x50105u, 0x18000u, 0x1800000u, 0u, 0x101u },
    { 0x80202u, 0x50105u, 0x28000u, 0x1800000u, 0u, 0x101u },
    { 0x80203u, 0x50105u, 0x38000u, 0x1800000u, 0u, 0x101u },
    { 0x80204u, 0x50105u, 0x48000u, 0x1800000u, 0u, 0x101u },
    { 0x80201u, 0x40104u, 0x18C00u, 0x13E0000u, 1u, 0x100u },
    { 0x80202u, 0x40104u, 0x28C00u, 0x13E0000u, 1u, 0x100u },
    { 0x80203u, 0x40104u, 0x38C00u, 0x13E0000u, 1u, 0x100u },
    { 0x80201u, 0x40104u, 0x18000u, 0x13E0000u, 0u, 0x100u },
    { 0x80201u, 0x40104u, 0x18000u, 0x13E0000u, 1u, 0x100u },
    { 0x80202u, 0x40104u, 0x28000u, 0x13E0000u, 0u, 0x100u },
    { 0x80202u, 0x40104u, 0x28000u, 0x13E0000u, 1u, 0x100u },
    { 0x80203u, 0x40104u, 0x38000u, 0x13E0000u, 0u, 0x100u },
    { 0x80203u, 0x40104u, 0x38000u, 0x13E0000u, 1u, 0x100u },
    { 0x80204u, 0x40104u, 0x48000u, 0x13E0000u, 0u, 0x100u },
    { 0x100u, 0u, 0u, 0u, 0x10001u, 0u },
    { 0x1680201u, 0x70105u, 0x10000u, 0x1800000u, 0u, 0x200u },
    { 0x200u, 0x40105u, 0u, 0x1400000u, 0u, 0x100u },
    { 0x100u, 0x40105u, 0u, 0u, 0x10000u, 0x100u },
};
static u32 wind_table(const u8* table)
{
    if (table == NULL)
        return 0;
    if (table >= bg_wind_steps_slow && table < bg_wind_steps_slow + 12)
        return 0x100 | (u32)(table - bg_wind_steps_slow) / 4;
    if (table >= bg_wind_steps_fast && table < bg_wind_steps_fast + 12)
        return 0x200 | (u32)(table - bg_wind_steps_fast) / 4;
    return 0x300 | (u32)(table - bg_wind_steps_medium) / 4;
}
static u32 test_bg_wind_phases(u32 row)
{
    u32 observed[WIND_WORDS];
    bg_wind_phase_cases[row]();
    observed[0] = (u8)wind.unk5 | (u32)(u8)wind.state << 8 | (u32)(u16)wind.ext.effect_9.movement_timer << 16;
    observed[1] = wind.ext.effect_9.timer | (u32)(u8)wind.ext.effect_9.frame << 8 | (u32)wind.ext.effect_9.target_x << 16;
    observed[2] = wind.ext.effect_9.velocity;
    observed[3] = background_objects[2].y_pos.val;
    observed[4] = (u16)wind.ext.effect_9.direction | (u32)(u16)wind.ext.effect_9.transition_timer << 16;
    observed[5] = wind_table(wind.ext.effect_9.movement_table);
    return c_test_observe(1, row, observed, bg_wind_phase_expected[row], WIND_WORDS);
}

u8 player_in_bounds(s16* bounds);
static s16 wind_bounds[4] = { 0x10, 0x100, 0x20, 0x80 };
static const s16 player_in_bounds_points[][2] = { { 0x10, 0x40 }, { 0x100, 0x40 }, { 0x50, 0x20 }, { 0x50, 0x80 }, { 0x50, 0x40 } };
static const u32 player_in_bounds_expected[] = { 0u, 0u, 0u, 0u, 1u };
static u32 test_player_in_bounds(u32 row)
{
    u32 observed;
    g_Player.x_pos.i.hi = player_in_bounds_points[row][0];
    g_Player.y_pos.i.hi = player_in_bounds_points[row][1];
    observed = player_in_bounds(wind_bounds);
    return c_test_observe(2, row, &observed, &player_in_bounds_expected[row], 1);
}

const struct CTestGroup c_test_groups[] = {
    { "bg_wind_delay", 0, 0, 1, test_bg_wind_delay },
    { "bg_wind_phases", 0, 0, COUNT(bg_wind_phase_cases), test_bg_wind_phases },
    { "player_in_bounds", 0, 0, COUNT(player_in_bounds_expected), test_player_in_bounds },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(bg_wind_phase_cases) + COUNT(player_in_bounds_expected);
