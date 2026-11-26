#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/weapons/weapon_60_ride_armor_missile.h"

#define sw state_room.weapon
#define MISSILE(kind, facing) (state_reset(0, 0, 0), sw.active = 1, sw.unk2 = kind, sw.unk15 = facing, sw.x_pos.i.hi = 0x80, sw.y_pos.i.hi = 0x60, func_80098F88(&sw), state_extra = sw.ext.weapon_60.direction)
static void rm_forward_left(void) { MISSILE(0, 0); }
static void rm_down_left(void) { MISSILE(1, 0); }
static void rm_down_right(void) { MISSILE(1, 0x40); }
static void rm_up_left(void) { MISSILE(2, 0); }
static void rm_up_right(void) { MISSILE(2, 0x40); }

static void (*const ride_armor_missile_init_cases[])(void) = {
    rm_forward_left,
    rm_down_left,
    rm_down_right,
    rm_up_left,
    rm_up_right,
};
static const u32 ride_armor_missile_init_expected[] = { 1u, 0xFF000001u, 0x580000u, 0x600000u, 0xFFFA0000u, 0u, 0u, 0x50000u, 0x10u, 0u, 1u, 0xFF000101u, 0x580000u, 0x600000u, 0xFFFBC1E2u, 0xFFFBC1E2u, 0u, 0x50000u, 0x14u, 0u, 1u, 0xFF400101u, 0xA80000u, 0x600000u, 0x43E1Eu, 0xFFFBC1E2u, 0u, 0x50000u, 0x1Cu, 0u, 1u, 0xFF000201u, 0x580000u, 0x600000u, 0xFFFBC1E2u, 0x43E1Eu, 0u, 0x50000u, 0xCu, 0u, 1u, 0xFF400201u, 0xA80000u, 0x600000u, 0x43E1Eu, 0x43E1Eu, 0u, 0x50000u, 4u, 0u };

static u32 test_ride_armor_missile_init(u32 row)
{
    return object_run(ride_armor_missile_init_cases[row], row, &ride_armor_missile_init_expected[row * 10]);
}

void func_80099118(struct WeaponObj*);
static struct MainObj missile_saved_mains[2];
static struct PlayerObj missile_armor;
#define FLY(target_x, target_y, setup) (memcpy(missile_saved_mains, main_objects, sizeof(missile_saved_mains)), memset(main_objects, 0, sizeof(missile_saved_mains)), main_objects[0].active = (target_x) != 0, main_objects[0].on_screen = 1, main_objects[0].x_pos.i.hi = target_x, main_objects[0].y_pos.i.hi = target_y, state_reset(0, 0, 0), sw.active = 1, sw.state = 1, sw.x_pos.i.hi = 0x80, sw.y_pos.i.hi = 0x60, sw.ext.weapon_60.direction = 0x10, sw.unk8A = 1, WEAPON_FRAME_COUNTER = 2, setup, func_80099118(&sw), state_extra = sw.ext.weapon_60.direction | (u32)(sw.ext.target != NULL) << 7 | (u32)(u16)sw.unk88.half << 8 | (u32)(u16)sw.unk84.word << 16 | (u32)sw.unk8A << 28, sw.ext.target = NULL, memcpy(main_objects, missile_saved_mains, sizeof(missile_saved_mains)))
static void rm_homes_up(void)
{
    FLY(0x40, 0x20, 0);
}
static void rm_homes_down(void) { FLY(0x40, 0xA0, 0); }
static void rm_on_target(void) { FLY(0x40, 0x60, 0); }
static void rm_tired(void) { FLY(0, 0, sw.unk84.word = 0x1DF); }
static void rm_launch_delay(void) { FLY(0x40, 0x20, sw.unk88.half = 3); }
static void rm_odd_frame(void) { FLY(0x40, 0x20, WEAPON_FRAME_COUNTER = 3); }
static void rm_trail(void) { FLY(0, 0, sw.unk8A = 0); }
static void rm_hit(void) { FLY(0, 0, sw.unk98 = 1); }
static void rm_off_screen(void) { FLY(0, 0, sw.x_pos.i.hi = 0x200); }
static void rm_despawn(void) { state_reset(0, 0, 0), memset(&missile_armor, 0, sizeof(missile_armor)), missile_armor.input.bytes.previous_high = 3, sw.active = 1, sw.state = 2, sw.unk2 = 1, sw.owner = &missile_armor, ride_armor_missile_update(&sw), state_extra = (u8)missile_armor.input.bytes.previous_high; }
static void (*const rm_fly_cases[])(void) = {
    rm_homes_up,
    rm_homes_down,
    rm_on_target,
    rm_tired,
    rm_launch_delay,
    rm_odd_frame,
    rm_trail,
    rm_hit,
    rm_off_screen,
    rm_despawn,
};
static const u32 rm_fly_expected[] = {
    0x1u,
    0x1u,
    0x7A74EEu,
    0x5DB436u,
    0xFFFA74EEu,
    0x24BCAu,
    0x0u,
    0x40000u,
    0x1008Eu,
    0x0u,
    0x1u,
    0x1u,
    0x7A74EEu,
    0x624BCAu,
    0xFFFA74EEu,
    0xFFFDB436u,
    0x0u,
    0x40000u,
    0x10092u,
    0x0u,
    0x1u,
    0x1u,
    0x7A0000u,
    0x600000u,
    0xFFFA0000u,
    0x0u,
    0x0u,
    0x40000u,
    0x10090u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x1E03C10u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x210u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10010010u,
    0x100u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10010u,
    0x0u,
    0x2u,
    0x1u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10010u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
};
static u32 test_rm_fly(u32 row)
{
    return object_run(rm_fly_cases[row], row, &rm_fly_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "ride_armor_missile_init", 0, 0, COUNT(ride_armor_missile_init_cases), test_ride_armor_missile_init },
    { "ride_armor_missile_fly", 0, 0, COUNT(rm_fly_cases), test_rm_fly },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ride_armor_missile_init_cases) + COUNT(rm_fly_cases);
