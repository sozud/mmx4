#include "test_runtime.h"
#include "main/mains/main_04_drill_copter.h"
#include "main/55C4.h"
#include "main/weapons/weapon_00_lemon.h"
extern union AnimationStep* drill_copter_animations[15];
extern struct Unk_unk68 D_801064F0[];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
void func_80044DE4(struct MainObj*);
extern struct Unk_unk68 D_800F9EBC;

struct drill_copter_approach_idle_case {
    u32 x_pos;
    u32 expected[3];
};
static const struct drill_copter_approach_idle_case drill_copter_approach_idle_cases[] = {
    { 6558260, { 3u, 0x641234u, 0x34010004u } },
    { -65536, { 3u, 0xFFFF0000u, 0x34010004u } },
};
static u32 test_drill_copter_approach_idle(u32 row)
{
    const struct drill_copter_approach_idle_case* c = &drill_copter_approach_idle_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.animation_table = (const u8* const*)drill_copter_animations;
    obj.state = 0;
    obj.unk2 = 0;
    obj.bg_offset = 0;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.x_pos.val = c->x_pos;
    obj.state = 3;
    set_animation(&obj, 7);
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    drill_copter_approach_idle(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.x_pos.val;
    observed_values[2] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static const u32 drill_copter_drop_fall_0_expected[] = { 0u, 0u, 0u, 0u };
static u32 test_drill_copter_drop_fall_0(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    drill_copter_drop_fall(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, drill_copter_drop_fall_0_expected, 4);
}

struct drill_copter_drop_fall_1_case {
    u32 unk15, obj_x_speed, expected_x_speed;
    u32 expected[5];
};
static const struct drill_copter_drop_fall_1_case drill_copter_drop_fall_1_cases[] = {
    { 0, -65536, -69632, { 0x631234u, 0x655678u, 0xFFFEF000u, 0xFFFED000u, 0x19010001u } },
    { 64, 65536, 69632, { 0x651234u, 0x655678u, 0x11000u, 0xFFFED000u, 0x19010001u } },
};
static u32 test_drill_copter_drop_fall_1(u32 row)
{
    const struct drill_copter_drop_fall_1_case* c = &drill_copter_drop_fall_1_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.animation_table = (const u8* const*)drill_copter_animations;
    obj.state = 0;
    obj.unk2 = 0;
    obj.bg_offset = 0;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    set_animation(&obj, 4);
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk15 = c->unk15;
    obj.collision_flags = 0;
    obj.air_state = 1;
    obj.x_speed = c->obj_x_speed;
    obj.y_speed = -0x10000;
    obj.x_accel = 0x1000;
    obj.gravity = 0x3000;
    expected = obj;
    expected.animation_cursor = (const union AnimationStep*)&drill_copter_animations[4][1];
    expected.animation_step = drill_copter_animations[4][1];
    expected.x_pos.val = obj.x_pos.val + obj.x_speed;
    expected.y_pos.val = obj.y_pos.val - obj.y_speed;
    expected.x_speed = c->expected_x_speed;
    expected.y_speed = -0x13000;
    player_before = g_Player;
    engine_before = engine_obj;
    drill_copter_drop_fall(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.x_pos.val;
    observed_values[1] = (u32)obj.y_pos.val;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    observed_values[4] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct drill_copter_drop_idle_case {
    u32 x_pos;
    u32 expected[3];
};
static const struct drill_copter_drop_idle_case drill_copter_drop_idle_cases[] = {
    { 6558260, { 3u, 0x641234u, 0x34010004u } },
    { -65536, { 3u, 0xFFFF0000u, 0x34010004u } },
};
static u32 test_drill_copter_drop_idle(u32 row)
{
    const struct drill_copter_drop_idle_case* c = &drill_copter_drop_idle_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.animation_table = (const u8* const*)drill_copter_animations;
    obj.state = 0;
    obj.unk2 = 0;
    obj.bg_offset = 0;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.x_pos.val = c->x_pos;
    obj.state = 3;
    set_animation(&obj, 7);
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    drill_copter_drop_idle(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.x_pos.val;
    observed_values[2] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static const u32 drill_copter_fire_shots_expected[] = { 0x38010001u, 3u, 2u, 1u };
static u32 test_drill_copter_fire_shots(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct ShotObj shots_before[32];
    u8 pools_full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.animation_table = (const u8* const*)drill_copter_animations;
    obj.state = 0;
    obj.unk2 = 0;
    obj.bg_offset = 0;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    set_animation(&obj, 7);
    obj.animation_cursor = &drill_copter_animations[7][5];
    obj.animation_step = drill_copter_animations[7][5];
    obj.unk5 = 5;
    obj.unk6 = 2;
    obj.unk7E = 3;
    D_8013E198[2] = -1;
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    expected = obj;
    expected.animation_step.fields.duration = 1;
    expected.animation_step.fields.event = 0;
    player_before = g_Player;
    engine_before = engine_obj;
    drill_copter_fire_shots(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    assert(D_8013E198[2] == -1);
    observed_values[0] = (u32)obj.animation_step.packed;
    observed_values[1] = (u32)obj.unk7E;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)shot_objects[31].active;
    return c_test_observe(0, row, observed_values, drill_copter_fire_shots_expected, 4);
}

struct drill_copter_noop_case {
    u32 x_pos;
    u32 expected[3];
};
static const struct drill_copter_noop_case drill_copter_noop_cases[] = {
    { 6558260, { 3u, 0x641234u, 0x34010004u } },
    { -65536, { 3u, 0xFFFF0000u, 0x34010004u } },
};
static u32 test_drill_copter_noop(u32 row)
{
    const struct drill_copter_noop_case* c = &drill_copter_noop_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.animation_table = (const u8* const*)drill_copter_animations;
    obj.state = 0;
    obj.unk2 = 0;
    obj.bg_offset = 0;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.x_pos.val = c->x_pos;
    obj.state = 3;
    set_animation(&obj, 7);
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    drill_copter_noop(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.x_pos.val;
    observed_values[2] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct drill_copter_sway_idle_case {
    u32 x_pos;
    u32 expected[3];
};
static const struct drill_copter_sway_idle_case drill_copter_sway_idle_cases[] = {
    { 6558260, { 3u, 0x641234u, 0x34010003u } },
    { -65536, { 3u, 0xFFFF0000u, 0x34010003u } },
};
static u32 test_drill_copter_sway_idle(u32 row)
{
    const struct drill_copter_sway_idle_case* c = &drill_copter_sway_idle_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.animation_table = (const u8* const*)drill_copter_animations;
    obj.state = 0;
    obj.unk2 = 0;
    obj.bg_offset = 0;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.x_pos.val = c->x_pos;
    obj.state = 3;
    set_animation(&obj, 7);
    expected = obj;
    --expected.animation_step.fields.duration;
    player_before = g_Player;
    engine_before = engine_obj;
    drill_copter_sway_idle(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.x_pos.val;
    observed_values[2] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct func_80044508_case {
    u32 unk2;
    u32 expected[6];
};
static const struct func_80044508_case func_80044508_cases[] = {
    { 0, { 2u, 0u, 0u, 0x9234u, 0x630063u, 0xA30Du } },
    { 2, { 2u, 0u, 2u, 0x9234u, 0x630063u, 0x366Au } },
};
static u32 test_func_80044508(u32 row)
{
    const struct func_80044508_case* c = &func_80044508_cases[row];
    u32 observed_values[6];
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    struct WeaponObj weapons_expected[16];
    struct ShotObj shots_before[32];
    struct VisualObj visuals_before[32];
    struct MiscObj misc_before[64];
    struct ItemObj items_before[32];
    u8 pools_full, fatal;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 4;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    D_8013E198[0] = -1;
    D_8013E198[1] = -1;
    D_8013E198[2] = -1;
    D_8013E198[3] = -1;
    D_8013E198[4] = -1;
    D_8013E198[5] = -1;
    g_Player.bg_offset = 0;
    g_Player.x_pos.val = 0;
    g_Player.y_pos.val = 0;
    g_Player.spike_immune = 1;
    engine_obj.stage = 0;
    engine_obj.substage = 0;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    cur_random = 0x1234;
    func_80044458(&obj);
    obj.unk5 = 1;
    obj.unk2 = c->unk2;
    obj.hp = 3;
    fatal = 1;
    pools_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pools_full ? 1 : 0;
    }
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
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pools_full ? 1 : 0;
    }
    pools_full = 0;
    {
        u32 slot;
        for (slot = 0; slot < 16; ++slot)
            weapon_objects[slot].active = pools_full ? 1 : 0;
    }
    memset(&weapon_objects[0], 0, sizeof(weapon_objects[0]));
    weapon_objects[0].active = 1;
    weapon_objects[0].id = 0;
    weapon_objects[0].unk50 = (const u8*)lemon_hit_box;
    weapon_objects[0].x_pos = obj.x_pos;
    weapon_objects[0].y_pos = obj.y_pos;
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.hp = 0;
    expected.unk42 = 0x9234;
    expected.on_screen = 1;
    if (fatal) {
        expected.state = 2;
    }
    if (fatal) {
        expected.on_screen = 0;
    }
    player_before = g_Player;
    engine_before = engine_obj;
    background_before = background_objects[0];
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    weapons_expected[0].unk98 = 1;
    weapons_expected[0].unk80.word = 0x00630063;
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(items_before, item_objects, sizeof(items_before));
    assert(((const u8*)D_801064F0)[1] == 3);
    func_80044508(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(shot_objects, shots_before, sizeof(shots_before));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_before));
    c_test_same_words(item_objects, items_before, sizeof(items_before));
    assert(D_8013E198[0] == -1 && D_8013E198[1] == -1 && D_8013E198[2] == -1 && D_8013E198[3] == -1 && D_8013E198[4] == -1 && D_8013E198[5] == -1);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.hp;
    observed_values[2] = (u32)obj.unk2;
    observed_values[3] = (u32)obj.unk42;
    observed_values[4] = (u32)weapon_objects[0].unk80.word;
    observed_values[5] = (u32)cur_random;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

static const u32 func_80044DE4_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_80044DE4(u32 row)
{
    u32 observed_values[27];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800F9EBC, 0, sizeof(D_800F9EBC));
    memset(&main_objects, 0, sizeof(main_objects));
    obj.unk7C = 1;
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 48; ++slot)
            main_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_80044DE4(&obj);
    observed_values[0] = (u32)main_objects[0].active;
    observed_values[1] = (u32)main_objects[0].air_state;
    observed_values[2] = (u32)main_objects[0].bg_offset;
    observed_values[3] = (u32)main_objects[0].contact_damage;
    observed_values[4] = (u32)main_objects[0].gravity;
    observed_values[5] = (u32)main_objects[0].hp;
    observed_values[6] = (u32)main_objects[0].id;
    observed_values[7] = (u32)main_objects[0].on_screen;
    observed_values[8] = (u32)main_objects[0].state;
    observed_values[9] = (u32)main_objects[0].unk15;
    observed_values[10] = (u32)main_objects[0].unk16;
    observed_values[11] = (u32)main_objects[0].unk18.val;
    observed_values[12] = (u32)main_objects[0].unk1C.val;
    observed_values[13] = (u32)main_objects[0].unk2;
    observed_values[14] = (u32)main_objects[0].unk40;
    observed_values[15] = (u32)main_objects[0].unk42;
    observed_values[16] = (u32)main_objects[0].unk5;
    observed_values[17] = (u32)main_objects[0].x_accel;
    observed_values[18] = (u32)main_objects[0].x_pos.val;
    observed_values[19] = (u32)main_objects[0].x_speed;
    observed_values[20] = (u32)main_objects[0].y_pos.val;
    observed_values[21] = (u32)main_objects[0].y_speed;
    observed_values[22] = (u32)obj.unk2;
    observed_values[23] = (u32)obj.unk5;
    observed_values[24] = (u32)obj.unk6;
    observed_values[25] = (u32)obj.unk7C;
    observed_values[26] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, func_80044DE4_expected, 27);
}

const struct CTestGroup c_test_groups[] = {
    { "drill_copter_approach_idle", 0, 0, 2, test_drill_copter_approach_idle },
    { "drill_copter_drop_fall_0", 0, 0, 1, test_drill_copter_drop_fall_0 },
    { "drill_copter_drop_fall_1", 0, 0, 2, test_drill_copter_drop_fall_1 },
    { "drill_copter_drop_idle", 0, 0, 2, test_drill_copter_drop_idle },
    { "drill_copter_fire_shots", 0, 0, 1, test_drill_copter_fire_shots },
    { "drill_copter_noop", 0, 0, 2, test_drill_copter_noop },
    { "drill_copter_sway_idle", 0, 0, 2, test_drill_copter_sway_idle },
    { "func_80044508", 0, 0, 2, test_func_80044508 },
    { "func_80044DE4", 0, 0, 1, test_func_80044DE4 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1 + 2 + 2 + 1 + 2 + 2 + 2 + 1;
