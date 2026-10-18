#include "test_runtime.h"
#include "main/mains/main_41_data_hopper.h"
#include "main/mains/main_56_jet_stingray.h"
#include "main/55C4.h"
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
#define CASE(m)                                              \
    static u32 data_hopper_vanish_animation_vanish_##m(void) \
    {                                                        \
        return vanish_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) data_hopper_vanish_animation_vanish_##m,
static const CTestCase data_hopper_vanish_animation_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 data_hopper_vanish_animation_cases_expected[] = { 0x10401u, 0x6020401u, 0x6010401u, 0x5000002u, 0x5030401u };
#undef CASE
#undef ENTRY

struct data_hopper_blink_case {
    u32 unk6, unk7C, on_screen;
    u32 expected[5];
};
static const struct data_hopper_blink_case data_hopper_blink_cases[] = {
    { -1, 0, 0, { 0u, 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 2, 6, -1, { 0u, 0u, 2u, 0u, 6u } },
};
static u32 test_data_hopper_blink(u32 row)
{
    const struct data_hopper_blink_case* c = &data_hopper_blink_cases[row];
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk6 = c->unk6;
    obj.unk7C = c->unk7C;
    obj.on_screen = c->on_screen;
    data_hopper_blink(&obj);
    observed_values[0] = (u32)obj.ext.main_41.unk83;
    observed_values[1] = (u32)obj.ext.main_41.unk84;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

static const u32 data_hopper_spawn_item_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_data_hopper_spawn_item(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&item_objects, 0, sizeof(item_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_0_full ? 1 : 0;
    }
    data_hopper_spawn_item(&obj);
    observed_values[0] = (u32)item_objects[0].active;
    observed_values[1] = (u32)item_objects[0].id;
    observed_values[2] = (u32)item_objects[0].unk15;
    observed_values[3] = (u32)item_objects[0].unk2;
    observed_values[4] = (u32)item_objects[0].unk40;
    observed_values[5] = (u32)item_objects[0].unk42;
    return c_test_observe(0, row, observed_values, data_hopper_spawn_item_expected, 6);
}

static const u32 data_hopper_vanish_expected[] = { 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u };
static u32 test_data_hopper_vanish(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk6 = -1;
    data_hopper_vanish(&obj);
    observed_values[0] = (u32)obj.ext.main_41.unk83;
    observed_values[1] = (u32)obj.ext.main_41.unk84;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, data_hopper_vanish_expected, 6);
}

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
    obj.unk5 = 5;
    obj.unk6 = 0;
    obj.ext.main_41.unk80 = c->unk80;
    obj.collision_flags = c->collision_flags;
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
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
    observed_values[11] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 12);
}

static const u32 func_80062AEC_expected[] = { 1u, 5u, 1u, 0u };
static u32 test_func_80062AEC(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct ItemObj items_before[32];
    struct PlayerObj player_before;
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 41;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    data_hopper_init(&obj);
    obj.unk5 = 5;
    obj.unk6 = 1;
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
    expected = obj;
    player_before = g_Player;
    memcpy(items_before, item_objects, sizeof(items_before));
    func_80062AEC(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(item_objects, items_before, sizeof(item_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk15;
    return c_test_observe(0, row, observed_values, func_80062AEC_expected, 4);
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
    g_Player.spike_immune = 1;
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
    observed_values[7] = (u32)weapon_objects[0].unk80.word;
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
    g_Player.spike_immune = 1;
    g_Player.x_pos.val = 65536000;
    obj.unk2 = 1;
    obj.unk5 = 6;
    obj.unk6 = 2;
    obj.unk7C = 6;
    obj.unk7E = 0;
    obj.x_pos.val = 65536000;
    obj.y_pos.val = 5242880;
    set_animation(&obj, 3);
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
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
const struct CTestGroup c_test_groups[] = {
    { "data_hopper_vanish_animation", data_hopper_vanish_animation_cases, data_hopper_vanish_animation_cases_expected, COUNT(data_hopper_vanish_animation_cases), 0 },
    { "data_hopper_blink", 0, 0, 2, test_data_hopper_blink },
    { "data_hopper_spawn_item", 0, 0, 1, test_data_hopper_spawn_item },
    { "data_hopper_vanish", 0, 0, 1, test_data_hopper_vanish },
    { "func_80062778", 0, 0, 4, test_func_80062778 },
    { "func_80062AEC", 0, 0, 1, test_func_80062AEC },
    { "func_80062BBC_0", 0, 0, 1, test_func_80062BBC_0 },
    { "func_80062BBC_1", 0, 0, 1, test_func_80062BBC_1 },
    { "data_hopper_blink_reset", data_hopper_blink_reset_cases, data_hopper_blink_reset_cases_expected, COUNT(data_hopper_blink_reset_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(data_hopper_vanish_animation_cases) + 2 + 1 + 1 + 4 + 1 + 1 + 1 + COUNT(data_hopper_blink_reset_cases);
