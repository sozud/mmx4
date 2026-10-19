#include "test_runtime.h"
#include "main/player_common.h"
#include "main/195B4.h"
#include "main/player_animations.h"
#include "main/player_animations_2.h"
#include "main/sprite_animations.h"
#include "main/player_special.h"
#include "main/55C4.h"
#include "main/102FC.h"
#include "main/2824.h"
void player_check_splash_tile(struct PlayerObj*);

static s32 gfx_archive[4] = { 8, 12, 0x11223344, 0x55667788 };
static s32 sprite_archive[12] = { 24, 28, 32, 36, 40, 44, 1, 2, 3, 4, 5, 6 };
static u32 entry_case(u32 mode)
{
    struct PlayerObj obj, expected, player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj bg_before[3];
    struct RideArmorObj ride_before;
    u8 palette_before = need_palette_load;
    u32 i, animation = 5, actual;
    s32 placed = mode >= 2 && mode <= 8 || mode == 11 || mode == 13;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    obj.active = 0x41;
    obj.state = 0;
    obj.unk5 = 7;
    obj.unk6 = 2;
    obj.unk2 = mode >= 6 && mode <= 8;
    obj.is_clone = mode == 9;
    obj.hp = 16;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 3 * 65536;
    obj.y_vel.val = 4 * 65536;
    obj.unk28 = 123;
    obj.unk2C = 456;
    obj.animation_table = (u32**)(obj.unk2 ? D_8011AFF0 : D_80119DF0);
    engine_obj.max_hp = 16;
    engine_obj.armor_parts = 4;
    engine_obj.arm_type = 3;
    engine_obj.gameplay_locked = 1;
    engine_obj.stage = mode == 4 ? 1 : mode == 5 || mode == 6 ? 6
        : mode == 8 || mode == 11 || mode == 12               ? 3
        : mode == 10                                          ? 5
                                                              : 12;
    if (mode == 13)
        engine_obj.stage = 8;
    engine_obj.substage = mode == 3 || mode == 5 || mode == 10 || mode == 11 ? 0 : 1;
    engine_obj.checkpoint = mode == 2 || mode == 10 || mode == 12 ? 0 : mode == 3 || mode == 5 ? 2
                                                                                               : 1;
    engine_obj.unk1E = mode == 0 ? 0 : mode == 11 || mode == 12 ? -1
                                                                : 1;
    TEST_PLAYER_GFX = (u8*)gfx_archive;
    TEST_SPRITE_FRAMES = (u8*)sprite_archive;
    expected = obj;
    engine_before = engine_obj;
    ride_before = qux_object;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    if (mode <= 3 || mode >= 9 && mode <= 12) {
        if (mode) {
            expected.state = 1;
            expected.on_screen = 1;
        }
        if (mode && mode != 9)
            engine_before.unk1F = 1;
    }
    if (mode == 1 || mode == 12) {
        animation = 1;
        expected.x_vel.val = 0;
        expected.unk28 = 0;
        expected.y_vel.val = -8 * 65536;
        expected.unk2C = 0;
        expected.air_state = -1;
        expected.unk5 = PLAYER_BEAM_IN;
    } else if (placed) {
        if (mode == 2)
            expected.y_pos.i.hi = 0x1CB;
        if (mode == 3) {
            assert(player_stage_12_entry_y[2] == 0x69B);
            expected.y_pos.i.hi = 0x69B;
        }
        if (mode == 5) {
            assert(player_stage_6_entry_y[2] == 0x2CB);
            expected.y_pos.i.hi = 0x2CB;
        }
        if (mode == 6)
            expected.y_pos.i.hi = 0x9CB;
        if (mode == 7)
            expected.y_pos.i.hi = 0x1CB;
        if (mode == 8) {
            assert(player_stage_3_entry_y[1][1] == 0x1AB);
            expected.y_pos.i.hi = 0x1AB;
        }
        if (mode == 11) {
            assert(player_stage_3_entry_y[0][1] == 0xAB);
            expected.y_pos.i.hi = 0xAB;
        }
        if (obj.unk2)
            expected.y_pos.i.hi--;
        else {
            expected.armor_parts = 4;
            expected.arm_type = 3;
        }
        expected.y_pos.i.lo = 0;
        expected.unk68 = obj.unk2 ? &player_zero_collision_bounds : &player_x_collision_bounds;
        expected.unk5 = PLAYER_IDLE;
        expected.unk6 = 0;
        engine_before.gameplay_locked = 0;
        for (i = 0; i < 3; i++)
            bg_before[i].unk44 = 1;
    } else if (mode == 9) {
        animation = 0x61;
        expected.unk5 = PLAYER_SOUL_BODY_CLONE;
    } else if (mode == 10) {
        expected.armor_parts = 4;
        expected.arm_type = 3;
        expected.ride_state = -1;
        expected.air_state = 1;
        expected.ride_animation = 0x29;
        expected.unk5 = PLAYER_RIDE;
        expected.unk6 = 1;
        ride_before.active = 1;
    }
    if (mode != 0 && mode != 10) {
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (u32*)obj.animation_table[animation];
        expected.animation_step = *(union AnimationStep*)expected.animation_cursor;
        expected.unk3C = (void*)(sprite_archive + 6);
        if (obj.unk2) {
            assert(D_8011AF60[animation] == 0);
            expected.unk38 = gfx_archive + 2;
        }
    }
    if (mode >= 4 && mode <= 8 || mode == 13)
        player_entry_placed(&obj);
    else
        player_update_init(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(qux_object) / 4; i++)
        assert(((u32*)&qux_object)[i] == ((u32*)&ride_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(gfx_archive[0] == 8 && gfx_archive[1] == 12 && gfx_archive[2] == 0x11223344 && gfx_archive[3] == 0x55667788);
    for (i = 0; i < 6; i++) {
        assert(sprite_archive[i] == 24 + i * 4 && sprite_archive[i + 6] == i + 1);
        assert(D_8013E198[i] == -1);
    }
    assert(need_palette_load == palette_before);
    actual = (u8)obj.unk5 | ((u32)(u16)obj.y_pos.i.hi << 8) | ((u32)(u8)obj.state << 24);
    return actual;
}
static const u32 player_entry_callbacks_cases_expected[] = { 0xC807u, 0x100C800u, 0x101CB02u, 0x1069B02u, 0xC802u, 0x2CB02u, 0x9CA02u, 0x1CA02u, 0x1AA02u, 0x100C824u, 0x100C812u, 0x100AB02u, 0x100C800u, 0xC802u };

static Palette palette_bank[14];
static u16 palette_storage[0x152];
static u32 palette_case(u32 mode)
{
    struct PlayerObj obj, before, player_before = g_Player;
    struct EngineObj engine_before;
    u32 i, j, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.state = 1;
    obj.unk2 = mode >= 3;
    obj.is_clone = mode == 1;
    obj.weapon = mode == 2 ? 1 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    engine_obj.unk37 = mode == 4;
    for (i = 0; i < 14; i++)
        for (j = 0; j < 16; j++)
            palette_bank[i][j] = 0x1200 + i * 16 + j;
    for (i = 0; i < COUNT(palette_storage); i++)
        palette_storage[i] = 0xBEEF;
    need_palette_load = 0x80;
    TEST_PALETTE = (u8*)&palette_storage[1];
    TEST_PALETTE_BANK = (u8*)palette_bank;
    before = obj;
    engine_before = engine_obj;
    player_reset_palette(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(palette_storage[0] == 0xBEEF && palette_storage[0x151] == 0xBEEF);
    for (i = 0; i < 0x150; i++) {
        u16 expected = 0xBEEF;
        if (mode == 0 && i < 16)
            expected = 0x1200 + i;
        if (mode == 0 && i >= 0x130)
            expected = 0x1210 + i - 0x130;
        if (mode == 2 && i < 32)
            expected = 0x1230 + i;
        if (mode == 2 && i >= 0x130)
            expected = 0x1250 + i - 0x130;
        if (mode >= 3 && i < 16)
            expected = (mode == 4 ? 0x12D0 : 0x1200) + i;
        assert(palette_storage[i + 1] == expected);
    }
    for (i = 0; i < 14; i++)
        for (j = 0; j < 16; j++)
            assert(palette_bank[i][j] == 0x1200 + i * 16 + j);
    assert(need_palette_load == (mode == 1 ? 0x80 : 0x81));
    actual = palette_storage[1] | ((u32)palette_storage[0x131] << 16);
    return actual;
}
static const u32 player_reset_palette_banks_cases_expected[] = { 0x12101200u, 0xBEEFBEEFu, 0x12501230u, 0xBEEF1200u, 0xBEEF12D0u };

static u8 tilemap[256];
static u16 pixels[512];
static u32 attributes[1];
static s32 menu_frames[16] = { 32, 36, 40, 44, 48, 52, 56, 60, 1, 2, 3, 4, 5, 6, 7, 8 };
static u32 page_metadata[8];
static u32 splash_case(u32 mode)
{
    struct PlayerObj obj, expected, player_before = g_Player;
    struct VisualObj pool_before[32];
    struct EngineObj engine_before;
    u32 i, actual;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    obj.active = 0x41;
    obj.state = 1;
    obj.unk15 = 0x40;
    obj.unkDF = mode == 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = mode == 3 && i == 31 ? 0 : 1;
        visual_objects[i].id = 39;
        visual_objects[i].state = 40;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = mode ? 0x24 : 0x20;
    for (i = 0; i < 8; i++)
        page_metadata[i] = 0x400 + i * 0x80;
    SP_BG_TILEMAP = tilemap;
    layout_size = 256;
    layout_width = 16;
    D_801406A8 = page_metadata;
    cur_random = 0x1234;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    TEST_MENU_FRAMES = (u8*)menu_frames;
    expected = obj;
    engine_before = engine_obj;
    memcpy(pool_before, visual_objects, sizeof(pool_before));
    if (mode >= 2)
        expected.unkDF = 1;
    if (mode == 3) {
        assert(s_StageMainIds[1][0][4] == 0x84 && (u8)func_8002938C(0x84) == 4);
        pool_before[31].active = 0x41;
        pool_before[31].id = 3;
        pool_before[31].unk2 = 9;
        pool_before[31].bg_offset = 0;
        pool_before[31].unk16 = 1;
        pool_before[31].animation_table = (const u8* const*)D_8011BF40;
        pool_before[31].unk3C = (void*)(menu_frames + 12);
        pool_before[31].unk40 = 12;
        pool_before[31].unk42 = 0x7888;
        pool_before[31].unk15 = 0x40;
        pool_before[31].x_pos.i.hi = 100;
        pool_before[31].y_pos.i.hi = 184;
    }
    player_check_splash_tile(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < 256; i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < 512; i++)
        assert(pixels[i] == 0);
    assert(attributes[0] == (mode ? 0x24 : 0x20));
    for (i = 0; i < 8; i++) {
        assert(page_metadata[i] == 0x400 + i * 0x80);
        assert(menu_frames[i] == 32 + i * 4);
        assert(menu_frames[i + 8] == i + 1);
    }
    assert(cur_random == (mode >= 2 ? 0x366A : 0x1234));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    actual = obj.unkDF | ((u32)(u8)visual_objects[31].id << 8) | ((u32)(u16)visual_objects[31].y_pos.i.hi << 16);
    return actual;
}
static const u32 player_splash_tile_visual_pool_cases_expected[] = { 0x3C2700u, 0x3C2701u, 0x3C2701u, 0xB80301u };

static const u32 inputs_0[2][3] = {
    { 0, 0, 0 },
    { 2, 3, -1 },
};
struct player_damage_case {
    u32 expected[2];
};
static const struct player_damage_case player_damage_cases[] = {
    { { 0xFFFFFF80u, 0u } },
    { { 0xFFFFFF82u, 0xFFFFFFFFu } },
};
static u32 test_player_damage(u32 row)
{
    const struct player_damage_case* c = &player_damage_cases[row];
    u32 observed_values[2];
    s8 damage;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.armor_parts = inputs_0[row][0];
    g_Player.hp = inputs_0[row][1];
    damage = inputs_0[row][2];
    player_damage(damage);
    observed_values[0] = (u32)g_Player.hp;
    observed_values[1] = (u32)g_Player.stun_timer;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

static const u32 player_spawn_dash_dust_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_player_spawn_dash_dust(u32 row)
{
    u32 observed_values[6];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    FILL_ACTIVE(visual_objects, 32, 255 ? 1 : 0);
    player_spawn_dash_dust(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].state;
    observed_values[4] = (u32)visual_objects[0].unk5;
    observed_values[5] = (u32)visual_objects[0].unk6;
    return c_test_observe(0, row, observed_values, player_spawn_dash_dust_expected, 6);
}

static const u32 player_spawn_wall_slide_dust_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_player_spawn_wall_slide_dust(u32 row)
{
    u32 observed_values[6];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    FILL_ACTIVE(visual_objects, 32, 255 ? 1 : 0);
    player_spawn_wall_slide_dust(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].state;
    observed_values[4] = (u32)visual_objects[0].unk5;
    observed_values[5] = (u32)visual_objects[0].unk6;
    return c_test_observe(0, row, observed_values, player_spawn_wall_slide_dust_expected, 6);
}

#include "support/pool_full.h"
static u32 pool_full_player_spawn_wall_kick_spark(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    player_spawn_wall_kick_spark(&g_Player);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_player_spawn_wall_kick_spark,
};
static const u32 pool_full_cases_expected[] = { 0x50000u };

static u32 bounds_case(s8 riding, s8 character)
{
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ride_state = riding;
    obj.unk2 = character;
    player_set_collision_bounds(&obj);
    if (obj.unk68 == NULL)
        return 0;
    if (obj.unk68 == &player_x_collision_bounds)
        return 1;
    if (obj.unk68 == &player_zero_collision_bounds)
        return 2;
    return 0xFFFFFFFFu;
}

#define BOUNDS_CASE(name, riding, character)         \
    static u32 name(void)                            \
    {                                                \
        u32 actual = bounds_case(riding, character); \
        assert(actual <= 2);                         \
        return actual;                               \
    }
BOUNDS_CASE(bounds_riding, -1, 0)
BOUNDS_CASE(bounds_x, 0, 0)
BOUNDS_CASE(bounds_zero, 0, 1)
#undef BOUNDS_CASE
static const CTestCase collision_bounds_identity_cases[] = {
    bounds_riding,
    bounds_x,
    bounds_zero,
};

static const u32 collision_bounds_identity_cases_expected[] = { 0x0u, 0x1u, 0x2u };

extern s32 D_80139538, D_80139540, D_80139544;
extern s16 D_80139560;
static void capture(u32* v)
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
static u32 music(u32 row)
{
    struct EngineObj engine;
    struct PlayerObj player;
    u32 before[15], after[15];
    engine_obj.state = 5;
    engine_obj.gameplay_locked = 1;
    engine_obj.unk5F = 10;
    engine_obj.stage = 12;
    engine_obj.substage = row == 0 ? 1 : 0;
    engine_obj.checkpoint = row == 0 ? 0 : 14;
    engine_obj.cur_character = row == 0 ? CHARACTER_ZERO : CHARACTER_X;
    engine_obj.character_state.bytes[8] = 0;
    engine_obj.character_state.bytes[11] = row == 0 ? 0 : 1;
    engine = engine_obj;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.unk2 = engine_obj.cur_character;
    g_Player.animation_table = (u32**)(row == 0 ? D_8011AFF0 : D_80119DF0);
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    player = g_Player;
    D_80171EA9 = 0;
    capture(before);
    if (row != 0) {
        before[0] = 60661248;
        before[1] = 149190;
        before[2] = 173774;
        before[3] = XA_ARCHIVE_BGM1;
        before[4] = 0;
        before[5] = 7;
        before[6] = 2;
        before[7] = 23330817;
        before[8] = 1;
        before[9] = (before[9] & 0xFFFF0000) | 0x401;
        before[10] = (before[10] & 0xFF000000) | 0x151133;
        before[11] = before[12] = 127;
        before[13] = 0x3F3F3F3F;
    }
    cur_random = 0x1234;
    func_8001FEC0();
    capture(after);
    c_test_same_words(after, before, sizeof(before));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    assert(D_80171EA9 == 0 && cur_random == 0x1234);
    return 1;
}

static const u16 pads[8] = { 0, 0x2000, 0x8000, 0xA000, 0x1000, 0x4000, 0x5000, 0xFFFF };
static const u16 mapped[8] = { 0, 1, 2, 0, 4, 8, 0, 0x7F0 };
static const u16 bindings[16] = { 0x2000, 0x8000, 0x1000, 0x4000, 0x80, 0x10, 2, 0x40, 0x20, 8, 4, 0, 0, 0, 0, 0 };
static u32 routing(u32 row)
{
    struct PlayerObj player_expected, entity_expected;
    struct ControllerInput controller_before;
    struct EngineObj engine_before = engine_obj;
    u32 input = row % 8, clone = row / 8, i;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.controlling_clone = clone;
    g_Player.hp = 30;
    g_Player.input.buttons.held = 0x1234;
    g_Player.input.buttons.previous = 0x2345;
    g_Player.pressed_input = 0x3456;
    g_Entity.active = 0x41;
    g_Entity.state = 1;
    g_Entity.is_clone = 1;
    g_Entity.input.buttons.held = 0x4567;
    g_Entity.input.buttons.previous = 0x5678;
    g_Entity.pressed_input = 0x6789;
    controller_input.held = pads[input];
    controller_input.previous = pads[(input + 1) % 8];
    controller_input.pressed = pads[(input + 2) % 8];
    controller_before = controller_input;
    player_expected = g_Player;
    entity_expected = g_Entity;
    if (clone) {
        player_expected.input.buttons.held = player_expected.input.buttons.previous = player_expected.pressed_input = 0;
        entity_expected.input.buttons.held = mapped[input];
        entity_expected.input.buttons.previous = mapped[(input + 1) % 8];
        entity_expected.pressed_input = mapped[(input + 2) % 8];
    } else {
        player_expected.input.buttons.held = mapped[input];
        player_expected.input.buttons.previous = mapped[(input + 1) % 8];
        player_expected.pressed_input = mapped[(input + 2) % 8];
    }
    player_read_input();
    assert(controller_input.pressed == controller_before.pressed);
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_expected, sizeof(g_Entity));
    c_test_same_words(&controller_input, &controller_before, sizeof(controller_input));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    for (i = 0; i < COUNT(bindings); i++)
        assert(D_800EE430[i] == bindings[i]);
    return 1;
}

static u32 map_words[12], metadata[5], archive[12], attributes_player_dash_effect_capacity[1];
static u16 pixels_player_dash_effect_capacity[512];
static struct VisualObj pool_expected[32];
static u32 dash(u32 row)
{
    struct PlayerObj obj, player_before = g_Player, expected;
    struct EngineObj engine_before;
    u32 character = row % 2, face = row / 2 % 2, free_slot = row / 4 % 2, water = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.hp = 24;
    obj.state = 1;
    obj.unk2 = character;
    obj.unk15 = face ? 0x40 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    player_set_collision_bounds(&obj);
    expected = obj;
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    assert(func_8002938C(0x84) == 4);
    memset(map_words, 1, sizeof(map_words));
    memset(pixels_player_dash_effect_capacity, 0, sizeof(pixels_player_dash_effect_capacity));
    attributes_player_dash_effect_capacity[0] = water ? 0x24 : 0;
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (u8*)pixels_player_dash_effect_capacity;
    TEST_BG_TILE_ATTRS = (u8*)attributes_player_dash_effect_capacity;
    layout_width = 4;
    layout_size = 16;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(archive); i++)
        archive[i] = i < 5 ? 20 + i * 4 : 0x13570000 + i;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = TEST_SPRITE_FRAMES = (u8*)archive;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++) {
        visual_objects[i].active = i == 31 && free_slot ? 0 : 1;
        visual_objects[i].id = 0;
    }
    memcpy(pool_expected, visual_objects, sizeof(pool_expected));
    if (free_slot) {
        struct VisualObj* v = &pool_expected[31];
        v->active = water ? 0x41 : 0x21;
        v->id = 3;
        v->unk2 = water ? 8 : 2;
        v->bg_offset = 0;
        v->unk16 = 1;
        v->animation_table = D_8011BF40;
        v->unk3C = (u8*)archive + (water ? 36 : 24);
        v->unk40 = water ? 5 : 0;
        v->unk42 = water ? 0x7888 : 0x7804;
        v->unk15 = obj.unk15;
        v->x_pos.i.hi = 160 + (face ? -1 : 1) * (character ? 26 : 16);
        v->y_pos.i.hi = 120 + (water ? 0 : character ? 17
                                                     : 14);
    }
    player_spawn_dash_spark(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(visual_objects, pool_expected, sizeof(pool_expected));
    assert(SP_BG_TILEMAP == (u8*)map_words && TEST_BG_TILE_PIXELS == (u8*)pixels_player_dash_effect_capacity && TEST_BG_TILE_ATTRS == (u8*)attributes_player_dash_effect_capacity && attributes_player_dash_effect_capacity[0] == (water ? 0x24 : 0) && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive && TEST_SPRITE_FRAMES == (u8*)archive);
    for (i = 0; i < COUNT(map_words); i++)
        assert(map_words[i] == 0x01010101);
    for (i = 0; i < COUNT(pixels_player_dash_effect_capacity); i++)
        assert(pixels_player_dash_effect_capacity[i] == 0);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i < 5 ? 20 + i * 4 : 0x13570000 + i));
    return 1;
}

static struct VisualObj visuals[32];
static struct MiscObj misc[64];
static struct UnkObj afterimages[3];
static struct BazObj muzzles[2];
static u32 gfx[64], frames[64];
static u16 palette[0x152];
static Palette bank[3];
static u32 full_capacity(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    u8 *old_gfx = TEST_PLAYER_GFX, *old_frames = TEST_SPRITE_FRAMES, *old_palette = TEST_PALETTE, *old_bank = TEST_PALETTE_BANK;
    u16 rng = cur_random;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&g_Entity, sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)foo_objects, sizeof(foo_objects) / 4);
    c_test_zero_words((u32*)baz_objects, sizeof(baz_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    c_test_copy_words((u32*)misc, (u32*)misc_objects, sizeof(misc) / 4);
    gfx[0] = frames[0] = 64;
    frames[1] = 128;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    for (i = 0; i < COUNT(palette); i++)
        palette[i] = 0xBEEF;
    for (i = 0; i < 48; i++)
        ((u16*)bank)[i] = 0x1200 + i;
    TEST_PALETTE = (u8*)&palette[1];
    TEST_PALETTE_BANK = (u8*)bank;
    need_palette_load = 0x80;
    engine_obj.stage = 1;
    engine_obj.max_hp = 32;
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.unk1E = -2;
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    for (i = 0; i < COUNT(cameras); i++)
        cameras[i].unk44 = 0;
    player.active = 1;
    player.hp = player.hud_hp = player.spawn_hp = 32;
    for (i = 0; i < 16; i++)
        player.weapon_energy[i] = 48;
    player.animation_table = (u32**)D_80119DF0;
    player.unk38 = (u8*)gfx + 64;
    player.unk3C = (u8*)frames + 64;
    player.unk40 = 0x500;
    player.unk16 = 2;
    player.unk42 = 0x7800;
    player.unk49 = 3;
    entity.is_clone = 1;
    entity.animation_table = (u32**)D_80119DF0;
    entity.hp = entity.hud_hp = entity.spawn_hp = 32;
    entity.unk38 = (u8*)gfx + 64;
    entity.unk3C = (u8*)gfx + 64;
    entity.unk40 = 0x540;
    entity.unk16 = 2;
    entity.unk42 = 0x7800;
    entity.unk49 = 1;
    for (i = 0; i < COUNT(afterimages); i++) {
        afterimages[i].active = 0x11;
        afterimages[i].unk2 = i;
        afterimages[i].unk38 = (u8*)gfx + 64;
        afterimages[i].unk3C = (u8*)frames + 64;
        afterimages[i].unk40 = 0x500;
        afterimages[i].unk42 = 0x780D + i;
        afterimages[i].unk16 = 4;
        if (i == 0)
            afterimages[i].link.player = &g_Player;
        else
            afterimages[i].link.previous = &foo_objects[i - 1];
    }
    for (i = 0; i < COUNT(muzzles); i++) {
        muzzles[i].active = 0x21;
        muzzles[i].unk2 = i;
        muzzles[i].unk3C = (u8*)frames + 128;
        muzzles[i].animation_table = D_8011BF40;
        muzzles[i].unk42 = 0x7800;
        muzzles[i].unk16 = 2;
    }
    player_spawn();
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0);
    assert(c_test_word_difference((u32*)foo_objects, (u32*)afterimages, sizeof(afterimages) / 4) == 0 && c_test_word_difference((u32*)baz_objects, (u32*)muzzles, sizeof(muzzles) / 4) == 0);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc, sizeof(misc) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == 0x81);
    for (i = 0; i < COUNT(palette); i++)
        assert(palette[i] == (i >= 1 && i <= 16 ? 0x1200 + i - 1 : i >= 0x131 && i <= 0x150 ? 0x1210 + i - 0x131
                                                                                            : 0xBEEF));
    for (i = 0; i < 48; i++)
        assert(((u16*)bank)[i] == 0x1200 + i);
    for (i = 0; i < COUNT(gfx); i++)
        assert(gfx[i] == (i == 0 ? 64u : 0) && frames[i] == (i == 0 ? 64u : i == 1 ? 128u
                                                                                   : 0));
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_PALETTE == (u8*)&palette[1] && TEST_PALETTE_BANK == (u8*)bank);
    TEST_PLAYER_GFX = old_gfx;
    TEST_SPRITE_FRAMES = old_frames;
    TEST_PALETTE = old_palette;
    TEST_PALETTE_BANK = old_bank;
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "player_entry_callbacks", NULL, player_entry_callbacks_cases_expected, COUNT(player_entry_callbacks_cases_expected), entry_case },
    { "player_reset_palette_banks", NULL, player_reset_palette_banks_cases_expected, COUNT(player_reset_palette_banks_cases_expected), palette_case },
    { "player_splash_tile_visual_pool", NULL, player_splash_tile_visual_pool_cases_expected, COUNT(player_splash_tile_visual_pool_cases_expected), splash_case },
    { "player_damage", 0, 0, 2, test_player_damage },
    { "player_spawn_dash_dust", 0, 0, 1, test_player_spawn_dash_dust },
    { "player_spawn_wall_slide_dust", 0, 0, 1, test_player_spawn_wall_slide_dust },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "collision_bounds_identity", collision_bounds_identity_cases, collision_bounds_identity_cases_expected, COUNT(collision_bounds_identity_cases), 0 },
    { "Zero_final_fortress_before_cutscene_suppresses_music_and_Jet_rematch_return_resumes_exact_XA_track", NULL, NULL, 2, music },
    { "real_soul_body_control_routes_all_button_edges_and_opposing_directions", NULL, NULL, 16, routing },
    { "actual_X_Zero_bounds_dry_and_water_dash_both_facings_full_last_visual_slot", NULL, NULL, 16, dash },
    { "supported_initial_X_spawn_full_visual_and_misc_pools", NULL, NULL, 1, full_capacity },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(player_entry_callbacks_cases_expected) + COUNT(player_reset_palette_banks_cases_expected) + COUNT(player_splash_tile_visual_pool_cases_expected) + 2 + 1 + 1 + COUNT(pool_full_cases) + COUNT(collision_bounds_identity_cases) + 2 + 16 + 16 + 1;
