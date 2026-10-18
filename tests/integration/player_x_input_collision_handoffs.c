#include "test_runtime.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/player_animations.h"
#include "main/player_special.h"
#include "main/player_weapon.h"
#include "main/player_check.h"
#include "main/player.h"
#include "main/player_enter.h"
#include "main/player_common.h"
s32 player_check_nova_strike(struct PlayerObj* self);
void player_air_dash(struct PlayerObj*);
void player_enter_air_dash(struct PlayerObj*);
void player_hover(struct PlayerObj*);
void player_wall_jump_push(struct PlayerObj*);
void player_nova_strike(struct PlayerObj*);
void player_update_normal(struct PlayerObj*);
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
static u32 terrain;
static void prepare(u32 mode)
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
    terrain = mode;
    for (i = 0; i < COUNT(tiles); i++)
        tiles[i] = i >= 256 && (mode == 1 ? (i & 15) == 8 : mode == 2 ? (i & 15) == 5 || (i & 15) == 8
                           : mode == 3                                ? (i & 255) / 16 >= 8
                                                                      : 0);
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
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.stage = 4;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    g_Player.active = 0x41;
    g_Player.unk2 = CHARACTER_X;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.x_pos.i.hi = 512;
    g_Player.y_pos.i.hi = 512;
    g_Player.animation_table = (u32**)D_80119DF0;
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
static void collide(void)
{
    CollisionRelated(&g_Player);
    g_Player.unk88.bytes.collision_flags = g_Player.unk70;
}
static void previous(void)
{
    g_Player.unk18 = g_Player.x_pos;
    g_Player.unk1C = g_Player.y_pos;
}
static u32 dash_buster(u32 row)
{
    (void)row;
    prepare(0);
    player_enter_fall(&g_Player);
    g_Player.armor_parts = 8;
    g_Player.pressed_input = PLAYER_INPUT_DASH;
    assert(player_check_air_move(&g_Player) == 1 && g_Player.unk5 == PLAYER_AIR_DASH);
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    capture();
    pose(0x84, 0x28010005, 0);
    expected.attacking = expected.shot_fired = 1;
    expected.last_shot_type = expected.shot_type = 0;
    expected.attack_ended = 0;
    expected.attack_pose_timer = 20;
    expected.shot_cooldown = expected.shot_palette_timer = 6;
    expected.shot_count = expected.shot_cycle = 1;
    expected.x_vel.val = expected.unk28 = expected.y_vel.val = 0;
    expected.unk2C = 0x4200;
    expected.air_state = -1;
    expected.dash_momentum = expected.afterimage = 0;
    expected.unk5 = PLAYER_FALL;
    expected.unk6 = 0;
    weapons[0].active = 1;
    weapons[0].id = 0;
    weapons[0].owner = &g_Player;
    player_air_dash(&g_Player);
    check();
    return 1;
}
static u32 charge_input(u32 row)
{
    u32 i;
    prepare(0);
    (void)row;
    g_Player.arm_type = 1;
    g_Player.armor_parts = 4;
    g_Player.input.buttons.held = PLAYER_INPUT_SHOOT;
    for (i = 0; i < 150; i++)
        player_charge_shoot_button(&g_Player);
    player_update_shot_types(&g_Player);
    assert(g_Player.stock_charge == 4 && g_Player.charge_state[0] == PLAYER_CHARGE_FULL && g_Player.shot_types[0] == 0x13);
    capture();
    expected.flash_palette = 0x2C;
    assert(player_set_charge_flash(&g_Player, 0) == 1);
    check();
    return 1;
}
static void hover_wall_entry(void)
{
    u32 i;
    prepare(1);
    g_Player.x_pos.i.hi = 112;
    g_Player.y_pos.i.hi = 202;
    g_Player.unk15 = 0x40;
    player_enter_fall(&g_Player);
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
    for (i = 0; i < 8 && !(g_Player.unk70 & PLAYER_COLLIDE_RIGHT); i++) {
        previous();
        player_hover(&g_Player);
        collide();
    }
    assert(g_Player.unk6 == 3 && g_Player.unk70 == PLAYER_COLLIDE_RIGHT && g_Player.wall_climbable == 1);
    g_Player.input.buttons.held = 0;
    player_hover(&g_Player);
    assert(g_Player.unk6 == 4);
}
static u32 hover_wall(u32 row)
{
    (void)row;
    hover_wall_entry();
    g_Player.input.buttons.held = PLAYER_INPUT_RIGHT;
    capture();
    pose(0xD, 0x37010003, 0);
    expected.hover_timer--;
    expected.x_vel.val = expected.unk28 = expected.y_vel.val = expected.unk2C = 0;
    expected.dash_momentum = expected.air_action = 0;
    expected.afterimage = -1;
    expected.unk8A.bytes.low = 8;
    expected.unk5 = PLAYER_WALL_CLING;
    expected.unk6 = 0;
    player_hover(&g_Player);
    check();
    return 1;
}
static u32 narrow_wall_kick(u32 row)
{
    u32 i;
    (void)row;
    prepare(2);
    g_Player.x_pos.i.hi = 107;
    g_Player.y_pos.i.hi = 202;
    previous();
    collide();
    assert(g_Player.unk70 == PLAYER_COLLIDE_LEFT && g_Player.wall_climbable == 1);
    g_Player.input.buttons.held = PLAYER_INPUT_LEFT;
    assert(player_check_wall(&g_Player) == 1);
    g_Player.pressed_input = PLAYER_INPUT_JUMP;
    assert(player_check_wall(&g_Player) == 1 && g_Player.unk5 == PLAYER_WALL_JUMP && g_Player.unk6 == 0);
    g_Player.pressed_input = g_Player.input.buttons.held = 0;
    for (i = 0; i < 8 && !(g_Player.unk70 & PLAYER_COLLIDE_RIGHT); i++) {
        previous();
        player_wall_jump_push(&g_Player);
        collide();
    }
    assert(g_Player.unk6 == 0 && g_Player.unk70 == PLAYER_COLLIDE_RIGHT && g_Player.unk8A.bytes.low > 0);
    capture();
    pose(0xB, 0x29010004, 0);
    expected.x_vel.val = expected.unk28 = expected.y_vel.val = 0;
    expected.unk2C = 0x4200;
    expected.air_state = -1;
    expected.unk5 = PLAYER_FALL;
    expected.unk6 = 0;
    player_wall_jump_push(&g_Player);
    check();
    return 1;
}
static u32 nova_early_wall(u32 row)
{
    u32 i;
    (void)row;
    prepare(1);
    g_Player.x_pos.i.hi = 112;
    g_Player.y_pos.i.hi = 202;
    g_Player.unk15 = 0x40;
    player_enter_fall(&g_Player);
    previous();
    collide();
    assert(g_Player.unk70 == 0);
    g_Player.armor_parts = 2;
    g_Player.weapon_energy[0] = 48;
    g_Player.pressed_input = PLAYER_INPUT_GIGA;
    assert(player_check_nova_strike(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 20 && g_Player.unk6 == 0; i++) {
        previous();
        player_nova_strike(&g_Player);
        collide();
    }
    assert(g_Player.unk6 == 1 && g_Player.unk70 == PLAYER_COLLIDE_RIGHT && g_Player.animation_step.packed == 0xD6010003);
    capture();
    expected.animation_step.fields.duration--;
    player_nova_strike(&g_Player);
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "X_actual_air_dash_normal_Buster_enters_fall_shooting", NULL, NULL, 1, dash_buster },
    { "X_actual_stock_charge_flash", NULL, NULL, 1, charge_input },
    { "X_actual_hover_braking_wall_grab", NULL, NULL, 1, hover_wall },
    { "X_actual_narrow_gap_wall_kick_hits_opposite_wall", NULL, NULL, 1, narrow_wall_kick },
    { "X_actual_Nova_windup_wall_contact_before_cancel_event", NULL, NULL, 1, nova_early_wall },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 1 + 1 + 1;
