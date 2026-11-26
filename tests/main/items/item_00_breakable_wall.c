#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/tile_writes.h"
#include "main/items/item_00_breakable_wall.h"

void breakable_wall_main(struct ItemObj*);
#define bw state_room.item
#define BW(sub, x, y, life)                                                   \
    (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)),       \
        engine_obj.stage = 4, engine_obj.substage = 1, g_Player.unk68 = NULL, \
        bw.active = 1, bw.id = 0, bw.state = 1, bw.unk2 = sub,             \
        bw.x_pos.i.hi = x, bw.y_pos.i.hi = y,                              \
        ((struct MainObj*)&bw)->hp = life, state_hit((struct MainObj*)&bw, 0, 0, 1), tile_writes_begin())
#define BWX() (state_extra = tile_writes_end() ^ (u8)((struct MainObj*)&bw)->hp << 24, engine_obj.stage = engine_obj.substage = 0)
static void bw_hit(void) { BW(0, 0x1320, 0x288, 4), breakable_wall_main(&bw), BWX(); }
static void bw_break_first(void) { BW(0, 0x1320, 0x288, 1), tile_writes_expect(2, 0x1300, 0x270, 1), breakable_wall_main(&bw), BWX(); }
static void bw_break_other(void) { BW(1, 0xC20, 0x1A8, 1), tile_writes_expect(7, 0xC00, 0x190, 1), breakable_wall_main(&bw), BWX(); }

static void (*const breakable_wall_states_cases[])(void) = {
    bw_hit,
    bw_break_first,
    bw_break_other,
};
static const u32 breakable_wall_states_expected[] = {
    0x1u, 0x1u, 0x13200000u, 0x2880000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0x3000000u, 0x2100u,
    0x2u, 0x1u, 0x13200000u, 0x2880000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0x98086E6u, 0x41002100u,
    0x2u, 0x101u, 0xC200000u, 0x1A80000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0xE9E9800Cu, 0x41002100u,
};

static u32 test_breakable_wall_states(u32 row)
{
    return object_run(breakable_wall_states_cases[row], row, &breakable_wall_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "breakable_wall_states", 0, 0, COUNT(breakable_wall_states_cases), test_breakable_wall_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(breakable_wall_states_cases);
