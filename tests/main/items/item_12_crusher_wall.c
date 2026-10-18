#include "test_runtime.h"
#include "main/items/item_12_crusher_wall.h"

static const u32 inputs_0[2][5] = {
    { 0, 0x41, 12, 1, 0x27 },
    { 8, 0x41, 12, 1, 0x27 },
};
struct crusher_wall_crush_case {
    u32 expected[1];
};
static const struct crusher_wall_crush_case crusher_wall_crush_cases[] = {
    { { 0x27u } },
    { { 0xFFFFFF80u } },
};
static u32 test_crusher_wall_crush(u32 row)
{
    const struct crusher_wall_crush_case* c = &crusher_wall_crush_cases[row];
    u32 observed_values[1];
    struct ItemObj obj, before;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.unk70 = inputs_0[row][0];
    obj.active = inputs_0[row][1];
    obj.id = inputs_0[row][2];
    obj.state = inputs_0[row][3];
    obj.x_pos.val = g_Player.x_pos.val = 100 * 65536 + 0x1234;
    g_Player.hp = inputs_0[row][4];
    before = obj;
    player_before = g_Player;
    crusher_wall_crush(&obj);
    if (player_before.unk70 & 8) {
        player_before.hp = -0x80;
    }
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u32)g_Player.hp;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static const u32 crusher_wall_player_near_expected[] = { 0u };
static u32 test_crusher_wall_player_near(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    u8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.x_pos.i.hi = 16430;
    return_value = crusher_wall_player_near(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, crusher_wall_player_near_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "crusher_wall_crush", 0, 0, 2, test_crusher_wall_crush },
    { "crusher_wall_player_near", 0, 0, 1, test_crusher_wall_player_near },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1;
