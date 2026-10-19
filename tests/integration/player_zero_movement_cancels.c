#include "test_runtime.h"
#include "main/55C4.h"
#include "main/player_animations_2.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/player_special.h"
#include "main/player_enter.h"
#include "main/player_common.h"
void player_walk_start(struct PlayerObj*);
void player_enter_walk_start(struct PlayerObj*);
void player_walk(struct PlayerObj*);
void player_settle(struct PlayerObj*);
void player_land(struct PlayerObj*);
void player_dash_start(struct PlayerObj*);
void player_air_dash(struct PlayerObj*);
void player_wall_slide_release(struct PlayerObj*);
void player_enter_air_dash(struct PlayerObj*);
void player_enter_air_dash_end(struct PlayerObj*);
void func_80034B64(struct PlayerObj*);
static u32 gfx[64], frames[64], attributes[1];
static u8 map[3 * 256];
static u16 tiles[256], palette[18];
static Palette bank[1];
static struct PlayerObj expected, entity;
static struct EngineObj engine;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds[3];
static struct WeaponObj weapons[16];
static struct VisualObj visuals[32];
static struct ControllerInput input;
static u8 dirty;
static void prepare(void)
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
    memset(map, 0, sizeof(map));
    memset(tiles, 0, sizeof(tiles));
    attributes[0] = 0;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(bank, 0, sizeof(bank));
    memset(palette, 0, sizeof(palette));
    palette[0] = palette[17] = 0xBEEF;
    TEST_PALETTE_BANK = (u8*)bank;
    TEST_PALETTE = (u8*)&palette[1];
    engine_obj.cur_character = CHARACTER_ZERO;
    engine_obj.stage = 4;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    g_Player.active = 0x41;
    g_Player.unk2 = CHARACTER_ZERO;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.x_pos.i.hi = 512;
    g_Player.y_pos.i.hi = 512;
    g_Player.animation_table = (u32**)D_8011AFF0;
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
    assert(cur_random == 0x1234 && need_palette_load == dirty);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && SP_BG_TILEMAP == map && layout_width == 16 && layout_height == 16 && layout_size == 256 && attributes[0] == 0);
    for (i = 0; i < COUNT(map); i++)
        assert(map[i] == 0);
    for (i = 0; i < COUNT(tiles); i++)
        assert(tiles[i] == 0);
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i == 0 ? 64u : i == 1 ? 128u
                                                : 0)
            && frames[i] == (i == 0 ? 64u : i == 5 ? 128u
                                                   : 0));
    assert(palette[0] == 0xBEEF && palette[17] == 0xBEEF);
    for (i = 0; i < 16; i++)
        assert(palette[i + 1] == 0 && bank[0][i] == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}
static void raijingeki(void)
{
    pose(0x5F, 0x56010002, 1);
    expected.attacking = 1;
    expected.combo = expected.afterimage = 0;
    expected.unk5 = PLAYER_ZERO_RAIJINGEKI;
    expected.unk6 = 1;
}
static u32 ground(u32 row)
{
    static void (*const enter[])(struct PlayerObj*) = { player_enter_walk_start, player_enter_walk, player_enter_stand, player_enter_land, player_enter_dash };
    static void (*const run[])(struct PlayerObj*) = { player_walk_start, player_walk, player_settle, player_land, player_dash_start };
    prepare();
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    enter[row](&g_Player);
    g_Player.boss_flags = 1;
    g_Player.pressed_input = PLAYER_INPUT_SPECIAL;
    capture();
    raijingeki();
    run[row](&g_Player);
    check();
    return 1;
}
static u32 dash_saber(u32 row)
{
    (void)row;
    prepare();
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    player_enter_dash(&g_Player);
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    capture();
    pose(0x58, 0x3D010001, 0);
    expected.attacking = 1;
    expected.combo = expected.dash_momentum = expected.air_action = expected.afterimage = 0;
    expected.unk5 = PLAYER_ZERO_SABER;
    expected.unk6 = 1;
    player_dash_start(&g_Player);
    check();
    return 1;
}
static void air_entry(u32 phase)
{
    u32 i;
    g_Player.boss_flags = 0x10;
    g_Player.air_state = -1;
    player_enter_air_dash(&g_Player);
    g_Player.input.buttons.held = PLAYER_INPUT_DASH;
    if (phase) {
        for (i = 0; i < 8 && g_Player.unk6 == 0; i++)
            player_air_dash(&g_Player);
        assert(g_Player.unk6 == 1);
    }
    if (phase == 2) {
        g_Player.input.buttons.held = 0;
        player_air_dash(&g_Player);
        assert(g_Player.unk6 == 2 && g_Player.unk17 == 0x13);
    }
}
static u32 air_slash(u32 row)
{
    u32 i;
    prepare();
    if (row < 3)
        air_entry(row);
    else {
        g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_RIGHT;
        func_80034B64(&g_Player);
        g_Player.unk88.bytes.collision_flags = 0;
    }
    g_Player.input.buttons.held = 0;
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    capture();
    pose(0x5B, 0xD5010001, 0);
    expected.attacking = 1;
    expected.combo = expected.afterimage = 0;
    expected.unk5 = PLAYER_ZERO_FALL_SLASH;
    expected.unk6 = 1;
    expected.y_pos.val -= expected.y_vel.val;
    expected.x_vel.val = 0;
    expected.unk28 = 0;
    expected.y_vel.val = row == 3 ? -0x4200 : 0;
    expected.unk2C = 0x4200;
    expected.air_state = -1;
    expected.dash_momentum = 0;
    for (i = 0; i < COUNT(weapons) && weapons[i].active; i++) { }
    assert(i < COUNT(weapons));
    weapons[i].active = 1;
    weapons[i].id = 0x1B;
    weapons[i].unk2 = 0;
    weapons[i].bg_offset = expected.bg_offset;
    weapons[i].unk84.word = 0x5B;
    if (row < 3)
        player_air_dash(&g_Player);
    else
        player_wall_slide_release(&g_Player);
    check();
    return 1;
}
static u32 end_finished(u32 row)
{
    u32 i;
    (void)row;
    prepare();
    air_entry(2);
    for (i = 0; i < 6; i++)
        player_air_dash(&g_Player);
    assert(g_Player.unk6 == 2 && g_Player.animation_step.packed == 0x2C010101);
    capture();
    pose(0x14, 0x18010003, 0);
    expected.y_pos.val -= expected.y_vel.val;
    expected.y_vel.val -= expected.unk2C;
    expected.unk5 = PLAYER_FALL;
    expected.unk6 = 0;
    player_air_dash(&g_Player);
    check();
    return 1;
}
static u32 saber_recovery(u32 row)
{
    u32 i;
    prepare();
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    assert(player_zero_check_saber(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 40 && !(g_Player.animation_step.fields.event & 0x40); i++)
        player_zero_saber(&g_Player);
    assert(g_Player.animation_step.fields.event == 0x40 && g_Player.unk5 == PLAYER_ZERO_SABER);
    g_Player.boss_flags = row ? 0 : 1;
    g_Player.pressed_input = row ? PLAYER_INPUT_SHOOT : PLAYER_INPUT_SPECIAL;
    capture();
    if (row) {
        pose(0x58, 0x3D010001, 0);
        expected.attacking = 1;
        expected.combo = expected.dash_momentum = expected.air_action = expected.afterimage = 0;
        expected.unk5 = PLAYER_ZERO_SABER;
        expected.unk6 = 1;
    } else
        raijingeki();
    player_zero_saber(&g_Player);
    check();
    return 1;
}
static u32 shippuuga_wait(u32 row)
{
    u32 i;
    (void)row;
    prepare();
    g_Player.unk88.bytes.collision_flags = PLAYER_COLLIDE_GROUND;
    player_enter_dash(&g_Player);
    g_Player.boss_flags = 0x80;
    g_Player.pressed_input = PLAYER_INPUT_SPECIAL;
    assert(player_zero_check_shippuuga(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 40 && !(g_Player.animation_step.fields.event & 0x40); i++)
        player_zero_shippuuga(&g_Player);
    assert(g_Player.animation_step.fields.event == 0x40 && g_Player.unk5 == PLAYER_ZERO_SHIPPUUGA);
    capture();
    assert(player_zero_shippuuga_cancel(&g_Player) == 0);
    check();
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "Zero_real_ground_movement_entry_then_Raijingeki_input", NULL, NULL, 5, ground },
    { "Zero_real_dash_entry_then_saber_input", NULL, NULL, 1, dash_saber },
    { "Zero_real_air_dash_phases_and_wall_release_then_fall_slash", NULL, NULL, 4, air_slash },
    { "Zero_own_air_dash_end_terminal_tick_enters_fall", NULL, NULL, 1, end_finished },
    { "Zero_own_saber_recovery_then_technique_or_saber_input", NULL, NULL, 2, saber_recovery },
    { "Zero_own_Shippuuga_recovery_without_new_input", NULL, NULL, 1, shippuuga_wait },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 5 + 1 + 4 + 1 + 2 + 1;
