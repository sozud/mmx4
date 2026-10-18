#include "test_runtime.h"
#include "main/mains/main_13_heavy_mech.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 func_8004C860_0_expected[] = { 3u, 0u, 2u, 0u, 0u, 0u, 0u };
static u32 test_func_8004C860_0(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.x_pos.val = 0;
    obj.y_pos.val = 0;
    obj.unk5 = 0;
    obj.state = 2;
    func_8004C860(&obj);
    observed_values[0] = (u32)obj.ext.main_13.saved_unk5;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk18.val;
    observed_values[4] = (u32)obj.unk1C.val;
    observed_values[5] = (u32)obj.unk7C;
    observed_values[6] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, func_8004C860_0_expected, 7);
}

struct func_8004C860_1_case {
    u32 on_screen;
    u32 expected[5];
};
static const struct func_8004C860_1_case func_8004C860_1_cases[] = {
    { 0, { 2u, 2u, 0x15u, 0x10u, 0u } },
    { 1, { 2u, 2u, 0x15u, 0x10u, 1u } },
};
static u32 test_func_8004C860_1(u32 row)
{
    const struct func_8004C860_1_case* c = &func_8004C860_1_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct WeaponObj weapons_before[16];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 13;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 16;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)heavy_mech_animations;
    obj.hurt_box = &heavy_mech_hurt_box;
    obj.attack_box = &heavy_mech_attack_box;
    obj.terrain_box = &heavy_mech_terrain_box;
    obj.collision_data = D_801068F0;
    obj.contact_damage = 3;
    obj.ext.main_13.unk80 = 0x8000;
    set_animation(&obj, 0);
    obj.state = 2;
    obj.unk5 = 1;
    obj.ext.main_13.saved_unk5 = 2;
    obj.air_state = 1;
    obj.unk7C = 21;
    obj.unk7E = 4;
    obj.unk42 = 0x9234;
    obj.on_screen = c->on_screen;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 16;
    g_Player.x_pos = obj.x_pos;
    g_Player.y_pos = obj.y_pos;
    g_Player.unk54 = (const u32*)&heavy_mech_attack_box;
    FILL_ACTIVE(weapon_objects, 16, 0);
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    expected = obj;
    expected.unk5 = 2;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk42 = 0x1234;
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004C860(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)g_Player.hp;
    observed_values[4] = (u32)obj.on_screen;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct func_8004CA94_case {
    u32 hi, cur_random;
    u32 expected[4];
};
static const struct func_8004CA94_case func_8004CA94_cases[] = {
    { 229, 2, { 0x8001u, 0u, 0x1000Bu, 2u } },
    { -29, 3, { 0x8001u, 0u, 0x1000Bu, 3u } },
    { 228, 2, { 0x8001u, 0u, 0x1000Bu, 2u } },
};
static u32 test_func_8004CA94(u32 row)
{
    const struct func_8004CA94_case* c = &func_8004CA94_cases[row];
    u32 observed_values[4];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 13;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 16;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)heavy_mech_animations;
    obj.hurt_box = &heavy_mech_hurt_box;
    obj.attack_box = &heavy_mech_attack_box;
    obj.terrain_box = &heavy_mech_terrain_box;
    obj.collision_data = D_801068F0;
    obj.contact_damage = 3;
    obj.ext.main_13.unk80 = 0x8000;
    set_animation(&obj, 0);
    obj.unk7C = 1;
    g_Player.x_pos.i.hi = c->hi;
    obj.x_pos.i.hi = 100;
    cur_random = c->cur_random;
    expected = obj;
    expected.animation_step.fields.duration = 11;
    expected.unk7C = 0;
    expected.ext.main_13.unk80 = 0x8001;
    player_expected = g_Player;
    engine_before = engine_obj;
    func_8004CA94(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    observed_values[0] = (u32)obj.ext.main_13.unk80;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.animation_step.packed;
    observed_values[3] = (u32)cur_random;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

struct heavy_mech_stomp_1_case {
    u32 unk80;
};
static const struct heavy_mech_stomp_1_case heavy_mech_stomp_1_cases[] = {
    { 32769 },
    { 32768 },
};
static u32 test_heavy_mech_stomp_1(u32 row)
{
    const struct heavy_mech_stomp_1_case* c = &heavy_mech_stomp_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 13;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 16;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)heavy_mech_animations;
    obj.hurt_box = &heavy_mech_hurt_box;
    obj.attack_box = &heavy_mech_attack_box;
    obj.terrain_box = &heavy_mech_terrain_box;
    obj.collision_data = D_801068F0;
    obj.contact_damage = 3;
    obj.ext.main_13.unk80 = 0x8000;
    set_animation(&obj, 0);
    set_animation(&obj, 2);
    obj.animation_cursor = (const u8*)&heavy_mech_animations[2][8];
    obj.animation_step = heavy_mech_animations[2][8];
    obj.unk5 = 5;
    obj.unk6 = 1;
    obj.ext.main_13.unk80 = c->unk80;
    expected = obj;
    expected.unk5 = 2;
    expected.unk6 = 0;
    if (obj.ext.main_13.unk80 == 0x8000) {
        set_animation(&expected, 0);
    }
    player_expected = g_Player;
    engine_before = engine_obj;
    heavy_mech_stomp(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

struct heavy_mech_throw_anim_1_case {
    u32 full;
};
static const struct heavy_mech_throw_anim_1_case heavy_mech_throw_anim_1_cases[] = {
    { 1 },
    { 0 },
};
static u32 test_heavy_mech_throw_anim_1(u32 row)
{
    const struct heavy_mech_throw_anim_1_case* c = &heavy_mech_throw_anim_1_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 13;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 16;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)heavy_mech_animations;
    obj.hurt_box = &heavy_mech_hurt_box;
    obj.attack_box = &heavy_mech_attack_box;
    obj.terrain_box = &heavy_mech_terrain_box;
    obj.collision_data = D_801068F0;
    obj.contact_damage = 3;
    obj.ext.main_13.unk80 = 0x8000;
    set_animation(&obj, 0);
    set_animation(&obj, 3);
    obj.animation_cursor = (const u8*)&heavy_mech_animations[3][1];
    obj.animation_step = heavy_mech_animations[3][1];
    obj.unk5 = 4;
    obj.unk6 = 0;
    obj.ext.main_13.unk88 = 2;
    D_8013E198[2] = -1;
    FILL_ACTIVE(shot_objects, 32, 1);
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 5;
    }
    if (!full) {
        shots_expected[31].unk2 = 0;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].bg_offset = obj.bg_offset;
    }
    if (!full) {
        shots_expected[31].x_pos = obj.x_pos;
    }
    if (!full) {
        shots_expected[31].y_pos = obj.y_pos;
    }
    if (!full) {
        shots_expected[31].unk84.collision_state = &obj.ext.main_13.unk80;
    }
    if (!full) {
        shots_expected[31].state = 3;
    }
    expected = obj;
    expected.animation_step.fields.duration = 17;
    player_expected = g_Player;
    engine_before = engine_obj;
    heavy_mech_throw_anim(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    assert(D_8013E198[2] == -1);
    return 1;
}

static void hm_fall(void)
{
    state_reset(4, 0, 0);
    so.gravity = 0x4000;
    heavy_mech_fall(&so);
}
static void hm_land(void)
{
    state_reset(4, 0, 0);
    so.collision_flags = 8;
    so.x_speed = 0x10000;
    heavy_mech_fall(&so);
}
static void hm_land_turn(void)
{
    state_reset(4, 0, 0);
    so.collision_flags = 8;
    so.ext.main_13.unk80 = 0x8000;
    g_Player.x_pos.i.hi = 0x100;
    heavy_mech_fall(&so);
}

static void (*const heavy_mech_misc_cases[])(void) = {
    hm_fall,
    hm_land,
    hm_land_turn,
};
static const u32 heavy_mech_misc_expected[] = { 4u, 0u, 0u, 0u, 0xFFFFC000u, 0x400000u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u };

static u32 test_heavy_mech_misc(u32 row)
{
    return state_run(heavy_mech_misc_cases[row], row, &heavy_mech_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "heavy_mech_misc", 0, 0, COUNT(heavy_mech_misc_cases), test_heavy_mech_misc },
    { "func_8004C860_0", 0, 0, 1, test_func_8004C860_0 },
    { "func_8004C860_1", 0, 0, 2, test_func_8004C860_1 },
    { "func_8004CA94", 0, 0, 3, test_func_8004CA94 },
    { "heavy_mech_stomp_1", 0, 0, 2, test_heavy_mech_stomp_1 },
    { "heavy_mech_throw_anim_1", 0, 0, 2, test_heavy_mech_throw_anim_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(heavy_mech_misc_cases) + 1 + 2 + 3 + 2 + 2;
