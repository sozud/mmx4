#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/tile_fixture.h"
#include "main/effects/effect_39_tile_strip_anim.h"

extern u8* tile_strip_anim_scripts[2];
#define ts state_room.effect
#define SX39 ts.ext.effect_39
#define STRIP(st, kind, setup) (state_reset(0, 0, 0), tile_fixture_begin(), ts.active = 1, ts.state = st, ts.unk2 = kind, ts.x_pos.i.hi = 0x80, ts.y_pos.i.hi = 0x60, SX39.palette_source.bytes = tile_strip_anim_scripts[kind], SX39.palette.fields.timer = 3, setup, tile_strip_anim_update(&ts), state_extra = SX39.palette.fields.timer | (u32)SX39.palette.fields.id << 8, SX39.palette_source.bytes = NULL, state_room.shot.x_vel.val = tile_fixture_end())
static void strip_init_long(void)
{
    STRIP(0, 0, 0);
}
static void strip_init_spot(void) { STRIP(0, 1, 0); }
static void strip_waits(void) { STRIP(1, 1, 0); }
static void strip_long_frame(void) { STRIP(1, 0, (SX39.palette.fields.timer = 1, SX39.palette.fields.step = 1)); }
static void strip_spot_frame(void) { STRIP(1, 1, (SX39.palette.fields.timer = 1, SX39.palette.fields.step = 1)); }
static void (*const strip_cases[])(void) = {
    strip_init_long,
    strip_init_spot,
    strip_waits,
    strip_long_frame,
    strip_spot_frame,
};
static const u32 strip_expected[] = {
    0x1u,
    0x1u,
    0x9400000u,
    0x2D00000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x308u,
    0x0u,
    0x1u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x8u,
    0x0u,
    0x1u,
    0x101u,
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
    SATURN_ALT(0x4440003u, 0x4C40200u),
    0x0u,
    0x0u,
    0x50000u,
    0x408u,
    0x0u,
    0x1u,
    0x101u,
    0x800000u,
    0x600000u,
    0x4410000u | TILE_FIXTURE_WRITES(6, 1),
    0x0u,
    0x0u,
    0x50000u,
    0x108u,
    0x0u,
};
static u32 test_strip(u32 row)
{
    return object_run(strip_cases[row], row, &strip_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "tile_strip_anim_states", 0, 0, COUNT(strip_cases), test_strip },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(strip_cases);
