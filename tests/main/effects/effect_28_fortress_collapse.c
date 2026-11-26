#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/effects/effect_28_fortress_collapse.h"
#include "main/1AC84.h"
void fortress_collapse_despawn(struct EffectObj*);

#define fe state_room.effect
#define FX28 fe.ext.effect_28
#define FCOL(st, timer_, filter, burst, shake, setup) (state_reset(0, 0, shake), memset(weapon_objects, 0, sizeof(weapon_objects)), g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0x1234, need_palette_load = 0, cur_random = 0x1234, WEAPON_FRAME_COUNTER = 1, fe.active = 1, fe.state = st, FX28.timer = timer_, FX28.filter_timer = filter, FX28.unk1A = burst, setup, fortress_collapse_update(&fe), fe.x_pos.val = g_FilterAmountR | g_FilterAmountG << 16, fe.y_pos.val = g_FilterAmountB | need_palette_load << 16, state_extra = FX28.unk1B | FX28.finished << 2 | FX28.palette_index << 3 | FX28.timer << 8 | FX28.filter_timer << 16 | (u32)FX28.unk1A << 24)
static void fcol_despawn(void)
{
    state_reset(0, 0, 0);
    state_room.effect.active = 1;
    state_room.effect.state = 3;
    fortress_collapse_despawn(&state_room.effect);
}
static void fcol_init(void) { FCOL(0, 0, 0, 0, 0, 0); }
static void fcol_shake_starts(void) { FCOL(1, 0, 0, 0, 0, 0); }
static void fcol_shake_waits(void) { FCOL(1, 0, 0, 0, 5, 0); }
static void fcol_flash_due(void) { FCOL(2, 1, 4, 2, 0, 0); }
static void fcol_red(void) { FCOL(2, 1, 3, 2, 3, FX28.finished = 1); }
static void fcol_red_ends(void) { FCOL(2, 1, 1, 2, 3, FX28.finished = 1); }
static void fcol_white(void) { FCOL(2, 1, 3, 2, 3, (FX28.finished = 1, FX28.palette_index = 1)); }
static void fcol_white_ends(void) { FCOL(2, 1, 1, 2, 3, (FX28.finished = 1, FX28.palette_index = 1)); }
static void fcol_burst_a(void) { FCOL(2, 5, 4, 1, 3, cur_random = 1); }
static void fcol_burst_b(void) { FCOL(2, 5, 4, 1, 3, cur_random = 2); }
static void fcol_burst_c(void) { FCOL(2, 5, 4, 1, 3, cur_random = 3); }
static void fcol_burst_d(void) { FCOL(2, 5, 4, 1, 3, (cur_random = 4, WEAPON_FRAME_COUNTER = 4)); }
static void (*const fcol_cases[])(void) = {
    fcol_despawn,
    fcol_init,
    fcol_shake_starts,
    fcol_shake_waits,
    fcol_flash_due,
    fcol_red,
    fcol_red_ends,
    fcol_white,
    fcol_white_ends,
    fcol_burst_a,
    fcol_burst_b,
    fcol_burst_c,
    fcol_burst_d,
};
static const u32 fcol_expected[] = {
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x27000001u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x3042800u, 0x0u,
    0x9000002u, 0x1u, 0x12341234u, 0x1234u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x4000001u, 0x1u, 0x12341234u, 0x1234u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x9000002u, 0x1u, 0x12341234u, 0x1234u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1040004u, 0x0u,
    0x2000002u, 0x1u, 0x1Fu, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1020104u, 0x0u,
    0x2000002u, 0x1u, 0x0u, 0x10000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1045A08u, 0x0u,
    0x2000002u, 0x1u, 0x3E0001Fu, 0x7C00u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x102010Cu, 0x0u,
    0x2000002u, 0x1u, 0x0u, 0x10000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1042800u, 0x0u,
    0x2000002u, 0x1u, 0x12341234u, 0x1234u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x3040401u, 0x2100u,
    0x2000002u, 0x1u, 0x12341234u, 0x1234u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x3040402u, 0x2100u,
    0x2000002u, 0x1u, 0x12341234u, 0x1234u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x3040403u, 0x2100u,
    0x2000002u, 0x1u, 0x12341234u, 0x1234u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x3040400u, 0x2100u,
};
static u32 test_fcol(u32 row)
{
    return object_run(fcol_cases[row], row, &fcol_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "fortress_collapse_misc", 0, 0, COUNT(fcol_cases), test_fcol },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(fcol_cases);
