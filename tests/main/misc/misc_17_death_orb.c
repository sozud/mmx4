#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_17_death_orb.h"

static u32 orb_frames[4];
#define om state_room.misc
#define ORB(st, kind, setup) (state_reset(0, 0, 0), TEST_SPRITE_FRAMES = (u8*)orb_frames, g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, om.active = 1, om.state = st, om.unk2 = kind, om.x_pos.i.hi = 0x80, om.y_pos.i.hi = 0x60, om.x_vel.val = 0x10000, setup, death_orb_update(&om), state_extra = om.unk17)
static void orb_init_fast(void) { ORB(0, 0x88, 0); }
static void orb_init_slow(void) { ORB(0, 0x09, 0); }
static void orb_fast_gone(void) { ORB(1, 0x88, om.x_pos.i.hi = 0x7000); }
static void orb_fast_flies(void) { ORB(1, 0x88, 0); }
static void orb_slow_flies(void) { ORB(1, 0x09, 0); }
static void (*const orb_cases[])(void) = {
    orb_init_fast,
    orb_init_slow,
    orb_fast_gone,
    orb_fast_flies,
    orb_slow_flies,
};
static const u32 orb_expected[] = {
    0x1u, 0xFF008801u, 0x800000u, 0x580000u, 0x0u, 0x80000u, 0x0u, 0x30000u | OBJECT_CLUT(0x7802), 0x7u, 0x0u,
    0x1u, 0xFF000901u, 0x7F8327u, 0x5D8C4Eu, 0xFFFF8327u, 0x273B2u, 0x0u, 0x20000u | OBJECT_CLUT(0x7802), 0x6u, 0x0u,
    0x0u, 0x0u, 0x70000000u, 0x600000u, 0x10000u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0x8801u, 0x810000u, 0x600000u, 0x10000u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x1u, 0x901u, 0x810000u, 0x600000u, 0x10000u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
};
static u32 test_orb(u32 row)
{
    return object_run(orb_cases[row], row, &orb_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "death_orb_states", 0, 0, COUNT(orb_cases), test_orb },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(orb_cases);
