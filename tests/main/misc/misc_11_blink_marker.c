#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_11_blink_marker.h"

#define bm state_room.misc
#define BLINK(st, kind) (state_reset(0, 0, 0), bm.active = 1, bm.state = st, bm.unk2 = kind, bm.x_pos.i.hi = 0x80, bm.y_pos.i.hi = 0x60)
#define BX() (state_extra = bm.unk17 | (u32)bm.on_screen << 8 | (u32)(u8)bm.ext.misc_11.active << 16)
static void blink_init_plain(void) { BLINK(0, 0), bm.ext.misc_11.active = 1, blink_marker_update(&bm), BX(); }
static void blink_init_1(void) { BLINK(0, 1), blink_marker_update(&bm), BX(); }
static void blink_init_2(void) { BLINK(0, 2), blink_marker_update(&bm), BX(); }
static void blink_init_3(void) { BLINK(0, 3), blink_marker_update(&bm), BX(); }
static void blink_shows(void) { BLINK(1, 0), bm.ext.misc_11.active = 1, blink_marker_update(&bm), BX(); }
static void blink_hides(void) { BLINK(1, 0), bm.on_screen = 1, blink_marker_update(&bm), BX(); }
static void blink_animates(void) { BLINK(1, 2), blink_marker_update(&bm), BX(); }
static void blink_despawn(void) { BLINK(2, 0), bm.ext.misc_11.active = 1, blink_marker_update(&bm), BX(); }
static void (*const blink_cases[])(void) = {
    blink_init_plain,
    blink_init_1,
    blink_init_2,
    blink_init_3,
    blink_shows,
    blink_hides,
    blink_animates,
    blink_despawn,
};
static const u32 blink_expected[] = {
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0xFF000101u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2u, 0x0u,
    0x1u, 0xFF000201u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x3u, 0x0u,
    0x1u, 0x301u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x100u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x10100u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0x201u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_blink(u32 row)
{
    return object_run(blink_cases[row], row, &blink_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "blink_marker_states", 0, 0, COUNT(blink_cases), test_blink },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(blink_cases);
