#include "test_runtime.h"
#include "main/items/item_08_boss_door.h"

static const u32 boss_door_block_player_expected[] = { 0u };
static u32 test_boss_door_block_player(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk72 = 12;
    boss_door_block_player(&obj);
    observed_values[0] = (u32)g_Player.unk71;
    return c_test_observe(0, row, observed_values, boss_door_block_player_expected, 1);
}

static const u32 func_800C1E7C_expected[] = { 0u };
static u32 test_func_800C1E7C(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    struct Unk_unk68 child_0;
    u8 child_0_present;
    struct Unk_unk68 child_1;
    u8 child_1_present;
    s8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.unk2 = -1;
    obj.x_pos.i.hi = 32766;
    g_Player.x_pos.i.hi = 1;
    child_0_present = 255;
    child_1_present = 255;
    child_0.unk0 = 106;
    child_1.unk0 = 47;
    obj.unk68 = child_0_present ? &child_0 : NULL;
    g_Player.unk68 = child_1_present ? &child_1 : NULL;
    return_value = func_800C1E7C(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, func_800C1E7C_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "boss_door_block_player", 0, 0, 1, test_boss_door_block_player },
    { "func_800C1E7C", 0, 0, 1, test_func_800C1E7C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1;
