#include "test_runtime.h"
#include "main/collision.h"
#include "main/player_animations.h"
#include "main/player_weapon.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/player_special.h"
#include "main/player_enter.h"
#include "main/player_common.h"
#include "main/sprite_animations.h"
void player_update_normal(struct PlayerObj*);
void dash_dust_update(struct VisualObj*);
void wall_slide_dust_update(struct VisualObj*);
void aiming_laser_charged_update(struct WeaponObj*);
void func_800961B0(struct WeaponObj*);
void player_update_init(struct PlayerObj*);
static u32 gfx[64], frames[64], attributes[2];
static u32 map_words[192];
#define map ((u8*)map_words)
static u16 tiles[512], tiles_before[512], palette[0x152], palette_expected[0x152];
static u8 sound_commands[32];
static Palette bank[40];
static struct QuadObj quads[32];
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
static void prepare(u32 wall)
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
        tiles[i] = i >= 256 && ((i & 255) / 16 >= 14 || (wall && (i & 15) == 14));
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
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    engine_obj.cur_character = 0;
    engine_obj.stage = 8;
    engine_obj.substage = 0;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    g_Player.active = 0x41;
    g_Player.unk2 = 0;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.x_pos.i.hi = wall ? 208 : 160;
    g_Player.y_pos.i.hi = 203;
    g_Player.unk15 = 0x40;
    g_Player.animation_table = (u32**)D_80119DF0;
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
    c_test_copy_words((u32*)quads, (u32*)g_QuadObjects, 4 * sizeof(quads[0]) / 4);
    input = controller_input;
    dirty = need_palette_load;
    rng = cur_random;
}
static void check(void)
{
    u32 i;
    assert(zero_difference((u32*)misc_objects, sizeof(misc_objects) / 4) == 0 && c_test_word_difference((u32*)g_QuadObjects, (u32*)quads, 4 * sizeof(quads[0]) / 4) == 0 && zero_difference((u32*)&g_QuadObjects[4], 28 * sizeof(quads[0]) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&expected, sizeof(expected) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0);
    assert(c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0);
    assert(c_test_word_difference((u32*)background_objects, (u32*)backgrounds, sizeof(backgrounds) / 4) == 0);
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons, 2 * sizeof(weapons[0]) / 4) == 0 && zero_difference((u32*)&weapon_objects[2], 14 * sizeof(weapons[0]) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, 2 * sizeof(visuals[0]) / 4) == 0 && zero_difference((u32*)&visual_objects[2], 30 * sizeof(visuals[0]) / 4) == 0);
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
static void entity_tick(u32 held)
{
    g_Entity.unk18 = g_Entity.x_pos;
    g_Entity.unk1C = g_Entity.y_pos;
    g_Entity.pressed_input = held & ~g_Entity.input.buttons.held;
    g_Entity.input.buttons.previous = g_Entity.input.buttons.held;
    g_Entity.input.buttons.held = held;
    player_update_normal(&g_Entity);
    CollisionRelated(&g_Entity);
}
static void clone_birth(u32 wall)
{
    u32 i;
    prepare(wall);
    shoot(3, 1);
    for (i = 0; i < 16 && !g_Entity.active; i++)
        player_update_normal(&g_Player);
    assert(g_Player.controlling_clone == 1 && g_Player.unk5 == PLAYER_SOUL_BODY && g_Entity.active == 1 && g_Entity.is_clone == 1 && g_Entity.clone_timer == 240);
    player_update_init(&g_Entity);
    for (i = 0; i < 20 && g_Entity.unk5 == PLAYER_SOUL_BODY_CLONE; i++)
        entity_tick(0);
    for (i = 0; i < 12 && g_Entity.air_state != 0; i++)
        entity_tick(0);
    assert(g_Entity.state == PLAYER_STATE_NORMAL && g_Entity.air_state == 0 && g_Player.controlling_clone == 1);
}
static u32 clone_dust(u32 row)
{
    struct VisualObj* visual;
    u32 i, slot;
    clone_birth(row);
    if (row)
        entity_tick(PLAYER_INPUT_JUMP | PLAYER_INPUT_RIGHT);
    for (i = 0; i < 40; i++) {
        for (slot = 0; slot < COUNT(visual_objects); slot++)
            if (visual_objects[slot].active && visual_objects[slot].id == (row ? 0 : 1))
                break;
        if (slot < COUNT(visual_objects))
            break;
        entity_tick(PLAYER_INPUT_RIGHT | (row ? PLAYER_INPUT_JUMP : PLAYER_INPUT_DASH));
    }
    assert(slot < COUNT(visual_objects));
    visual = &visual_objects[slot];
    assert(visual->active == 0x21 && visual->id == (row ? 0 : 1) && visual->state == 0 && g_Entity.active == 1 && g_Player.controlling_clone == 1);
    capture();
    visuals[slot].on_screen = 1;
    visuals[slot].unk38 = 0;
    visuals[slot].unk3C = (u8*)frames + 128;
    visuals[slot].animation_table = D_8011BF40;
    visuals[slot].unk40 = 0;
    visuals[slot].unk42 = row ? 0x7804 : 0x7802;
    visuals[slot].unk16 = row ? 1 : 3;
    visuals[slot].unk15 = g_Entity.unk15;
    visuals[slot].x_pos.i.hi = g_Entity.x_pos.i.hi + (g_Entity.unk15 ? -1 : 1) * (row ? 10 : 32);
    visuals[slot].y_pos.i.hi = g_Entity.y_pos.i.hi + (row ? 17 : 12);
    visuals[slot].unk17 = row ? 3 : 2;
    visuals[slot].animation_cursor = D_8011BF40[row ? 3 : 2];
    visuals[slot].animation_step.packed = D_8011BF40[row ? 3 : 2][0].packed;
    visuals[slot].previous_animation_index = 0xFF;
    visuals[slot].state = 1;
    if (row)
        wall_slide_dust_update(visual);
    else
        dash_dust_update(visual);
    check();
    return 1;
}
static u32 laser_lifetime(u32 row)
{
    struct WeaponObj* beam;
    u32 i;
    (void)row;
    prepare(0);
    g_Player.weapon = 6;
    g_Player.boss_flags = 32;
    g_Player.weapon_energy[6] = 48;
    player_equip_weapon(&g_Player);
    assert(weapon_objects[0].id == 6 && weapon_objects[0].unk2 == 3);
    func_800961B0(&weapon_objects[0]);
    shoot(6, 1);
    assert(weapon_objects[1].active == 1 && weapon_objects[1].id == 15 && g_Player.last_shot_type == 15 && g_Player.attacking != 0);
    capture();
    weapons[0].on_screen = 0;
    func_800961B0(&weapon_objects[0]);
    check();
    beam = &weapon_objects[1];
    aiming_laser_charged_update(beam);
    assert(beam->state == 1 && beam->ext.weapon_6.lifetime == 240 && beam->ext.weapon_6.direction == 8);
    for (i = 0; i < 30; i++) {
        player_update_normal(&g_Player);
        aiming_laser_charged_update(beam);
    }
    assert(beam->unk5 == 1 && beam->ext.weapon_6.lifetime == 210 && g_Player.input.buttons.held == 0);
    capture();
    weapons[1].ext.weapon_6.lifetime--;
    weapons[1].ext.weapon_6.timer--;
    aiming_laser_charged_update(beam);
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "real_Soul_Body_clone_dash_and_wall_slide_dust", NULL, NULL, 2, clone_dust },
    { "real_charged_Aiming_Laser_reticle_and_30_tick_warmup", NULL, NULL, 1, laser_lifetime },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1;
