#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/tile_writes.h"
#include "main/items/item_18_drop_pillar.h"

#define dp state_room.item
#define DP(sub, st, y)                                                                                        \
    (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 8,                    \
        engine_obj.substage = 1, g_Player.unk68 = NULL, dp.active = 0x41, dp.id = 0x12, dp.unk2 = sub, dp.state = st, \
        dp.x_pos.i.hi = 0x24B0, dp.y_pos.i.hi = y, dp.y_vel.val = -0x40000, dp.unk2C = 0x2000, tile_writes_begin_wide())
#define DPX() (state_extra = tile_writes_end(), engine_obj.stage = engine_obj.substage = 0)
static void dp_fall(void) { DP(0, 1, 0x100), drop_pillar_update(&dp), DPX(); }
static void dp_fall_land(void)
{
    DP(0, 1, 0x186);
    drop_pillar_update(&dp);
    assert(dp.state == 2);
    tile_writes_expect(0xC, 0x24A0, dp.y_pos.i.hi - 0x30, 1);
    drop_pillar_update(&dp);
    DPX();
}
static void dp_land_tall(void) { DP(2, 2, 0x10C), tile_writes_expect(0xD, 0x24A0, 0x10C - 0x70, 1), drop_pillar_update(&dp), DPX(); }

static void (*const drop_pillar_states_cases[])(void) = {
    dp_fall,
    dp_fall_land,
    dp_land_tall,
};
static const u32 drop_pillar_states_expected[] = {
    0x1u, 0x41u, 0x24B00000u, 0x1040000u, 0x0u, 0xFFFBE000u, 0x200000u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x24B00000u, 0x18A0000u, 0x0u, 0xFFFBE000u, 0x200000u, 0x50000u, 0xF13A738Eu, 0x0u,
    0x0u, 0x0u, 0x24B00000u, 0x10C0000u, 0x0u, 0xFFFC0000u, 0x200000u, 0x50000u, 0x7C277EEDu, 0x0u,
};

static u32 test_drop_pillar_states(u32 row)
{
    return object_run(drop_pillar_states_cases[row], row, &drop_pillar_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "drop_pillar_states", 0, 0, COUNT(drop_pillar_states_cases), test_drop_pillar_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(drop_pillar_states_cases);
