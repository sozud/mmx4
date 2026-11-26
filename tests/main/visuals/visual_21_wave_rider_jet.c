#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_21_wave_rider_jet.h"

static struct PlayerObj jet_rider;
#define wj state_room.visual
#define WJET(st, rider_state, frame, shown, setup) (state_reset(0, 0, 0), memset(&jet_rider, 0, sizeof(jet_rider)), jet_rider.state = rider_state, jet_rider.animation_step.fields.frame_index = frame, jet_rider.animation_table = (void*)state_table, jet_rider.unk42 = 0x8123, jet_rider.x_pos.i.hi = 0x90, jet_rider.y_pos.i.hi = 0x70, wj.active = 1, wj.state = st, wj.unk2 = shown, wj.unk50 = &jet_rider, setup, wave_rider_jet_update(&wj), state_extra = wj.unk17, wj.unk50 = NULL)
static void wjet_init(void) { WJET(0, 1, 1, 0, 0); }
static void wjet_rider_reset(void) { WJET(1, 0, 1, 7, 0); }
static void wjet_rider_gone(void) { WJET(1, 2, 1, 7, 0); }
static void wjet_turns(void) { WJET(1, 1, 2, 7, 0); }
static void wjet_burns(void) { WJET(1, 1, 1, 7, 0); }
static void wjet_despawn(void) { WJET(2, 1, 1, 7, 0); }
static void (*const wjet_cases[])(void) = {
    wjet_init,
    wjet_rider_reset,
    wjet_rider_gone,
    wjet_turns,
    wjet_burns,
    wjet_despawn,
};
static const u32 wjet_expected[] = {
    0x1u, 0xFF000701u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x7u, 0x0u,
    0x2u, 0x701u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x2u, 0x701u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0xFF000801u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x8u, 0x0u,
    0x1u, 0x701u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_wjet(u32 row)
{
    return object_run(wjet_cases[row], row, &wjet_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "wave_rider_jet_states", 0, 0, COUNT(wjet_cases), test_wjet },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wjet_cases);
