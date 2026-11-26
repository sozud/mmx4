#include "test_runtime.h"
#include "main/visuals/visual_25_flame_jet_fx.h"
#include "support/state_cases.h"
#include "weapon_resources.h"

static struct MainObj jet_owner;
#define sv state_room.visual
#define JET(st, kind) (state_reset(0, 0, 0), memset(&jet_owner, 0, sizeof(jet_owner)), jet_owner.animation_table = (void*)state_table, jet_owner.unk40 = 0x1234, jet_owner.unk42 = (s16)0x8456, jet_owner.unk15 = PLAYER_FACING_RIGHT, jet_owner.bg_offset = 1, sv.active = 1, sv.state = st, sv.unk2 = kind, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, sv.unk50 = (struct PlayerObj*)&jet_owner, flame_jet_fx_update(&sv), state_extra = sv.unk17 | (u32)(u8)sv.unk16 << 8 | (u32)(u8)sv.bg_offset << 16)
static void fj_start_behind(void) { JET(0, 0); }
static void fj_start_front(void) { JET(0, 1); }
static void (*const flame_jet_fx_steps_cases[])(void) = {
    fj_start_behind,
    fj_start_front,
};
static const u32 flame_jet_fx_steps_expected[] = {
    1u, 0xFF400001u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50456u, 0x10000u | (u32)VISUAL_SATURN_LAYER(6) << 8, 0u,
    1u, 0xFF400101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50456u, 0x10101u, 0u,
};
static u32 test_flame_jet_fx_steps(u32 row)
{
    return object_run(flame_jet_fx_steps_cases[row], row, &flame_jet_fx_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "flame_jet_fx_steps", 0, 0, COUNT(flame_jet_fx_steps_cases), test_flame_jet_fx_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flame_jet_fx_steps_cases);
