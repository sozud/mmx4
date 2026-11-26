#include "test_runtime.h"
#include "main/weapons/weapon_09_charge_shot.h"
#include "support/state_cases.h"

extern struct Unk_unk68 D_80108708[];
#define sw state_room.weapon
#define CHARGE(st, kind, setup) (state_reset(0, 0, 0), sw.active = 1, sw.id = kind, sw.state = st, sw.on_screen = 1, sw.x_pos.i.hi = 0x80, sw.y_pos.i.hi = 0x60, sw.x_vel.val = 0x80000, setup, charge_shot_update(&sw), state_extra = sw.unk17 | (u32)(sw.unk50 == (const u8*)&D_80108708[sw.unk2]) << 8 | (u32)(u8)sw.on_screen << 16)
static void cs_level_2_left(void)
{
    CHARGE(0, 9, 0);
}
static void cs_level_3_right(void) { CHARGE(0, 18, sw.unk15 = PLAYER_FACING_RIGHT); }
static void cs_far(void) { CHARGE(1, 9, sw.x_pos.i.hi = 0x1000); }
static void cs_stopped(void) { CHARGE(1, 9, sw.unk98 = 1); }
static void cs_flying(void) { CHARGE(1, 9, 0); }
static void (*const charge_shot_steps_cases[])(void) = {
    cs_level_2_left,
    cs_level_3_right,
    cs_far,
    cs_stopped,
    cs_flying,
};
static const u32 charge_shot_steps_expected[] = {
    0x1u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0xFFF80000u,
    0u,
    0u,
    0x50000u,
    0x1011Au,
    0u,
    0x1u,
    0xFF400101u,
    0x800000u,
    0x600000u,
    0xA0000u,
    0u,
    0u,
    0x50000u,
    0x1011Bu,
    0u,
    0x3u,
    0x1u,
    0x10000000u,
    0x600000u,
    0x80000u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x3u,
    0x1u,
    0x800000u,
    0x600000u,
    0x80000u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x1u,
    0x1u,
    0x880000u,
    0x600000u,
    0x80000u,
    0u,
    0u,
    0x40000u,
    0x10000u,
    0u,
};
static u32 test_charge_shot_steps(u32 row)
{
    return object_run(charge_shot_steps_cases[row], row, &charge_shot_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "charge_shot_steps", 0, 0, COUNT(charge_shot_steps_cases), test_charge_shot_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(charge_shot_steps_cases);
