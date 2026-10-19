#include "test_runtime.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/player_animations.h"
#include "main/player_animations_2.h"
#include "main/player.h"
#include "main/player_special.h"
#include "main/player_common.h"
#include "main/player_check.h"
void func_80033D54(struct PlayerObj*);
void player_check_damage(struct PlayerObj*);
void player_hurt(struct PlayerObj*);
void player_update_normal(struct PlayerObj*);
void player_zero_wall_slash(struct PlayerObj*);
void player_zero_ryuenjin(struct PlayerObj*);
void player_zero_ryuenjin_rise(struct PlayerObj*);
void train_scroll_init(struct LayerObj*);
void train_scroll_main(struct LayerObj*);
extern s32 D_80139538, D_80139540, D_80139544;
extern s16 D_80139560;
static u32 gfx[64], frames[64], attributes[2];
static u32 map_words[3 * 256];
#define map ((u8*)map_words)
static u16 tiles[512], tiles_before[512], palette[0x152];
static Palette bank[3];
static struct PlayerObj expected, entity;
static struct EngineObj engine;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds[3];
static struct WeaponObj weapons[16];
static struct VisualObj visuals[32];
static struct MiscObj misc[64];
static struct ControllerInput input;
static u8 dirty;
static u16 rng;
static u32 hurt_only;
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
static u32 terrain;
static void prepare(u32 character, u32 tile)
{
    u32 i;
    hurt_only = 0;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    memset(gfx, 0, sizeof(gfx));
    memset(frames, 0, sizeof(frames));
    gfx[0] = frames[0] = 64;
    gfx[1] = frames[5] = 128;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    memset(map_words, 1, sizeof(map_words));
    terrain = tile;
    for (i = 0; i < COUNT(tiles); i++)
        tiles[i] = (i >= 256) && (tile == 0 ? (i & 255) / 16 >= 14 : tile == 1 ? (i & 255) / 16 >= 14 && (i & 15) < 13
                           : tile == 2                                         ? (i & 15) == 5
                                                                               : (i & 255) / 16 == 10);
    c_test_copy_words((u32*)tiles_before, (u32*)tiles, sizeof(tiles) / 4);
    attributes[0] = 0;
    attributes[1] = 0x38;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = 64;
    layout_height = 16;
    layout_size = 1024;
    memset(bank, 0, sizeof(bank));
    memset(palette, 0, sizeof(palette));
    palette[0] = palette[0x151] = 0xBEEF;
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
    c_test_copy_words((u32*)backgrounds, (u32*)background_objects, sizeof(backgrounds) / 4);
    if (!hurt_only) {
        c_test_copy_words((u32*)weapons, (u32*)weapon_objects, sizeof(weapons) / 4);
        c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
        c_test_copy_words((u32*)misc, (u32*)misc_objects, sizeof(misc) / 4);
    }
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
    if (hurt_only) {
        assert(zero_difference((u32*)weapon_objects, sizeof(weapon_objects) / 4) == 0 && zero_difference((u32*)visual_objects, sizeof(visual_objects) / 4) == 0 && zero_difference((u32*)misc_objects, sizeof(misc_objects) / 4) == 0);
    } else {
        assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0);
        assert(c_test_word_difference((u32*)misc_objects, (u32*)misc, sizeof(misc) / 4) == 0);
    }
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_random == rng && need_palette_load == dirty);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && SP_BG_TILEMAP == map && layout_width == 64 && layout_height == 16 && layout_size == 1024 && attributes[0] == 0 && attributes[1] == 0x38);
    for (i = 0; i < COUNT(map_words); i += 8)
        assert(((map_words[i] ^ 0x01010101) | (map_words[i + 1] ^ 0x01010101) | (map_words[i + 2] ^ 0x01010101) | (map_words[i + 3] ^ 0x01010101) | (map_words[i + 4] ^ 0x01010101) | (map_words[i + 5] ^ 0x01010101) | (map_words[i + 6] ^ 0x01010101) | (map_words[i + 7] ^ 0x01010101)) == 0);
    assert(c_test_word_difference((u32*)tiles, (u32*)tiles_before, sizeof(tiles) / 4) == 0);
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
static u32 train_recovery(u32 row)
{
    struct LayerObj train, train_expected;
    struct BackgroundObj moved[3];
    u32 i;
    prepare(1, row);
    hurt_only = 1;
    g_Player.x_pos.i.hi = row ? 2243 : 2240;
    g_Player.y_pos.i.hi = 202;
    previous();
    collide();
    assert(g_Player.unk70 == PLAYER_COLLIDE_GROUND);
    memset(&train, 0, sizeof(train));
    train.active = 1;
    train.id = 0;
    train.x_pos.i.hi = 768;
    train.y_pos.i.hi = 304;
    train_scroll_init(&train);
    assert(train.state == 1 && train.unk5 == 0 && train.bg_offset == 0 && engine_obj.gameplay_locked == 0);
    g_Player.hurt_type = row + 1;
    func_80033D54(&g_Player);
    assert(g_Player.unk5 == PLAYER_HURT && g_Player.invincibility_timer == (row ? 100 : 75));
    for (i = 0; i < (row ? 39u : 14u); i++) {
        previous();
        player_check_damage(&g_Player);
        player_hurt(&g_Player);
        if (row && i != 0 && g_Player.y_pos.val < 200 * 65536) {
            assert(g_Player.unk70 == 0 && g_Player.y_pos.val + 22 * 65536 < 224 * 65536);
        } else
            collide();
    }
    assert(g_Player.invincibility_timer == 61 && g_Player.unk5 == PLAYER_HURT && g_Player.x_pos.i.hi >= 2256 && g_Player.x_pos.i.hi <= 2272);
    assert(g_Player.unk2C == 0 && ((g_Player.unk70 & PLAYER_COLLIDE_GROUND) != 0) == !row);
    train_expected = train;
    train_expected.unk15 = 0;
    train_expected.bg_offset = 1;
    train_expected.unk5 = 1;
    train_expected.unk6 = 1;
    train_expected.unk7 = 0;
    train_expected.unk16--;
    memcpy(moved, background_objects, sizeof(moved));
    moved[0].unk24 = moved[0].unk26 = 0x8D0;
    moved[1].x_pos.val += 0x80000;
    moved[2].x_pos.val += 0x40000;
    train_scroll_main(&train);
    assert(c_test_word_difference((u32*)&train, (u32*)&train_expected, sizeof(train) / 4) == 0);
    assert(c_test_word_difference((u32*)background_objects, (u32*)moved, sizeof(moved) / 4) == 0);
    assert(g_Player.script_state == 1 && g_Player.script_action == PLAYER_SCRIPT_WAIT && g_Player.script_facing == 0x40 && engine_obj.gameplay_locked == 1 && g_Player.invincibility_timer == 61);
    previous();
    capture();
    expected.input_locked = 1;
    expected.actions_reset = 0;
    expected.voice_timer = -1;
    expected.x_pos.val += expected.x_vel.val;
    expected.y_pos.val -= expected.y_vel.val;
    expected.hurt_phase = expected.invincibility_timer = 0;
    expected.unk6 = 0;
    if (row) {
        pose(0xB, 0x18010003, 0);
        expected.x_vel.val = expected.unk28 = expected.y_vel.val = 0;
        expected.unk2C = 0x4200;
        expected.air_state = -1;
        expected.unk5 = PLAYER_FALL;
        expected.unk54 = &D_8011A230[2];
    } else {
        pose(5, 0x00010015, 0);
        expected.x_vel.val = expected.unk28 = expected.y_vel.val = expected.unk2C = 0;
        expected.unk5 = PLAYER_SCRIPT_WAIT;
        expected.script_state = -1;
        expected.unk15 = 0x40;
        expected.unk54 = &D_8011A230[1];
        dirty |= 1;
    }
    player_update_normal(&g_Player);
    check();
    assert(c_test_word_difference((u32*)&train, (u32*)&train_expected, sizeof(train) / 4) == 0);
    return 1;
}
static u32 wall_finish(u32 row)
{
    u32 i;
    (void)row;
    prepare(1, 2);
    g_Player.x_pos.i.hi = 106;
    g_Player.y_pos.i.hi = 200;
    g_Player.x_vel.val = 0x12345;
    previous();
    collide();
    assert(g_Player.unk70 == PLAYER_COLLIDE_LEFT && g_Player.wall_climbable == 1);
    g_Player.input.buttons.held = PLAYER_INPUT_LEFT;
    assert(player_check_wall(&g_Player) == 1);
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    assert(player_zero_check_wall_slash(&g_Player) == 1);
    g_Player.pressed_input = 0;
    assert(g_Player.unk5 == PLAYER_ZERO_WALL_SLASH && g_Player.unk6 == 1);
    for (i = 0; i < 28; i++)
        player_zero_wall_slash(&g_Player);
    assert(g_Player.animation_step.packed == 0x32014001 && g_Player.unk5 == PLAYER_ZERO_WALL_SLASH);
    capture();
    pose(0xF, 0x29010002, 0);
    expected.attacking = 0;
    expected.unk5 = PLAYER_WALL_SLIDE;
    expected.unk6 = 0;
    player_zero_wall_slash(&g_Player);
    check();
    return 1;
}
static u32 rise_ceiling(u32 row)
{
    u32 i;
    (void)row;
    prepare(1, 3);
    g_Player.x_pos.i.hi = 200;
    g_Player.y_pos.i.hi = 202;
    g_Player.boss_flags = 8;
    g_Player.input.buttons.held = PLAYER_INPUT_UP;
    g_Player.pressed_input = PLAYER_INPUT_SPECIAL;
    assert(player_zero_check_ryuenjin(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 20 && g_Player.unk6 == 0; i++)
        player_zero_ryuenjin(&g_Player);
    assert(g_Player.unk6 == 1 && g_Player.y_vel.val == 0x6C000);
    for (i = 0; i < 4 && !(g_Player.unk70 & PLAYER_COLLIDE_CEILING); i++) {
        previous();
        player_zero_ryuenjin(&g_Player);
        collide();
    }
    assert(g_Player.unk6 == 1 && g_Player.unk70 == PLAYER_COLLIDE_CEILING);
    capture();
    pose(0x66, 0x9C010003, 1);
    expected.x_vel.val = expected.unk28 = expected.y_vel.val = 0;
    expected.air_state = -1;
    expected.unk6 = 3;
    visuals[0].active = 1;
    visuals[0].id = 0x27;
    visuals[0].unk2 = 0;
    visuals[0].bg_offset = expected.bg_offset;
    player_zero_ryuenjin_rise(&g_Player);
    check();
    return 1;
}
static void sound_state(u32* v)
{
    v[0] = D_80139538;
    v[1] = D_80139540;
    v[2] = D_80139544;
    v[3] = D_80139560;
    v[4] = D_80139568;
    v[5] = D_80139530;
    v[6] = D_80141BD4;
    v[7] = D_80137CC0;
    v[8] = D_80173C84;
    v[9] = D_80175EE8[0];
    v[10] = D_80139514;
    v[11] = D_80139524;
    v[12] = D_80139528;
    memcpy(&v[13], &D_80139520, 4);
    v[14] = D_8013955C;
}
static u32 saber_victory(u32 row)
{
    u32 i, music[15], after[15];
    (void)row;
    prepare(1, 0);
    engine_obj.substage = 1;
    g_Player.x_pos.i.hi = 9248;
    g_Player.y_pos.i.hi = 458;
    previous();
    collide();
    assert(g_Player.unk70 == PLAYER_COLLIDE_GROUND);
    g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    assert(player_zero_check_saber(&g_Player) == 1);
    g_Player.pressed_input = 0;
    for (i = 0; i < 45 && g_Player.animation_step.packed != 0x86014001; i++)
        player_zero_saber(&g_Player);
    assert(g_Player.animation_step.packed == 0x86014001 && g_Player.unk5 == PLAYER_ZERO_SABER);
    engine_obj.unkF = 0x10;
    D_80171EA9 = 0;
    previous();
    capture();
    sound_state(music);
    music[0] = 3606784;
    music[1] = 226571;
    music[2] = 227619;
    music[3] = XA_ARCHIVE_BGM5;
    music[4] = 1;
    music[5] = 7;
    music[6] = 2;
    music[7] = 23330817;
    music[8] = 1;
    music[9] = (music[9] & 0xFFFF0000) | 0x101;
    music[10] = (music[10] & 0xFF000000) | 0x712250;
    music[11] = music[12] = 0x72;
    music[13] = 0x39393939;
    pose(5, 0x00010015, 0);
    expected.input_locked = 0x10;
    expected.actions_reset = expected.attacking = expected.shot_fired = expected.attack_ended = 0;
    expected.voice_timer = -1;
    expected.unk5 = PLAYER_STAGE_CLEAR;
    expected.unk6 = 0;
    expected.unk54 = &D_8011A230[1];
    engine.gameplay_locked = 1;
    dirty |= 1;
    player_update_normal(&g_Player);
    check();
    sound_state(after);
    assert(c_test_word_difference((u32*)after, (u32*)music, sizeof(music) / 4) == 0);
    assert(D_80171EA9 == 0);
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "Zero_real_hurt_clock_floor_edge_and_train_camera_lock_recovery", NULL, NULL, 2, train_recovery },
    { "Zero_real_wall_collision_own_saber_terminal_enters_slide", NULL, NULL, 1, wall_finish },
    { "Zero_real_Ryuenjin_rise_ceiling_collision_enters_fall", NULL, NULL, 1, rise_ceiling },
    { "Zero_own_saber_terminal_with_stage_clear_flag_selects_exact_victory_music", NULL, NULL, 1, saber_victory },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1 + 1 + 1;
