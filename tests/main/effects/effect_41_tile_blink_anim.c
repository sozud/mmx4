#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/tile_fixture.h"
#include "main/effects/effect_41_tile_blink_anim.h"

extern u8* tile_blink_anim_scripts[1];
#define be state_room.effect
#define BX41 be.ext.effect_41
#define BLINK41(st, setup) (state_reset(0, 0, 0), tile_fixture_begin(), be.active = 1, be.state = st, be.x_pos.i.hi = 0x80, be.y_pos.i.hi = 0x60, setup, tile_blink_anim_update(&be), state_extra = BX41.palette.fields.timer | (u32)BX41.palette.fields.id << 8 | (u32)BX41.unk14 << 16, BX41.palette_source.bytes = NULL, state_room.shot.x_vel.val = tile_fixture_end())
static void blink41_init(void) { BLINK41(0, 0); }
static void blink41_off_screen(void) { BLINK41(1, be.x_pos.i.hi = 0x200); }
static void blink41_waits(void) { BLINK41(1, (BX41.palette_source.bytes = tile_blink_anim_scripts[0], BX41.palette.fields.timer = 3)); }
static void blink41_next_frame(void) { BLINK41(1, (BX41.palette_source.bytes = tile_blink_anim_scripts[0], BX41.palette.fields.timer = 1, BX41.palette.fields.step = 1)); }
static void (*const blink41_cases[])(void) = {
    blink41_init,
    blink41_off_screen,
    blink41_waits,
    blink41_next_frame,
};
static const u32 blink41_expected[] = {
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1000Eu, 0x0u,
    0x0u, 0x0u, 0x2000000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x5710000u | TILE_FIXTURE_WRITES(6, 1), 0x0u, 0x0u, 0x50000u, 0x10Eu, 0x0u,
};
static u32 test_blink41(u32 row)
{
    return object_run(blink41_cases[row], row, &blink41_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "tile_blink_anim_states", 0, 0, COUNT(blink41_cases), test_blink41 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(blink41_cases);
