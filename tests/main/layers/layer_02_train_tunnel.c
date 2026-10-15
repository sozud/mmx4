#include "test_runtime.h"

static const u32 train_tunnel_accelerate_0_expected[] = { 0x80000u, 5u, 0u };
static u32 test_train_tunnel_accelerate_0(u32 row)
{
    u32 observed_values[3];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before[3];
    struct LayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    background_objects[0].x_pos.i.hi = -16640;
    background_objects[0].unk26 = 16384;
    obj.unk18.val = 524288;
    g_Player.spike_immune = 7;
    engine_obj.gameplay_locked = 0x27;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(background_before, background_objects, sizeof(background_before));
    train_tunnel_accelerate(&obj);
    player_before.script_state = 0;
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, background_before, sizeof(background_before));
    observed_values[0] = (u32)obj.unk18.val;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, train_tunnel_accelerate_0_expected, 3);
}
static const u32 train_tunnel_accelerate_1_expected[] = { 0x400u, 0u, 0u };
static u32 test_train_tunnel_accelerate_1(u32 row)
{
    u32 observed_values[3];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before[3];
    struct LayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    g_Player.script_state = -128;
    g_Player.spike_immune = 7;
    engine_obj.gameplay_locked = 0x27;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(background_before, background_objects, sizeof(background_before));
    train_tunnel_accelerate(&obj);
    player_before.script_state = 0;
    player_before.spike_immune = 0;
    engine_before.gameplay_locked = 0;
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, background_before, sizeof(background_before));
    observed_values[0] = (u32)obj.unk18.val;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(1, row, observed_values, train_tunnel_accelerate_1_expected, 3);
}
static u32 test_train_tunnel_accelerate(u32 index)
{
    if (index < 1)
        return test_train_tunnel_accelerate_0(index);
    index -= 1;
    return test_train_tunnel_accelerate_1(index);
}

static const u32 train_tunnel_player_at_lock_expected[] = { 0u };
static u32 test_train_tunnel_player_at_lock(u32 row)
{
    u32 observed_values[1];
    struct LayerObj obj;
    u8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.bg_offset = 4;
    return_value = train_tunnel_player_at_lock(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, train_tunnel_player_at_lock_expected, 1);
}

static const u32 train_tunnel_update_section_expected[] = { 4u, 4u, 0u, 0u };
static u32 test_train_tunnel_update_section(u32 row)
{
    u32 observed_values[4];
    struct LayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = 14384;
    train_tunnel_update_section(&obj);
    observed_values[0] = (u32)obj.bg_offset;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    return c_test_observe(0, row, observed_values, train_tunnel_update_section_expected, 4);
}

#include "support/train_sections.h"
SECTION_CASE(7)
SECTION_CASE(8)
SECTION_CASE(9)
SECTION_CASE(10)
static const CTestCase train_tunnel_sections_cases[] = { SECTION_ENTRY(7) SECTION_ENTRY(8) SECTION_ENTRY(9) SECTION_ENTRY(10) };

static const u32 train_tunnel_sections_cases_expected[] = { 0x103u, 0x5u, 0x104u, 0x5u };
const struct CTestGroup c_test_groups[] = {
    { "train_tunnel_accelerate", 0, 0, 2, test_train_tunnel_accelerate },
    { "train_tunnel_player_at_lock", 0, 0, 1, test_train_tunnel_player_at_lock },
    { "train_tunnel_update_section", 0, 0, 1, test_train_tunnel_update_section },
    { "train_tunnel_sections", train_tunnel_sections_cases, train_tunnel_sections_cases_expected, COUNT(train_tunnel_sections_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1 + 1 + COUNT(train_tunnel_sections_cases);
