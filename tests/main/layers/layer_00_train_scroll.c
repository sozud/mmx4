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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)main_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
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
                if (visible)
                    cache_expected[0][y % 32][x % 32] = r->tiles[tile];
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

const struct CTestGroup c_test_groups[] = {
    { "train_scroll_event_context", train_scroll_event_context_cases, train_scroll_event_context_cases_expected, COUNT(train_scroll_event_context_cases), 0 },
    { "train_scroll_update_section", 0, 0, 1, test_train_scroll_update_section },
    { "train_scroll_sections", train_scroll_sections_cases, train_scroll_sections_cases_expected, COUNT(train_scroll_sections_cases), 0 },
    { "actual_final_stop_shipped_tile_records_and_visible_cache", NULL, NULL, 2, tiles },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_scroll_event_context_cases) + 1 + COUNT(train_scroll_sections_cases) + 2;
