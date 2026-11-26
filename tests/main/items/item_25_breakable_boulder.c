#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/tile_writes.h"
#include "main/items/item_25_breakable_boulder.h"

#define bb state_room.item
static u32 bb_archive[16], bb_meta[64];
#define BB(st, setup)                                                                                                    \
    (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 2, memset(weapon_objects, 0, \
        sizeof(weapon_objects)), g_Player.unk68 = NULL, TEST_MENU_FRAMES = (u8*)bb_archive, D_801406A8 = bb_meta, bb.active = 0x41, bb.id = 0x19, \
        bb.state = st, bb.x_pos.i.hi = 0x450, bb.y_pos.i.hi = 0x1B0, tile_writes_begin(), setup, breakable_boulder_update(&bb), \
        state_extra = tile_writes_end() ^ (u8)bb.unk15, engine_obj.stage = 0)
static void bb_init(void) { BB(0, 0), bb.unk42 = 0, bb.sprite_frames = NULL; }
static void bb_shatter(void) { BB(1, (state_hit((struct MainObj*)&bb, 0, 0, 1), tile_writes_expect(0x26, 0x430, 0x170, 1))); }
static void bb_on_screen(void) { BB(1, (background_objects[0].x_pos.i.hi = 0x3A0, background_objects[0].y_pos.i.hi = 0x140)); }
static void bb_off_screen(void) { BB(1, 0); }

static void (*const breakable_boulder_states_cases[])(void) = {
    bb_init,
    bb_shatter,
    bb_on_screen,
    bb_off_screen,
};
static const u32 breakable_boulder_states_expected[] = {
    0x1u, 0x41u, 0x4500000u, 0x1B00000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x4500000u, 0x1B00000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0x110C2F18u, 0x41002100u,
    0x1u, 0x41u, 0x4500000u, 0x1B00000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x4500000u, 0x1B00000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};

static u32 test_breakable_boulder_states(u32 row)
{
    return object_run(breakable_boulder_states_cases[row], row, &breakable_boulder_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "breakable_boulder_states", 0, 0, COUNT(breakable_boulder_states_cases), test_breakable_boulder_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(breakable_boulder_states_cases);
