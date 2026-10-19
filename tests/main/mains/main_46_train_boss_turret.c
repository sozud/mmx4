#include "test_runtime.h"
#include "main/mains/main_46_train_boss_turret.h"
#include "main/55C4.h"
#include "main/mains/main_45_train_boss.h"
#include "main/weapons/weapon_00_lemon.h"
#include "support/state_cases.h"

static const u32 train_boss_turret_fire_expected[] = { 0xDu, 0x11000101u, 0x80u, 0x1B001234u, 0x645678u };
static u32 test_train_boss_turret_fire(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj, parent_expected;
    struct ShotObj shots_before[32];
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
    memset(&main_objects[47], 0, sizeof(main_objects[47]));
    main_objects[47].active = 0x41;
    main_objects[47].id = 45;
    main_objects[47].state = 1;
    main_objects[47].ext.main_45.projectile_command = 3;
    obj.ext.main_46.owner = &main_objects[47].ext.main_45;
    parent_expected = main_objects[47];
    parent_expected.ext.main_45.projectile_command = 0x80;
    FILL_ACTIVE(shot_objects, 32, 1);
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

static struct Main45Ext turret_boss;
static struct Main45LayerSignals turret_signals;
#define TT(st, step, sub) (state_reset(step, sub, 0), memset(&turret_boss, 0, sizeof(turret_boss)), memset(&turret_signals, 0, sizeof(turret_signals)), turret_boss.layer_signals = &turret_signals, so.state = st, so.x_pos.i.hi = 0x100, so.y_pos.i.hi = 0x100, so.ext.main_46.owner = &turret_boss)
#define SEEN() (state_extra = turret_boss.attack_flags | turret_boss.projectile_command << 8 | turret_signals.collision_state << 16 | (u32)shot_objects[0].id << 24)
static void tt_fire_idle(void)
{
    TT(1, 0, 0);
    train_boss_turret_fire(&so);
    SEEN();
}
static void tt_fire(void)
{
    TT(1, 0, 0);
    turret_boss.projectile_command = 3;
    train_boss_turret_fire(&so);
    SEEN();
}
static void tt_arrive(void)
{
    TT(1, 0, 0);
    so.x_speed = 0x10000;
    train_boss_turret_arrive(&so);
}
static void tt_arrive_end(void)
{
    TT(1, 0, 0);
    so.x_pos.i.hi = 0x1AB0;
    train_boss_turret_arrive(&so);
}
static void tt_arrived(void)
{
    TT(1, 0, 1);
    train_boss_turret_arrive(&so);
}
static void tt_main_shielded(void)
{
    TT(1, 2, 1);
    so.unk42 = 0x8000;
    train_boss_turret_update(&so);
    SEEN();
}
static void tt_main_armor_gone(void)
{
    TT(1, 2, 1);
    turret_boss.attack_flags = 7;
    train_boss_turret_update(&so);
    SEEN();
}
static void tt_main_destroyed(void)
{
    TT(1, 2, 1);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    train_boss_turret_update(&so);
    SEEN();
}

static void (*const train_boss_turret_states_cases[])(void) = {
    tt_fire_idle,
    tt_fire,
    tt_arrive,
    tt_arrive_end,
    tt_arrived,
    tt_main_shielded,
    tt_main_armor_gone,
    tt_main_destroyed,
};
static const u32 train_boss_turret_states_expected[] = { 0u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000000u, 0u, 0u, 0u, 0xDu, 0u, 0x18008000u, 0x410000u, 0u, 0u, 0x1010000u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0x78u, 0x1AB00000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x100u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0u, 0x1000000u, 0u, 0u, 0u, 0xEu, 0u, 0xFu, 0x2100u, 0x102u, 0u, 0x1000000u, 0u, 0u, 0u, 0xEu, 1u, 8u, 0x2100u };

static u32 test_train_boss_turret_states(u32 row)
{
    return state_run(train_boss_turret_states_cases[row], row, &train_boss_turret_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "train_boss_turret_states", 0, 0, COUNT(train_boss_turret_states_cases), test_train_boss_turret_states },
    { "train_boss_turret_fire", 0, 0, 1, test_train_boss_turret_fire },
    { "train_boss_turret_main", 0, 0, 3, test_train_boss_turret_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_boss_turret_states_cases) + 1 + 3;
