#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/weapons/weapon_60_ride_armor_missile.h"

#define sw state_room.weapon
#define MISSILE(kind, facing) (state_reset(0, 0, 0), sw.active = 1, sw.unk2 = kind, sw.unk15 = facing, sw.x_pos.i.hi = 0x80, sw.y_pos.i.hi = 0x60, func_80098F88(&sw), state_extra = sw.ext.weapon_60.direction)
static void rm_forward_left(void) { MISSILE(0, 0); }
static void rm_forward_right(void) { MISSILE(0, 0x40); }
static void rm_down_left(void) { MISSILE(1, 0); }
static void rm_down_right(void) { MISSILE(1, 0x40); }
static void rm_up_left(void) { MISSILE(2, 0); }
static void rm_up_right(void) { MISSILE(2, 0x40); }

static void (*const ride_armor_missile_init_cases[])(void) = {
    rm_forward_left,
    rm_forward_right,
    rm_down_left,
    rm_down_right,
    rm_up_left,
    rm_up_right,
};
static const u32 ride_armor_missile_init_expected[] = { 1u, 0xFF000001u, 0x580000u, 0x600000u, 0xFFFA0000u, 0u, 0u, 0x50000u, 0x10u, 0u, 1u, 0xFF400001u, 0xA80000u, 0x600000u, 0x60000u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000101u, 0x580000u, 0x600000u, 0xFFFBC1E2u, 0xFFFBC1E2u, 0u, 0x50000u, 0x14u, 0u, 1u, 0xFF400101u, 0xA80000u, 0x600000u, 0x43E1Eu, 0xFFFBC1E2u, 0u, 0x50000u, 0x1Cu, 0u, 1u, 0xFF000201u, 0x580000u, 0x600000u, 0xFFFBC1E2u, 0x43E1Eu, 0u, 0x50000u, 0xCu, 0u, 1u, 0xFF400201u, 0xA80000u, 0x600000u, 0x43E1Eu, 0x43E1Eu, 0u, 0x50000u, 4u, 0u };

static u32 test_ride_armor_missile_init(u32 row)
{
    return object_run(ride_armor_missile_init_cases[row], row, &ride_armor_missile_init_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "ride_armor_missile_init", 0, 0, COUNT(ride_armor_missile_init_cases), test_ride_armor_missile_init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ride_armor_missile_init_cases);
