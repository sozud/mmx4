#include "test_runtime.h"
#include "main/player_animations.h"
#include "main/player_animations_2.h"
#include "main/player_special.h"
#include "main/player_check.h"
#include "main/player.h"
#include "main/player_enter.h"
#include "main/player_common.h"
#include "main/player_weapon.h"
void player_hover(struct PlayerObj*);
void player_zero_saber(struct PlayerObj*);
void func_80058740(struct MainObj*);
void dash_gunner_wait_for_player(struct MainObj*);
void soul_body_init(struct WeaponObj*);
void soul_body_main(struct WeaponObj*);
extern struct Unk_unk68 dash_gunner_boxes[10];
extern struct Unk_unk68 *D_8013B828, *D_8013B82C, *D_8013B830, *D_8013B834;
static u32 gfx[64], frames[64], attributes[2];
static u8 map[3 * 256];
static u16 tiles[512], tiles_before[512], palette[0x152];
static u8 sound_commands[32];
static Palette bank[3];
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
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    memset(gfx, 0, sizeof(gfx));
    memset(frames, 0, sizeof(frames));
    gfx[0] = frames[0] = 64;
    gfx[1] = frames[1] = frames[5] = 128;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    memset(map, 1, sizeof(map));
    memset(tiles, 0, sizeof(tiles));
    c_test_copy_words((u32*)tiles_before, (u32*)tiles, sizeof(tiles) / 4);
    attributes[0] = 0;
    attributes[1] = 0x38;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(bank, 0, sizeof(bank));
    memset(palette, 0, sizeof(palette));
    palette[0] = palette[0x151] = 0xBEEF;
    TEST_PALETTE_BANK = (u8*)bank;
    TEST_PALETTE = (u8*)&palette[1];
    engine_obj.cur_character = character;
    engine_obj.stage = 4;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    g_Player.active = 0x41;
    g_Player.unk2 = character;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.x_pos.i.hi = 512;
    g_Player.y_pos.i.hi = 512;
    g_Player.animation_table = (u32**)(character ? D_8011AFF0 : D_80119DF0);
    g_Player.unk38 = (u8*)gfx + 64;
    player_enter_idle(&g_Player);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = 0x1234;
    memset(sound_commands, 0, sizeof(sound_commands));
    D_80141F50[1] = sound_commands;
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
    input = controller_input;
    dirty = need_palette_load;
    rng = cur_random;
}
static void pose(u32 animation, u32 word, u32 saber_bank)
{
    expected.unk17 = animation;
    expected.previous_animation_index = 255;
    expected.animation_cursor = expected.animation_table[animation];
    expected.animation_step.packed = word;
    expected.unk38 = (u8*)gfx + (saber_bank ? 128 : 64);
    expected.unk3C = (u8*)frames + (saber_bank ? 128 : 64);
}
static void check(void)
{
    u32 i;
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0);
    assert(c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0);
    assert(c_test_word_difference((u32*)background_objects, (u32*)backgrounds, sizeof(backgrounds) / 4) == 0);
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_random == rng && need_palette_load == dirty);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && SP_BG_TILEMAP == map && layout_width == 16 && layout_height == 16 && layout_size == 256 && attributes[0] == 0 && attributes[1] == 0x38);
    for (i = 0; i < COUNT(map); i++)
        assert(map[i] == 1);
    assert(c_test_word_difference((u32*)tiles, (u32*)tiles_before, sizeof(tiles) / 4) == 0);
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i == 0 ? 64u : i == 1 ? 128u
                                                : 0)
            && frames[i] == (i == 0 ? 64u : i == 1 || i == 5 ? 128u
                                                             : 0));
    assert(palette[0] == 0xBEEF && palette[0x151] == 0xBEEF);
    for (i = 1; i < 0x151; i++)
        assert(palette[i] == 0);
    for (i = 0; i < 48; i++)
        assert(((u16*)bank)[i] == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < COUNT(sound_commands); i++)
        assert(sound_commands[i] == 0);
    assert(D_80141F50[1] == sound_commands);
}
static u32 hover_cancel(u32 row)
{
    u32 i;
    (void)row;
    prepare(0);
    player_enter_fall(&g_Player);
    g_Player.unk15 = 0x40;
    g_Player.armor_parts = 8;
    g_Player.pressed_input = PLAYER_INPUT_JUMP;
    assert(player_check_hover(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 12 && g_Player.unk6 == 0; i++)
        player_hover(&g_Player);
    assert(g_Player.unk6 == 1);
    g_Player.input.buttons.held = PLAYER_INPUT_RIGHT;
    player_hover(&g_Player);
    assert(g_Player.unk6 == 3);
    g_Player.input.buttons.held = 0;
    player_hover(&g_Player);
    assert(g_Player.unk6 == 4);
    for (i = 0; i < 12 && g_Player.unk6 == 4; i++)
        player_hover(&g_Player);
    assert(g_Player.unk6 == 2 && g_Player.hover_timer > 1);
    g_Player.pressed_input = PLAYER_INPUT_JUMP;
    capture();
    pose(0xB, 0x29010004, 0);
    expected.hover_timer--;
    expected.x_vel.val = expected.unk28 = expected.y_vel.val = 0;
    expected.unk2C = 0x4200;
    expected.air_state = -1;
    expected.unk5 = PLAYER_FALL;
    expected.unk6 = 0;
    player_hover(&g_Player);
    check();
    return 1;
}
static u32 saber_ryuenjin(u32 row)
{
    u32 i;
    (void)row;
    prepare(1);
    g_Player.boss_flags = 8;
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    assert(player_zero_check_saber(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 12 && g_Player.animation_step.packed != 0x47010001; i++)
        player_zero_saber(&g_Player);
    assert(g_Player.animation_step.packed == 0x47010001 && g_Player.attacking == 1 && g_Player.unk5 == PLAYER_ZERO_SABER);
    g_Player.input.buttons.held = PLAYER_INPUT_UP;
    g_Player.pressed_input = PLAYER_INPUT_SPECIAL;
    capture();
    pose(0x65, 0x56010001, 1);
    expected.attacking = expected.air_state = expected.spike_immune = 1;
    expected.combo = expected.afterimage = 0;
    expected.unk5 = PLAYER_ZERO_RYUENJIN;
    expected.unk6 = 0;
    player_zero_saber(&g_Player);
    check();
    return 1;
}
static u32 gunner_wait(u32 row)
{
    struct MainObj actor, before;
    (void)row;
    prepare(0);
    engine_obj.stage = 12;
    engine_obj.substage = 0;
    g_Player.x_pos.i.hi = 1960;
    g_Player.y_pos.i.hi = 1112;
    memset(&actor, 0, sizeof(actor));
    actor.active = 0x41;
    actor.id = 27;
    actor.unk2 = 5;
    actor.x_pos.i.hi = 1760;
    actor.y_pos.i.hi = 1112;
    func_80058740(&actor);
    assert(actor.state == 1 && actor.unk5 == 3 && actor.ext.main_27.unk80 == 0 && actor.unk7A == 1);
    assert(D_8013B828 == &dash_gunner_boxes[5] && D_8013B82C == &dash_gunner_boxes[6] && D_8013B830 == &dash_gunner_boxes[8] && D_8013B834 == &dash_gunner_boxes[7]);
    before = actor;
    before.unk7A = 0;
    before.unk5 = 2;
    before.unk6 = 0;
    capture();
    dash_gunner_wait_for_player(&actor);
    check();
    assert(c_test_word_difference((u32*)&actor, (u32*)&before, sizeof(actor) / 4) == 0);
    assert(D_8013B828 == &dash_gunner_boxes[5] && D_8013B82C == &dash_gunner_boxes[6] && D_8013B830 == &dash_gunner_boxes[8] && D_8013B834 == &dash_gunner_boxes[7]);
    return 1;
}
static u32 soul_left(u32 row)
{
    (void)row;
    prepare(0);
    memset(background_objects, 0, sizeof(background_objects));
    player_enter_fall(&g_Player);
    g_Player.weapon = 3;
    g_Player.boss_flags = 4;
    g_Player.weapon_energy[3] = 48;
    player_update_shot_types(&g_Player);
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    assert(player_check_shoot_air(&g_Player) == 0 && g_Player.shot_fired == 1 && weapon_objects[0].active == 1 && weapon_objects[0].id == 3);
    soul_body_init(&weapon_objects[0]);
    assert(weapon_objects[0].state == 1 && weapon_objects[0].unk5 == 0 && weapon_objects[0].unk15 == 0 && weapon_objects[0].ext.weapon_3.offset == 0);
    capture();
    weapons[0].ext.weapon_3.offset = 8;
    weapons[0].ext.weapon_3.unk91 = 7;
    weapons[0].on_screen = 0;
    soul_body_main(&weapon_objects[0]);
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "X_actual_hover_hold_Jump_cancels_to_fall", NULL, NULL, 1, hover_cancel },
    { "Zero_own_saber_combo_window_Up_Special_starts_Ryuenjin", NULL, NULL, 1, saber_ryuenjin },
    { "Original_stage12_gunner5_wait_enters_ordinary_run", NULL, NULL, 1, gunner_wait },
    { "X_actual_Soul_Body_spawn_and_left_extension", NULL, NULL, 1, soul_left },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 1 + 1;
