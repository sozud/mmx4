#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/tile_fixture.h"
#include "main/effects/effect_23_tile_flicker.h"

#define fl state_room.effect
#define FX23 fl.ext.effect_23
#define FLICKER(st, kind, setup) (state_reset(0, 0, 0), tile_fixture_begin(), fl.active = 1, fl.state = st, fl.unk2 = kind, fl.x_pos.i.hi = 0x80, fl.y_pos.i.hi = 0x60, FX23.palette_source.bytes = tile_flicker_scripts[0], FX23.palette.fields.timer = 3, setup, tile_flicker_update(&fl), state_extra = FX23.palette.fields.timer | (u32)FX23.palette.fields.id << 8, FX23.palette_source.bytes = NULL, state_room.shot.x_vel.val = tile_fixture_end())
static void flicker_init_first(void) { FLICKER(0, 0, 0); }
static void flicker_init_second(void) { FLICKER(0, 1, 0); }
static void flicker_off_screen(void) { FLICKER(1, 0, fl.x_pos.i.hi = 0x200); }
static void flicker_stopped(void) { FLICKER(1, 0, engine_obj.character_state.bytes[0] = 1); }
static void flicker_waits(void) { FLICKER(1, 0, 0); }
static void flicker_next_frame(void) { FLICKER(1, 0, (FX23.palette.fields.timer = 1, FX23.palette.fields.step = 1)); }
static void (*const flicker_cases[])(void) = {
    flicker_init_first,
    flicker_init_second,
    flicker_off_screen,
    flicker_stopped,
    flicker_waits,
    flicker_next_frame,
};
static const u32 flicker_expected[] = {
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x102u,
    0x0u,
    0x1u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x402u,
    0x0u,
    0x0u,
    0x0u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x3u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x3u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x6420000u | TILE_FIXTURE_WRITES(6, 1),
    0x0u,
    0x0u,
    0x50000u,
    0x202u,
    0x0u,
};
static u32 test_flicker(u32 row)
{
    return object_run(flicker_cases[row], row, &flicker_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "tile_flicker_states", 0, 0, COUNT(flicker_cases), test_flicker },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flicker_cases);
