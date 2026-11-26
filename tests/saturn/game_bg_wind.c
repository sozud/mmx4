#include "test_runtime.h"
#include "saturn/game_low.h"

void bg_wind_gust_slow(struct EffectObj* effect);
void bg_wind_gust_fast(struct EffectObj* self);
void bg_wind_gust_medium(struct EffectObj* self);
extern u8 bg_wind_steps_slow[];

static struct EffectObj wind;

static void reset(s16 movement_timer, s16 direction, s32 velocity)
{
    c_test_zero_words((u32*)&wind, sizeof(wind) / 4);
    wind.active = 1;
    wind.unk5 = 4;
    wind.ext.effect_9.movement_timer = movement_timer;
    wind.ext.effect_9.direction = direction;
    wind.ext.effect_9.velocity = velocity;
    wind.ext.effect_9.movement_table = bg_wind_steps_slow;
    wind.ext.effect_9.timer = 5;
    wind.ext.effect_9.frame = 1;
    background_objects[2].x_pos.val = 0x00FFF000;
    background_objects[2].y_pos.val = 0x01400000;
    saturn_frame_dma_pending = 0;
}

static void slow_ends_right(void) { reset(1, 0, 0); bg_wind_gust_slow(&wind); }
static void slow_ends_left(void) { reset(1, 1, 0); bg_wind_gust_slow(&wind); }
static void fast_ends_right(void) { reset(1, 0, 0); bg_wind_gust_fast(&wind); }
static void fast_ends_left(void) { reset(1, 1, 0); bg_wind_gust_fast(&wind); }
static void medium_ends_right(void) { reset(1, 0, 0); bg_wind_gust_medium(&wind); }
static void medium_ends_left(void) { reset(1, 1, 0); bg_wind_gust_medium(&wind); }

static void blow_right_at_limit(void) { reset(9, 0, 0x30000); bg_wind_gust_fast(&wind); }
static void blow_left_decelerate(void) { reset(9, 1, 0x40000); bg_wind_gust_medium(&wind); }
static void blow_next_cell(void) { reset(9, 0, 0); wind.ext.effect_9.timer = 1; bg_wind_gust_slow(&wind); }
static void blow_wrap(void) { reset(9, 0, 0); background_objects[2].y_pos.val = 0x01020000; bg_wind_gust_slow(&wind); }

static void (*const wind_cases[])(void) = {
    slow_ends_right, slow_ends_left, fast_ends_right, fast_ends_left, medium_ends_right, medium_ends_left,
    blow_right_at_limit, blow_left_decelerate, blow_next_cell, blow_wrap,
};

#define WORDS 5
static const u32 wind_expected[][WORDS] = {
#include "game_bg_wind_expected.inc"
};

static u32 wind_run(u32 row)
{
    u32 observed[WORDS];
    wind_cases[row]();
    observed[0] = (u8)wind.unk5 | (u32)(u16)wind.ext.effect_9.movement_timer << 16;
    observed[1] = wind.ext.effect_9.timer | (u32)(u8)wind.ext.effect_9.frame << 8 | (u32)wind.ext.effect_9.target_x << 16;
    observed[2] = wind.ext.effect_9.velocity;
    observed[3] = background_objects[2].x_pos.val ^ (u32)saturn_frame_dma_pending << 28;
    observed[4] = background_objects[2].y_pos.val;
    return c_test_observe(0, row, observed, wind_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_bg_wind", 0, 0, COUNT(wind_cases), wind_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wind_cases);
