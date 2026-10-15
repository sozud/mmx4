#include "test_runtime.h"
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
#define CASE(m)                                       \
    static u32 player_entry_callbacks_entry_##m(void) \
    {                                                 \
        return entry_case(m);                         \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
CASE(10)
CASE(11)
CASE(12)
CASE(13)
#define ENTRY(m) player_entry_callbacks_entry_##m,
static const CTestCase player_entry_callbacks_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) ENTRY(12) ENTRY(13) };
static const u32 player_entry_callbacks_cases_expected[] = { 0xC807u, 0x100C800u, 0x101CB02u, 0x1069B02u, 0xC802u, 0x2CB02u, 0x9CA02u, 0x1CA02u, 0x1AA02u, 0x100C824u, 0x100C812u, 0x100AB02u, 0x100C800u, 0xC802u };
#undef CASE
#undef ENTRY

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
#define CASE(m)                                             \
    static u32 player_reset_palette_banks_palette_##m(void) \
    {                                                       \
        return palette_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) player_reset_palette_banks_palette_##m,
static const CTestCase player_reset_palette_banks_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 player_reset_palette_banks_cases_expected[] = { 0x12101200u, 0xBEEFBEEFu, 0x12501230u, 0xBEEF1200u, 0xBEEF12D0u };
#undef CASE
#undef ENTRY

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
#define CASE(m)                                                \
    static u32 player_splash_tile_visual_pool_splash_##m(void) \
    {                                                          \
        return splash_case(m);                                 \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) player_splash_tile_visual_pool_splash_##m,
static const CTestCase player_splash_tile_visual_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 player_splash_tile_visual_pool_cases_expected[] = { 0x3C2700u, 0x3C2701u, 0x3C2701u, 0xB80301u };
#undef CASE
#undef ENTRY

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

static const u32 player_map_buttons_expected[] = { 0x7F0u };
static u32 test_player_map_buttons(u32 row)
{
    u32 observed_values[1];
    u16 return_value;
    s32 pad;
    pad = 61694;
    return_value = player_map_buttons(pad);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, player_map_buttons_expected, 1);
}

static const u32 player_spawn_dash_dust_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_player_spawn_dash_dust(u32 row)
{
    u32 observed_values[6];
    struct PlayerObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
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
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    player_spawn_wall_slide_dust(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].state;
    observed_values[4] = (u32)visual_objects[0].unk5;
    observed_values[5] = (u32)visual_objects[0].unk6;
    return c_test_observe(0, row, observed_values, player_spawn_wall_slide_dust_expected, 6);
}

static u32 normalize_return(struct WeaponObj* value)
{
    u32 i;
    if (value == NULL)
        return 0;
    for (i = 0; i < 16; ++i)
        if (value == &weapon_objects[i])
            return i + 1;
    assert(0);
    return ~0u;
}
static const u32 player_spawn_weapon_expected[] = { 0u, 1u, 0u, 0u, 0u };
static u32 test_player_spawn_weapon(u32 row)
{
    u32 observed_values[5];
    struct PlayerObj argument_obj_3;
    u8 pool_0_full;
    struct WeaponObj* return_value;
    u32 normalized_return;
    s8 active;
    s8 id;
    s8 type;
    memset(&argument_obj_3, 0, sizeof(argument_obj_3));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    pool_0_full = 255;
    active = 0;
    id = 0;
    type = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pool_0_full ? 1 : 0;
    }
    return_value = player_spawn_weapon(active, id, type, &argument_obj_3);
    normalized_return = normalize_return(return_value);
    observed_values[0] = (u32)normalized_return;
    observed_values[1] = (u32)weapon_objects[0].active;
    observed_values[2] = (u32)weapon_objects[0].bg_offset;
    observed_values[3] = (u32)weapon_objects[0].id;
    observed_values[4] = (u32)weapon_objects[0].unk2;
    return c_test_observe(0, row, observed_values, player_spawn_weapon_expected, 5);
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
const struct CTestGroup c_test_groups[] = {
    { "player_entry_callbacks", player_entry_callbacks_cases, player_entry_callbacks_cases_expected, COUNT(player_entry_callbacks_cases), 0 },
    { "player_reset_palette_banks", player_reset_palette_banks_cases, player_reset_palette_banks_cases_expected, COUNT(player_reset_palette_banks_cases), 0 },
    { "player_splash_tile_visual_pool", player_splash_tile_visual_pool_cases, player_splash_tile_visual_pool_cases_expected, COUNT(player_splash_tile_visual_pool_cases), 0 },
    { "player_damage", 0, 0, 2, test_player_damage },
    { "player_map_buttons", 0, 0, 1, test_player_map_buttons },
    { "player_spawn_dash_dust", 0, 0, 1, test_player_spawn_dash_dust },
    { "player_spawn_wall_slide_dust", 0, 0, 1, test_player_spawn_wall_slide_dust },
    { "player_spawn_weapon", 0, 0, 1, test_player_spawn_weapon },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "collision_bounds_identity", collision_bounds_identity_cases, collision_bounds_identity_cases_expected, COUNT(collision_bounds_identity_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(player_entry_callbacks_cases) + COUNT(player_reset_palette_banks_cases) + COUNT(player_splash_tile_visual_pool_cases) + 2 + 1 + 1 + 1 + 1 + COUNT(pool_full_cases) + COUNT(collision_bounds_identity_cases);
