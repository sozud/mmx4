#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_40_ambient_bubble.h"

static u32 bubble_frames[0x40], bubble_pages[0x40];
#define ab state_room.misc
#define BUBBLE(st, step, setup) (state_reset(step, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), TEST_MENU_FRAMES = (u8*)bubble_frames, D_801406A8 = bubble_pages, cur_random = 0x1234, ab.active = 1, ab.state = st, ab.unk2 = 1, ab.bg_offset = -1, ab.x_pos.i.hi = 0x80, ab.y_pos.i.hi = 0x60, ab.ext.misc_24.timer = 3, setup, ambient_bubble_update(&ab), state_extra = ab.unk17 | (u32)(u16)ab.ext.misc_24.timer << 16)
static void bubble_init(void)
{
    BUBBLE(0, 0, 0);
}
static void bubble_waits(void) { BUBBLE(1, 0, 0); }
static void bubble_spawns(void) { BUBBLE(1, 0, ab.ext.misc_24.timer = 0); }
static void bubble_tops_out(void) { BUBBLE(1, 1, ab.y_vel.val = -0x40000); }
static void bubble_rises_off_screen(void) { BUBBLE(1, 1, (ab.y_vel.val = 0x7FFFFFF, ab.x_pos.i.hi = 0x400)); }
static void bubble_despawn(void) { BUBBLE(2, 0, 0); }
static void (*const bubble_cases[])(void) = {
    bubble_init,
    bubble_waits,
    bubble_spawns,
    bubble_tops_out,
    bubble_rises_off_screen,
    bubble_despawn,
};
static const u32 bubble_expected[] = {
    0x1u,
    0x400141u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u | VISUAL_STAGE_PALETTE(14),
    0x12C0000u,
    0x0u,
    0x1u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20000u,
    0x0u,
    0x101u,
    0xFF000101u,
    0x14A0000u,
    0xB00000u,
    0xFFFD8000u,
    0x0u,
    0x100000u,
    0x50000u,
    0x1u,
    0x0u,
    0x101u,
    0xFF000101u,
    0x800000u,
    0x640000u,
    0x0u,
    0xFFFC1000u,
    0xFFF00000u,
    0x40000u,
    0x30002u,
    0x0u,
    0x1u,
    0x101u,
    0x4000000u,
    0xF8600001u,
    0x0u,
    0x7FFFFFFu,
    0x0u,
    0x40000u,
    0x1560000u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x30000u,
    0x0u,
};
static u32 test_bubble(u32 row)
{
    return object_run(bubble_cases[row], row, &bubble_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "ambient_bubble_states", 0, 0, COUNT(bubble_cases), test_bubble },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bubble_cases);
