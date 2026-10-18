#include "test_runtime.h"
#include "main/collision.h"
#include "main/player_animations_2.h"
#include "main/player.h"
#include "main/player_check.h"
#include "main/player_special.h"
#include "main/player_common.h"
#include "main/55C4.h"
void player_zero_hyouretsuzan_drop(struct PlayerObj*);
void player_wall_jump_rise(struct PlayerObj*);
static u32 gfx[16] = { 0x20, 0x24 }, sprites[16] = { 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34 };
static u8 map[3 * 256];
static u16 pixels[2][16][16];
static u32 attributes[] = { 0x20, 0x38 };
static struct MiscObj misc_expected[64];
static struct WeaponObj weapons_before[16];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static void animation(struct PlayerObj* p, u32 index, u32 word, u32 saber)
{
    p->unk17 = index;
    p->previous_animation_index = 0xFF;
    p->animation_cursor = (u32*)D_8011AFF0[index];
    p->animation_step.packed = word;
    p->unk38 = (u8*)gfx + (saber ? 0x24 : 0x20);
    p->unk3C = (u8*)sprites + (saber ? 0x34 : 0x20);
}
static u32 interrupt(u32 row)
{
    struct PlayerObj expected;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 mode = row % 5, facing = row / 5 % 2, layer = row / 10 % 3, drop = row / 30, i;
    s32 column = -1;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    memset(pixels, 0, sizeof(pixels));
    memset(map, 1, sizeof(map));
    for (i = 0; i < 32; i++)
        ((u16*)pixels)[480 + i] = 1;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    layout_width = layout_height = 16;
    layout_size = 256;
    engine_obj.cur_character = 1;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 16; i++) {
        weapon_objects[i].active = 1;
        weapon_objects[i].id = 39;
    }
    for (i = 0; i < 64; i++)
        misc_objects[i].active = !(drop && mode == 4 && i >= 62);
    g_Player.active = 0x41;
    g_Player.unk2 = 1;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.bg_offset = layer;
    g_Player.unk15 = facing ? 0x40 : 0;
    g_Player.unk5 = drop ? PLAYER_ZERO_HYOURETSUZAN : PLAYER_WALL_JUMP;
    g_Player.unk6 = 1;
    g_Player.air_state = 1;
    g_Player.unk68 = &player_zero_collision_bounds;
    g_Player.x_pos.val = (100 + layer * 16) * 65536 + 0x1234;
    g_Player.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.x_vel.val = 0x12345;
    g_Player.y_vel.val = 0x38000;
    g_Player.unk2C = 0x4200;
    g_Player.afterimage = 1;
    g_Player.dash_momentum = 1;
    g_Player.input.buttons.held = PLAYER_INPUT_JUMP;
    g_Player.combo = 7;
    g_Player.attacking = drop;
    g_Player.voice_timer = 1;
    g_Player.animation_table = (u32**)D_8011AFF0;
    set_animation(&g_Player, drop ? 97 : 14);
    if (mode == 0)
        g_Player.input.buttons.held |= PLAYER_INPUT_UP;
    else if (mode == 1) {
        g_Player.x_pos.val = ((facing ? 102 : 106) + layer * 16) * 65536;
        column = (facing ? 7 : 5) + layer;
        for (i = 0; i < 14; i++)
            pixels[1][i][column] = 1;
        g_Player.unk18 = g_Player.x_pos;
        g_Player.unk1C = g_Player.y_pos;
        CollisionRelated(&g_Player);
        assert(g_Player.unk70 == (facing ? PLAYER_COLLIDE_RIGHT : PLAYER_COLLIDE_LEFT) && g_Player.wall_climbable == 1);
        g_Player.unk88.bytes.collision_flags = g_Player.unk70;
        g_Player.input.buttons.held |= facing ? PLAYER_INPUT_RIGHT : PLAYER_INPUT_LEFT;
    } else if (mode == 2) {
        g_Player.boss_flags = 4;
        g_Player.pressed_input = PLAYER_INPUT_JUMP;
    } else if (!drop && mode == 3)
        g_Player.input_locked = 1;
    else if (!drop)
        g_Player.pressed_input = PLAYER_INPUT_SHOOT;
    else {
        g_Player.x_pos.val = 104 * 65536;
        g_Player.y_pos.val = 202 * 65536;
        g_Player.unk18 = g_Player.x_pos;
        g_Player.unk1C = g_Player.y_pos;
        CollisionRelated(&g_Player);
        assert(g_Player.unk70 == PLAYER_COLLIDE_GROUND);
        g_Player.unk88.bytes.collision_flags = g_Player.unk70;
    }
    expected = g_Player;
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    if (drop && mode < 3)
        expected.attacking = 0;
    if (mode == 0) {
        animation(&expected, 31, 0xAE010002, 0);
        expected.x_pos.i.hi = (expected.x_pos.u.hi & 0xFFF0) + 8;
        expected.x_pos.u.lo = expected.y_pos.u.lo = 0;
        expected.x_vel.val = expected.unk28 = expected.unk2C = 0;
        expected.y_vel.val = 0x18000;
        expected.dash_momentum = expected.air_action = 0;
        expected.afterimage = -1;
        expected.unk5 = PLAYER_LADDER_UP;
        expected.unk6 = 0;
    } else if (mode == 1) {
        animation(&expected, 13, 0x23010002, 0);
        expected.x_vel.val = expected.y_vel.val = expected.unk28 = expected.unk2C = 0;
        expected.dash_momentum = expected.air_action = 0;
        expected.afterimage = -1;
        expected.unk8A.bytes.low = 8;
        expected.unk5 = PLAYER_WALL_CLING;
        expected.unk6 = 0;
    } else if (mode == 2) {
        animation(&expected, 99, 0x16010004, 0);
        expected.x_vel.val = expected.unk28 = 0;
        expected.y_vel.val = 0x5D000 - 0x4200;
        expected.unk2C = 0x4200;
        expected.y_pos.val -= 0x5D000;
        expected.dash_momentum = 0;
        expected.air_action = 6;
        expected.afterimage = 0;
        expected.unk5 = PLAYER_JUMP;
        expected.unk6 = 0;
    } else if (drop) {
        animation(&expected, 98, 0x8A010002, 1);
        expected.air_state = expected.dash_momentum = expected.air_action = expected.afterimage = 0;
        expected.unk6 = 2;
        if (mode == 4)
            for (i = 62; i < 64; i++) {
                struct MiscObj* m = &misc_expected[i];
                m->active = 0x21;
                m->id = 47;
                m->bg_offset = layer;
                m->x_pos.i.hi = facing ? 120 : 88;
                m->y_pos.i.hi = 202;
            }
    } else if (mode == 3) {
        animation(&expected, 11, 0x18010003, 0);
        expected.x_vel.val = 0;
        expected.y_vel.val = -0x4200;
        expected.air_state = -1;
        expected.unk5 = PLAYER_FALL;
        expected.unk6 = 0;
    } else {
        animation(&expected, 91, 0xD5010001, 0);
        expected.attacking = 1;
        expected.combo = expected.afterimage = 0;
        expected.x_vel.val = 0;
        expected.y_pos.val -= 0x38000;
        expected.y_vel.val -= 0x4200;
        expected.unk5 = PLAYER_ZERO_JUMP_SLASH;
        expected.unk6 = 1;
    }
    D_8013E198[0] = D_8013E198[1] = -1;
    if (drop)
        player_zero_hyouretsuzan_drop(&g_Player);
    else
        player_wall_jump_rise(&g_Player);
    SAME(g_Player, expected);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(misc_objects, misc_expected);
    SAME(weapon_objects, weapons_before);
    for (i = 0; i < sizeof(map); i++)
        assert(map[i] == 1);
    for (i = 0; i < 512; i++)
        assert(((u16*)pixels)[i] == (i >= 480 || (i >= 256 && (s32)(i % 16) == column)));
    assert(attributes[0] == 0x20 && attributes[1] == 0x38);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "wall_jump_and_ice_drop_ladder_wall_double_jump_and_pool_handoffs", NULL, NULL, 60, interrupt } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 60;
