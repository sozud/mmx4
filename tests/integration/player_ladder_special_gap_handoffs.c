#include "test_runtime.h"
#include "main/player_animations.h"
#include "main/player_animations_2.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/player_special.h"
#include "main/player_enter.h"
#include "main/player_common.h"
#include "main/player_weapon.h"
s32 player_check_nova_strike(struct PlayerObj* self);
void player_settle(struct PlayerObj*);
void player_land(struct PlayerObj*);
void player_ladder_shoot(struct PlayerObj*);
void player_update_normal(struct PlayerObj*);
void player_ladder_grab(struct PlayerObj*);
static u32 gfx[64], frames[64], attributes[2];
static u8 map[3 * 256];
static u16 tiles[512], palette[0x152];
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
static u32 terrain;
static void prepare(u32 character, u32 tile)
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
    gfx[1] = frames[5] = 128;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    memset(map, 1, sizeof(map));
    memset(tiles, 0, sizeof(tiles));
    terrain = tile;
    attributes[0] = tile;
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
    player_set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = 0x1234;
}
static void capture(void)
{
    expected = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    memcpy(weapons, weapon_objects, sizeof(weapons));
    memcpy(visuals, visual_objects, sizeof(visuals));
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
    c_test_same_words(&g_Player, &expected, sizeof(expected));
    c_test_same_words(&g_Entity, &entity, sizeof(entity));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_random == rng && need_palette_load == dirty);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && SP_BG_TILEMAP == map && layout_width == 16 && layout_height == 16 && layout_size == 256 && attributes[0] == terrain && attributes[1] == 0x38);
    for (i = 0; i < COUNT(map); i++)
        assert(map[i] == 1);
    for (i = 0; i < COUNT(tiles); i++)
        assert(tiles[i] == 0);
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i == 0 ? 64u : i == 1 ? 128u
                                                : 0)
            && frames[i] == (i == 0 ? 64u : i == 5 ? 128u
                                                   : 0));
    assert(palette[0] == 0xBEEF && palette[0x151] == 0xBEEF);
    for (i = 1; i < 0x151; i++)
        assert(palette[i] == 0);
    for (i = 0; i < 48; i++)
        assert(((u16*)bank)[i] == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}
static void grab(void)
{
    pose(0x1B, 0xC2010003, 0);
    expected.x_pos.i.hi = (expected.x_pos.u.hi & 0xFFF0) + 8;
    expected.x_pos.u.lo = expected.y_pos.u.lo = 0;
    expected.x_vel.val = expected.unk28 = expected.unk2C = 0;
    expected.y_vel.val = 0x10000;
    expected.air_state = 1;
    expected.dash_momentum = expected.air_action = 0;
    if (expected.afterimage > 0)
        expected.afterimage = -1;
    expected.attacking = expected.shot_fired = expected.attack_ended = expected.attack_pose_timer = expected.shot_cooldown = expected.shot_palette_timer = 0;
    expected.unk5 = PLAYER_LADDER_TRANSITION;
    expected.unk6 = 0;
    dirty |= 1;
}
static u32 ground_ladder(u32 row)
{
    u32 i;
    prepare(1, 0x20);
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    if (row == 0)
        player_enter_stand(&g_Player);
    else if (row == 1)
        player_enter_land(&g_Player);
    else {
        g_Player.pressed_input = PLAYER_INPUT_SHOOT;
        assert(player_zero_check_saber(&g_Player) == 1);
        g_Player.pressed_input = 0;
        for (i = 0; i < 40 && !(g_Player.animation_step.fields.event & 0x40); i++)
            player_zero_saber(&g_Player);
        assert(g_Player.animation_step.packed == 0x52014002);
    }
    g_Player.input.buttons.held = PLAYER_INPUT_UP;
    capture();
    grab();
    if (row == 0)
        player_settle(&g_Player);
    else if (row == 1)
        player_land(&g_Player);
    else
        player_zero_saber(&g_Player);
    check();
    return 1;
}
static void enter_ladder(void)
{
    u32 i;
    g_Player.input.buttons.held = PLAYER_INPUT_UP;
    assert(player_check_ladder(&g_Player) == 1);
    for (i = 0; i < 12 && g_Player.unk5 == PLAYER_LADDER_TRANSITION; i++)
        player_ladder_grab(&g_Player);
    assert(g_Player.unk5 == PLAYER_LADDER_UP && g_Player.air_state == 1);
    g_Player.input.buttons.held = 0;
}
static void buster_on_ladder(void)
{
    u32 i;
    prepare(0, 0x20);
    g_Player.unk15 = 0x40;
    enter_ladder();
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    assert(player_check_shoot_ladder(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 6; i++)
        player_update_normal(&g_Player);
    assert(g_Player.unk5 == PLAYER_LADDER_SHOOT && g_Player.shot_cooldown == 0 && g_Player.attack_pose_timer == 14 && g_Player.animation_step.packed == 0x9B010002 && g_Player.shot_count == 1);
}
static u32 ladder_input(u32 row)
{
    (void)row;
    buster_on_ladder();
    g_Player.pressed_input = PLAYER_INPUT_LEFT;
    capture();
    expected.shot_type = -1;
    expected.animation_step.fields.duration--;
    expected.unk15 = 0;
    player_ladder_shoot(&g_Player);
    check();
    return 1;
}
static u32 charged_ladder_pose(u32 row)
{
    u32 i;
    (void)row;
    prepare(0, 0x20);
    enter_ladder();
    g_Player.weapon = 6;
    g_Player.armor_parts = 4;
    g_Player.arm_type = 1;
    g_Player.weapon_energy[6] = 48;
    g_Player.input.buttons.held = PLAYER_INPUT_SHOOT;
    for (i = 0; i < 90; i++)
        player_charge_shoot_button(&g_Player);
    assert(g_Player.charge_state[0] == PLAYER_CHARGE_FULL);
    player_update_shot_types(&g_Player);
    g_Player.input.buttons.held = 0;
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    capture();
    pose(0x5D, 0x960100F2, 0);
    expected.shot_type = expected.last_shot_type = 15;
    expected.attacking = expected.shot_fired = 1;
    expected.attack_ended = 0;
    expected.attack_pose_timer = expected.shot_cooldown = 250;
    expected.special_shot_count = 1;
    expected.shot_cycle = 1;
    expected.weapon_energy[6] = 36;
    expected.unk5 = PLAYER_LADDER_SHOOT;
    expected.unk6 = 0;
    weapons[0].active = 1;
    weapons[0].id = 15;
    weapons[0].owner = &g_Player;
    assert(player_check_shoot_ladder(&g_Player) == 1);
    check();
    return 1;
}
static u32 ground_giga(u32 row)
{
    (void)row;
    prepare(1, 0);
    player_enter_stand(&g_Player);
    g_Player.boss_flags = 0x20;
    g_Player.weapon_energy[0] = 12;
    g_Player.pressed_input = PLAYER_INPUT_GIGA;
    capture();
    pose(0x67, 0xB1010004, 1);
    expected.attacking = 1;
    expected.combo = expected.afterimage = 0;
    expected.air_state = expected.spike_immune = 1;
    expected.weapon_energy[0] = 0;
    expected.unk5 = PLAYER_ZERO_RAKUHOUHA;
    expected.unk6 = 0;
    dirty |= 1;
    player_settle(&g_Player);
    check();
    return 1;
}
static u32 blocked_ice_slash(u32 row)
{
    (void)row;
    prepare(1, 0);
    player_enter_fall(&g_Player);
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    assert(player_zero_check_fall_slash(&g_Player) == 1);
    g_Player.boss_flags = 2;
    g_Player.input.buttons.held = PLAYER_INPUT_DOWN;
    g_Player.pressed_input = PLAYER_INPUT_SPECIAL;
    capture();
    assert(player_zero_check_fall_slash(&g_Player) == 0);
    check();
    return 1;
}
static u32 low_nova(u32 row)
{
    (void)row;
    prepare(0, 0);
    g_Player.armor_parts = 2;
    g_Player.weapon_energy[0] = 47;
    g_Player.pressed_input = PLAYER_INPUT_GIGA;
    capture();
    assert(player_check_nova_strike(&g_Player) == 0);
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "Zero_actual_settle_land_and_saber_recovery_grab_ladder", NULL, NULL, 3, ground_ladder },
    { "X_actual_ladder_buster_six_normal_updates_then_Left", NULL, NULL, 1, ladder_input },
    { "X_actual_90_tick_charged_aiming_laser_ladder_pose", NULL, NULL, 1, charged_ladder_pose },
    { "Zero_actual_Rakuhouha_input_during_settle", NULL, NULL, 1, ground_giga },
    { "Zero_actual_fall_saber_rejects_down_special_during_attack", NULL, NULL, 1, blocked_ice_slash },
    { "X_Nova_Strike_input_with_less_than_full_energy", NULL, NULL, 1, low_nova },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + 1 + 1 + 1 + 1 + 1;
