#include "test_runtime.h"
#include "main/items/item_27_boss_teleporter.h"

static const u32 func_800C7970_expected[] = { 1u };
static u32 test_func_800C7970(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    struct PlayerObj argument_obj_1;
    struct Unk_unk68 child_0;
    u8 child_0_present;
    struct Unk_unk68 child_1;
    u8 child_1_present;
    s8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    child_0_present = 255;
    child_1_present = 255;
    obj.x_pos.u.hi = 55300;
    child_1.unk2 = 136;
    argument_obj_1.x_pos.u.hi = 32768;
    child_0.unk2 = 192;
    obj.y_pos.u.hi = 32704;
    child_1.unk1 = 64;
    argument_obj_1.y_pos.u.hi = 12160;
    child_0.unk1 = 127;
    argument_obj_1.unk68 = child_0_present ? &child_0 : NULL;
    obj.unk68 = child_1_present ? &child_1 : NULL;
    return_value = func_800C7970(&obj, &argument_obj_1);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, func_800C7970_expected, 1);
}

#include "support/pool_full.h"
static u32 pool_full_boss_teleporter_warp_start(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    boss_teleporter_warp_start(&pf_item);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_boss_teleporter_warp_start,
};
static const u32 pool_full_cases_expected[] = { 0x50000u };

#include "support/warp_spawns.h"
WARP_BOSS_CASE(boss_first_uncleared, 8, 0)
WARP_BOSS_CASE(boss_last_uncleared, 15, 0)
WARP_BOSS_CASE(boss_spawn, 0, 0)
WARP_BOSS_CASE(boss_full, 0, 1)
static const CTestCase bosses_cleared_warp_cases[] = { WARP_ENTRY(boss_first_uncleared) WARP_ENTRY(boss_last_uncleared) WARP_ENTRY(boss_spawn) WARP_ENTRY(boss_full) };

static const u32 bosses_cleared_warp_cases_expected[] = { 0x7u, 0x7u, 0x1410100u, 0x10100u };
const struct CTestGroup c_test_groups[] = {
    { "func_800C7970", 0, 0, 1, test_func_800C7970 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "bosses_cleared_warp", bosses_cleared_warp_cases, bosses_cleared_warp_cases_expected, COUNT(bosses_cleared_warp_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(pool_full_cases) + COUNT(bosses_cleared_warp_cases);
