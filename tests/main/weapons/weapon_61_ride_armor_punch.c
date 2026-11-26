#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/weapons/weapon_61_ride_armor_punch.h"

static struct PlayerObj punch_armor;
#define pw state_room.weapon
#define PUNCH(st, kind, setup) (state_reset(0, 0, 0), memset(&punch_armor, 0, sizeof(punch_armor)), punch_armor.state = 1, punch_armor.unk17 = 8, punch_armor.unk5 = 3, punch_armor.x_pos.i.hi = 0x90, punch_armor.y_pos.i.hi = 0x70, pw.active = 1, pw.state = st, pw.unk2 = kind, pw.owner = &punch_armor, pw.unk88.half = 6, setup, ride_armor_punch_update(&pw), state_extra = (pw.unk50 != NULL) | (u32)(u8)pw.unk64 << 8 | (u32)(u16)pw.unk88.half << 16, pw.owner = NULL)
static void punch_init_idle_frame(void) { PUNCH(0, 0, 0); }
static void punch_hits(void) { PUNCH(1, 0, punch_armor.animation_step.fields.event = 0x20); }
static void punch_dash_counts(void) { PUNCH(1, 1, (punch_armor.unk17 = 9, punch_armor.unk5 = 9)); }
static void punch_dash_next_hit(void) { PUNCH(1, 1, (punch_armor.unk17 = 9, punch_armor.unk5 = 9, pw.unk88.half = 1)); }
static void punch_other_animation(void) { PUNCH(1, 0, punch_armor.unk17 = 9); }
static void punch_other_step(void) { PUNCH(1, 0, punch_armor.unk5 = 4); }
static void punch_armor_left_state(void) { PUNCH(1, 0, punch_armor.state = 2); }
static void punch_despawn(void) { PUNCH(2, 0, 0); }
static void (*const punch_cases[])(void) = {
    punch_init_idle_frame,
    punch_hits,
    punch_dash_counts,
    punch_dash_next_hit,
    punch_other_animation,
    punch_other_step,
    punch_armor_left_state,
    punch_despawn,
};
static const u32 punch_expected[] = {
    0x1u, 0x1u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x60100u, 0x0u,
    0x1u, 0x1u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x60001u, 0x0u,
    0x1u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x50000u, 0x0u,
    0x1u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x60100u, 0x0u,
    0x0u, 0x0u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x60000u, 0x0u,
    0x0u, 0x0u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x60000u, 0x0u,
    0x0u, 0x0u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x60000u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x60000u, 0x0u,
};
static u32 test_punch(u32 row)
{
    return object_run(punch_cases[row], row, &punch_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "ride_armor_punch_states", 0, 0, COUNT(punch_cases), test_punch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(punch_cases);
