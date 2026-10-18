#include "test_runtime.h"
#include "main/mains/main_46_train_boss_turret.h"
#include "main/55C4.h"
#include "main/mains/main_45_train_boss.h"
#include "main/weapons/weapon_00_lemon.h"

static const u32 train_boss_turret_arrive_0_expected[] = { 0u, 0xFFFFFFFFu, 0u };
static u32 test_train_boss_turret_arrive_0(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk6 = -1;
    train_boss_turret_arrive(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, train_boss_turret_arrive_0_expected, 3);
}

static const u32 train_boss_turret_arrive_1_expected[] = { 2u, 1u, 0x1B001234u };
static u32 test_train_boss_turret_arrive_1(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x45;
    obj.id = 46;
    obj.x_pos.val = 452989492;
    obj.y_pos.val = 6575736;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)train_boss_animations;
    train_boss_turret_init(&obj);
    set_animation(&obj, 0xB);
    obj.unk6 = 1;
    expected = obj;
    player_before = g_Player;
    train_boss_turret_arrive(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &expected, sizeof(obj));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.x_pos.val;
    return c_test_observe(0, row, observed_values, train_boss_turret_arrive_1_expected, 3);
}

struct train_boss_turret_destroyed_case {
    u32 x_pos, on_screen;
    u32 expected[4];
};
static const struct train_boss_turret_destroyed_case train_boss_turret_destroyed_cases[] = {
    { 452989492, 1, { 1u, 2u, 0x1B001234u, 0x645678u } },
    { 805311028, 0, { 0u, 2u, 0x30001234u, 0x645678u } },
};
static u32 test_train_boss_turret_destroyed(u32 row)
{
    const struct train_boss_turret_destroyed_case* c = &train_boss_turret_destroyed_cases[row];
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x45;
    obj.id = 46;
    obj.x_pos.val = 452989492;
    obj.y_pos.val = 6575736;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)train_boss_animations;
    train_boss_turret_init(&obj);
    set_animation(&obj, 0xB);
    obj.state = 2;
    obj.x_pos.val = c->x_pos;
    background_objects[0].x_pos.val = 436207616;
    background_objects[0].y_pos.val = 0;
    expected = obj;
    expected.on_screen = c->on_screen;
    player_before = g_Player;
    train_boss_turret_destroyed(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &expected, sizeof(obj));
    observed_values[0] = (u32)obj.on_screen;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.x_pos.val;
    observed_values[3] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 train_boss_turret_fire_expected[] = { 0xDu, 0x11000101u, 0x80u, 0x1B001234u, 0x645678u };
static u32 test_train_boss_turret_fire(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj, parent_expected;
    struct ShotObj shots_before[32];
    struct PlayerObj player_before;
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x45;
    obj.id = 46;
    obj.x_pos.val = 452989492;
    obj.y_pos.val = 6575736;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)train_boss_animations;
    train_boss_turret_init(&obj);
    set_animation(&obj, 0xB);
    memset(&main_objects[47], 0, sizeof(main_objects[47]));
    main_objects[47].active = 0x41;
    main_objects[47].id = 45;
    main_objects[47].state = 1;
    main_objects[47].ext.main_45.projectile_command = 3;
    obj.ext.main_46.owner = &main_objects[47].ext.main_45;
    parent_expected = main_objects[47];
    parent_expected.ext.main_45.projectile_command = 0x80;
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    player_before = g_Player;
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    train_boss_turret_fire(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_objects[47], &parent_expected, sizeof(main_objects[47]));
    c_test_same_words(shot_objects, shots_before, sizeof(shot_objects));
    observed_values[0] = (u32)obj.unk17;
    observed_values[1] = (u32)obj.animation_step.packed;
    observed_values[2] = (u32)main_objects[47].ext.main_45.projectile_command;
    observed_values[3] = (u32)obj.x_pos.val;
    observed_values[4] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, train_boss_turret_fire_expected, 5);
}

struct train_boss_turret_main_case {
    u32 v_47_main_45_attack_flags, hp, active, parent_expected_main_45_attack_flags, unk17;
    u32 expected[12];
};
static const struct train_boss_turret_main_case train_boss_turret_main_cases[] = {
    { 7, 32, 0, 15, 0, { 2u, 3u, 0u, 0x20u, 0x1234u, 0x1B001234u, 0x645678u, 0xFu, 0u, 0x12000101u, 0u, 0u } },
    { 0, 3, 1, 8, 0, { 2u, 3u, 0u, 0u, 0x1234u, 0x1B001234u, 0x645678u, 8u, 0u, 0x12000101u, 0x81AABu, 1u } },
    { 0, 32, 1, 0, 2, { 1u, 3u, 0u, 0x1Du, 0x9234u, 0x1B001234u, 0x645678u, 0u, 2u, 0xF000101u, 0x81AABu, 1u } },
};
static u32 test_train_boss_turret_main(u32 row)
{
    const struct train_boss_turret_main_case* c = &train_boss_turret_main_cases[row];
    u32 observed_values[12];
    struct MainObj obj, parent_expected;
    struct LayerObj layers_expected[4];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x45;
    obj.id = 46;
    obj.x_pos.val = 452989492;
    obj.y_pos.val = 6575736;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)train_boss_animations;
    train_boss_turret_init(&obj);
    set_animation(&obj, 0xB);
    cur_random = 0x1234;
    memset(&main_objects[47], 0, sizeof(main_objects[47]));
    memset(&layer_objects[3], 0, sizeof(layer_objects[3]));
    main_objects[47].active = 0x41;
    main_objects[47].id = 45;
    main_objects[47].state = 1;
    main_objects[47].animation_table = obj.animation_table;
    main_objects[47].ext.main_45.attack_flags = c->v_47_main_45_attack_flags;
    main_objects[47].ext.main_45.layer_signals = (struct Main45LayerSignals*)&layer_objects[3].unk16;
    main_objects[47].ext.main_45.layer_bg_offset = (u8*)&layer_objects[3].bg_offset;
    main_objects[47].ext.main_45.layer_parameter = &layer_objects[3].unk15;
    layer_objects[3].active = 1;
    layer_objects[3].id = 3;
    layer_objects[3].unk2 = 1;
    obj.ext.main_46.owner = &main_objects[47].ext.main_45;
    obj.unk5 = 3;
    obj.hp = c->hp;
    g_Player.spike_immune = 1;
    g_Player.x_pos.val = 65536000;
    background_objects[0].x_pos.val = 436207616;
    background_objects[0].y_pos.val = 0;
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
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = c->active;
    weapon_objects[0].id = 0;
    weapon_objects[0].unk50 = (const u8*)lemon_hit_box;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    weapon_objects[0].x_pos.i.hi = obj.x_pos.i.hi - 0x54;
    weapon_objects[0].y_pos.i.hi = obj.y_pos.i.hi - 0x5B;
    parent_expected = main_objects[47];
    parent_expected.ext.main_45.attack_flags = c->parent_expected_main_45_attack_flags;
    memcpy(layers_expected, layer_objects, sizeof(layers_expected));
    layers_expected[3].unk17 = c->unk17;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    train_boss_turret_main(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    c_test_same_words(&main_objects[47], &parent_expected, sizeof(main_objects[47]));
    c_test_same_words(layer_objects, layers_expected, sizeof(layer_objects));
    c_test_same_words(visual_objects, visuals_before, sizeof(visual_objects));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.unk42;
    observed_values[5] = (u32)obj.x_pos.val;
    observed_values[6] = (u32)obj.y_pos.val;
    observed_values[7] = (u32)main_objects[47].ext.main_45.attack_flags;
    observed_values[8] = (u32)layer_objects[3].unk17;
    observed_values[9] = (u32)obj.animation_step.packed;
    observed_values[10] = (u32)weapon_objects[0].unk80.word;
    observed_values[11] = (u32)weapon_objects[0].unk98;
    return c_test_observe(0, row, observed_values, c->expected, 12);
}

static const u32 train_boss_turret_start_idle_expected[] = { 3u, 0u };
static u32 test_train_boss_turret_start_idle(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x45;
    obj.id = 46;
    obj.x_pos.val = 452989492;
    obj.y_pos.val = 6575736;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)train_boss_animations;
    train_boss_turret_init(&obj);
    set_animation(&obj, 0xB);
    obj.unk5 = 1;
    obj.unk6 = 1;
    expected = obj;
    expected.unk5 = 3;
    expected.unk6 = 0;
    player_before = g_Player;
    train_boss_turret_start_idle(&obj);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&obj, &expected, sizeof(obj));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, train_boss_turret_start_idle_expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "train_boss_turret_arrive_0", 0, 0, 1, test_train_boss_turret_arrive_0 },
    { "train_boss_turret_arrive_1", 0, 0, 1, test_train_boss_turret_arrive_1 },
    { "train_boss_turret_destroyed", 0, 0, 2, test_train_boss_turret_destroyed },
    { "train_boss_turret_fire", 0, 0, 1, test_train_boss_turret_fire },
    { "train_boss_turret_main", 0, 0, 3, test_train_boss_turret_main },
    { "train_boss_turret_start_idle", 0, 0, 1, test_train_boss_turret_start_idle },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 2 + 1 + 3 + 1;
