#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/tile_fixture.h"
#include "main/effects/effect_29_tile_anim_trigger.h"

#define ae state_room.effect
#define AX29 ae.ext.effect_29
#define TANIM(st, setup) (state_reset(0, 0, 0), tile_fixture_begin(), ae.active = 1, ae.state = st, ae.unk2 = 1, ae.x_pos.i.hi = 0x80, ae.y_pos.i.hi = 0x60, setup, tile_anim_trigger_update(&ae), state_extra = AX29.palette.fields.timer | (u32)AX29.palette.fields.id << 8 | (u32)AX29.unk14 << 16, AX29.palette_source.animation = NULL, state_room.shot.x_vel.val = tile_fixture_end())
static void tanim_init(void) { TANIM(0, 0); }
static void tanim_init_off_screen(void) { TANIM(0, ae.x_pos.i.hi = 0x200); }
static void tanim_off_screen(void) { TANIM(1, ae.x_pos.i.hi = 0x200); }
static void tanim_waits(void) { TANIM(1, (AX29.palette_source.animation = tile_anim_scripts[1], AX29.palette.fields.timer = 3)); }
static void tanim_next_frame(void) { TANIM(1, (AX29.palette_source.animation = tile_anim_scripts[1], AX29.palette.fields.timer = 1, AX29.palette.fields.step = 1)); }
static void (*const tanim_cases[])(void) = {
    tanim_init,
    tanim_init_off_screen,
    tanim_off_screen,
    tanim_waits,
    tanim_next_frame,
};
static const u32 tanim_expected[] = {
    0x1u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20302u,
    0x0u,
    0x0u,
    0x101u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20000u,
    0x0u,
    0x0u,
    0x0u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
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
    0x101u,
    0x800000u,
    0x600000u,
    0x4440000u | TILE_FIXTURE_WRITES(6, 1),
    0x0u,
    0x0u,
    0x50000u,
    0x402u,
    0x0u,
};
static u32 test_tanim(u32 row)
{
    return object_run(tanim_cases[row], row, &tanim_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "tile_anim_trigger_states", 0, 0, COUNT(tanim_cases), test_tanim },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tanim_cases);
