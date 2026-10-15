#ifndef MMX4_TESTS_ENEMY_WORLD_H
#define MMX4_TESTS_ENEMY_WORLD_H
#include "support/retail_sound_commands.h"

static struct MainObj world_mains_expected[48];
static struct VisualObj world_visuals_expected[32];
static struct BackgroundObj world_backgrounds_expected[3];
static struct WeaponObj world_weapons_expected[16];
static struct ShotObj world_shots_expected[32];
static struct MiscObj world_miscs_expected[64];
static struct EngineObj world_engine_expected;
static struct PlayerObj world_player_expected;
static struct MainBssState world_bss_expected;
static struct StageObjectRecord* world_record;
static struct StageObjectRecord world_record_expected;
static u8 world_tiles[128], world_tiles_expected[128];
static u16 world_pixels[512], world_pixels_expected[512];
static u32 world_attrs[3], world_attrs_expected[3];
static u32 world_sound_expected[163];
static u16 world_random_expected;
#define world_expected (&world_mains_expected[0])
#define WORLD_WORDS(object) (sizeof(object) / 4)

static struct MainObj* world_spawn(u32 id, u32 stage, u32 substage, u32 kind, struct StageObjectRecord* record)
{
    struct MainObj* obj = &main_objects[0];
    c_test_zero_words((u32*)&engine_obj, WORLD_WORDS(engine_obj));
    c_test_zero_words((u32*)&g_Player, WORLD_WORDS(g_Player));
    c_test_zero_words((u32*)main_objects, WORLD_WORDS(main_objects));
    c_test_zero_words((u32*)background_objects, WORLD_WORDS(background_objects));
    c_test_zero_words((u32*)weapon_objects, WORLD_WORDS(weapon_objects));
    c_test_zero_words((u32*)shot_objects, WORLD_WORDS(shot_objects));
    c_test_zero_words((u32*)misc_objects, WORLD_WORDS(misc_objects));
    D_8013E198[2] = -1;
    engine_obj.stage = stage;
    engine_obj.substage = substage;
    obj->active = 0x41;
    obj->id = id;
    obj->unk2 = kind;
    obj->backref = record;
    world_record = record;
    obj->x_pos.i.hi = 400;
    obj->y_pos.i.hi = 200;
    SP_CUR_MAIN_OBJ = obj;
    world_tiles[0] = 1;
    SP_BG_TILEMAP = world_tiles;
    TEST_BG_TILE_PIXELS = (u8*)world_pixels;
    TEST_BG_TILE_ATTRS = (u8*)world_attrs;
    layout_size = 128;
    layout_width = 16;
    g_Player.x_pos.i.hi = 400;
    g_Player.y_pos.i.hi = 200;
    D_80141F50[2] = (u8*)retail_sound_commands;
    D_80141EE8[2] = (u8*)(retail_sound_commands + 163);
    return obj;
}

static void world_snapshot(void)
{
    c_test_copy_words((u32*)world_mains_expected, (const u32*)main_objects, WORLD_WORDS(main_objects));
    c_test_copy_words((u32*)world_visuals_expected, (const u32*)visual_objects, WORLD_WORDS(visual_objects));
    c_test_copy_words((u32*)world_backgrounds_expected, (const u32*)background_objects, WORLD_WORDS(background_objects));
    c_test_copy_words((u32*)world_weapons_expected, (const u32*)weapon_objects, WORLD_WORDS(weapon_objects));
    c_test_copy_words((u32*)world_shots_expected, (const u32*)shot_objects, WORLD_WORDS(shot_objects));
    c_test_copy_words((u32*)world_miscs_expected, (const u32*)misc_objects, WORLD_WORDS(misc_objects));
    c_test_copy_words((u32*)world_tiles_expected, (const u32*)world_tiles, WORLD_WORDS(world_tiles));
    c_test_copy_words((u32*)world_pixels_expected, (const u32*)world_pixels, WORLD_WORDS(world_pixels));
    c_test_copy_words(world_attrs_expected, world_attrs, WORLD_WORDS(world_attrs));
    c_test_copy_words(world_sound_expected, retail_sound_commands, WORLD_WORDS(retail_sound_commands));
    world_engine_expected = engine_obj;
    world_player_expected = g_Player;
    world_bss_expected = main_bss_state;
    world_record_expected = *world_record;
    world_random_expected = cur_random;
}

static void world_check(void)
{
    assert(c_test_word_difference((const u32*)main_objects, (const u32*)world_mains_expected, WORLD_WORDS(main_objects)) == 0);
    assert(c_test_word_difference((const u32*)visual_objects, (const u32*)world_visuals_expected, WORLD_WORDS(visual_objects)) == 0);
    assert(c_test_word_difference((const u32*)background_objects, (const u32*)world_backgrounds_expected, WORLD_WORDS(background_objects)) == 0);
    assert(c_test_word_difference((const u32*)weapon_objects, (const u32*)world_weapons_expected, WORLD_WORDS(weapon_objects)) == 0);
    assert(c_test_word_difference((const u32*)shot_objects, (const u32*)world_shots_expected, WORLD_WORDS(shot_objects)) == 0);
    assert(c_test_word_difference((const u32*)misc_objects, (const u32*)world_miscs_expected, WORLD_WORDS(misc_objects)) == 0);
    assert(c_test_word_difference((const u32*)world_tiles, (const u32*)world_tiles_expected, WORLD_WORDS(world_tiles)) == 0);
    assert(c_test_word_difference((const u32*)world_pixels, (const u32*)world_pixels_expected, WORLD_WORDS(world_pixels)) == 0);
    assert(c_test_word_difference(world_attrs, world_attrs_expected, WORLD_WORDS(world_attrs)) == 0);
    assert(c_test_word_difference(retail_sound_commands, world_sound_expected, WORLD_WORDS(retail_sound_commands)) == 0);
    assert(c_test_word_difference((const u32*)&engine_obj, (const u32*)&world_engine_expected, WORLD_WORDS(engine_obj)) == 0);
    assert(c_test_word_difference((const u32*)&g_Player, (const u32*)&world_player_expected, WORLD_WORDS(g_Player)) == 0);
    assert(c_test_word_difference((const u32*)&main_bss_state, (const u32*)&world_bss_expected, WORLD_WORDS(main_bss_state)) == 0);
    assert(c_test_word_difference((const u32*)world_record, (const u32*)&world_record_expected, WORLD_WORDS(world_record_expected)) == 0);
    assert(SP_CUR_MAIN_OBJ == &main_objects[0]);
    assert(SP_BG_TILEMAP == world_tiles);
    assert(TEST_BG_TILE_PIXELS == (u8*)world_pixels);
    assert(TEST_BG_TILE_ATTRS == (u8*)world_attrs);
    assert(layout_size == 128 && layout_width == 16);
    assert(cur_random == world_random_expected);
    assert(D_8013E198[2] == -1);
    assert(D_80141F50[2] == (u8*)retail_sound_commands);
    assert(D_80141EE8[2] == (u8*)(retail_sound_commands + 163));
}
#endif
