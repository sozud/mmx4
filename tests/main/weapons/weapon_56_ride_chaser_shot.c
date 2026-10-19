#include "test_runtime.h"
#include "main/weapons/weapon_56_ride_chaser_shot.h"

extern union AnimationStep* D_800F8FC4[38];
void ride_chaser_shot_update(struct WeaponObj*);

static struct PlayerObj rider;
static struct WeaponObj shot;

static void launch(u32 kind, u32 facing)
{
    c_test_zero_words((u32*)&rider, sizeof(rider) / 4);
    c_test_zero_words((u32*)&shot, sizeof(shot) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    shot.active = 0x41;
    shot.unk2 = kind;
    shot.unk15 = facing;
    shot.owner = &rider;
    shot.animation_table = (u32**)D_800F8FC4;
    shot.x_pos.i.hi = 160;
    shot.y_pos.i.hi = 120;
    rider.shot_count = 2;
    ride_chaser_shot_update(&shot);
    assert(shot.state == 1 && shot.unk60 == 3 && shot.unk5C == 1);
}

static u32 init(u32 row)
{
    launch(row % 5, row >= 5 ? 0x40 : 0);
    return (u16)shot.x_pos.i.hi | (u32)(u16)shot.y_pos.i.hi << 16 ^ shot.x_vel.val ^ shot.y_vel.val;
}

static u32 fly(u32 row)
{
    launch(2, 0);
    background_objects[0].unk4 = row == 0;
    background_objects[0].x_pos.i.hi = 6;
    shot.unk98 = row == 2;
    if (row == 3)
        shot.x_pos.i.hi = 500;
    if (row == 4)
        shot.y_pos.i.hi = 400;
    ride_chaser_shot_update(&shot);
    if (row >= 2) {
        assert(shot.state == 2 && shot.on_screen == 0);
        ride_chaser_shot_update(&shot);
        assert(shot.active == 0 && rider.shot_count == 1);
        return 1;
    }
    assert(shot.state == 1 && shot.on_screen == 1);
    return shot.x_pos.i.hi;
}

const struct CTestGroup c_test_groups[] = {
    { "launch_kinds", NULL, NULL, 10, init },
    { "flight", NULL, NULL, 5, fly },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 10 + 5;
