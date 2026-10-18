#include "test_runtime.h"
#include "main/tile_effects.h"
void floor_trap_wait(struct EffectObj*);
void floor_trap_explode(struct EffectObj*);
extern struct TileEffectRecord** tile_effect_tables[26];
static u32 map_words[192];
static u16 pixels[256], pixels_expected[256], cache_expected[3][32][32];
static struct ShotObj shots_expected[32];
static struct VisualObj visuals_before[32];
static const s16 positions[3] = { 12552, 12616, 12678 };
static u32 explode(u32 row)
{
    struct EffectObj obj, expected;
    struct RideArmorObj ride_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 place = row % 3, slots = row / 3 % 3, wait = row / 9, i, y, x, ox = positions[place] & ~15;
    memset(&obj, 0, sizeof(obj));
    memset(&qux_object, 0, sizeof(qux_object));
    qux_object.active = 0x41;
    qux_object.id = 0;
    qux_object.state = 1;
    qux_object.x_pos.i.hi = ox + 24;
    qux_object.y_pos.i.hi = 102;
    ride_before = qux_object;
    engine_obj.stage = 5;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = ox;
    background_objects[0].y_pos.i.hi = 96;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(map_words, 0, sizeof(map_words));
    memset(pixels, 0xA5, sizeof(pixels));
    memcpy(pixels_expected, pixels, sizeof(pixels));
    memset(D_801441C8, 0xB6, sizeof(D_801441C8));
    memcpy(cache_expected, D_801441C8, sizeof(cache_expected));
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    layout_width = 64;
    layout_size = 256;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i >= 32 - slots ? 0 : 1;
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 1;
    obj.id = 31;
    obj.x_pos.val = positions[place] * 65536 + 0x1234;
    obj.y_pos.val = 138 * 65536 + 0x5678;
    floor_trap_wait(&obj);
    assert(obj.state == 1 && obj.unk5 == 3 && obj.x_pos.val == ox * 65536 && obj.y_pos.val == 128 * 65536);
    for (i = 0; i < (wait ? 1 : 2); i++)
        floor_trap_explode(&obj);
    expected = obj;
    expected.unk5--;
    if (!wait) {
        for (i = 0; i < slots; i++) {
            struct ShotObj* s = &shots_expected[32 - slots + i];
            s->active = 0x41;
            s->id = 32;
            s->unk2 = i;
            s->unk7C = WEAPON_OBJECT(&obj);
        }
        for (y = 0; y < 4; y++) {
            struct TileEffectRecord* r = &tile_effect_tables[10][10][y];
            assert(r->layer == 0 && r->packed_count == 9 && r->has_next == (y != 3));
            for (x = 0; x < 4; x++) {
                u32 tx = ox / 16 + x, ty = 6 + y;
                pixels_expected[(ty % 16) * 16 + tx % 16] = r->tiles[x];
                cache_expected[0][ty][tx % 32] = r->tiles[x];
            }
        }
        memset(&expected, 0, 8);
    }
    floor_trap_explode(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&qux_object, &ride_before, sizeof(qux_object));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(pixels, pixels_expected, sizeof(pixels));
    c_test_same_words(D_801441C8, cache_expected, sizeof(cache_expected));
    assert(SP_BG_TILEMAP == (u8*)map_words && TEST_BG_TILE_PIXELS == (u8*)pixels && layout_width == 64 && layout_size == 256);
    for (i = 0; i < COUNT(map_words); i++)
        assert(map_words[i] == 0);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "real_bike_trigger_countdown_shipped_floor_tiles_zero_one_two_shot_slots", NULL, NULL, 18, explode } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 18;
