#include "test_runtime.h"
#include "main/layers/layer_00_train_scroll.h"
#include "main/layers/layer_02_train_tunnel.h"
#include "main/tile_effects.h"
void train_scroll_update_section(struct LayerObj*);

static u32 event_case(u32 section, u32 mode)
{
    struct LayerObj obj, before;
    struct MainObj pool_before[48];
    struct BackgroundObj background_before[3];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(main_objects, 0, sizeof(main_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 48; i++) {
        main_objects[i].active = 1;
        main_objects[i].id = 0x27;
        main_objects[i].state = 0x28;
    }
    if (mode == 2)
        main_objects[17].active = 0;
    obj.active = 0x41;
    obj.id = 0;
    obj.state = 1;
    obj.bg_offset = section;
    obj.unk6 = 0x25;
    obj.unk7 = 0;
    background_objects[0].x_pos.i.hi = mode == 0 ? 99 : 100;
    background_objects[0].unk26 = 100;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(pool_before, main_objects, sizeof(pool_before));
    memcpy(background_before, background_objects, sizeof(background_before));
    if (section == 3)
        train_scroll_section_3_event(&obj);
    else
        train_scroll_section_4_event(&obj);
    if (mode != 0)
        before.unk7 = 1;
    if (mode == 2) {
        pool_before[17].active = 0x41;
        pool_before[17].id = 0x22;
        pool_before[17].unk2 = section - 1;
        pool_before[17].backref = &obj;
    }
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(main_objects, pool_before, sizeof(pool_before));
    c_test_same_words(background_objects, background_before, sizeof(background_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return (u8)obj.unk7 | ((u32)main_objects[17].id << 8) | ((u32)main_objects[17].unk2 << 16);
}
#define CASE(s, m)                                              \
    static u32 train_scroll_event_context_event_##s##_##m(void) \
    {                                                           \
        return event_case(s, m);                                \
    }
CASE(3, 0)
CASE(3, 1)
CASE(3, 2)
CASE(4, 0)
CASE(4, 1)
CASE(4, 2)
#define ENTRY(s, m) train_scroll_event_context_event_##s##_##m,
static const CTestCase train_scroll_event_context_cases[]
    = { ENTRY(3, 0) ENTRY(3, 1) ENTRY(3, 2) ENTRY(4, 0) ENTRY(4, 1) ENTRY(4, 2) };
static const u32 train_scroll_event_context_cases_expected[] = { 0x2700u, 0x2701u, 0x22201u, 0x2700u, 0x2701u, 0x32201u };
#undef CASE
#undef ENTRY

static const u32 train_scroll_update_section_expected[] = { 4u, 4u, 0u };
static u32 test_train_scroll_update_section(u32 row)
{
    u32 observed_values[3];
    struct LayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = 7168;
    train_scroll_update_section(&obj);
    observed_values[0] = (u32)obj.bg_offset;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, train_scroll_update_section_expected, 3);
}

#include "support/train_sections.h"
SECTION_CASE(0)
SECTION_CASE(1)
SECTION_CASE(2)
SECTION_CASE(3)
SECTION_CASE(4)
SECTION_CASE(5)
SECTION_CASE(6)
static const CTestCase train_scroll_sections_cases[] = { SECTION_ENTRY(0) SECTION_ENTRY(1) SECTION_ENTRY(2) SECTION_ENTRY(3) SECTION_ENTRY(4) SECTION_ENTRY(5) SECTION_ENTRY(6) };

static const u32 train_scroll_sections_cases_expected[] = { 0x4u, 0x104u, 0x4u, 0x10104u, 0x104u, 0x10104u, 0x4u };

extern struct TileEffectRecord** tile_effect_tables[26];
static u32 map_words[96];
static u16 pixels[256], pixels_expected[256], cache_expected[3][32][32];
#ifdef MMX4_SATURN
static u32 stage_cells[0x4000];
#endif
static u32 tiles(u32 row)
{
    struct LayerObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 visible = row, effect, record, tile;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(map_words, 0, sizeof(map_words));
    memset(pixels, 0xA5, sizeof(pixels));
    memcpy(pixels_expected, pixels, sizeof(pixels));
    memset(D_801441C8, 0xB6, sizeof(D_801441C8));
    memcpy(cache_expected, D_801441C8, sizeof(cache_expected));
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    layout_width = 32;
    layout_size = 128;
#ifdef MMX4_SATURN
    TEST_BG_TILE_ATTRS = (u8*)stage_cells;
#endif
    engine_obj.stage = 8;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    background_objects[0].x_pos.i.hi = visible ? 0x1A40 : 0;
    background_objects[0].y_pos.i.hi = visible ? 0x160 : 0;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 1;
    obj.id = 0;
    obj.state = 1;
    obj.bg_offset = 4;
    obj.unk5 = 4;
    obj.unk6 = 1;
    obj.unk7 = 2;
    expected = obj;
    expected.unk7 = 3;
    for (effect = 0; effect < 2; effect++) {
        struct TileEffectRecord* records = tile_effect_tables[16][effect ? 7 : 0];
        u32 count = effect ? 5 : 9, ox = effect ? 0x1B30 : 0x1A40, oy = effect ? 0x170 : 0x160;
        for (record = 0; record < count; record++) {
            struct TileEffectRecord* r = &records[record];
            assert(r->layer == 0 && r->has_next == (record + 1 != count));
            for (tile = 0; tile < r->packed_count / 2; tile++) {
                u32 x = (ox + r->x) / 16 + (r->packed_count % 2 ? tile : 0), y = (oy + r->y) / 16 + (r->packed_count % 2 ? 0 : tile);
                pixels_expected[(y % 16) * 16 + x % 16] = r->tiles[tile];
#ifndef MMX4_SATURN
                if (visible)
                    cache_expected[0][y % 32][x % 32] = r->tiles[tile];
#endif
            }
        }
    }
    train_scroll_open_tiles(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(pixels, pixels_expected, sizeof(pixels));
    c_test_same_words(D_801441C8, cache_expected, sizeof(cache_expected));
    assert(SP_BG_TILEMAP == (u8*)map_words && TEST_BG_TILE_PIXELS == (u8*)pixels && layout_width == 32 && layout_size == 128);
    for (effect = 0; effect < COUNT(map_words); effect++)
        assert(map_words[effect] == 0);
    return 1;
}

#include "support/tile_writes.h"
#include "main/player_common.h"
void train_scroll_shake(struct LayerObj*);
void train_scroll_release(struct LayerObj*);
static struct LayerObj ts;
static void ts_reset(u8 section, u8 unk6, s16 player_x)
{
    memset(&ts, 0, sizeof(ts));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(main_objects, 0, sizeof(main_objects));
    memset(background_objects, 0, sizeof(background_objects));
    ts.active = 0x41;
    ts.state = 1;
    ts.unk5 = section;
    ts.unk6 = unk6;
    ts.bg_offset = section;
    ts.unk16 = 5;
    g_Player.x_pos.i.hi = player_x;
    background_objects[0].x_pos.i.hi = 0x900;
    background_objects[0].unk24 = 0x123;
    background_objects[0].unk26 = 0x900;
}
#define TS_SEEN() (ts.unk5 | (u32)ts.unk6 << 8 | (u32)ts.unk7 << 16 | (u32)(u8)g_Player.script_action << 24)
static u32 ts_section_1_early(void)
{
    ts_reset(1, 0, 0x8E1);
    train_scroll_section_1(&ts);
    assert(background_objects[0].unk24 == 0x123 && g_Player.script_state == 0 && engine_obj.gameplay_locked == 0);
    return TS_SEEN();
}
static u32 ts_section_1_event(void)
{
    ts_reset(1, 1, 0x8D0);
    train_scroll_section_1(&ts);
    assert(main_objects[0].active == 0x41 && main_objects[0].id == 0x22 && main_objects[0].unk2 == 0);
    assert(main_objects[0].backref == (void*)&ts);
    return TS_SEEN();
}
static u32 ts_section_2_lock(void)
{
    ts_reset(2, 0, 0xD40);
    train_scroll_section_2(&ts);
    assert(background_objects[0].unk24 == 0xD30 && background_objects[0].unk26 == 0xD30);
    assert(g_Player.script_state == 1 && g_Player.script_facing == PLAYER_FACING_RIGHT && engine_obj.gameplay_locked == 1);
    return TS_SEEN();
}
static u32 ts_section_2_early(void)
{
    ts_reset(2, 0, 0xD2F);
    train_scroll_section_2(&ts);
    assert(background_objects[0].unk26 == 0x900 && g_Player.script_state == 0);
    return TS_SEEN();
}
static u32 ts_section_2_event(void)
{
    ts_reset(2, 1, 0xD30);
    train_scroll_section_2(&ts);
    assert(main_objects[0].active == 0x41 && main_objects[0].id == 0x22 && main_objects[0].unk2 == 1);
    return TS_SEEN();
}
static u32 ts_section_2_scrolling(void)
{
    ts_reset(2, 1, 0xD30);
    background_objects[0].x_pos.i.hi = 0x8FF;
    train_scroll_section_2(&ts);
    assert(main_objects[0].active == 0);
    return TS_SEEN();
}
static const u16 open_tiles_effects[3][2][3] = {
    { { 0xD, 0x8C0, 0x160 }, { 0xC, 0x970, 0x190 } },
    { { 0, 0xD20, 0x160 }, { 7, 0xE10, 0x170 } },
    { { 0, 0x13B0, 0x160 }, { 7, 0x14A0, 0x170 } },
};
static u32 open_tiles(u8 section)
{
    u32 i;
    ts_reset(section, 1, 0);
    ts.unk7 = 2;
    engine_obj.stage = 8;
    tile_writes_begin();
    for (i = 0; i < 2; i++)
        tile_writes_expect(open_tiles_effects[section - 1][i][0], open_tiles_effects[section - 1][i][1], open_tiles_effects[section - 1][i][2], 1);
    train_scroll_open_tiles(&ts);
    assert(ts.unk7 == 3);
    return tile_writes_end();
}
static u32 ts_open_tiles_1(void) { return open_tiles(1); }
static u32 ts_open_tiles_2(void) { return open_tiles(2); }
static u32 ts_open_tiles_3(void) { return open_tiles(3); }
static u32 ts_release(void)
{
    ts_reset(4, 1, 0x1A50);
    ts.unk7 = 3;
    ts.private_state.signed_byte = 1;
    player_start_script_action(0x14, PLAYER_FACING_RIGHT);
    g_Player.script_state = -1;
    train_scroll_release(&ts);
    assert(g_Player.script_state == 0 && engine_obj.gameplay_locked == 0 && ts.private_state.signed_byte == 0);
    assert(background_objects[0].unk1C == 0x1A50 && background_objects[0].unk24 == 0x1A50);
    return TS_SEEN();
}
static u32 ts_release_wait(void)
{
    ts_reset(4, 1, 0x1A50);
    ts.unk7 = 3;
    player_start_script_action(0x14, PLAYER_FACING_RIGHT);
    train_scroll_release(&ts);
    assert(g_Player.script_state == 1 && engine_obj.gameplay_locked == 1 && background_objects[0].unk24 == 0x123);
    return TS_SEEN();
}
static u32 ts_shake(void)
{
    ts_reset(4, 1, 0);
    ts.unk16 = 1;
    train_scroll_shake(&ts);
    assert(background_objects[0].unk37 == 0x30 && background_objects[0].unk46 == 2);
    return ts.unk16;
}
static const CTestCase train_scroll_paths_cases[] = {
    ts_section_1_early,
    ts_section_1_event,
    ts_section_2_lock,
    ts_section_2_early,
    ts_section_2_event,
    ts_section_2_scrolling,
    ts_open_tiles_1,
    ts_open_tiles_2,
    ts_open_tiles_3,
    ts_release,
    ts_release_wait,
    ts_shake,
};
static const u32 train_scroll_paths_cases_expected[] = { 0x1u, 0x10101u, 0x14000102u, 0x2u, 0x10102u, 0x102u, 0x8C638A23u, 0x5CF84668u, 0xA9E963C8u, 0x14000005u, 0x14030104u, 0x78u };

const struct CTestGroup c_test_groups[] = {
    { "train_scroll_event_context", train_scroll_event_context_cases, train_scroll_event_context_cases_expected, COUNT(train_scroll_event_context_cases), 0 },
    { "train_scroll_update_section", 0, 0, 1, test_train_scroll_update_section },
    { "train_scroll_sections", train_scroll_sections_cases, train_scroll_sections_cases_expected, COUNT(train_scroll_sections_cases), 0 },
    { "actual_final_stop_shipped_tile_records_and_visible_cache", NULL, NULL, 2, tiles },
    { "train_scroll_paths", train_scroll_paths_cases, train_scroll_paths_cases_expected, COUNT(train_scroll_paths_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_scroll_event_context_cases) + 1 + COUNT(train_scroll_sections_cases) + 2 + COUNT(train_scroll_paths_cases);
