#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_41_data_hopper.h"
#include "main/mains/main_56_jet_stingray.h"
#include "main/55C4.h"
#include "support/state_cases.h"
void data_hopper_idle(struct MainObj* arg0);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
void data_hopper_spawn_item(struct MainObj*);
extern struct Unk_unk68 ride_chaser_shot_hit_box[];
void func_80062AEC(struct MainObj*);

static u32 vanish_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 41;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = mode == 0 ? 0 : mode == 3 ? 2
        : mode == 4                      ? 3
                                         : 1;
    obj.unk7C = mode == 1 ? 6 : 5;
    obj.ext.main_41.unk83 = 0x27;
    obj.ext.main_41.unk84 = 0x28;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)data_hopper_animations;
    set_animation_frame(&obj, mode == 3 ? 12 : 11, mode == 3 ? 17 : mode == 2 ? 2
                                                                              : 0);
    before = obj;
    data_hopper_vanish(&obj);
    if (mode == 0 || mode == 1) {
        before.unk6 = mode == 0 ? 1 : 2;
        before.unk17 = mode == 0 ? 11 : 12;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)data_hopper_animations[before.unk17];
        before.animation_step = *data_hopper_animations[before.unk17];
        if (mode == 0) {
            before.unk7C = 0;
            before.ext.main_41.unk83 = before.ext.main_41.unk84 = 0;
        }
    } else if (mode == 2) {
        before.unk7C = 6;
        before.animation_cursor = (const u8*)data_hopper_animations[11];
        before.animation_step = *data_hopper_animations[11];
    } else if (mode == 3) {
        before.state = 2;
        before.unk5 = before.unk6 = 0;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk6 << 16) | ((u32)(u8)obj.unk7C << 24);
}
static const u32 data_hopper_vanish_animation_cases_expected[] = { 0x10401u, 0x6020401u, 0x6010401u, 0x5000002u, 0x5030401u };

struct func_80062778_case {
    u32 unk80, collision_flags;
    u32 expected[12];
};
static const struct func_80062778_case func_80062778_cases[] = {
    { 1, 0, { 1u, 3u, 0u, 0u, 0u, 1u, 0x640000u, 0x500000u, 0u, 0u, 0x2000u, 0x10005u } },
    { 1, 8, { 1u, 5u, 1u, 0u, 0u, 1u, 0x640000u, 0x500000u, 0x2000u, 0u, 0x2000u, 0x10004u } },
    { 1, 10, { 1u, 5u, 1u, 0u, 0u, 1u, 0x640000u, 0x500000u, 0x2000u, 0u, 0x2000u, 0x10004u } },
    { 0, 9, { 1u, 5u, 1u, 0u, 0u, 1u, 0x640000u, 0x500000u, 0xFFFFE000u, 0u, 0x2000u, 0x10004u } },
};
static u32 test_func_80062778(u32 row)
{
    const struct func_80062778_case* c = &func_80062778_cases[row];
    u32 observed_values[12];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct ItemObj items_before[32];
    u8 tiles[256], tiles_before[256];
    memset(&tiles, 0, sizeof(tiles));
    SP_BG_TILEMAP = tiles;
    layout_size = 256;
    layout_width = 16;
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 41;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    data_hopper_init(&obj);
    obj.unk5 = 5;
    obj.unk6 = 0;
    obj.ext.main_41.unk80 = c->unk80;
    obj.collision_flags = c->collision_flags;
    FILL_ACTIVE(item_objects, 32, 1);
    player_before = g_Player;
    memcpy(items_before, item_objects, sizeof(items_before));
    func_80062778(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    c_test_same_words(item_objects, items_before, sizeof(item_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.ext.main_41.unk80;
    observed_values[4] = (u32)obj.ext.main_41.unk83;
    observed_values[5] = (u32)obj.ext.main_41.unk84;
    observed_values[6] = (u32)obj.x_pos.val;
    observed_values[7] = (u32)obj.y_pos.val;
    observed_values[8] = (u32)obj.x_speed;
    observed_values[9] = (u32)obj.y_speed;
    observed_values[10] = (u32)obj.x_accel;
    observed_values[11] = C_TEST_STEP(obj.animation_step.packed);
    return c_test_observe(0, row, observed_values, c->expected, 12);
}

static const u32 func_80062BBC_0_expected[] = { 2u, 3u, 0u, 0u, 0u, 0u, 0x8000u, 0x54006Cu, 0u, 0x640000u, 0x500000u };
static u32 test_func_80062BBC_0(u32 row)
{
    u32 observed_values[11];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct ItemObj items_before[32];
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    u8 pools_full;
    u8 tiles[256], tiles_before[256];
    memset(&tiles, 0, sizeof(tiles));
    SP_BG_TILEMAP = tiles;
    layout_size = 256;
    layout_width = 16;
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 41;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    data_hopper_init(&obj);
    cur_random = 0x1234;
    SPIKE_IMMUNE_SET(g_Player, 1);
    g_Player.x_pos.val = 65536000;
    g_Player.bg_offset = 0;
    obj.unk5 = 5;
    obj.unk6 = 1;
    obj.hp = 1;
    obj.ext.main_41.unk84 = 1;
    obj.ext.main_41.unk83 = 0;
    obj.hurt_box = &data_hopper_terrain_box;
    set_animation(&obj, 0);
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pools_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pools_full ? 1 : 0;
    }
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 56;
    weapon_objects[0].unk50 = (const u8*)ride_chaser_shot_hit_box;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(items_before, item_objects, sizeof(items_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    func_80062BBC(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(item_objects, items_before, sizeof(item_objects));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk63;
    observed_values[5] = (u32)obj.unk65;
    observed_values[6] = (u32)obj.unk42;
    observed_values[7] = TEST_LE_HALVES(&weapon_objects[0].unk80);
    observed_values[8] = (u32)weapon_objects[0].unk98;
    observed_values[9] = (u32)obj.x_pos.val;
    observed_values[10] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, func_80062BBC_0_expected, 11);
}

static const u32 func_80062BBC_1_expected[] = { 2u, 2u, 0u, 6u, 0u, 0u, 0u, 0x3E80000u, 0x500000u };
static u32 test_func_80062BBC_1(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u8 tiles[256], tiles_before[256];
    memset(&tiles, 0, sizeof(tiles));
    SP_BG_TILEMAP = tiles;
    layout_size = 256;
    layout_width = 16;
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 41;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    data_hopper_init(&obj);
    SPIKE_IMMUNE_SET(g_Player, 1);
    g_Player.x_pos.val = 65536000;
    obj.unk2 = 1;
    obj.unk5 = 6;
    obj.unk6 = 2;
    obj.unk7C = 6;
    obj.unk7E = 0;
    obj.x_pos.val = 65536000;
    obj.y_pos.val = 5242880;
    set_animation(&obj, 3);
    FILL_ACTIVE(item_objects, 32, 0);
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_80062BBC(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.unk7E;
    observed_values[5] = (u32)obj.on_screen;
    observed_values[6] = (u32)obj.collision_flags;
    observed_values[7] = (u32)obj.x_pos.val;
    observed_values[8] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, func_80062BBC_1_expected, 9);
}

#include "support/ambush_rise_and_hopper_blink.h"
RESET_CASE(1)
RESET_CASE(2)
RESET_CASE(4)
static const CTestCase data_hopper_blink_reset_cases[] = { RESET_ENTRY(1) RESET_ENTRY(2) RESET_ENTRY(4) };

static const u32 data_hopper_blink_reset_cases_expected[] = { 0x2u, 0x2u, 0x303u };
static void dh_idle(void)
{
    state_reset(2, 0, 0);
    data_hopper_idle(&so);
}

static void (*const data_hopper_misc_cases[])(void) = {
    dh_idle,
};
static const u32 data_hopper_misc_expected[] = { 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_data_hopper_misc(u32 row)
{
    return state_run(data_hopper_misc_cases[row], row, &data_hopper_misc_expected[row * 10]);
}

extern struct Unk_unk68 data_hopper_terrain_box;
static const u8 materials[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0x24, 255 };
static const u8 kinds[] = { 0, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 0, 0 };
static u8 map[3 * 16 * 16];
static u32 attributes[1];
static u16 pixels[2][16][16];
static u32 terrain_kind(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 material = row % COUNT(materials), layer = row / COUNT(materials) % 3, edge = row / COUNT(materials) / 3;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(map, 1, sizeof(map));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = TEST_DISC32(materials[material]);
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 41;
    obj.state = 1;
    obj.unk5 = 5;
    obj.bg_offset = layer;
    obj.terrain_box = &data_hopper_terrain_box;
    obj.ext.main_41.unk80 = 0x7E;
    obj.x_pos.val = (edge ? 256 : 255) * 65536 + 0x1234;
    obj.y_pos.val = (edge ? 256 - 23 : 255 - 23) * 65536 + 0x5678;
    expected = obj;
    expected.ext.main_41.unk80 = kinds[material];
    func_80062650(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (row = 0; row < sizeof(map); row++)
        assert(map[row] == 1);
    for (row = 0; row < sizeof(pixels) / 2; row++)
        assert(((u16*)pixels)[row] == 0);
    assert(attributes[0] == TEST_DISC32(materials[material]));
    assert(data_hopper_terrain_box.unk1 == 0 && data_hopper_terrain_box.unk3 == 23);
    assert(SP_BG_TILEMAP == map && TEST_BG_TILE_PIXELS == (u8*)pixels && TEST_BG_TILE_ATTRS == (u8*)attributes);
    return 1;
}

void data_hopper_update(struct MainObj*);
void data_hopper_spawn_item(struct MainObj*);
void data_hopper_stand(struct MainObj*);
void data_hopper_fall(struct MainObj*);
void data_hopper_land(struct MainObj*);
void func_80062778(struct MainObj*);
void data_hopper_blink(struct MainObj*);
void data_hopper_vanish(struct MainObj*);
void func_80062BBC(struct MainObj*);
void data_hopper_despawn(struct MainObj*);
extern struct Unk_unk68 data_hopper_terrain_box;
#define DH2(step, sub) (state_reset(step, sub, 0), memset(item_objects, 0, sizeof(item_objects)), memset(weapon_objects, 0, sizeof(weapon_objects)), so.active = 0x41, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.terrain_box = &data_hopper_terrain_box, so.collision_flags = 8, state_terrain(0))
#define DH2X() (state_extra = so.state | so.ext.main_41.unk80 << 8 | so.ext.main_41.unk83 << 16 | (u32)so.ext.main_41.unk84 << 24)
static void dh2_init_spawned(void)
{
    DH2(0, 0), so.state = 0, so.unk2 = 1, data_hopper_update(&so), DH2X();
}
static void dh2_spawn_item(void) { DH2(5, 0), data_hopper_spawn_item(&so), DH2X(), state_extra ^= item_objects[0].id << 8 | (u32)item_objects[0].unk2 << 16; }
static void dh2_stand_start(void) { DH2(2, 0), data_hopper_stand(&so), DH2X(); }
static void dh2_stand_drop(void) { DH2(2, 1), so.collision_flags = 0, data_hopper_stand(&so), DH2X(); }
static void dh2_fall_start(void) { DH2(3, 0), so.collision_flags = 0, data_hopper_fall(&so), DH2X(); }
static void dh2_fall_land(void) { DH2(3, 1), data_hopper_fall(&so), DH2X(); }
static void dh2_land_start(void) { DH2(4, 0), so.animation_step.fields.relative_step = 1, data_hopper_land(&so), DH2X(); }
static void dh2_land_flat(void) { DH2(4, 1), so.ext.main_41.unk80 = 2, data_hopper_land(&so), DH2X(); }
static void dh2_land_kind_16(void) { DH2(4, 1), state_terrain(16), so.ext.main_41.unk80 = 2, data_hopper_land(&so), DH2X(); }
static void dh2_hop_wall(void) { DH2(5, 1), so.collision_flags = 9, so.unk15 = PLAYER_FACING_RIGHT, func_80062778(&so), DH2X(); }
static void dh2_hop_slope_ahead(void) { DH2(5, 1), state_terrain(1), so.unk15 = PLAYER_FACING_RIGHT, func_80062778(&so), DH2X(); }
static void dh2_hop_fast_left(void) { DH2(5, 1), state_terrain(1), so.x_speed = -0x50000, func_80062778(&so), DH2X(); }
static void dh2_hop_fast_right(void) { DH2(5, 1), state_terrain(5), so.unk15 = PLAYER_FACING_RIGHT, so.x_speed = 0x50000, func_80062778(&so), DH2X(); }
static void dh2_blink_start(void) { DH2(6, 0), data_hopper_blink(&so), DH2X(); }
static void dh2_blink_open(void) { DH2(6, 1), so.animation_step.fields.relative_step = -1, data_hopper_blink(&so), DH2X(); }
static void dh2_blink_opening(void) { DH2(6, 1), data_hopper_blink(&so), DH2X(); }
static void dh2_blink_count(void) { DH2(6, 2), so.unk7C = 2, so.animation_step.fields.relative_step = -1, data_hopper_blink(&so), DH2X(); }
static void dh2_blink_hold(void) { DH2(6, 2), so.unk7C = 2, data_hopper_blink(&so), DH2X(); }
static void dh2_vanish_spin(void) { DH2(7, 1), so.unk7C = 2, data_hopper_vanish(&so), DH2X(); }
static void dh2_check_items(void)
{
    u32 i;
    DH2(2, 1);
    for (i = 0; i < 4; i++) {
        item_objects[i].active = 1;
        item_objects[i].id = i ? 0x13 : 0x12;
        item_objects[i].unk2 = i == 1 ? 5 : 1;
        item_objects[i].unk68 = (struct Unk_unk68*)&data_hopper_terrain_box;
        item_objects[i].x_pos.i.hi = i == 2 ? 0x200 : 0x80;
        item_objects[i].y_pos.i.hi = 0x60;
    }
    func_80062BBC(&so);
    DH2X(), state_extra ^= item_objects[3].unk7C.item_19.open_requested << 4 | item_objects[2].unk7C.item_19.open_requested << 5;
}
static void dh2_main_vanish_standing(void) { DH2(7, 2), so.ext.main_41.unk83 = 1, so.animation_step.fields.relative_step = 1, func_80062BBC(&so), DH2X(); }
static void dh2_main_away(void) { DH2(1, 0), so.x_pos.i.hi = 0x400, func_80062BBC(&so), DH2X(); }
static void dh2_main_away_spawned(void) { DH2(1, 0), so.unk2 = 1, so.unk7E = 5, so.x_pos.i.hi = 0x400, func_80062BBC(&so), DH2X(), state_extra ^= so.unk7E << 4; }
static void dh2_despawn(void) { DH2(0, 0), so.state = 2, data_hopper_despawn(&so), DH2X(); }
static void dh2_despawn_spawned(void) { DH2(0, 0), so.state = 2, so.unk2 = 1, data_hopper_despawn(&so), DH2X(); }
static void (*const dh2_cases[])(void) = {
    dh2_init_spawned,
    dh2_spawn_item,
    dh2_stand_start,
    dh2_stand_drop,
    dh2_fall_start,
    dh2_fall_land,
    dh2_land_start,
    dh2_land_flat,
    dh2_land_kind_16,
    dh2_hop_wall,
    dh2_hop_slope_ahead,
    dh2_hop_fast_left,
    dh2_hop_fast_right,
    dh2_blink_start,
    dh2_blink_open,
    dh2_blink_opening,
    dh2_blink_count,
    dh2_blink_hold,
    dh2_vanish_spin,
    dh2_check_items,
    dh2_main_vanish_standing,
    dh2_main_away,
    dh2_main_away_spawned,
    dh2_despawn,
    dh2_despawn_spawned,
};
static const u32 dh2_expected[] = {
    0x6u,
    0xF00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x30002u,
    0x1u,
    0x41000000u,
    0x5u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0xFF801301u,
    0x41000000u,
    0x102u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x5u,
    0x0u,
    0x10001u,
    0x41000000u,
    0x3u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x103u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFFFBE00u,
    0x420000u,
    0x4u,
    0x0u,
    0x1000001u,
    0x41000000u,
    0x4u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x104u,
    0x1u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x10001u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x5u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x201u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x1u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x201u,
    0x41000000u,
    0x105u,
    0x0u,
    0x7BE000u,
    0xFFFBE000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x201u,
    0x41000000u,
    0x105u,
    0x0u,
    0x842000u,
    0x42000u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x101u,
    0x41000000u,
    0x106u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x1u,
    0x41000000u,
    0x206u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x3u,
    0x0u,
    0x1u,
    0x41000000u,
    0x106u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x206u,
    0x3u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x206u,
    0x2u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x107u,
    0x2u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x107u,
    0xF00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0xBu,
    0x0u,
    0x11u,
    0x41000000u,
    0x207u,
    0xF00000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x10001u,
    0x41000000u,
    0x1u,
    0x0u,
    0x4000000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x41000000u,
    0x1u,
    0x40000u,
    0x4000000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41u,
    0x41000000u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
};
static u32 dh2_run(u32 row)
{
    return state_run(dh2_cases[row], row, &dh2_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "data_hopper_branch_steps", 0, 0, COUNT(dh2_cases), dh2_run },
    { "data_hopper_misc", 0, 0, COUNT(data_hopper_misc_cases), test_data_hopper_misc },
    { "data_hopper_vanish_animation", NULL, data_hopper_vanish_animation_cases_expected, COUNT(data_hopper_vanish_animation_cases_expected), vanish_case },
    { "func_80062778", 0, 0, 4, test_func_80062778 },
    { "func_80062BBC_0", 0, 0, 1, test_func_80062BBC_0 },
    { "func_80062BBC_1", 0, 0, 1, test_func_80062BBC_1 },
    { "data_hopper_blink_reset", data_hopper_blink_reset_cases, data_hopper_blink_reset_cases_expected, COUNT(data_hopper_blink_reset_cases), 0 },
    { "terrain_kind_layers_and_block_edges", NULL, NULL, COUNT(materials) * 6, terrain_kind },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dh2_cases) + COUNT(data_hopper_misc_cases) + COUNT(data_hopper_vanish_animation_cases_expected) + 4 + 1 + 1 + COUNT(data_hopper_blink_reset_cases) + COUNT(materials) * 6;
