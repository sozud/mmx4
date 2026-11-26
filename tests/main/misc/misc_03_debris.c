#include "test_runtime.h"
#include "main/misc/misc_03_debris.h"
#include "support/state_cases.h"

static struct MainObj debris_owner;
static u8 debris_frames[4];
#define sm state_room.misc
#define DEBRIS(st, kind, setup) (state_reset(0, 0, 0), memset(&debris_owner, 0, sizeof(debris_owner)), debris_owner.sprite_frames = debris_frames, debris_owner.animation_table = (void*)state_table, debris_owner.unk40 = 0x1234, debris_owner.unk42 = (s16)0x8567, debris_owner.x_speed = 0x20000, sm.active = 0x41, sm.state = st, sm.unk2 = kind, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.y_vel.val = 0x10000, sm.unk2C = 0x5000, sm.ext.misc_2.owner = &debris_owner, sm.ext.misc_2.unk58 = 3, cur_random = 0x1234, setup, debris_update(&sm), state_extra = (u16)sm.unk42 | (u32)sm.unk17 << 16 | (u32)(u8)sm.on_screen << 24)
static void db_start_owned(void)
{
    DEBRIS(0, 0, 0);
    assert(sm.unk3C == debris_frames && sm.animation_table == (void*)state_table && sm.unk40 == 0x1234);
}
static void db_start_stage(void) { DEBRIS(0, 1, sm.unk42 = 0x55); }
static void db_fall_shown(void) { DEBRIS(1, 0, sm.on_screen = 0); }
static void db_fall_hidden(void) { DEBRIS(1, 0, sm.on_screen = 1); }
static void db_fall_gone(void) { DEBRIS(1, 0, sm.x_pos.i.hi = 0x1000); }
static void (*const debris_steps_cases[])(void) = {
    db_start_owned,
    db_start_stage,
    db_fall_shown,
    db_fall_hidden,
    db_fall_gone,
};
static const u32 debris_steps_expected[] = {
    0x1u,
    0xFF000041u,
    0x800000u,
    0x600000u,
    0x28000u,
    0x50000u,
    0x500000u,
    0x50567u,
    0x1030567u,
    0u,
    0x1u,
    0xFF000141u,
    0x800000u,
    0x600000u,
    0x28000u,
    0x50000u,
    0x500000u,
    0x50055u,
    0x1030055u,
    0u,
    0x1u,
    0x41u,
    0x800000u,
    0x5F0000u,
    0u,
    0xB000u,
    0x500000u,
    0x40000u,
    0x1000000u,
    0u,
    0x1u,
    0x41u,
    0x800000u,
    0x5F0000u,
    0u,
    0xB000u,
    0x500000u,
    0x40000u,
    0u,
    0u,
    0u,
    0u,
    0x10000000u,
    0x600000u,
    0u,
    0x10000u,
    0x500000u,
    0x50000u,
    0u,
    0u,
};
static u32 test_debris_steps(u32 row)
{
    return object_run(debris_steps_cases[row], row, &debris_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "debris_steps", 0, 0, COUNT(debris_steps_cases), test_debris_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(debris_steps_cases);
