#include "test_runtime.h"
#include "main/quads/quad_16_sigma_laser.h"

static struct QuadObj laser;
static struct MainObj laser_owner;

static void laser_reset(u8 state, u8 step, u16 timer)
{
    memset(&laser, 0, sizeof(laser));
    memset(&laser_owner, 0, sizeof(laser_owner));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(background_objects, 0, sizeof(background_objects));
    laser.active = 1;
    laser.state = state;
    laser.unk5 = step;
    laser.ext.unk38 = timer;
    laser.unk5C = (struct PlayerObj*)&laser_owner;
}

static u32 laser_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[8];
    run();
    seen[0] = (u8)laser.active | (u8)laser.state << 8 | (u8)laser.unk5 << 16 | (u32)(u8)laser.unk2 << 24;
    seen[1] = laser.unk34 | (u32)(u16)laser.ext.unk38 << 16;
    seen[2] = laser.vertices[0].x.val ^ laser.vertices[1].y.val;
    seen[3] = laser.vertices[2].x.val;
    seen[4] = laser.vertices[2].y.val;
    seen[5] = laser.vertices[3].x.val ^ laser.vertices[3].y.val;
    seen[6] = laser_owner.ext.main_74.pad95;
    seen[7] = visual_objects[0].active | (u32)visual_objects[1].active << 8;
    return c_test_observe(0, row, seen, expected, 8);
}

static void l_init_beam(void)
{
    laser_reset(0, 0, 0);
    laser.unk2 = 1;
    sigma_laser_update(&laser);
}
static void l_init_cancel(void)
{
    laser_reset(0, 0, 0);
    laser.unk2 = 0x11;
    sigma_laser_update(&laser);
}
static void l_owner_dead(void)
{
    laser_reset(1, 1, 3);
    laser_owner.ext.main_74.death_kind = 1;
    laser.active = 1;
    sigma_laser_update(&laser);
}
static void l_wait(void)
{
    laser_reset(1, 0, 1);
    sigma_laser_update(&laser);
}
static void l_wait_count(void)
{
    laser_reset(1, 0, 2);
    sigma_laser_update(&laser);
}
static void l_extend(void)
{
    laser_reset(1, 1, 3);
    laser.unk2 = 1;
    sigma_laser_update(&laser);
}
static void l_extend_done(void)
{
    laser_reset(1, 1, 1);
    laser.unk2 = 2;
    sigma_laser_update(&laser);
}
static void l_flash(void)
{
    laser_reset(1, 2, 3);
    sigma_laser_update(&laser);
}
static void l_flash_done(void)
{
    laser_reset(1, 2, 1);
    laser_owner.ext.main_74.pad95 = 1;
    sigma_laser_update(&laser);
}
static void l_retract(void)
{
    laser_reset(1, 3, 5);
    laser.unk2 = 3;
    sigma_laser_update(&laser);
}
static void l_retract_done(void)
{
    laser_reset(1, 3, 1);
    laser.unk2 = 1;
    sigma_laser_update(&laser);
}
static void l_cancel_wait(void)
{
    laser_reset(3, 0, 1);
    sigma_laser_update(&laser);
}
static void l_cancel_wait_count(void)
{
    laser_reset(3, 0, 2);
    sigma_laser_update(&laser);
}
static void l_cancel_side(void)
{
    laser_reset(3, 1, 6);
    laser.unk2 = 1;
    sigma_laser_update(&laser);
}
static void l_cancel_down(void)
{
    laser_reset(3, 1, 12);
    sigma_laser_update(&laser);
}
static void l_cancel_done(void)
{
    laser_reset(3, 1, 1);
    sigma_laser_update(&laser);
}
static void l_despawn(void)
{
    laser_reset(2, 0, 0);
    sigma_laser_update(&laser);
}

static void (*const laser_cases[])(void) = {
    l_init_beam,
    l_init_cancel,
    l_owner_dead,
    l_wait,
    l_wait_count,
    l_extend,
    l_extend_done,
    l_flash,
    l_flash_done,
    l_retract,
    l_retract_done,
    l_cancel_wait,
    l_cancel_wait_count,
    l_cancel_side,
    l_cancel_down,
    l_cancel_done,
    l_despawn,
};
static const u32 laser_expected[] = { 0x1000193u, 0x140012u, 0x6870000u, 0x4100000u, 0x2D00000u, 0x6C10000u, 0u, 0u, 0x1000393u, 0xF0013u, 0x6A50000u, 0x2C00000u, 0x2F00000u, 0x340000u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10101u, 0x80000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x101u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1010101u, 0x20000u, 0u, 0x4100000u, 0x2B74000u, 0x6E44000u, 0u, 0u, 0x2020101u, 0x2F0000u, 0u, 0x4100000u, 0x2730000u, 0x6D30000u, 1u, 0u, 0x20101u, 0x20014u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30101u, 0x100012u, 0u, 0u, 0u, 0u, 0u, 0u, 0x3030101u, 0x40000u, 0u, 0x4100000u, 0x226C000u, 0x62D8000u, 0u, 0u, 0x1000201u, 0u, 0u, 0x4100000u, 0x2D00000u, 0x6C10000u, 0u, 0u, 0x10301u, 0x100000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x301u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1010301u, 0x50000u, 0u, 0x380000u, 0u, 0x380000u, 1u, 0x21u, 0x10301u, 0xB0000u, 0u, 0u, 0xFFEC0000u, 0xFFEC0000u, 1u, 0x21u, 0x20201u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_sigma_laser_states(u32 row)
{
    return laser_run(laser_cases[row], row, &laser_expected[row * 8]);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_laser_states", 0, 0, COUNT(laser_cases), test_sigma_laser_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(laser_cases);
