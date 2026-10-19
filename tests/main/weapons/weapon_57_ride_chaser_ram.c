#include "test_runtime.h"

extern union AnimationStep* D_800F8FC4[38];
extern u8 ride_chaser_ram_hit_box[4];
void ride_chaser_ram_update(struct WeaponObj*);

static struct PlayerObj rider;
static struct WeaponObj ram;

static u32 ram_case(u32 row)
{
    c_test_zero_words((u32*)&rider, sizeof(rider) / 4);
    c_test_zero_words((u32*)&ram, sizeof(ram) / 4);
    ram.active = 0x41;
    ram.bg_offset = -1;
    ram.owner = &rider;
    ram.animation_table = (u32**)D_800F8FC4;
    rider.state = row == 0 ? 2 : 1;
    rider.unk5 = row == 1 ? 3 : row == 2 ? 0
                                         : 5;
    rider.animation_step.fields.frame_index = row == 2 ? 1 : 3;
    rider.x_pos.i.hi = 100;
    rider.y_pos.i.hi = 80;
    ride_chaser_ram_update(&ram);
    assert(ram.state == 1 && ram.unk50 == ride_chaser_ram_hit_box && ram.unk60 == 3);
    ride_chaser_ram_update(&ram);
    if (row < 2) {
        assert(ram.state == 2 && ram.on_screen == 0);
        ride_chaser_ram_update(&ram);
        assert(ram.active == 0);
        return 1;
    }
    assert(ram.state == 1 && ram.x_pos.i.hi == (row == 2 ? 0 : 100) && ram.on_screen == (row == 3));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "follow_charging_rider", NULL, NULL, 4, ram_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4;
