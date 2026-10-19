#include "test_runtime.h"
#include "main/effects/edge_spawner_data.h"
#include "main/effects/effect_13_edge_spawner.h"
void func_800B887C(s16, s16, s16, s16);

static u32 spawn_case(u32 observation)
{
    struct Effect1314ItemSpawn before_table[19];
    struct ItemObj before[32];
    u32 i, j, actual, reservation_mask = 0, allocated_mask = 0, entry_index[32];
    for (i = 0; i < 18; i++)
        edge_spawner_items[i].reserved = i == 10;
    assert(edge_spawner_items[18].id == 0xFF);
    memcpy(before_table, edge_spawner_items, sizeof(before_table));
    memset(item_objects, 0, sizeof(item_objects));
    for (i = 0; i < 32; i++) {
        item_objects[i].active = i == 3 || i == 17 || i == 31 ? 0 : 0x41;
        item_objects[i].id = 3;
        item_objects[i].unk2 = 0x25;
        item_objects[i].unk5 = i;
        item_objects[i].x_pos.val = 0x12345678;
        item_objects[i].y_pos.val = 0x23456789;
    }
    memcpy(before, item_objects, sizeof(before));
    func_800B887C(0x1510, 0x15A0, 0x620, 0x820);
    for (i = 0; i < 19; i++) {
        if (i < 18 && edge_spawner_items[i].reserved)
            reservation_mask |= 1u << i;
        before_table[i].reserved = edge_spawner_items[i].reserved;
        assert(edge_spawner_items[i].reserved <= 1);
    }
    for (i = 0; i < sizeof(before_table); i++)
        assert(((u8*)before_table)[i] == ((u8*)edge_spawner_items)[i]);
    for (i = 0; i < 32; i++) {
        entry_index[i] = 0;
        if (!before[i].active && item_objects[i].active) {
            allocated_mask |= 1u << i;
            for (j = 0; j < 18; j++)
                if (item_objects[i].backref == &edge_spawner_items[j])
                    entry_index[i] = j + 1;
            assert(entry_index[i] != 0);
            before[i].active = item_objects[i].active;
            before[i].id = item_objects[i].id;
            before[i].unk2 = item_objects[i].unk2;
            before[i].x_pos = item_objects[i].x_pos;
            before[i].y_pos = item_objects[i].y_pos;
            before[i].backref = item_objects[i].backref;
        }
        for (j = 0; j < sizeof(struct ItemObj) / 4; j++)
            assert(((u32*)&item_objects[i])[j] == ((u32*)&before[i])[j]);
    }
    if (observation == 0)
        actual = reservation_mask;
    else if (observation == 1)
        actual = allocated_mask;
    else {
        i = observation < 6 ? 3 : 17;
        switch ((observation - 2) % 4) {
        case 0:
            actual = ((u32*)&item_objects[i])[0];
            break;
        case 1:
            actual = item_objects[i].x_pos.val;
            break;
        case 2:
            actual = item_objects[i].y_pos.val;
            break;
        default:
            actual = entry_index[i];
            break;
        }
    }
    return actual;
}
static const u32 edge_spawner_bounds_cases_expected[] = { 0x2480u, 0x20008u, 0x10741u, 0x15800000u, 0x6B00000u, 0x8u, 0x10741u, 0x15400000u, 0x7C00000u, 0xEu };

struct func_800B887C_case {
    u32 id, reserved, pool_0_full, x_max, y_max;
    u32 expected[6];
};
static const struct func_800B887C_case func_800B887C_cases[] = {
    { 255, 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 255, 0, 5632, 2244, { 0xFFu, 0x41u, 7u, 1u, 0x15100000u, 0x5D00000u } },
    { 0, 255, 255, 5632, 2244, { 0xFFu, 1u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800B887C(u32 row)
{
    const struct func_800B887C_case* c = &func_800B887C_cases[row];
    u32 observed_values[6];
    u8 pool_0_full;
    s16 x_min;
    s16 x_max;
    s16 y_min;
    s16 y_max;
    memset(&item_objects, 0, sizeof(item_objects));
    edge_spawner_items[0].id = c->id;
    edge_spawner_items[0].reserved = c->reserved;
    edge_spawner_items[0].x = 0;
    edge_spawner_items[0].y = 0;
    pool_0_full = c->pool_0_full;
    x_min = 0;
    x_max = c->x_max;
    y_min = 0;
    y_max = c->y_max;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_800B887C(x_min, x_max, y_min, y_max);
    observed_values[0] = (u32)edge_spawner_items[0].reserved;
    observed_values[1] = (u32)item_objects[0].active;
    observed_values[2] = (u32)item_objects[0].id;
    observed_values[3] = (u32)item_objects[0].unk2;
    observed_values[4] = (u32)item_objects[0].x_pos.val;
    observed_values[5] = (u32)item_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

void edge_spawner_main(struct EffectObj*);
static u32 above(u32 row)
{
    struct EffectObj obj, expected;
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    struct BackgroundObj background;
    (void)row;
    engine_obj.stage = 2;
    engine_obj.substage = 0;
    engine = engine_obj;
    background_objects[0].x_pos.i.hi = 5112;
    background_objects[0].y_pos.i.hi = 833;
    background = background_objects[0];
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 13;
    obj.state = 1;
    obj.x_pos.i.hi = 5272;
    obj.y_pos.i.hi = 816;
    expected = obj;
    cur_random = 0x1234;
    edge_spawner_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&background_objects[0], &background, sizeof(background));
    assert(cur_random == 0x1234);
    return 1;
}

static struct MainObj expected_pool[48];
static u32 full(u32 row)
{
    struct EffectObj obj, expected;
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    engine_obj.stage = 2;
    engine_obj.substage = 0;
    engine = engine_obj;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    memcpy(expected_pool, main_objects, sizeof(expected_pool));
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 13;
    obj.x_pos.i.hi = 5272;
    obj.y_pos.i.hi = 816;
    expected = obj;
    expected.state = 1;
    cur_random = 0x1234;
    edge_spawner_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(main_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    return 1;
}

static u32 map[192], pixels[256], attributes[1];
static struct MainObj mains_before[48];
static u32 exhaust(u32 row)
{
    struct EffectObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 solid = row % 2, scene = row / 2 % 3, edge = row / 6, i;
    for (i = 0; i < COUNT(map); i++)
        map[i] = 0x01010101;
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = solid ? 0x38 : 0;
    SP_BG_TILEMAP = (u8*)map;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 13;
    obj.state = 1;
    obj.x_pos.val = (edge ? 529 : 528) * 65536 + 0x1234;
    obj.y_pos.val = (512 + scene * 16) * 65536 + 0x5678;
    background_objects[0].x_pos.i.hi = obj.x_pos.i.hi - 160;
    background_objects[0].y_pos.i.hi = obj.y_pos.i.hi - 120;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    c_test_copy_words((u32*)mains_before, (u32*)main_objects, sizeof(mains_before) / 4);
    expected = obj;
    expected.x_pos.i.hi -= 16;
    cur_random = 0x1234;
    func_800B875C(&obj, background_objects[0].x_pos.i.hi);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((u32*)main_objects, (u32*)mains_before, sizeof(mains_before) / 4) == 0 && cur_random == 0x1234);
    for (i = 0; i < COUNT(map); i++)
        assert(map[i] == 0x01010101);
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == 0);
    assert(attributes[0] == (solid ? 0x38 : 0) && SP_BG_TILEMAP == (u8*)map && TEST_BG_TILE_PIXELS == (u8*)pixels && TEST_BG_TILE_ATTRS == (u8*)attributes);
    assert(layout_width == 16 && layout_height == 16 && layout_size == 256);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "edge_spawner_bounds", NULL, edge_spawner_bounds_cases_expected, COUNT(edge_spawner_bounds_cases_expected), spawn_case },
    { "func_800B887C", 0, 0, 3, test_func_800B887C },
    { "shipped_edge_spawner_one_pixel_above_camera_scan_bounds", NULL, NULL, 1, above },
    { "shipped_Frost_Walrus_edge_spawner_initial_enemy_full_main_pool", NULL, NULL, 1, full },
    { "all_fifteen_solid_or_empty_probes_exhaust_without_spawning", NULL, NULL, 12, exhaust },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(edge_spawner_bounds_cases_expected) + 3 + 1 + 1 + 12;
