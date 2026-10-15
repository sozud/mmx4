#include "test_runtime.h"
void double_face_player(struct MainObj*);
void double_spawn_afterimage(struct MainObj*, s8);

static u32 wall_left(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.collision_flags = 1;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}

static u32 wall_right(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.collision_flags = 2;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}

static u32 player_right(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = 100;
    g_Player.x_pos.i.hi = 101;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}

static u32 player_level(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = 100;
    g_Player.x_pos.i.hi = 100;
    obj.unk15 = 0xA5;
    double_face_player(&obj);
    return obj.unk15;
}
static const CTestCase double_cases[] = {
    wall_left,
    wall_right,
    player_right,
    player_level,
};
static const u32 double_cases_expected[] = { 0x0u, 0x40u, 0x40u, 0x0u };

static u32 intro_case(u32 mode)
{
    struct MainObj obj, expected;
    struct EffectObj linked, linked_before, pool_expected[32];
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&linked, 0, sizeof(linked));
    memset(effect_objects, 0, sizeof(effect_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = i == 31 && (mode == 0 || mode == 8) ? 0 : 1;
        effect_objects[i].id = 39;
        effect_objects[i].state = 40;
        effect_objects[i].unk2 = 9;
        effect_objects[i].unk5 = 3;
        effect_objects[i].unk6 = 4;
    }
    linked.active = mode == 3 ? 1 : 0;
    linked.id = 24;
    linked.state = 2;
    obj.active = 0x41;
    obj.id = 73;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk7 = 17;
    obj.unk6 = mode < 2 || mode == 8 ? 0 : mode < 4 ? 1
        : mode < 6                                  ? 2
        : mode == 6                                 ? -1
                                                    : 3;
    obj.unk7C = mode == 4 ? 1 : 2;
    obj.ext.main_73.unk80.effect = &linked;
    obj.hp = 127;
    obj.contact_damage = 7;
    obj.invincibility_timer = 3;
    obj.unk62 = 4;
    obj.unk63 = 5;
    obj.bg_offset = -1;
    obj.x_pos.val = (mode == 7 ? 1000 : 100) * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    g_Player.capsule_state = mode == 8 ? 1 : 0;
    g_Player.hp = 27;
    g_Player.script_state = 0;
    g_Player.script_action = 0;
    g_Player.script_facing = 0x22;
    g_Player.spike_immune = 0;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 0x33;
    engine_obj.boss_ptr = NULL;
    engine_obj.gameplay_locked = 0x77;
    expected = obj;
    linked_before = linked;
    player_expected = g_Player;
    engine_expected = engine_obj;
    memcpy(pool_expected, effect_objects, sizeof(pool_expected));
    expected.on_screen = mode != 7;
    if (mode < 2) {
        if (mode == 0) {
            pool_expected[31].active = 1;
            pool_expected[31].id = 24;
            expected.ext.main_73.unk80.effect = &effect_objects[31];
        }
        expected.unk6 = 1;
        expected.unk7 = 0;
        player_expected.script_state = 1;
        player_expected.script_action = 0x14;
        player_expected.script_facing = 0x40;
        player_expected.spike_immune = 1;
        engine_expected.gameplay_locked = 1;
    } else if (mode == 2) {
        expected.contact_damage = 6;
        expected.invincibility_timer = -128;
        expected.unk6 = 2;
        expected.hp = 0;
        expected.unk62 = 0;
        expected.unk63 = 2;
        expected.unk7C = 0x20;
        engine_expected.enable_boss = 0;
        engine_expected.unk25 = 0;
        engine_expected.boss_ptr = &obj;
    } else if (mode == 4 || mode == 5) {
        expected.unk7C--;
        if (mode == 4) {
            expected.unk5 = 2;
            expected.unk6 = 0;
            expected.unk7 = 0;
        }
    }
    func_8008BB6C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(linked) / 4; i++)
        assert(((u32*)&linked)[i] == ((u32*)&linked_before)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    i = (u8)obj.unk6 | ((u32)(u16)obj.unk7C << 8) | ((u32)(u8)obj.hp << 24);
    return i;
}
#define CASE(m)                                                  \
    static u32 double_intro_effect_pool_defaults_intro_##m(void) \
    {                                                            \
        return intro_case(m);                                    \
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
#define ENTRY(m) double_intro_effect_pool_defaults_intro_##m,
static const CTestCase double_intro_effect_pool_defaults_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) };
static const u32 double_intro_effect_pool_defaults_cases_expected[] = { 0x7F000201u, 0x7F000201u, 0x2002u, 0x7F000201u, 0x7F000000u, 0x7F000102u, 0x7F0002FFu, 0x7F000203u, 0x7F000200u };
#undef CASE
#undef ENTRY

static const u32 double_death_blink_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 5u, 0u, 5u };
static u32 test_double_death_blink(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    double_death_blink(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.u.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.u.hi;
    observed_values[4] = (u32)obj.ext.main_73.blink_delay;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, double_death_blink_expected, 9);
}

static const u32 double_spawn_afterimage_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_double_spawn_afterimage(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    s8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    double_spawn_afterimage(&obj, arg1);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].id;
    observed_values[2] = (u32)misc_objects[0].unk15;
    observed_values[3] = (u32)misc_objects[0].unk16;
    observed_values[4] = (u32)misc_objects[0].unk2;
    observed_values[5] = (u32)misc_objects[0].unk40;
    observed_values[6] = (u32)misc_objects[0].unk42;
    observed_values[7] = (u32)misc_objects[0].x_pos.val;
    observed_values[8] = (u32)misc_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, double_spawn_afterimage_expected, 9);
}

static const u32 double_spawn_shot_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_double_spawn_shot(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    s32 arg1;
    s32 arg2;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    arg1 = 0;
    arg2 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    double_spawn_shot(&obj, arg1, arg2);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].id;
    observed_values[2] = (u32)shot_objects[0].unk15;
    observed_values[3] = (u32)shot_objects[0].unk16;
    observed_values[4] = (u32)shot_objects[0].unk2;
    observed_values[5] = (u32)shot_objects[0].unk40;
    observed_values[6] = (u32)shot_objects[0].unk42;
    observed_values[7] = (u32)shot_objects[0].x_pos.val;
    observed_values[8] = (u32)shot_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, double_spawn_shot_expected, 9);
}

static const u32 func_8008BB6C_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u };
static u32 test_func_8008BB6C(u32 row)
{
    u32 observed_values[13];
    struct MainObj obj;
    struct EffectObj child_0;
    u8 child_0_present;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&background_objects, 0, sizeof(background_objects));
    pool_0_full = 255;
    child_0_present = 255;
    obj.ext.main_73.unk80.effect = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8008BB6C(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)engine_obj.enable_boss;
    observed_values[3] = (u32)engine_obj.unk25;
    observed_values[4] = (u32)obj.contact_damage;
    observed_values[5] = (u32)obj.hp;
    observed_values[6] = (u32)obj.invincibility_timer;
    observed_values[7] = (u32)obj.unk5;
    observed_values[8] = (u32)obj.unk6;
    observed_values[9] = (u32)obj.unk62;
    observed_values[10] = (u32)obj.unk63;
    observed_values[11] = (u32)obj.unk7;
    observed_values[12] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, func_8008BB6C_expected, 13);
}

const struct CTestGroup c_test_groups[] = {
    { "double", double_cases, double_cases_expected, COUNT(double_cases), 0 },
    { "double_intro_effect_pool_defaults", double_intro_effect_pool_defaults_cases, double_intro_effect_pool_defaults_cases_expected, COUNT(double_intro_effect_pool_defaults_cases), 0 },
    { "double_death_blink", 0, 0, 1, test_double_death_blink },
    { "double_spawn_afterimage", 0, 0, 1, test_double_spawn_afterimage },
    { "double_spawn_shot", 0, 0, 1, test_double_spawn_shot },
    { "func_8008BB6C", 0, 0, 1, test_func_8008BB6C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_cases) + COUNT(double_intro_effect_pool_defaults_cases) + 1 + 1 + 1 + 1;
