#include "test_runtime.h"

extern union AnimationStep* D_800F8FC4[38];
void ride_chaser_jet_update(struct VisualObj*);

static struct PlayerObj rider;
static struct VisualObj jet;

static u32 jet_case(u32 row)
{
    static const s16 x[] = { 100, 100, 100, 100, 100, 400, 100 };
    static const s16 y[] = { 80, 80, 80, 80, 80, 80, 300 };
    c_test_zero_words((u32*)&rider, sizeof(rider) / 4);
    c_test_zero_words((u32*)&jet, sizeof(jet) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    jet.active = 0x41;
    jet.bg_offset = row == 6 ? -1 : 0;
    jet.unk50 = &rider;
    jet.animation_table = (u32**)D_800F8FC4;
    rider.state = row == 1 ? 2 : 1;
    rider.x_pos.i.hi = x[row];
    rider.y_pos.i.hi = y[row];
    rider.animation_step.fields.frame_index = row == 3 ? 5 : 1;
    ride_chaser_jet_update(&jet);
    assert(jet.state == 1 && jet.unk54 == 0xFF && jet.unk16 == 6);
    jet.unk56 = row == 3 ? 5 : 9;
    jet.unk54 = row == 4 ? 0x16 : 0xFF;
    ride_chaser_jet_update(&jet);
    if (row == 1) {
        assert(jet.state == 2);
        ride_chaser_jet_update(&jet);
        assert(jet.active == 0);
        return 1;
    }
    assert(jet.unk56 == (row == 3 ? 5 : row == 4 ? 9
                                                 : 1)
        && jet.x_pos.i.hi == x[row]);
    assert(jet.on_screen == (row < 5));
    return jet.animation_step.packed;
}

const struct CTestGroup c_test_groups[] = {
    { "follow_rider_frames", NULL, NULL, 7, jet_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 7;
