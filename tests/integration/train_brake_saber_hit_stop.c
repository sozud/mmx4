#include "test_runtime.h"
#include "main/collision.h"
#include "main/player_animations_2.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/player_special.h"
#include "main/1E1BC.h"
#include "main/player_enter.h"
#include "main/player_common.h"
void player_update_normal(struct PlayerObj*);
void player_update(void);
void zero_saber_update(struct WeaponObj*);
void func_800D9268(struct LayerObj*);
void train_tunnel_main(struct LayerObj*);
void train_tunnel_brake(struct LayerObj*);
void func_80068548(struct MainObj*);
static u32 gfx[64], frames[64], attributes[2];
static u32 map_words[384];
#define map ((u8*)map_words)
static u16 tiles[512], tiles_before[512], palette[0x152], palette_expected[0x152];
static u8 sound_commands[32];
static Palette bank[40];
static struct MainObj main_expected[32];
static struct EffectObj effects[32];
static struct LayerObj train, train_before;
static struct MainObj* current_before;
static u32 metadata[8], menu[64];
static struct PlayerObj expected, entity;
static struct EngineObj engine;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds[3];
static struct WeaponObj weapons[16];
static struct VisualObj visuals[32];
static struct ControllerInput input;
static u8 dirty;
static u16 rng;
static u32 zero_difference(const u32* p, u32 count)
{
    u32 different = 0;
    while (count >= 8) {
        different |= p[0] | p[1] | p[2] | p[3] | p[4] | p[5] | p[6] | p[7];
        p += 8;
        count -= 8;
    }
    while (count--)
        different |= *p++;
    return different;
}
static void prepare(void)
{
    u32 i;
    c_test_zero_words((u32*)(&g_Player), sizeof(g_Player) / 4);
    c_test_zero_words((u32*)(&g_Entity), sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)(background_objects), sizeof(background_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)(&engine_obj), sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)(&main_bss_state), sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)(gfx), sizeof(gfx) / 4);
    c_test_zero_words((u32*)(frames), sizeof(frames) / 4);
    gfx[0] = frames[0] = 64;
    gfx[1] = gfx[8] = gfx[9] = frames[1] = frames[5] = frames[16] = frames[17] = 128;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    for (i = 0; i < COUNT(map_words); i += 8) {
        map_words[i] = map_words[i + 1] = map_words[i + 2] = map_words[i + 3] = map_words[i + 4] = map_words[i + 5] = map_words[i + 6] = map_words[i + 7] = 0x01010101;
    }
    for (i = 0; i < COUNT(tiles); i++)
        tiles[i] = i >= 256 && (i & 255) / 16 >= 11;
    c_test_copy_words((u32*)tiles_before, (u32*)tiles, sizeof(tiles) / 4);
    attributes[0] = 0;
    attributes[1] = 0x38;
    map[512] = 0x1E;
    map[513] = 0x18;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = 32;
    layout_height = 16;
    layout_size = 512;
    c_test_zero_words((u32*)(bank), sizeof(bank) / 4);
    c_test_zero_words((u32*)(palette), sizeof(palette) / 4);
    palette[0] = palette[0x151] = palette_expected[0] = palette_expected[0x151] = 0xBEEF;
    TEST_PALETTE_BANK = (u8*)bank;
    TEST_PALETTE = (u8*)&palette[1];
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    engine_obj.cur_character = 1;
    engine_obj.stage = 8;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    g_Player.active = 0x41;
    g_Player.unk2 = 1;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.x_pos.i.hi = 5808;
    g_Player.y_pos.i.hi = 410;
    g_Player.unk15 = 0x40;
    g_Player.animation_table = (u32**)D_8011AFF0;
    g_Player.unk38 = (u8*)gfx + 64;
    player_enter_idle(&g_Player);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = 0x1234;
    c_test_zero_words((u32*)(sound_commands), sizeof(sound_commands) / 4);
    D_80141F50[1] = sound_commands;
    g_Player.unk18 = g_Player.x_pos;
    g_Player.unk1C = g_Player.y_pos;
    CollisionRelated(&g_Player);
    assert(g_Player.unk70 == PLAYER_COLLIDE_GROUND);
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(menu); i++)
        menu[i] = i < 8 ? 64 : 0;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)menu;
    current_before = SP_CUR_MAIN_OBJ;
    background_objects[0].x_pos.i.hi = 5648;
    background_objects[0].y_pos.i.hi = 256;
}
static void capture(void)
{
    expected = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds, (u32*)background_objects, sizeof(backgrounds) / 4);
    c_test_copy_words((u32*)weapons, (u32*)weapon_objects, 2 * sizeof(weapons[0]) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, 2 * sizeof(visuals[0]) / 4);
    main_expected[0] = main_objects[0];
    effects[0] = effect_objects[0];
    train_before = train;
    input = controller_input;
    dirty = need_palette_load;
    rng = cur_random;
}
static void check(void)
{
    u32 i;
    assert(zero_difference((u32*)misc_objects, sizeof(misc_objects) / 4) == 0 && zero_difference((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4) == 0 && c_test_word_difference((u32*)main_objects, (u32*)main_expected, sizeof(main_expected[0]) / 4) == 0 && zero_difference((u32*)&main_objects[1], 31 * sizeof(main_expected[0]) / 4) == 0 && c_test_word_difference((u32*)effect_objects, (u32*)effects, sizeof(effects[0]) / 4) == 0 && zero_difference((u32*)&effect_objects[1], 31 * sizeof(effects[0]) / 4) == 0 && c_test_word_difference((u32*)&train, (u32*)&train_before, sizeof(train) / 4) == 0 && SP_CUR_MAIN_OBJ == current_before);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0);
    assert(c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0);
    assert(c_test_word_difference((u32*)background_objects, (u32*)backgrounds, sizeof(backgrounds) / 4) == 0);
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons, 2 * sizeof(weapons[0]) / 4) == 0 && zero_difference((u32*)&weapon_objects[2], 14 * sizeof(weapons[0]) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, 2 * sizeof(visuals[0]) / 4) == 0 && zero_difference((u32*)&visual_objects[2], 30 * sizeof(visuals[0]) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_random == rng && need_palette_load == dirty);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && SP_BG_TILEMAP == map && layout_width == 32 && layout_height == 16 && layout_size == 512 && attributes[0] == 0 && attributes[1] == 0x38);
    for (i = 0; i < COUNT(map_words); i += 8)
        assert(((map_words[i] ^ (i == 128 ? 0x0101181E : 0x01010101)) | (map_words[i + 1] ^ 0x01010101) | (map_words[i + 2] ^ 0x01010101) | (map_words[i + 3] ^ 0x01010101) | (map_words[i + 4] ^ 0x01010101) | (map_words[i + 5] ^ 0x01010101) | (map_words[i + 6] ^ 0x01010101) | (map_words[i + 7] ^ 0x01010101)) == 0);
    assert(c_test_word_difference((u32*)tiles, (u32*)tiles_before, sizeof(tiles) / 4) == 0);
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i == 0 ? 64u : (i == 1 || i == 8 || i == 9) ? 128u
                                                                      : 0)
            && frames[i] == (i == 0 ? 64u : i == 1 || i == 5 || i == 16 || i == 17 ? 128u
                                                                                   : 0));
    assert(palette[0] == 0xBEEF && palette[0x151] == 0xBEEF);
    assert(c_test_word_difference((u32*)palette, (u32*)palette_expected, sizeof(palette) / 4) == 0);
    assert(zero_difference((u32*)bank, sizeof(bank) / 4) == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < COUNT(sound_commands); i++)
        assert(sound_commands[i] == 0);
    assert(D_80141F50[1] == sound_commands && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)menu);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(menu); i++)
        assert(menu[i] == (i < 8 ? 64u : 0));
}
static void collide(void)
{
    CollisionRelated(&g_Player);
}
static u32 brake_pause(u32 row)
{
    u32 i;
    (void)row;
    prepare();
    c_test_zero_words((u32*)&train, sizeof(train) / 4);
    train.active = 1;
    train.id = 2;
    train.x_pos.i.hi = 48;
    train.y_pos.i.hi = 304;
    func_800D9268(&train);
    assert(train.state == 1 && train.unk5 == 1 && train.unk7 == 1 && g_Player.script_state == 1);
    for (i = 0; i < 40 && train.unk6 != 2; i++)
        train_tunnel_main(&train);
    assert(train.unk6 == 2 && train.unk17 == 2 && train.unk18.val == 0x80000 && g_Player.script_state == 1);
    for (i = 0; i < 256; i++) {
        assert(train.unk18.val == (s32)(0x80000 - i * 0x800));
        train_tunnel_brake(&train);
    }
    assert(train.unk18.val == 0 && train.unk7 == 0);
    train_tunnel_brake(&train);
    assert(train.unk7 == 1 && train.unk17 == 0 && g_Player.script_state == 0 && engine_obj.gameplay_locked == 0);
    g_Player.x_pos.i.hi = 6660;
    g_Player.unk18 = g_Player.x_pos;
    background_objects[0].x_pos.i.hi = 6500;
    background_objects[0].unk14.i.hi = 6498;
    CollisionRelated(&g_Player);
    assert(g_Player.unk70 == PLAYER_COLLIDE_GROUND);
    main_objects[0].active = 0x41;
    main_objects[0].id = 49;
    main_objects[0].x_pos.i.hi = 6673;
    main_objects[0].y_pos.i.hi = 411;
    SP_CUR_MAIN_OBJ = &main_objects[0];
    func_80068548(&main_objects[0]);
    assert(main_objects[0].state == 1 && main_objects[0].hp == 6);
    SP_CUR_MAIN_OBJ = current_before;
    g_Player.boss_flags = 8;
    g_Player.input.buttons.held = PLAYER_INPUT_UP | PLAYER_INPUT_SPECIAL;
    g_Player.pressed_input = PLAYER_INPUT_SPECIAL;
    player_update_normal(&g_Player);
    g_Player.pressed_input = 0;
    g_Player.input.buttons.previous = g_Player.input.buttons.held;
    for (i = 0; i < 12 && !weapon_objects[0].active; i++)
        player_update_normal(&g_Player);
    assert(weapon_objects[0].active == 1 && weapon_objects[0].id == 35 && g_Player.unk5 == PLAYER_ZERO_RYUENJIN);
    zero_saber_update(&weapon_objects[0]);
    assert(weapon_objects[0].state == 1 && weapon_objects[0].unk50 != NULL);
    assert(func_8002DD04(&main_objects[0]) != 0 && g_Player.update_delay_request == 1);
    player_update();
    assert(g_Player.update_delay == 5 && g_Player.update_delay_request == 0);
    capture();
    train_tunnel_brake(&train);
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "actual_train_braking_release_soldier_saber_hit_and_camera_pause", NULL, NULL, 1, brake_pause } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
