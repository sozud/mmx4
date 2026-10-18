#include "test_runtime.h"

extern union AnimationStep* D_800F8FC4[38];
void ride_chaser_flash_update(struct VisualObj*);

static struct PlayerObj rider;
static struct VisualObj flash;

static u32 flash_case(u32 row)
{
    c_test_zero_words((u32*)&rider, sizeof(rider) / 4);
    c_test_zero_words((u32*)&flash, sizeof(flash) / 4);
    flash.active = 0x41;
    flash.bg_offset = -1;
    flash.unk50 = &rider;
    flash.animation_table = (u32**)D_800F8FC4;
    rider.state = row == 1 ? 2 : 1;
    rider.x_pos.i.hi = 100;
    rider.y_pos.i.hi = 80;
    ride_chaser_flash_update(&flash);
    assert(flash.state == 1 && flash.unk54 == 3 && flash.unk16 == 2);
    flash.unk54 = row == 2 ? 1 : 3;
    flash.animation_step.fields.relative_step = row >= 2 ? -1 : 1;
    ride_chaser_flash_update(&flash);
    assert(flash.x_pos.i.hi == 100 && flash.unk54 == (row == 2 ? 0 : row == 3 ? 2
                                                                              : 3));
    assert(flash.state == (row == 1 || row == 2 ? 2 : 1));
    if (flash.state == 2) {
        ride_chaser_flash_update(&flash);
        assert(flash.active == 0);
    }
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "follow_rider_until_done", NULL, NULL, 4, flash_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4;
