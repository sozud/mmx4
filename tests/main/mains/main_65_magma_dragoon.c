#include "test_runtime.h"
#include "main/mains/main_65_magma_dragoon.h"
#include "main/55C4.h"
extern void* magma_dragoon_animations[38];

static u32 breath_case(u32 mode)
{
    struct MainObj obj, expected, linked, linked_before;
    struct ShotObj shots[32];
    struct PlayerObj player_before = g_Player;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    union AnimationStep* animation = (union AnimationStep*)magma_dragoon_animations[10];
    u32 i, step = mode <= 1 ? 3 : mode == 2 ? 6
        : mode <= 4                         ? 9
        : mode == 5                         ? 0
                                            : 2;
    memset(&obj, 0, sizeof(obj));
    memset(&linked, 0, sizeof(linked));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        struct ShotObj* s = &shot_objects[i];
        s->active = 1;
        s->id = 39;
        s->state = 40;
        s->unk2 = 9;
        s->unk5 = 3;
        s->unk6 = 4;
        s->unk7 = 5;
        s->x_pos.val = 50 * 65536 + 0xBEEF;
        s->y_pos.val = 60 * 65536 + 0xCAFE;
        s->unk50.data = (const u8*)&box;
        s->unk54 = (const u8*)&box;
        s->unk68 = &box;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 7;
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 7;
        s->unk62 = s->unk63 = s->unk7A = s->unk75 = 7;
    }
    if (mode == 1 || mode == 6)
        shot_objects[31].active = 0;
    linked.active = 0x41;
    linked.id = 41;
    linked.state = 1;
    linked.unk6 = 4;
    obj.active = 0x41;
    obj.id = 65;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.main_65.object = &linked;
    obj.ext.main_65.attack = mode == 3 ? 3 : 2;
    obj.animation_table = (const u8* const*)magma_dragoon_animations;
    set_animation(&obj, 10);
    obj.animation_cursor = (const u8*)&animation[step];
    obj.animation_step = animation[step];
    if (mode == 6)
        obj.animation_step.fields.duration = 1;
    expected = obj;
    linked_before = linked;
    memcpy(shots, shot_objects, sizeof(shots));
    if (mode >= 3 && mode <= 4) {
        expected.unk6 = 0;
        expected.unk5 = mode == 3 ? 12 : 3;
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)magma_dragoon_animations[0];
        expected.animation_step = *(union AnimationStep*)magma_dragoon_animations[0];
    } else {
        if (mode == 6) {
            expected.animation_cursor = (const u8*)&animation[3];
            expected.animation_step = animation[3];
        } else
            expected.animation_step.fields.duration--;
        if (mode <= 1 || mode == 6) {
            expected.animation_step.fields.event = 0;
            expected.ext.main_65.object = mode == 0 ? NULL : MAIN_OBJECT(&shot_objects[31]);
            if (mode != 0) {
                struct ShotObj* s = &shots[31];
                s->active = 0x41;
                s->id = 0x29;
                s->unk2 = 2;
                s->unk7C = WEAPON_OBJECT(&obj);
                s->unk50.data = NULL;
                s->unk54 = NULL;
                s->unk68 = NULL;
                s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 0;
                s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 0;
                s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
            }
        } else if (mode == 2) {
            expected.animation_step.fields.event = 0;
            linked_before.unk6 = 5;
        }
    }
    magma_dragoon_breath_fire(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(linked) / 4; i++)
        assert(((u32*)&linked)[i] == ((u32*)&linked_before)[i]);
    for (i = 0; i < sizeof(shots) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)shots)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)linked.unk6 << 16) | ((u32)(obj.ext.main_65.object != NULL) << 24);
}
#define CASE(m)                                             \
    static u32 dragoon_breath_link_and_end_breath_##m(void) \
    {                                                       \
        return breath_case(m);                              \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
#define ENTRY(m) dragoon_breath_link_and_end_breath_##m,
static const CTestCase dragoon_breath_link_and_end_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) };
static const u32 dragoon_breath_link_and_end_cases_expected[] = { 0x40107u, 0x1040107u, 0x1050107u, 0x104000Cu, 0x1040003u, 0x1040107u, 0x1040107u };
#undef CASE
#undef ENTRY

static u32 flame_case(u32 mode)
{
    struct MainObj owner, owner_before;
    struct MiscObj pool[64];
    struct PlayerObj player_before = g_Player;
    u32 i, available = mode < 4 ? mode : mode == 7 ? 1
        : mode == 5                                ? 2
                                                   : 3;
    u32 arg = mode < 4 ? 0 : mode == 4 || mode == 7 ? 1
        : mode == 5                                 ? 2
                                                    : 0xFFFFFFFF;
    u32 count = available < (arg < 2 ? 3 : 2) ? available : arg < 2 ? 3
                                                                    : 2;
    memset(&owner, 0, sizeof(owner));
    memset(misc_objects, 0, sizeof(misc_objects));
    owner.active = 0x41;
    owner.id = 65;
    owner.state = 1;
    owner.unk5 = 6;
    owner.unk6 = 2;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 200 * 65536 + 0x5678;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - available ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].unk7 = 5;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    owner_before = owner;
    memcpy(pool, misc_objects, sizeof(pool));
    for (i = 0; i < count; i++) {
        struct MiscObj* child = &pool[64 - available + i];
        child->active = 0x41;
        child->id = 0x26;
        child->unk2 = i < 2 ? i + 2 : arg;
        child->ext.misc_7.position = ANIMATED_OBJECT(&owner);
    }
    magma_dragoon_spawn_flames(ANIMATED_OBJECT(&owner), arg);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)misc_objects[61].active | ((u32)(u8)misc_objects[62].active << 8) | ((u32)(u8)misc_objects[63].active << 16) | ((u32)(u8)misc_objects[63].unk2 << 24);
}
#define CASE(m)                                               \
    static u32 dragoon_flame_allocation_steps_flame_##m(void) \
    {                                                         \
        return flame_case(m);                                 \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) dragoon_flame_allocation_steps_flame_##m,
static const CTestCase dragoon_flame_allocation_steps_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 dragoon_flame_allocation_steps_cases_expected[] = { 0x9010101u, 0x2410101u, 0x3414101u, 0x414141u, 0x1414141u, 0x3414101u, 0x9004141u, 0x2410101u };
#undef CASE
#undef ENTRY

static u32 leap_case(u32 right, u32 observation)
{
    struct MainObj obj, before;
    struct MiscObj pool_before[64];
    struct PlayerObj player_before;
    struct BackgroundObj bg_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x17;
    }
    magma_dragoon_arena_left = 0;
    magma_dragoon_arena_right = 1000;
    D_8013E198[2] = -1;
    obj.active = 0x41;
    obj.id = 65;
    obj.state = 1;
    obj.unk6 = 0x21;
    obj.unk15 = right ? 0x40 : 0;
    obj.air_state = 1;
    obj.collision_flags = 8;
    obj.x_pos.val = (right ? 1016 : 32) * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.y_speed = -65536;
    obj.ext.main_65.leap_frames = 2;
    obj.ext.main_65.leap_to_right = right;
    obj.animation_table = (const u8* const*)magma_dragoon_animations;
    set_animation(&obj, 0);
    before = obj;
    player_before = g_Player;
    memcpy(pool_before, misc_objects, sizeof(pool_before));
    memcpy(bg_before, background_objects, sizeof(bg_before));
    func_8007F174(&obj);
    before.ext.main_65.leap_frames = 1;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.x_speed = 0;
    before.y_speed = 0;
    before.gravity = 0;
    before.air_state = 0;
    before.unk6++;
    before.unk17 = 6;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)magma_dragoon_animations[6];
    before.animation_step = *(union AnimationStep*)magma_dragoon_animations[6];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(D_8013E198[2] == -1 && magma_dragoon_arena_left == 0
        && magma_dragoon_arena_right == 1000);
    switch (observation) {
    case 0:
        return obj.x_pos.val;
    case 1:
        return obj.y_pos.val;
    case 2:
        return obj.x_speed;
    case 3:
        return obj.y_speed;
    case 4:
        return obj.gravity;
    case 5:
        return obj.animation_step.packed;
    default:
        return (u8)obj.unk6 | ((u32)(u8)obj.air_state << 8)
            | ((u32)obj.ext.main_65.leap_frames << 16) | ((u32)obj.unk17 << 24);
    }
}
#define CASE(m, n)                                       \
    static u32 dragoon_leap_context_leap_##m##_##n(void) \
    {                                                    \
        return leap_case(m, n);                          \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2) CASE(m, 3) CASE(m, 4) CASE(m, 5) CASE(m, 6)
MODE(0)
MODE(1)
#define ENTRY(m, n) dragoon_leap_context_leap_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3) ENTRY(m, 4) ENTRY(m, 5) ENTRY(m, 6)
static const CTestCase dragoon_leap_context_cases[]
    = { ENTRIES(0) ENTRIES(1) };
static const u32 dragoon_leap_context_cases_expected[] = { 0x301234u, 0xC95678u, 0x0u, 0x0u, 0x0u, 0x3010002u, 0x6010022u, 0x3B81234u, 0xC95678u, 0x0u, 0x0u, 0x0u, 0x3010002u, 0x6010022u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 func_8007FF00_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 1u, 0u, 5u };
static u32 test_func_8007FF00(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    pool_0_full = 255;
    obj.invincibility_timer = 31;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8007FF00(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.u.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.u.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, func_8007FF00_expected, 9);
}

static const u32 inputs_0[3][15] = {
    { 255, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 255, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
struct func_8007FFFC_case {
    u32 expected[37];
};
static const struct func_8007FFFC_case func_8007FFFC_cases[] = {
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 9u, 0u, 0xFFFFFF80u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_8007FFFC(u32 row)
{
    const struct func_8007FFFC_case* c = &func_8007FFFC_cases[row];
    u32 observed_values[37];
    struct MainObj obj;
    struct BaseObj child_0;
    u8 child_0_present;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&magma_dragoon_arena_center, 0, sizeof(magma_dragoon_arena_center));
    memset(&magma_dragoon_arena_floor, 0, sizeof(magma_dragoon_arena_floor));
    memset(&magma_dragoon_arena_left, 0, sizeof(magma_dragoon_arena_left));
    memset(&magma_dragoon_arena_right, 0, sizeof(magma_dragoon_arena_right));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    child_0_present = inputs_0[row][0];
    child_0.active = inputs_0[row][1];
    engine_obj.stage = inputs_0[row][2];
    engine_obj.checkpoint = inputs_0[row][3];
    child_0.unk7 = inputs_0[row][4];
    obj.unk7E = inputs_0[row][5];
    obj.unk42 = inputs_0[row][6];
    obj.unk5 = inputs_0[row][7];
    magma_dragoon_arena_center = inputs_0[row][8];
    g_Player.x_pos.i.hi = inputs_0[row][9];
    magma_dragoon_arena_right = inputs_0[row][10];
    g_Player.ride_state = inputs_0[row][11];
    magma_dragoon_arena_left = inputs_0[row][12];
    magma_dragoon_arena_floor = inputs_0[row][13];
    pool_0_full = inputs_0[row][14];
    obj.ext.main_65.object = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8007FFFC(&obj);
    observed_values[0] = (u32)background_objects[0].unk24;
    observed_values[1] = (u32)background_objects[0].unk26;
    observed_values[2] = (u32)background_objects[0].unk28;
    observed_values[3] = (u32)background_objects[0].unk2A;
    observed_values[4] = (u32)engine_obj.character_state.bytes[0];
    observed_values[5] = (u32)engine_obj.character_state.bytes[10];
    observed_values[6] = (u32)engine_obj.character_state.bytes[11];
    observed_values[7] = (u32)engine_obj.character_state.bytes[12];
    observed_values[8] = (u32)engine_obj.character_state.bytes[13];
    observed_values[9] = (u32)engine_obj.character_state.bytes[14];
    observed_values[10] = (u32)engine_obj.character_state.bytes[15];
    observed_values[11] = (u32)engine_obj.character_state.bytes[1];
    observed_values[12] = (u32)engine_obj.character_state.bytes[2];
    observed_values[13] = (u32)engine_obj.character_state.bytes[3];
    observed_values[14] = (u32)engine_obj.character_state.bytes[4];
    observed_values[15] = (u32)engine_obj.character_state.bytes[5];
    observed_values[16] = (u32)engine_obj.character_state.bytes[6];
    observed_values[17] = (u32)engine_obj.character_state.bytes[7];
    observed_values[18] = (u32)engine_obj.character_state.bytes[8];
    observed_values[19] = (u32)engine_obj.character_state.bytes[9];
    observed_values[20] = (u32)engine_obj.checkpoint;
    observed_values[21] = (u32)engine_obj.enable_boss;
    observed_values[22] = (u32)engine_obj.unkF;
    observed_values[23] = (u32)g_Player.x_pos.i.hi;
    observed_values[24] = (u32)g_Player.y_pos.i.hi;
    observed_values[25] = (u32)misc_objects[0].active;
    observed_values[26] = (u32)misc_objects[0].id;
    observed_values[27] = (u32)misc_objects[0].unk2;
    observed_values[28] = (u32)obj.unk15;
    observed_values[29] = (u32)obj.unk42;
    observed_values[30] = (u32)obj.unk5;
    observed_values[31] = (u32)obj.unk7E;
    observed_values[32] = (u32)obj.x_pos.i.hi;
    observed_values[33] = (u32)obj.y_pos.i.hi;
    observed_values[34] = (u32)qux_object.unk15;
    observed_values[35] = (u32)qux_object.x_pos.i.hi;
    observed_values[36] = (u32)qux_object.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 37);
}

#include "support/boss_death_flash.h"
BOSS_DEATH_FLASH_TESTS(magma_dragoon_death_flash, func_8007FF00, 3)

#include "support/pool_full.h"
static u32 pool_full_magma_dragoon_intro_warning(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    magma_dragoon_intro_warning(&pf_self);
    pf_expected.unk15 = 0;
    pf_expected.unk6++;
    pf_script(0x14, 0x40);
    pf_backgrounds_expected[0].unk26 = pf_backgrounds_expected[0].unk24 = 0x1490;
    pf_backgrounds_expected[0].unk2A = pf_backgrounds_expected[0].unk28 = 0x1EB;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_magma_dragoon_ground_shot(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    func_8007F404(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_magma_dragoon_air_shot(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    func_8007F5B0(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_magma_dragoon_fire_volley_fire(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    magma_dragoon_fire_volley_fire(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_magma_dragoon_intro_warning,
    pool_full_magma_dragoon_ground_shot,
    pool_full_magma_dragoon_air_shot,
    pool_full_magma_dragoon_fire_volley_fire,
};

static const u32 magma_dragoon_death_flash_cases_expected[] = { 0x10501u, 0x10502u, 0x10502u, 0x50001u, 0xF0F01u, 0x5FB01u, 0x50001u };
static const u32 pool_full_cases_expected[] = { 0x50100u, 0x50000u, 0x50000u, 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "dragoon_breath_link_and_end", dragoon_breath_link_and_end_cases, dragoon_breath_link_and_end_cases_expected, COUNT(dragoon_breath_link_and_end_cases), 0 },
    { "dragoon_flame_allocation_steps", dragoon_flame_allocation_steps_cases, dragoon_flame_allocation_steps_cases_expected, COUNT(dragoon_flame_allocation_steps_cases), 0 },
    { "dragoon_leap_context", dragoon_leap_context_cases, dragoon_leap_context_cases_expected, COUNT(dragoon_leap_context_cases), 0 },
    { "func_8007FF00", 0, 0, 1, test_func_8007FF00 },
    { "func_8007FFFC", 0, 0, 3, test_func_8007FFFC },
    { "magma_dragoon_death_flash", magma_dragoon_death_flash_cases, magma_dragoon_death_flash_cases_expected, COUNT(magma_dragoon_death_flash_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dragoon_breath_link_and_end_cases) + COUNT(dragoon_flame_allocation_steps_cases) + COUNT(dragoon_leap_context_cases) + 1 + 3 + COUNT(magma_dragoon_death_flash_cases) + COUNT(pool_full_cases);
