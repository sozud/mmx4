#include "test_runtime.h"
#include "main/layers/layer_00_train_scroll.h"
#include "main/layers/layer_02_train_tunnel.h"

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

void train_tunnel_spawn_scroll_prop(struct LayerObj*);
static struct ItemObj items_expected[32];
static struct MiscObj misc_expected[64];
static u32 map_words[12];
static u32 crusher(u32 row)
{
    struct LayerObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 stop = row % 3, full = row / 3 % 2, ready = row / 6, i;
    engine_obj.stage = 8;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    memset(&obj, 0, sizeof(obj));
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    for (i = 0; i < COUNT(item_objects); i++)
        item_objects[i].active = i == 31 && !full ? 0 : 1;
    memcpy(items_expected, item_objects, sizeof(items_expected));
    obj.active = 1;
    obj.id = 0;
    obj.state = 1;
    obj.bg_offset = stop == 2 ? 4 : stop + 1;
    obj.unk5 = obj.bg_offset;
    obj.unk6 = obj.unk7 = 1;
    obj.private_state.signed_byte = ready;
    expected = obj;
    if (ready) {
        expected.unk7 = 2;
        if (!full) {
            items_expected[31].active = 0x41;
            items_expected[31].id = 12;
            items_expected[31].unk2 = obj.bg_offset - 1;
        }
    }
    train_scroll_spawn_crusher(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(item_objects, items_expected, sizeof(items_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}
static u32 prop(u32 row)
{
    struct LayerObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 mode = row % 3, full = row / 3 % 2, match = row / 6, i;
    engine_obj.stage = 8;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(map_words, 0xA5, sizeof(map_words));
    ((u8*)map_words)[16] = match ? 0x18 : 0x1E;
    SP_BG_TILEMAP = (u8*)map_words;
    layout_width = 4;
    layout_size = 16;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i == 63 && !full ? 0 : 1;
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    obj.active = 1;
    obj.id = 2;
    obj.state = 1;
    obj.unk5 = 2;
    obj.private_state.value.bytes[0] = mode == 2 ? 255 : mode;
    expected = obj;
    if (mode == 2 && !match)
        expected.private_state.value.bytes[0] = 0;
    if (!mode && match && !full) {
        expected.private_state.value.bytes[0] = 1;
        misc_expected[63].active = 0x41;
        misc_expected[63].id = 20;
        misc_expected[63].ext.misc_20.owner = &obj;
    }
    train_tunnel_spawn_scroll_prop(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(SP_BG_TILEMAP == (u8*)map_words && layout_width == 4 && layout_size == 16);
    for (i = 0; i < sizeof(map_words); i++)
        assert(((u8*)map_words)[i] == (i == 16 ? match ? 0x18 : 0x1E : 0xA5));
    return 1;
}

void train_tunnel_start_departure(struct LayerObj* arg0);
void train_tunnel_wait_stop_point(struct LayerObj* arg0);
static u32 map_words_train_tunnel_stop_and_departure[12];
static void script(struct PlayerObj* p, struct EngineObj* e)
{
    p->script_state = 1;
    p->script_action = 0x14;
    p->script_facing = 0x40;
    p->spike_immune = 1;
    e->gameplay_locked = 1;
}
static u32 stop(u32 row)
{
    struct LayerObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 mode = row % 7, character = row / 7, phase = mode < 3 ? 0 : mode < 5 ? 1
                                                                             : 2,
        screen = mode == 4 || mode == 6 ? 0x18 : 0x1E, i;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(map_words_train_tunnel_stop_and_departure, 0xA5, sizeof(map_words_train_tunnel_stop_and_departure));
    ((u8*)map_words_train_tunnel_stop_and_departure)[16] = screen;
    SP_BG_TILEMAP = (u8*)map_words_train_tunnel_stop_and_departure;
    layout_width = 4;
    layout_size = 16;
    engine_obj.stage = 8;
    engine_obj.substage = 1;
    engine_obj.cur_character = character;
    engine_expected = engine_obj;
    g_Player.unk2 = character;
    g_Player.x_pos.val = (mode == 1 ? 0x16C0 : mode == 2 ? 0x16C1
                                                         : 0x16B0)
            * 65536
        + 0x1234;
    player_expected = g_Player;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    obj.active = 1;
    obj.id = 2;
    obj.state = 1;
    obj.bg_offset = 1;
    obj.unk5 = 1;
    obj.unk7 = phase;
    expected = obj;
    if (!phase && mode != 2) {
        backgrounds_expected[0].unk24 = backgrounds_expected[0].unk26 = 0x16B0;
        script(&player_expected, &engine_expected);
        expected.unk7 = 1;
    } else if (phase == 1 && screen == 0x1E)
        expected.unk7 = 2;
    else if (phase == 2 && screen == 0x18) {
        expected.unk7 = 0;
        expected.unk6 = 1;
    }
    train_tunnel_wait_stop_point(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    for (i = 0; i < sizeof(map_words_train_tunnel_stop_and_departure); i++)
        assert(((u8*)map_words_train_tunnel_stop_and_departure)[i] == (i == 16 ? screen : 0xA5));
    assert(SP_BG_TILEMAP == (u8*)map_words_train_tunnel_stop_and_departure && layout_width == 4 && layout_size == 16);
    return 1;
}
static u32 departure(u32 row)
{
    struct LayerObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 resumed = row % 2, character = row / 2 % 2, scripted = row / 4;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 8;
    engine_obj.substage = 1;
    engine_obj.cur_character = character;
    engine_obj.checkpoint = resumed ? 3 : 2;
    engine_obj.character_state.bytes[0] = 1;
    engine_expected = engine_obj;
    g_Player.unk2 = character;
    g_Player.script_state = scripted ? -128 : 0;
    player_expected = g_Player;
    D_8013E198[5] = -1;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    obj.active = 1;
    obj.id = 2;
    obj.state = 1;
    obj.bg_offset = 2;
    obj.unk5 = 2;
    obj.unk18.val = 0x1234;
    expected = obj;
    expected.unk18.val = (resumed ? 8 : 2) * 65536;
    expected.unk17 = 1;
    expected.unk6 = 1;
    engine_expected.character_state.bytes[0] = 0;
    if (!resumed) {
        backgrounds_expected[0].unk26 = 0x1DE0;
        script(&player_expected, &engine_expected);
    }
    train_tunnel_start_departure(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    assert(D_8013E198[5] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "train_tunnel_accelerate", 0, 0, 2, test_train_tunnel_accelerate },
    { "train_tunnel_player_at_lock", 0, 0, 1, test_train_tunnel_player_at_lock },
    { "train_tunnel_update_section", 0, 0, 1, test_train_tunnel_update_section },
    { "train_tunnel_sections", train_tunnel_sections_cases, train_tunnel_sections_cases_expected, COUNT(train_tunnel_sections_cases), 0 },
    { "three_real_crusher_stops_ready_and_item_pool_full", NULL, NULL, 12, crusher },
    { "tunnel_constructor_FF_initial_state_screen_latch_and_misc_pool_full", NULL, NULL, 12, prop },
    { "first_stop_inclusive_lock_and_real_layout_wait_phases_both_characters", NULL, NULL, 14, stop },
    { "normal_and_checkpoint_three_departure_script_effects", NULL, NULL, 8, departure },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1 + 1 + COUNT(train_tunnel_sections_cases) + 12 + 12 + 14 + 8;
