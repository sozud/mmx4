#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_09_dust_puff.h"

static u32 puff_frames[8];
#define pv state_room.visual
#define PUFF(st, kind, phase, frame, setup) (state_reset(0, 0, phase), TEST_SPRITE_FRAMES = (u8*)puff_frames, cur_random = 0x1234, WEAPON_FRAME_COUNTER = frame, pv.active = 1, pv.state = st, pv.unk5C.value = kind, pv.x_pos.i.hi = 0x80, pv.y_pos.i.hi = 0x60, pv.animation_step.fields.relative_step = 1, setup, dust_puff_update(&pv), state_extra = pv.unk17 | (u32)pv.on_screen << 8 | (u32)(u16)pv.unk42 << 16)
static void puff_init_kind_2(void) { PUFF(0, 2, 1, 0, 0); }
static void puff_init_kind_0(void) { PUFF(0, 0, 0, 0, 0); }
static void puff_kind_2_shown(void) { PUFF(1, 2, 1, 0, 0); }
static void puff_kind_1_on_phase(void) { PUFF(1, 1, 1, 1, 0); }
static void puff_kind_0_off_phase(void) { PUFF(1, 0, 1, 2, 0); }
static void puff_ends(void) { PUFF(1, 0, 1, 2, pv.animation_step.fields.relative_step = 0); }
static void (*const puff_cases[])(void) = {
    puff_init_kind_2,
    puff_init_kind_0,
    puff_kind_2_shown,
    puff_kind_1_on_phase,
    puff_kind_0_off_phase,
    puff_ends,
};
static const u32 puff_expected[] = {
    0x1u, 0xFF000001u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x20000u | WEAPON_PALETTE_6, WEAPON_PALETTE_6 << 16 | 0x102u, 0x0u,
    0x1u, 0xFF000001u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x20000u | WEAPON_PALETTE_5, WEAPON_PALETTE_5 << 16 | 0x100u, 0x0u,
    0x1000001u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x1000001u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x1000001u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
};
static u32 test_puff(u32 row)
{
    return object_run(puff_cases[row], row, &puff_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dust_puff_states", 0, 0, COUNT(puff_cases), test_puff },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(puff_cases);
