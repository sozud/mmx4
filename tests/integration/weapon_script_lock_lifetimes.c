#include "test_runtime.h"
#include "main/collision.h"
#include "main/player_animations.h"
#include "main/player_animations_2.h"
#include "main/player_weapon.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/player_special.h"
#include "main/player_enter.h"
#include "main/player_common.h"
void train_scroll_init(struct LayerObj*);
void train_scroll_main(struct LayerObj*);
void player_update_normal(struct PlayerObj*);
void twin_slasher_update(struct WeaponObj*);
void twin_slasher_charged_update(struct WeaponObj*);
void zero_saber_update(struct WeaponObj*);
void double_cyclone_charged_update(struct WeaponObj*);
static u32 gfx[64], frames[64], attributes[2];
static u32 map_words[192];
#define map ((u8*)map_words)
static u16 tiles[512], tiles_before[512], palette[0x152], palette_expected[0x152];
static u8 sound_commands[32];
static Palette bank[40];
static const u32 bank_zero[320];
static struct MiscObj misc[64];
static struct LayerObj train, train_before;
static struct PlayerObj expected, entity;
static struct EngineObj engine;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds[3];
static struct WeaponObj weapons[16];
static struct VisualObj visuals[32];
static struct ControllerInput input;
static u8 dirty;
static u16 rng;
static void prepare(u32 character)
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
        tiles[i] = i >= 256 && (i & 255) / 16 >= 14;
    c_test_copy_words((u32*)tiles_before, (u32*)tiles, sizeof(tiles) / 4);
    attributes[0] = 0;
    attributes[1] = 0x38;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    c_test_zero_words((u32*)(bank), sizeof(bank) / 4);
    c_test_zero_words((u32*)(palette), sizeof(palette) / 4);
    palette[0] = palette[0x151] = palette_expected[0] = palette_expected[0x151] = 0xBEEF;
    TEST_PALETTE_BANK = (u8*)bank;
    TEST_PALETTE = (u8*)&palette[1];
    engine_obj.cur_character = character;
    engine_obj.stage = 8;
    engine_obj.substage = 0;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    g_Player.active = 0x41;
    g_Player.unk2 = character;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.x_pos.i.hi = 2254;
    g_Player.y_pos.i.hi = character ? 202 : 203;
    g_Player.unk15 = 0x40;
    g_Player.animation_table = (u32**)(character ? D_8011AFF0 : D_80119DF0);
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
    background_objects[0].x_pos.i.hi = 2192;
    c_test_zero_words((u32*)(&train), sizeof(train) / 4);
    train.active = 1;
    train.id = 0;
    train.x_pos.i.hi = 768;
    train.y_pos.i.hi = 304;
    train_scroll_init(&train);
    assert(train.state == 1 && train.unk5 == 0 && train.unk6 == 1 && engine_obj.gameplay_locked == 0);
}
static void capture(void)
{
    expected = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds, (u32*)background_objects, sizeof(backgrounds) / 4);
    c_test_copy_words((u32*)weapons, (u32*)weapon_objects, sizeof(weapons) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    c_test_copy_words((u32*)misc, (u32*)misc_objects, sizeof(misc) / 4);
    train_before = train;
    input = controller_input;
    dirty = need_palette_load;
    rng = cur_random;
}
static void check(void)
{
    u32 i;
    assert(c_test_word_difference((u32*)misc_objects, (u32*)misc, sizeof(misc) / 4) == 0 && c_test_word_difference((u32*)&train, (u32*)&train_before, sizeof(train) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0);
    assert(c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0);
    assert(c_test_word_difference((u32*)background_objects, (u32*)backgrounds, sizeof(backgrounds) / 4) == 0);
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_random == rng && need_palette_load == dirty);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && SP_BG_TILEMAP == map && layout_width == 16 && layout_height == 16 && layout_size == 256 && attributes[0] == 0 && attributes[1] == 0x38);
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
    assert(c_test_word_difference((u32*)bank, bank_zero, sizeof(bank) / 4) == 0);
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
static void shoot(u32 weapon, u32 charged)
{
    u32 i;
    g_Player.weapon = weapon;
    g_Player.boss_flags = 1u << (weapon - 1);
    g_Player.weapon_energy[weapon] = 48;
    g_Player.input.buttons.held = PLAYER_INPUT_SHOOT;
    if (charged) {
        g_Player.armor_parts = 4;
        for (i = 0; i < 90; i++)
            player_charge_shoot_button(&g_Player);
        assert(g_Player.charge_state[0] == PLAYER_CHARGE_FULL);
        g_Player.input.buttons.previous = PLAYER_INPUT_SHOOT;
        g_Player.input.buttons.held = 0;
        g_Player.pressed_input = 0;
    } else {
        g_Player.input.buttons.previous = 0;
        g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    }
    player_update_normal(&g_Player);
    g_Player.pressed_input = 0;
    g_Player.input.buttons.previous = g_Player.input.buttons.held;
    assert(g_Player.shot_fired == 1 && g_Player.last_shot_type == weapon + (charged ? 9 : 0));
}
static void weapon_tick(u32 kind, u32 index)
{
    if (kind == 0)
        twin_slasher_update(&weapon_objects[index]);
    else if (kind == 1)
        twin_slasher_charged_update(&weapon_objects[index]);
    else
        zero_saber_update(&weapon_objects[index]);
}
static void approach_train_lock(u32 kind, u32 count)
{
    u32 i, j;
    if (kind < 2) {
        g_Player.input.buttons.previous = g_Player.input.buttons.held;
        g_Player.input.buttons.held |= PLAYER_INPUT_RIGHT;
        g_Player.pressed_input = PLAYER_INPUT_RIGHT;
    }
    for (i = 0; i < 40 && g_Player.input_locked == 0; i++) {
        player_update_normal(&g_Player);
        g_Player.pressed_input = 0;
        g_Player.input.buttons.previous = g_Player.input.buttons.held;
        collide();
        train_scroll_main(&train);
        if (g_Player.input_locked == 0)
            for (j = 0; j < count; j++)
                if (weapon_objects[j].active)
                    weapon_tick(kind, j);
    }
    assert(g_Player.input_locked == 1 && g_Player.script_action == PLAYER_SCRIPT_WAIT && engine_obj.gameplay_locked == 1 && train.unk5 == 1 && train.unk6 == 1 && g_Player.x_pos.i.hi >= 2256 && g_Player.x_pos.i.hi <= 2272 && weapon_objects[0].active != 0);
}
static u32 twin_lock(u32 row)
{
    u32 i, count = row ? 8 : 2;
    prepare(0);
    shoot(8, row);
    for (i = 0; i < count; i++) {
        assert(weapon_objects[i].active == 1 && weapon_objects[i].id == (row ? 17 : 8) && weapon_objects[i].unk2 == i);
        weapon_tick(row, i);
        assert(weapon_objects[i].state == 1);
    }
    approach_train_lock(row, count);
    capture();
    expected.shot_count--;
    expected.special_shot_count--;
    memset(&weapons[0], 0, 8);
    weapons[0].unk50 = NULL;
    weapon_tick(row, 0);
    check();
    return 1;
}
static u32 saber_lock(u32 row)
{
    u32 i;
    (void)row;
    prepare(1);
    g_Player.boss_flags = 8;
    g_Player.input.buttons.held = PLAYER_INPUT_UP | PLAYER_INPUT_SPECIAL;
    g_Player.pressed_input = PLAYER_INPUT_SPECIAL;
    player_update_normal(&g_Player);
    g_Player.pressed_input = 0;
    g_Player.input.buttons.previous = g_Player.input.buttons.held;
    for (i = 0; i < 12 && weapon_objects[0].active == 0; i++) {
        player_update_normal(&g_Player);
        collide();
        train_scroll_main(&train);
    }
    assert(g_Player.unk5 == PLAYER_ZERO_RYUENJIN && weapon_objects[0].active == 1 && weapon_objects[0].id == 35);
    zero_saber_update(&weapon_objects[0]);
    assert(weapon_objects[0].state == 1);
    approach_train_lock(2, 1);
    assert(weapon_objects[0].unk84.word == g_Player.unk17);
    capture();
    memset(&weapons[0], 0, 8);
    zero_saber_update(&weapon_objects[0]);
    check();
    return 1;
}
static u32 cyclone_expiry(u32 row)
{
    u32 i;
    (void)row;
    prepare(0);
    shoot(7, 1);
    for (i = 0; i < 16 && weapon_objects[4].active == 0; i++)
        player_update_normal(&g_Player);
    assert(weapon_objects[4].active == 1 && weapon_objects[4].id == 16 && weapon_objects[4].unk2 == 4);
    double_cyclone_charged_update(&weapon_objects[4]);
    assert(weapon_objects[4].state == 1 && weapon_objects[4].ext.weapon_16.timer == 50);
    for (i = 0; i < 50; i++) {
        double_cyclone_charged_update(&weapon_objects[4]);
        assert(weapon_objects[4].state == 1);
    }
    assert(weapon_objects[4].ext.weapon_16.timer == 0 && g_Player.input_locked == 0 && g_Player.weapon == 7);
    capture();
    weapons[4].on_screen = 0;
    weapons[4].state = 3;
    weapons[4].unk50 = NULL;
    double_cyclone_charged_update(&weapon_objects[4]);
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "X_real_Twin_Slasher_shots_and_train_script_lock", NULL, NULL, 2, twin_lock },
    { "Zero_real_Ryuenjin_saber_and_train_script_lock", NULL, NULL, 1, saber_lock },
    { "X_real_charged_Cyclone_nonzero_fan_50_tick_expiry", NULL, NULL, 1, cyclone_expiry },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1 + 1;
