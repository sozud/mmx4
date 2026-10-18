#include "test_runtime.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/player_animations_2.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/player_special.h"
#include "main/1E1BC.h"
#include "main/player_enter.h"
#include "main/player_common.h"
#include "main/55C4.h"
void player_update_normal(struct PlayerObj*);
void player_update(void);
void zero_saber_update(struct WeaponObj*);
void frost_walrus_fx_update(struct VisualObj*);
void frost_walrus_regrow_start(struct MainObj*);
void sigma_final_laser_start(struct MainObj*);
void sigma_sequencer_fx_update(struct EffectObj*);
extern void* frost_walrus_animations[39];
extern void* sigma_final_animations[39];
extern struct Unk_unk68 frost_walrus_hurt_box, frost_walrus_terrain_box, D_80105368, D_80108284[];
extern struct EffectObj* sigma_sequencer;
static u32 gfx[64], frames[64], attributes[2];
static u32 map_words[384];
#define map ((u8*)map_words)
static u16 tiles[512], tiles_before[512], palette[0x152], palette_expected[0x152];
static u8 sound_commands[32];
static Palette bank[40];
static struct MainObj main_expected[32];
static struct EffectObj effects[32];
static struct EffectObj* sequencer;
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
static void prepare(u32 row)
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
        tiles[i] = i >= 256 && (i & 255) / 16 >= (row ? 6 : 14);
    c_test_copy_words((u32*)tiles_before, (u32*)tiles, sizeof(tiles) / 4);
    attributes[0] = 0;
    attributes[1] = 0x38;
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
    engine_obj.stage = row ? 12 : 2;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    g_Player.active = 0x41;
    g_Player.unk2 = 1;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.x_pos.i.hi = row ? 1383 : 7250;
    g_Player.y_pos.i.hi = row ? 586 : 458;
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
    background_objects[0].x_pos.i.hi = row ? 0x410 : 7128;
    background_objects[0].y_pos.i.hi = row ? 512 : 256;
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
    sequencer = sigma_sequencer;
    input = controller_input;
    dirty = need_palette_load;
    rng = cur_random;
}
static void check(void)
{
    u32 i;
    assert(zero_difference((u32*)misc_objects, sizeof(misc_objects) / 4) == 0 && zero_difference((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4) == 0 && c_test_word_difference((u32*)main_objects, (u32*)main_expected, sizeof(main_expected[0]) / 4) == 0 && zero_difference((u32*)&main_objects[1], 31 * sizeof(main_expected[0]) / 4) == 0 && c_test_word_difference((u32*)effect_objects, (u32*)effects, sizeof(effects[0]) / 4) == 0 && zero_difference((u32*)&effect_objects[1], 31 * sizeof(effects[0]) / 4) == 0 && sigma_sequencer == sequencer);
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
        assert(((map_words[i] ^ 0x01010101) | (map_words[i + 1] ^ 0x01010101) | (map_words[i + 2] ^ 0x01010101) | (map_words[i + 3] ^ 0x01010101) | (map_words[i + 4] ^ 0x01010101) | (map_words[i + 5] ^ 0x01010101) | (map_words[i + 6] ^ 0x01010101) | (map_words[i + 7] ^ 0x01010101)) == 0);
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
    assert(D_80141F50[1] == sound_commands);
}
static void collide(void)
{
    CollisionRelated(&g_Player);
}
static u32 hit_stop(u32 row)
{
    struct MainObj* boss = &main_objects[0];
    u32 i;
    prepare(row);
    boss->active = 0x41;
    boss->id = row ? 74 : 57;
    boss->state = 1;
    boss->hp = 48;
    boss->unk5 = row ? 9 : 11;
    boss->unk42 = 0x7800;
    boss->x_pos.i.hi = row ? 1383 : 7288;
    boss->y_pos.i.hi = row ? 647 : 414;
    boss->animation_table = (const u8* const*)(row ? sigma_final_animations : frost_walrus_animations);
    boss->sprite_frames = (u8*)frames + 128;
    if (row) {
        boss->hurt_box = (u8*)&D_80105368;
        boss->collision_data = (u16*)D_80108284;
        boss->ext.main_74.target = 1;
        boss->ext.main_74.upper_health = 48;
        set_animation(boss, 0);
        sigma_final_laser_start(boss);
        assert(effect_objects[0].active == 1 && effect_objects[0].id == 42 && effect_objects[0].ext.effect_42.owner.main == boss);
        sigma_sequencer_fx_update(&effect_objects[0]);
        assert(effect_objects[0].state == 2 && boss->ext.main_73_parts.effect_state == 1);
    } else {
        boss->hurt_box = (u8*)&frost_walrus_hurt_box;
        boss->terrain_box = &frost_walrus_terrain_box;
        boss->collision_data = (u16*)D_80107A78;
        set_animation(boss, 0);
        frost_walrus_regrow_start(boss);
        assert(visual_objects[0].active == 0x41 && visual_objects[0].id == 24 && visual_objects[0].unk2 == 0x20);
        frost_walrus_fx_update(&visual_objects[0]);
        assert(visual_objects[0].state == 1 && visual_objects[0].unk5 == 2);
    }
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
    assert(func_8002DD04(boss) != 0 && g_Player.update_delay_request == 1 && g_Player.update_delay == 0);
    player_update();
    assert(g_Player.update_delay == 5 && g_Player.update_delay_request == 0);
    capture();
    if (row)
        sigma_sequencer_fx_update(&effect_objects[0]);
    else {
        visuals[0].on_screen = 1;
        visuals[0].unk42 = boss->unk42;
        frost_walrus_fx_update(&visual_objects[0]);
    }
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "real_Ryuenjin_hit_stop_Walrus_regrowth_and_Sigma_sequencer", NULL, NULL, 2, hit_stop } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
