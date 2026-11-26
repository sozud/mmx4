#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_06_homing_point.h"

#define hm state_room.misc
#define HOME(st, px, py, setup) (state_reset(0, 0, 0), hm.active = 1, hm.state = st, hm.unk2 = 3, hm.x_pos.i.hi = px, hm.y_pos.i.hi = py, hm.ext.misc_6.saved_position.position.x = 0x80, hm.ext.misc_6.saved_position.position.y = 0x60, hm.ext.misc_6.timer = 5, setup, homing_point_update(&hm), state_extra = hm.ext.misc_6.timer | (u32)(u16)hm.ext.misc_6.saved_position.position.x << 16)
static void home_init(void) { HOME(0, 0x80, 0x60, 0); }
static void home_waits(void) { HOME(1, 0x80, 0x60, 0); }
static void home_wait_ends(void) { HOME(1, 0x80, 0x60, hm.ext.misc_6.timer = 1); }
static void home_left(void) { HOME(2, 0x60, 0x60, 0); }
static void home_right(void) { HOME(2, 0xA0, 0x60, 0); }
static void home_above(void) { HOME(2, 0x80, 0x40, 0); }
static void home_below(void) { HOME(2, 0x80, 0x80, 0); }
static void home_arrives(void) { HOME(2, 0x88, 0x58, 0); }
static void home_despawn(void) { HOME(3, 0x80, 0x60, 0); }
static void (*const home_cases[])(void) = {
    home_init,
    home_waits,
    home_wait_ends,
    home_left,
    home_right,
    home_above,
    home_below,
    home_arrives,
    home_despawn,
};
static const u32 home_expected[] = {
    0x1u, 0xFF000301u, 0xB87Cu, 0xFFE0B87Cu, 0x2D414u, 0xFFFD2BECu, 0x0u, 0x50000u, 0x800014u, 0x0u,
    0x1u, 0x301u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x800004u, 0x0u,
    0x2u, 0x301u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x800000u, 0x0u,
    0x2u, 0x301u, 0x600000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x800005u, 0x0u,
    0x2u, 0x301u, 0xA00000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x800005u, 0x0u,
    0x2u, 0x301u, 0x800000u, 0x400000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x800005u, 0x0u,
    0x2u, 0x301u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x800005u, 0x0u,
    0x3u, 0x301u, 0x880000u, 0x580000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x800005u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_home(u32 row)
{
    return object_run(home_cases[row], row, &home_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "homing_point_states", 0, 0, COUNT(home_cases), test_home },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(home_cases);
