#include "test_runtime.h"
#include "support/platform_fixture.h"
#ifndef VERSION_DEMO
#include "main/mains/main_65_magma_dragoon.h"
#include "main/55C4.h"
#include "support/state_cases.h"
#include "support/scalar_hash.h"
#include "main/collision_bounds.h"
void magma_dragoon_hold(struct MainObj* arg0);
void func_8007E848(struct MainObj*);
void magma_dragoon_fire_volley(struct MainObj* arg0);
void magma_dragoon_leap_center(struct MainObj* arg0);
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
        s->unk72 = s->unk73 = s->unk76 = s->unk77 = 7;
        OBJ_UNK78_SET(*s, 7);
        OBJ_UNK74_SET(*s, 7);
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
                s->unk72 = s->unk73 = s->unk76 = s->unk77 = 0;
                OBJ_UNK78_SET(*s, 0);
                OBJ_UNK74_SET(*s, 0);
                s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
            }
        } else if (mode == 2) {
            expected.animation_step.fields.event = 0;
            linked_before.unk6 = 5;
        }
    }
    magma_dragoon_breath_fire(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&linked, &linked_before, sizeof(linked));
    c_test_same_words(shot_objects, shots, sizeof(shots));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)linked.unk6 << 16) | ((u32)(obj.ext.main_65.object != NULL) << 24);
}
static const u32 dragoon_breath_link_and_end_cases_expected[] = { 0x40107u, 0x1040107u, 0x1050107u, 0x104000Cu, 0x1040003u, 0x1040107u, 0x1040107u };

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
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(misc_objects, pool, sizeof(pool));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return (u8)misc_objects[61].active | ((u32)(u8)misc_objects[62].active << 8) | ((u32)(u8)misc_objects[63].active << 16) | ((u32)(u8)misc_objects[63].unk2 << 24);
}
static const u32 dragoon_flame_allocation_steps_cases_expected[] = { 0x9010101u, 0x2410101u, 0x3414101u, 0x414141u, 0x1414141u, 0x3414101u, 0x9004141u, 0x2410101u };

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
    obj.unk15 = right ? PLAYER_FACING_RIGHT : 0;
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
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(misc_objects, pool_before, sizeof(pool_before));
    c_test_same_words(background_objects, bg_before, sizeof(bg_before));
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
        return C_TEST_STEP(obj.animation_step.packed);
    default:
        return (u8)obj.unk6 | ((u32)(u8)obj.air_state << 8)
            | ((u32)obj.ext.main_65.leap_frames << 16) | ((u32)obj.unk17 << 24);
    }
}
static const u32 dragoon_leap_context_cases_expected[] = { 0x301234u, 0xC95678u, 0x0u, 0x0u, 0x0u, 0x3010002u, 0x6010022u, 0x3B81234u, 0xC95678u, 0x0u, 0x0u, 0x0u, 0x3010002u, 0x6010022u };
static u32 dragoon_leap_context_cases_row(u32 row)
{
    return leap_case(row / 7, row % 7);
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
    observed_values[28] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[29] = (u32)obj.unk42;
    observed_values[30] = (u32)obj.unk5;
    observed_values[31] = (u32)obj.unk7E;
    observed_values[32] = (u32)obj.x_pos.i.hi;
    observed_values[33] = (u32)obj.y_pos.i.hi;
    observed_values[34] = C_TEST_PSX_FACING(qux_object.unk15);
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
    pf_script(0x14, PLAYER_FACING_RIGHT);
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
#define MD(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, magma_dragoon_arena_center = 0x80, magma_dragoon_arena_ceiling = 0x40)
#define VOLLEY(ev) (MD(9, 1), so.animation_step.fields.event = ev, magma_dragoon_fire_volley(&so), so.unk7E = shot_objects[0].unk7 | shot_objects[0].id << 8)
static void md_volley_start(void)
{
    MD(9, 0);
    g_Player.x_pos.i.hi = 0x100;
    magma_dragoon_fire_volley(&so);
}
static void md_volley_quiet(void) { VOLLEY(0); }
static void md_volley_last(void) { VOLLEY(0xA); }
static void md_volley_odd(void) { VOLLEY(3); }
static void md_volley_even(void) { VOLLEY(4); }
static void md_volley_wait(void)
{
    MD(9, 2);
    so.unk7C = 2;
    magma_dragoon_fire_volley(&so);
}
static void md_volley_done(void)
{
    MD(9, 2);
    so.unk7C = 1;
    magma_dragoon_fire_volley(&so);
}
static void md_center_from_right(void)
{
    MD(0, 0);
    so.x_pos.i.hi = 0xC0;
    magma_dragoon_leap_center(&so);
}
static void md_center_from_left(void)
{
    MD(0, 0);
    so.x_pos.i.hi = 0x40;
    magma_dragoon_leap_center(&so);
}
static void md_glide_ceiling(void)
{
    MD(0, 1);
    so.y_pos.i.hi = 0x20;
    magma_dragoon_leap_center(&so);
}
static void md_glide_left_past(void)
{
    MD(0, 1);
    so.x_pos.i.hi = 0x60;
    magma_dragoon_leap_center(&so);
}
static void md_glide_left(void)
{
    MD(0, 1);
    magma_dragoon_leap_center(&so);
}
static void md_glide_right_past(void)
{
    MD(0, 1);
    so.unk15 = PLAYER_FACING_RIGHT;
    so.x_pos.i.hi = 0xA0;
    magma_dragoon_leap_center(&so);
}
static void md_glide_right(void)
{
    MD(0, 1);
    so.unk15 = PLAYER_FACING_RIGHT;
    magma_dragoon_leap_center(&so);
}
static void md_land_wait(void)
{
    MD(4, 3);
    so.animation_step.fields.relative_step = 1;
    func_8007E848(&so);
}
static void md_land_volley(void)
{
    MD(4, 3);
    func_8007E848(&so);
}
static void md_land_breath(void)
{
    MD(4, 3);
    so.ext.main_65.attack = 1;
    func_8007E848(&so);
}
static void md_land_first(void)
{
    MD(4, 3);
    so.ext.main_65.attack = 2;
    func_8007E848(&so);
}
static void md_land_repeat(void)
{
    MD(4, 3);
    so.ext.main_65.attack = 2;
    so.ext.main_65.attack_repeat = 1;
    func_8007E848(&so);
}
static void md_hold(void)
{
    MD(0xD, 0);
    magma_dragoon_hold(&so);
}
static void md_punch_wait(void)
{
    MD(8, 1);
    func_8007F780(&so);
}
static void md_punch_near(void)
{
    MD(8, 1);
    so.animation_step.fields.event = 1;
    g_Player.x_pos.i.hi = 0xA0;
    func_8007F780(&so);
}
static void md_punch_mid(void)
{
    MD(8, 1);
    so.animation_step.fields.event = 1;
    g_Player.x_pos.i.hi = 0x40;
    func_8007F780(&so);
}
static void md_punch_far(void)
{
    MD(8, 1);
    so.animation_step.fields.event = 1;
    g_Player.x_pos.i.hi = 0x100;
    func_8007F780(&so);
}
static void md_burst_fire(void)
{
    MD(5, 1);
    so.animation_step.fields.event = 1;
    so.animation_step.fields.relative_step = 1;
    func_8007E95C(&so);
}
static void md_burst_even(void)
{
    MD(5, 1);
    so.animation_step.fields.event = 2;
    so.animation_step.fields.relative_step = 1;
    func_8007E95C(&so);
}
static void md_burst_wall(void)
{
    MD(5, 1);
    so.ext.main_65.attack = 6;
    func_8007E95C(&so);
}
static void md_burst_punch(void)
{
    MD(5, 1);
    so.ext.main_65.attack = 5;
    func_8007E95C(&so);
}
static void md_burst_idle(void)
{
    MD(5, 1);
    so.animation_table = (u32**)magma_dragoon_animations;
    func_8007E95C(&so);
}

static void (*const magma_dragoon_states_cases[])(void) = {
    md_volley_start,
    md_volley_quiet,
    md_volley_last,
    md_volley_odd,
    md_volley_even,
    md_volley_wait,
    md_volley_done,
    md_center_from_right,
    md_center_from_left,
    md_glide_ceiling,
    md_glide_left_past,
    md_glide_left,
    md_glide_right_past,
    md_glide_right,
    md_land_wait,
    md_land_volley,
    md_land_breath,
    md_land_first,
    md_land_repeat,
    md_hold,
    md_punch_wait,
    md_punch_near,
    md_punch_mid,
    md_punch_far,
    md_burst_fire,
    md_burst_even,
    md_burst_wall,
    md_burst_punch,
    md_burst_idle,
};
static const u32 magma_dragoon_states_expected[] = { 0x109u, 0u, 0x800000u, 0u, 0u, 0u, 0x400Cu, 0u, 0u, 0u, 0x109u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x209u, 0x290100F0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 0x109u, 0x29020000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 0x109u, 0x29030000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 0x209u, 1u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000100u, 0u, 0xC00000u, 0xFFFB0000u, 0x30000u, 0xFFF80000u, 3u, 2u, 0u, 0u, 0x1000100u, 0u, 0x400000u, 0x50000u, 0x30000u, 0xFFF80000u, 0x4003u, 2u, 0u, 0u, 0x100u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x200u, 0u, 0x600000u, 0u, 0u, 0x1F0000u, 0u, 0u, 0u, 0u, 0x100u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x200u, 0u, 0xA00000u, 0u, 0u, 0x1F0000u, 0x4000u, 0u, 0u, 0u, 0x100u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0x304u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xAu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xBu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xBu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xCu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xDu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x108u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000208u, 0u, 0x800000u, 0x60000u, 0x40000u, 0xFFE38000u, 0x4000u, 0u, 0u, 0u, 0x1000208u, 0u, 0x800000u, 0xFFFA0000u, 0x40000u, 0xFFE3C000u, 0u, 0u, 0u, 0u, 0x1000208u, 0u, 0x800000u, 0x60000u, 0x40000u, 0xFFE3E000u, 0x4000u, 0u, 0u, 0u, 0x105u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 0x105u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 7u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_magma_dragoon_states(u32 row)
{
    return state_run(magma_dragoon_states_cases[row], row, &magma_dragoon_states_expected[row * 10]);
}

extern void* magma_dragoon_animations[38];
static struct ShotObj expected_pool[32];
static u32 burst(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 event = row % 2, full = row / 2 % 2, face = row / 4, frame = event ? 26 : 24, i;
    engine_obj.stage = 4;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    D_8013E198[2] = -1;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i == 31 && !full ? 0 : 1;
    memcpy(expected_pool, shot_objects, sizeof(expected_pool));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 65;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 1;
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.x_pos.i.hi = 160;
    obj.y_pos.i.hi = 200;
    obj.animation_table = (const u8* const*)magma_dragoon_animations;
    set_animation_frame(ANIMATED_OBJECT(&obj), 11, frame);
    assert(obj.animation_step.packed == (event ? C_TEST_STEP(0x24010206) : C_TEST_STEP(0x24010106)));
    expected = obj;
    expected.animation_step.fields.duration = 5;
    expected.animation_step.fields.event = 0;
    if (!full) {
        struct ShotObj* s = &expected_pool[31];
        s->active = 0x41;
        s->id = 41;
        s->unk7C = WEAPON_OBJECT(&obj);
    }
    func_8007E95C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_8013E198[2] == -1);
    return 1;
}

extern void* magma_dragoon_animations[38];
static const s16 player_offsets[] = { -1, 0, 1 };
static struct MiscObj pool_expected[64];
static u32 defeat_scene(u32 row)
{
    struct MainObj obj, expected, effect, effect_before;
    struct PlayerObj player_expected;
    struct RideArmorObj ride_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 side = row % 3, riding = row / 3 % 2, available = row / 6 % 2, outside = row / 12, i;
    s16 scroll = side == 2 ? 0x1490 : 0x13F0;
    memset(&obj, 0, sizeof(obj));
    memset(&effect, 0, sizeof(effect));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&qux_object, 0, sizeof(qux_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    magma_dragoon_arena_left = 0x1430;
    magma_dragoon_arena_right = 0x1590;
    magma_dragoon_arena_center = 0x14E0;
    magma_dragoon_arena_floor = 0x280;
    background_objects[0].x_pos.val = (0x13F0 + outside * 512) * 65536;
    background_objects[0].y_pos.val = 0x1EB * 65536;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 39;
        misc_objects[i].unk2 = 9;
    }
    if (available)
        misc_objects[63].active = 0;
    obj.active = 0x41;
    obj.id = 65;
    obj.state = 1;
    obj.unk5 = 15;
    obj.unk6 = 3;
    obj.unk7 = 4;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.unk16 = VISUAL_SATURN_LAYER(7);
    obj.on_screen = 5;
    obj.bg_offset = 0;
    obj.x_pos.val = 0x14A01234;
    obj.y_pos.val = 0x02345678;
    obj.x_speed = 0x13579;
    obj.y_speed = -0x2468;
    obj.unk7E = 7;
    obj.animation_table = (const u8* const*)magma_dragoon_animations;
    set_animation(&obj, 0);
    effect.active = 0x41;
    effect.unk7 = 1;
    obj.ext.main_65.object = &effect;
    obj.ext.main_65.smoke = &effect;
    g_Player.x_pos.val = (0x14E0 + player_offsets[side]) * 65536 + 0xABCD;
    g_Player.y_pos.val = 0x0200FEDC;
    g_Player.ride_state = riding ? -1 : 0;
    g_Player.script_state = 3;
    g_Player.script_action = 7;
    g_Player.script_facing = 0x20;
    qux_object.active = 0x41;
    qux_object.unk15 = 0x20;
    qux_object.x_pos.val = 0x14F0BEEF;
    qux_object.y_pos.val = 0x0200CAFE;
    engine_obj.stage = 4;
    engine_obj.enable_boss = 1;
    engine_obj.boss_ptr = &obj;
    expected = obj;
    effect_before = effect;
    player_expected = g_Player;
    ride_expected = qux_object;
    engine_expected = engine_obj;
    memcpy(pool_expected, misc_objects, sizeof(pool_expected));
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    expected.unk5 = 16;
    expected.unk15 = side == 2 ? 0 : PLAYER_FACING_RIGHT;
    expected.x_pos.i.hi = side == 2 ? 0x1560 : 0x1460;
    expected.y_pos.i.hi = 0x280;
    expected.unk17 = 20;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)magma_dragoon_animations[20];
    expected.animation_step.packed = C_TEST_STEP(0x5C010032);
    expected.on_screen = !outside;
    player_expected.script_state = 1;
    player_expected.script_action = 0x14;
    player_expected.script_facing = side == 2 ? PLAYER_FACING_RIGHT : 0;
    SPIKE_IMMUNE_SET(player_expected, 1);
    if (riding) {
        ride_expected.unk15 = side == 2 ? PLAYER_FACING_RIGHT : 0;
        ride_expected.x_pos.i.hi = 0x14E0;
        ride_expected.y_pos.i.hi = 0x280;
    } else {
        player_expected.x_pos.i.hi = 0x14E0;
        player_expected.y_pos.i.hi = 0x280;
    }
    engine_expected.enable_boss = 0;
    engine_expected.boss_ptr = NULL;
    engine_expected.gameplay_locked = 1;
    backgrounds_expected[0].unk24 = backgrounds_expected[0].unk26 = scroll;
    backgrounds_expected[0].unk28 = backgrounds_expected[0].unk2A = 0x1EB;
    if (available) {
        pool_expected[63].active = 0x41;
        pool_expected[63].id = 0x26;
        pool_expected[63].unk2 = 5;
        pool_expected[63].ext.misc_7.position = &obj;
        expected.ext.main_65.smoke = MAIN_OBJECT(&misc_objects[63]);
    }
    func_8007FFFC(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&effect, &effect_before, sizeof(effect));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&qux_object, &ride_expected, sizeof(qux_object));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(misc_objects, pool_expected, sizeof(pool_expected));
    assert(magma_dragoon_arena_left == 0x1430 && magma_dragoon_arena_right == 0x1590);
    assert(magma_dragoon_arena_center == 0x14E0 && magma_dragoon_arena_floor == 0x280);
    return 1;
}

extern void* magma_dragoon_animations[38];
void func_8007E4C8(struct MainObj*);

static struct MainObj dragoon;

static u32 think(u32 row)
{
#ifdef MMX4_SATURN
    static const u32 expected[4] = { 0xF13DF744u, 0x5655C759u, 0xB3040744u, 0x181BD759u };
#else
    static const u32 expected[4] = { 991454243u, 2687513656u, 1110484003u, 2806543416u };
#endif
    u32 hash = 0, seen = 0, seed;
    for (seed = 0; seed < 48; seed++) {
        c_test_zero_words((u32*)&dragoon, sizeof(dragoon) / 4);
        c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
        dragoon.active = 0x41;
        dragoon.id = 65;
        dragoon.state = 1;
        dragoon.unk5 = 3;
        dragoon.hp = row & 1 ? 0x18 : 0x19;
        dragoon.x_pos.i.hi = 160;
        dragoon.y_pos.i.hi = 120;
        dragoon.ext.main_65.attack = 9;
        dragoon.ext.main_65.attack_repeat = 2;
        g_Player.x_pos.i.hi = row & 2 ? 100 : 200;
        dragoon.animation_table = (const u8* const*)magma_dragoon_animations;
        set_animation(&dragoon, 0);
        cur_random = seed * 0x9E37;
        func_8007E4C8(&dragoon);
        seen |= 1u << dragoon.ext.main_65.attack;
        hash = hash_animated(hash, (struct AnimatedObj*)&dragoon);
        hash = hash * 31 + dragoon.ext.main_65.attack + (dragoon.ext.main_65.attack_repeat << 8);
        hash = hash * 31 + cur_random;
    }
    assert(seen == (row & 1 ? 0x70u : 0xFu));
    return c_test_observe(0, row, &hash, &expected[row], 1);
}

extern void* magma_dragoon_animations[38];
extern struct Unk_unk68 magma_dragoon_attack_box, magma_dragoon_hurt_box;
static struct MiscObj expected_misc[64];
static u32 full(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player = g_Player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    engine_obj.stage = 4;
    engine_obj.substage = 1;
    engine = engine_obj;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 65;
    obj.state = 1;
    obj.hp = 40;
    obj.unk5 = 13;
    obj.ext.main_65.flash_timer = 254;
    obj.unk42 = 0x8000;
    obj.collision_data = D_801060F0;
    obj.x_pos.i.hi = 5493;
    obj.y_pos.i.hi = 646;
    obj.animation_table = (const u8* const*)magma_dragoon_animations;
    set_animation(&obj, 0);
    expected = obj;
    expected.unk17 = 13;
    expected.previous_animation_index = 255;
    expected.animation_cursor = magma_dragoon_animations[13];
    expected.animation_step.packed = *(u32*)magma_dragoon_animations[13];
    expected.attack_box = &magma_dragoon_attack_box;
    expected.hurt_box = &magma_dragoon_hurt_box;
    expected.y_speed = 0x40000;
    expected.contact_damage = 4;
    expected.gravity = 0x1C00;
    expected.unk6 = 1;
    cur_random = 0x1234;
    func_8007FAA4(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)misc_objects, (u32*)expected_misc, sizeof(expected_misc) / 4) == 0);
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    return 1;
}

void magma_dragoon_intro(struct MainObj*);
void magma_dragoon_dive_kick(struct MainObj*);
void magma_dragoon_flame_burst(struct MainObj*);
void magma_dragoon_breath(struct MainObj*);
void magma_dragoon_leap_wall(struct MainObj*);
void magma_dragoon_fireball(struct MainObj*);
void magma_dragoon_fireball_low(struct MainObj*);
void magma_dragoon_rising_punch(struct MainObj*);
void magma_dragoon_stagger(struct MainObj*);
void magma_dragoon_death(struct MainObj*);
extern struct Unk_unk68 D_80107D7C[];
extern struct Unk_unk68 magma_dragoon_terrain_box;
extern struct Unk_unk68 magma_dragoon_crouch_hurt_box;
extern struct Unk_unk68 magma_dragoon_leap_attack_box;
extern struct Unk_unk68 magma_dragoon_punch_attack_box;
extern struct Unk_unk68 magma_dragoon_dive_kick_attack_box;

static struct MainObj dg;
static u32 dg_pages[8];
static void dg_reset(u8 state, u8 unk5, u8 unk6, u8 unk7)
{
    memset(&dg, 0, sizeof(dg));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&abc_object, 0, sizeof(abc_object));
    engine_obj.unk36.timer = 0;
    engine_obj.stage = 4;
    D_80173C84 = 0;
    cur_random = 0;
    magma_dragoon_arena_left = 0x50;
    magma_dragoon_arena_center = 0xA0;
    magma_dragoon_arena_right = 0xF0;
    magma_dragoon_arena_ceiling = 0x40;
    magma_dragoon_arena_floor = 0x100;
    dg.active = 0x41;
    dg.id = 65;
    dg.state = state;
    dg.unk5 = unk5;
    dg.unk6 = unk6;
    dg.unk7 = unk7;
    dg.x_pos.i.hi = 160;
    dg.y_pos.i.hi = 120;
    dg.collision_data = D_80107D7C;
    dg.animation_table = (const u8* const*)magma_dragoon_animations;
    set_animation(&dg, 0);
}
static void dg_step(s8 duration, s8 event, s8 relative_step)
{
    dg.animation_step.fields.duration = duration;
    dg.animation_step.fields.event = event;
    dg.animation_step.fields.relative_step = relative_step;
}

static void dg_init(u8 stage)
{
    u8* frames = TEST_MENU_FRAMES;
    u32* pages = D_801406A8;
    dg_reset(0, 0, 0, 0);
    engine_obj.stage = stage;
    engine_obj.checkpoint = 1;
    TEST_MENU_FRAMES = (u8*)dg_pages;
    test_stage_graphics(dg_pages);
    magma_dragoon_update(&dg);
    TEST_MENU_FRAMES = frames;
    test_stage_graphics(pages);
    assert(dg.state == 1 && dg.unk5 == 2 && dg.hp == 0 && dg.contact_damage == 4 && dg.collision_data == D_80107D7C);
    assert(dg.attack_box == &magma_dragoon_attack_box && dg.hurt_box == NULL && engine_obj.boss_ptr == &dg);
}
static void dg_init_stage(void)
{
    dg_init(4);
    assert(dg.x_pos.i.hi == 0x15A5 && dg.y_pos.i.hi == 0x28F && engine_obj.checkpoint == 3);
    assert(magma_dragoon_arena_left == 0x1430 && magma_dragoon_arena_center == 0x14E0 && magma_dragoon_arena_right == 0x1590);
    assert(magma_dragoon_arena_floor == 0x280 && magma_dragoon_arena_ceiling == 0x260 && dg.unk42 == 0);
}
static void dg_init_rematch(void)
{
    dg_init(0xC);
    assert(dg.x_pos.i.hi == 0x2CE && dg.y_pos.i.hi == 0x69F && engine_obj.checkpoint == 1);
    assert(magma_dragoon_arena_left == 0x150 && magma_dragoon_arena_center == 0x200 && magma_dragoon_arena_right == 0x2B0);
    assert(magma_dragoon_arena_floor == 0x690 && magma_dragoon_arena_ceiling == 0x670);
    assert(dg.unk42 == OBJECT_CLUT(0x7888) && dg.sprite_frames == (u8*)dg_pages);
}
static void dg_intro_warning_rematch(void)
{
    dg_reset(1, 2, 0, 0);
    engine_obj.stage = 0xC;
    dg.unk15 = PLAYER_FACING_RIGHT;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 1 && dg.unk15 == 0 && effect_objects[0].active == 1 && effect_objects[0].id == 0x18);
    assert(effect_objects[0].x_pos.i.hi == 160 && effect_objects[0].y_pos.i.hi == 120 && dg.ext.main_65.object == MAIN_OBJECT(&effect_objects[0]));
    assert(g_Player.script_action == 0x14 && g_Player.script_facing == PLAYER_FACING_RIGHT);
    assert(background_objects[0].unk24 == 0x1B0 && background_objects[0].unk26 == 0x1B0 && background_objects[0].unk28 == 0x5FB && background_objects[0].unk2A == 0x5FB);
}
static void dg_intro_leap_descend(void)
{
    dg_reset(1, 2, 1, 0);
    effect_objects[0].active = 1;
    dg.ext.main_65.object = MAIN_OBJECT(&effect_objects[0]);
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 1 && misc_objects[0].active == 0);
    effect_objects[0].active = 0;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 2 && dg.y_speed == FIXED(2) && dg.x_accel == FIXED(0.0078125) && dg.air_state == 1 && dg.unk7E == 0x14 && dg.unk17 == 0xF);
    assert(misc_objects[0].id == 0x26 && misc_objects[0].unk2 == 2 && misc_objects[1].unk2 == 3 && misc_objects[2].unk2 == 0 && misc_objects[3].active == 0);
    dg.y_speed = 0;
    dg.x_accel = 0;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 2 && dg.y_pos.i.hi == 120);
    dg.y_pos.i.hi = 20;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 3 && dg.terrain_box == &magma_dragoon_terrain_box && dg.gravity == FIXED(0.1875));
    assert(dg.x_pos.i.hi == 158 && dg.y_pos.i.hi == 22 && dg.x_speed == FIXED(-2) && dg.y_speed == FIXED(-2) - FIXED(0.1875));
}
static void dg_intro_land_pose(void)
{
    dg_reset(1, 2, 3, 0);
    dg.air_state = 1;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 3 && misc_objects[0].active == 0);
    dg.collision_flags = 8;
    dg.x_speed = 0x10000;
    dg.gravity = 0x1000;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 4 && dg.air_state == 0 && dg.x_speed == 0 && dg.y_speed == 0 && dg.gravity == 0 && dg.unk17 == 0x10);
    assert(misc_objects[1].unk2 == 3 && misc_objects[2].active == 0);
    dg_step(5, 0, 1);
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 4);
    engine_obj.stage = 0;
    dg_step(5, 0, 0);
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 5 && dg.unk17 == 0x11 && engine_obj.character_state.bytes[8] == 0);
    dg.unk6 = 4;
    engine_obj.stage = 4;
    abc_object.unkC = 0x80;
    dg_step(5, 0, 0);
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 5 && engine_obj.character_state.bytes[8] == 1 && abc_object.unk10 == (s16)(0x8000 | 0xB));
}
static void dg_intro_ready_fill(void)
{
    dg_reset(1, 2, 5, 0);
    abc_object.unkC = 0x80;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 5);
    abc_object.unkC = 0;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 6);
    dg_step(5, 0, 1);
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 6);
    engine_obj.unk36.timer = 5;
    D_80173C84 = 1;
    dg_step(5, 0, 0);
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 6);
    engine_obj.unk36.timer = 0;
    engine_obj.enable_boss = 0;
    dg_step(5, 0, 0);
    dg.y_speed = 0x10000;
    magma_dragoon_intro(&dg);
    assert(dg.unk6 == 7 && engine_obj.enable_boss == 1 && dg.unk7E == 3 && dg.y_speed == 0 && dg.unk17 == 0x12);
    dg.unk7E = 2;
    magma_dragoon_intro(&dg);
    assert(dg.hp == 1 && dg.unk7E == 1);
    magma_dragoon_intro(&dg);
    assert(dg.hp == 2 && dg.unk7E == 3);
    dg.hp = 0x30;
    g_Player.script_state = 1;
    magma_dragoon_intro(&dg);
    assert(dg.unk5 == 3 && dg.unk6 == 0 && dg.hurt_box == &magma_dragoon_hurt_box && dg.unk17 == 0 && g_Player.script_state == 0);
    assert(background_objects[0].unk26 == 0x13F0 && background_objects[0].unk24 == 0x1490 && background_objects[0].unk48 == 4);
    dg.unk5 = 2;
    dg.unk6 = 7;
    engine_obj.stage = 0xC;
    magma_dragoon_intro(&dg);
    assert(dg.unk5 == 3 && background_objects[0].unk26 == 0x110 && background_objects[0].unk24 == 0x1B0);
}
static void dg_dive_kick_jump_rise(void)
{
    dg_reset(1, 4, 0, 0);
    g_Player.x_pos.i.hi = 161;
    magma_dragoon_dive_kick(&dg);
    assert(dg.unk6 == 1 && dg.unk15 == PLAYER_FACING_RIGHT && dg.x_speed == FIXED(0.75) && dg.y_speed == FIXED(4) && dg.air_state == 1);
    assert(dg.x_accel == FIXED(0.03125) && dg.gravity == FIXED(-0.03125) && dg.ext.main_65.jump_start_y == 120 && dg.unk17 == 3);
    assert(misc_objects[1].active == 0x41 && misc_objects[2].active == 0);
    dg.unk6 = 0;
    g_Player.x_pos.i.hi = 160;
    magma_dragoon_dive_kick(&dg);
    assert(dg.unk15 == 0 && dg.x_speed == FIXED(-0.75));
    dg.y_speed = 0;
    dg.x_accel = 0;
    dg.gravity = 0;
    dg.y_pos.i.hi = 40;
    magma_dragoon_dive_kick(&dg);
    assert(dg.unk6 == 1);
    dg.y_pos.i.hi = 39;
    magma_dragoon_dive_kick(&dg);
    assert(dg.unk6 == 2 && dg.contact_damage == 6 && dg.y_speed == FIXED(-6) && dg.unk17 == 4 && dg.y_pos.i.hi == 45);
}
static void dg_dive_kick_dive(void)
{
    static const s16 turns[][3] = { { 0x9F, 161, 1 }, { 0xA0, 161, 0 }, { 0x9F, 0, 1 }, { 0xA0, 0, 0 } };
    u32 i;
    dg_reset(1, 4, 2, 0);
    dg.y_speed = FIXED(-6);
    dg.attack_box = &magma_dragoon_dive_kick_attack_box;
    dg_step(5, 0, 1);
    magma_dragoon_dive_kick(&dg);
    assert(dg.attack_box == &magma_dragoon_attack_box && dg.y_pos.i.hi == 120 && dg.unk6 == 2);
    dg_step(5, 1, 1);
    magma_dragoon_dive_kick(&dg);
    assert(dg.attack_box == &magma_dragoon_dive_kick_attack_box && dg.y_pos.i.hi == 126);
    for (i = 0; i < COUNT(turns); i++) {
        dg.x_pos.i.hi = turns[i][0];
        g_Player.x_pos.i.hi = turns[i][1];
        dg_step(5, 2, 1);
        magma_dragoon_dive_kick(&dg);
        assert(dg.unk15 == (turns[i][2] ? PLAYER_FACING_RIGHT : 0) && dg.x_speed == (turns[i][2] ? 0x80000 : -0x80000));
    }
    dg.collision_flags = 8;
    dg.air_state = 1;
    dg.contact_damage = 6;
    dg_step(5, 1, 1);
    magma_dragoon_dive_kick(&dg);
    assert(dg.unk6 == 3 && dg.attack_box == &magma_dragoon_attack_box && dg.contact_damage == 4 && dg.air_state == 0 && dg.unk17 == 6);
}
static void dg_flame_burst_breath_start(void)
{
    dg_reset(1, 5, 0, 0);
    g_Player.x_pos.i.hi = 161;
    magma_dragoon_flame_burst(&dg);
    assert(dg.unk6 == 1 && dg.unk15 == PLAYER_FACING_RIGHT && dg.unk17 == 0xB);
    dg.unk5 = 7;
    dg.unk6 = 0;
    magma_dragoon_breath(&dg);
    assert(dg.unk6 == 1 && dg.unk15 == PLAYER_FACING_RIGHT && dg.unk17 == 0xA);
    dg.unk6 = 0;
    dg.x_pos.i.hi = 0xA1;
    magma_dragoon_breath(&dg);
    assert(dg.unk15 == 0);
}
static void dg_leap_center_land_recover(void)
{
    dg_reset(1, 8, 2, 0);
    dg.air_state = 1;
    dg.attack_box = &magma_dragoon_leap_attack_box;
    magma_dragoon_leap_center(&dg);
    assert(dg.unk6 == 2 && misc_objects[0].active == 0);
    dg.collision_flags = 8;
    magma_dragoon_leap_center(&dg);
    assert(dg.unk6 == 3 && dg.air_state == 0 && dg.unk17 == 6 && misc_objects[1].unk2 == 3 && misc_objects[2].active == 0);
    dg_step(5, 0, 1);
    magma_dragoon_leap_center(&dg);
    assert(dg.unk6 == 3);
    dg_step(5, 0, 0);
    magma_dragoon_leap_center(&dg);
    assert(dg.unk6 == 0 && dg.unk5 == 7 && dg.attack_box == &magma_dragoon_attack_box);
}
static void dg_leap_wall(void)
{
    dg_reset(1, 9, 0, 0);
    dg.x_pos.i.hi = 0x9F;
    g_Player.x_pos.i.hi = 0;
    magma_dragoon_leap_wall(&dg);
    assert(dg.unk6 == 1 && dg.ext.main_65.leap_frames == 0x40 && dg.ext.main_65.leap_to_right == 1 && dg.unk15 == 0);
    assert(dg.y_speed == FIXED(6) && dg.gravity == FIXED(0.1875) && dg.attack_box == &magma_dragoon_leap_attack_box && dg.air_state == 1);
    dg.x_pos.i.hi = 160;
    dg.y_speed = 0x10000;
    dg.collision_flags = 8;
    magma_dragoon_leap_wall(&dg);
    assert(dg.unk6 == 1 && dg.x_speed == 0x8000 && dg.ext.main_65.leap_frames == 0x3F && dg.y_speed == 0x10000 - FIXED(0.1875));
    dg.unk6 = 0;
    dg.x_pos.i.hi = 0xA0;
    magma_dragoon_leap_wall(&dg);
    assert(dg.ext.main_65.leap_to_right == 0);
    dg.x_pos.i.hi = 160;
    dg.y_speed = 0x10000;
    magma_dragoon_leap_wall(&dg);
    assert(dg.unk6 == 1 && dg.x_speed == -0x8000);
    dg.ext.main_65.leap_frames = 0;
    dg.x_speed = 0x1234;
    dg.collision_flags = 0;
    magma_dragoon_leap_wall(&dg);
    assert(dg.unk6 == 1 && dg.x_speed == 0x1234);
    dg.unk6 = 2;
    dg.ext.main_65.attack = 3;
    dg_step(5, 0, 1);
    magma_dragoon_leap_wall(&dg);
    assert(dg.unk5 == 9 && dg.unk6 == 2);
    dg_step(5, 0, 0);
    magma_dragoon_leap_wall(&dg);
    assert(dg.unk5 == 5 && dg.unk6 == 0);
    dg.unk5 = 9;
    dg.unk6 = 2;
    dg.ext.main_65.attack = 0;
    dg_step(5, 0, 0);
    magma_dragoon_leap_wall(&dg);
    assert(dg.unk5 == 3 && dg.unk6 == 0 && dg.unk17 == 0);
}
static void dg_fireball(void)
{
    dg_reset(1, 0xA, 0, 0);
    g_Player.x_pos.i.hi = 0;
    magma_dragoon_fireball(&dg);
    assert(dg.unk6 == 1 && dg.unk15 == 0 && dg.unk17 == 8 && dg.attack_box == &magma_dragoon_leap_attack_box);
    dg_step(5, 0, 1);
    magma_dragoon_fireball(&dg);
    assert(dg.unk6 == 1 && shot_objects[0].active == 0);
    dg_step(5, 1, 0);
    magma_dragoon_fireball(&dg);
    assert(shot_objects[0].active == 0x41 && shot_objects[0].id == 0x29 && shot_objects[0].unk2 == 3 && shot_objects[0].unk7C == WEAPON_OBJECT(&dg));
    assert(shot_objects[0].x_pos.i.hi == 137 && shot_objects[0].y_pos.i.hi == 120 && dg.unk5 == 0xB && dg.unk6 == 0);
    dg.unk6 = 1;
    dg.unk15 = PLAYER_FACING_RIGHT;
    dg.ext.main_65.attack = 1;
    dg_step(5, 1, 0);
    magma_dragoon_fireball(&dg);
    assert(shot_objects[1].x_pos.i.hi == 183 && dg.unk5 == 0xC);
    dg.unk6 = 1;
    dg.ext.main_65.attack = 2;
    dg_step(5, 0, 0);
    magma_dragoon_fireball(&dg);
    assert(dg.unk5 == 0xB && dg.ext.main_65.attack_repeat == 1);
    dg.unk6 = 1;
    dg_step(5, 0, 0);
    magma_dragoon_fireball(&dg);
    assert(dg.unk5 == 5 && dg.ext.main_65.attack_repeat == 2);
}
static void dg_fireball_low(void)
{
    dg_reset(1, 0xB, 0, 0);
    g_Player.x_pos.i.hi = 161;
    magma_dragoon_fireball_low(&dg);
    assert(dg.unk6 == 1 && dg.unk15 == PLAYER_FACING_RIGHT && dg.unk17 == 9 && dg.hurt_box == &magma_dragoon_hurt_box);
    dg_step(5, 0, 1);
    dg.animation_step.fields.frame_index = 0x19;
    magma_dragoon_fireball_low(&dg);
    assert(dg.unk6 == 1 && dg.hurt_box == &magma_dragoon_crouch_hurt_box && shot_objects[0].active == 0);
    dg_step(5, 1, 0);
    dg.animation_step.fields.frame_index = 0x1A;
    dg.attack_box = NULL;
    magma_dragoon_fireball_low(&dg);
    assert(shot_objects[0].x_pos.i.hi == 183 && shot_objects[0].y_pos.i.hi == 160 && shot_objects[0].unk2 == 3 && dg.hurt_box == &magma_dragoon_crouch_hurt_box);
    assert(dg.unk5 == 9 && dg.unk6 == 0 && dg.attack_box == &magma_dragoon_leap_attack_box);
    dg.unk6 = 1;
    dg.unk15 = 0;
    dg.ext.main_65.attack = 4;
    dg_step(5, 1, 0);
    magma_dragoon_fireball_low(&dg);
    assert(shot_objects[1].x_pos.i.hi == 137 && dg.unk5 == 4);
    dg.unk6 = 1;
    dg.ext.main_65.attack = 5;
    dg_step(5, 0, 0);
    magma_dragoon_fireball_low(&dg);
    assert(dg.unk5 == 0xA);
}
static void dg_rising_punch(void)
{
    dg_reset(1, 0xC, 0, 0);
    g_Player.x_pos.i.hi = 161;
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 1 && dg.contact_damage == 8 && dg.unk15 == PLAYER_FACING_RIGHT && dg.unk17 == 5 && dg.attack_box == &magma_dragoon_leap_attack_box);
    dg.unk6 = 2;
    dg.attack_box = NULL;
    dg.x_speed = 0x10000;
    dg.y_speed = 0x10000;
    dg_step(5, 0, 1);
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 2 && dg.x_speed == 0x10000 && dg.attack_box == NULL);
    dg_step(5, 2, 1);
    dg.x_speed = -0x1000;
    dg.x_accel = 0x100;
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 2 && dg.attack_box == &magma_dragoon_punch_attack_box && dg.x_speed == 0 && dg.x_accel == 0);
    dg.unk15 = 0;
    dg.x_accel = -0x100;
    dg_step(5, 0, 1);
    magma_dragoon_rising_punch(&dg);
    assert(dg.x_speed == 0 && dg.x_accel == 0);
    dg.y_speed = 0;
    dg.gravity = 1;
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 3 && dg.unk17 == 7 && dg.attack_box == &magma_dragoon_attack_box);
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 3);
    dg.collision_flags = 8;
    dg.contact_damage = 8;
    dg.air_state = 1;
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 4 && dg.contact_damage == 4 && dg.air_state == 0 && dg.unk17 == 6 && misc_objects[1].unk2 == 3);
}
static void dg_rising_punch_recover(void)
{
    dg_reset(1, 0xC, 4, 0);
    dg_step(5, 0, 1);
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 4);
    dg_step(5, 0, 0);
    dg.y_pos.i.hi = 0x101;
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 0 && dg.unk5 == 9);
    dg.unk5 = 0xC;
    dg.unk6 = 4;
    dg.y_pos.i.hi = 0x100;
    dg.ext.main_65.attack = 3;
    dg_step(5, 0, 0);
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk6 == 0 && dg.unk5 == 0xC && dg.ext.main_65.attack_repeat == 1);
    dg.unk6 = 4;
    dg_step(5, 0, 0);
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk5 == 9 && dg.ext.main_65.attack_repeat == 2);
    dg.unk5 = 0xC;
    dg.unk6 = 4;
    dg.ext.main_65.attack = 0;
    dg_step(5, 0, 0);
    magma_dragoon_rising_punch(&dg);
    assert(dg.unk5 == 9);
}
static void dg_stagger(void)
{
    dg_reset(1, 0xD, 0, 0);
    magma_dragoon_stagger(&dg);
    assert(dg.unk6 == 1 && misc_objects[0].active == 0x41 && misc_objects[0].id == 0x26 && misc_objects[0].unk2 == 4);
    assert(dg.ext.main_65.object == MAIN_OBJECT(&misc_objects[0]) && dg.y_speed == 0x40000 && dg.unk17 == 0xD);
    dg.gravity = 0;
    magma_dragoon_stagger(&dg);
    assert(dg.unk6 == 1);
    dg.y_speed = -1;
    magma_dragoon_stagger(&dg);
    assert(dg.unk6 == 2);
    misc_objects[0].animation_step.fields.relative_step = 0;
    magma_dragoon_stagger(&dg);
    assert(dg.unk6 == 2 && misc_objects[0].state == 0);
    misc_objects[0].animation_step.fields.relative_step = -1;
    magma_dragoon_stagger(&dg);
    assert(dg.unk6 == 3 && misc_objects[0].state == 2 && dg.y_speed == 0 && dg.gravity == FIXED(0.2578125));
    magma_dragoon_stagger(&dg);
    assert(dg.unk6 == 3);
    dg.collision_flags = 8;
    dg.ext.main_65.flash_timer = 3;
    magma_dragoon_stagger(&dg);
    assert(dg.unk6 == 4 && dg.ext.main_65.flash_timer == 0x3D && dg.unk7C == 1 && dg.unk17 == 0);
    dg.unk6 = 3;
    dg.ext.main_65.flash_timer = 2;
    magma_dragoon_stagger(&dg);
    assert(dg.ext.main_65.flash_timer == 0x3E);
    dg.unk7C = 2;
    magma_dragoon_stagger(&dg);
    assert(dg.unk7C == 1 && dg.unk5 == 0xD);
    magma_dragoon_stagger(&dg);
    assert(dg.unk5 == 9 && dg.unk6 == 0);
}
static void dg_fight(u8 weapon, u8 kind)
{
    dg.unk5 = 1;
    dg.unk6 = 0;
    dg.ext.main_65.flash_timer = 0;
    state_hit(&dg, weapon, kind, 1);
    magma_dragoon_update(&dg);
}
static void dg_fight_hits(void)
{
    dg_reset(1, 1, 0, 0);
    dg.hp = 20;
    dg.collision_data = D_801060F0;
    magma_dragoon_update(&dg);
    assert(dg.state == 1 && dg.collision_data == D_801060F0 && dg.unk42 == 0);
    dg.ext.main_65.flash_timer = 3;
    magma_dragoon_update(&dg);
    assert(dg.ext.main_65.flash_timer == 2 && dg.unk42 == 0x8000);
    dg.ext.main_65.flash_timer = 1;
    magma_dragoon_update(&dg);
    assert(dg.ext.main_65.flash_timer == 0 && dg.unk42 == 0 && dg.collision_data == D_80107D7C);
    dg_fight(0, 0);
    assert(dg.hp == 19 && dg.ext.main_65.flash_timer == 0x1D && dg.unk42 == 0x8000 && dg.collision_data == D_801060F0 && dg.unk5 == 1);
    dg_fight(0, 0xFF);
    assert(dg.hp == 19 && dg.ext.main_65.flash_timer == 0 && dg.collision_data == state_damage);
    dg_fight(0x18, 0);
    assert(dg.hp == 18 && dg.ext.main_65.flash_timer == 1);
    dg_fight(0x19, 0);
    assert(dg.hp == 17 && dg.ext.main_65.flash_timer == 1);
    dg_fight(0x10, 0);
    assert(dg.hp == 16 && dg.unk5 == 0xD && dg.unk6 == 1 && dg.ext.main_65.flash_timer == 0xFE);
    dg_fight(7, 0);
    assert(dg.hp == 15 && dg.unk5 == 0xD && dg.unk6 == 1 && dg.ext.main_65.flash_timer == 0xFE);
    dg.hp = 1;
    dg_fight(0, 0);
    assert(dg.state == 2 && dg.unk5 == 0 && dg.unk6 == 0 && dg.hp == 0 && SPIKE_IMMUNE(g_Player) == 1);
}
static void dg_death_start_wait(void)
{
    dg_reset(2, 0, 0, 0);
    dg.unk42 = 0x8123;
    g_Player.unk15 = PLAYER_FACING_RIGHT;
    magma_dragoon_update(&dg);
    assert(dg.unk5 == 1 && dg.unk42 == 0x123 && dg.unk7C == 0x7F && dg.unk7E == 0x19 && dg.invincibility_timer == 0x19 && dg.unk17 == 0xD);
    assert(g_Player.script_action == 0x14 && g_Player.script_facing == PLAYER_FACING_RIGHT);
    dg.unk5 = 2;
    effect_objects[0].active = 1;
    dg.ext.main_65.object = MAIN_OBJECT(&effect_objects[0]);
    dg.unk7E = 0;
    magma_dragoon_death(&dg);
    assert(dg.unk42 == 0x8123 && dg.unk7E == 5);
    dg.unk7E = 2;
    magma_dragoon_death(&dg);
    assert(dg.unk42 == 0x8123 && dg.unk7E == 1);
    dg.unk5 = 3;
    magma_dragoon_death(&dg);
    assert(dg.unk5 == 3);
    effect_objects[0].active = 0;
    abc_object.unkC = 0x80;
    magma_dragoon_death(&dg);
    assert(dg.unk5 == 4 && abc_object.unk10 == (s16)(0x8000 | 0xC));
    magma_dragoon_death(&dg);
    assert(dg.unk5 == 4);
    abc_object.unkC = 0;
    magma_dragoon_death(&dg);
    assert(dg.unk5 == 5 && dg.unk7C == 0x50 && dg.unk17 == 0x13);
}
static void dg_death_smoke_vanish(void)
{
    dg_reset(2, 5, 0, 0);
    misc_objects[3].active = 0x41;
    dg.ext.main_65.smoke = MAIN_OBJECT(&misc_objects[3]);
    dg.unk7C = 9;
    magma_dragoon_death(&dg);
    assert(dg.unk7C == 8 && visual_objects[0].active == 0x21 && visual_objects[0].id == 4 && visual_objects[0].x_pos.i.hi == 128 && visual_objects[0].y_pos.i.hi == 120);
    dg.unk7C = 2;
    magma_dragoon_death(&dg);
    assert(dg.unk7C == 1 && visual_objects[1].active == 0);
    magma_dragoon_death(&dg);
    assert(dg.unk5 == 6 && dg.unk7C == 0x28 && visual_objects[1].active == 0x21);
    dg.unk7C = 9;
    magma_dragoon_death(&dg);
    assert(dg.unk7C == 8 && visual_objects[2].active == 0x21);
    dg.unk7C = 4;
    magma_dragoon_death(&dg);
    assert(dg.unk7C == 3 && visual_objects[3].active == 0);
    dg.unk7C = 1;
    magma_dragoon_death(&dg);
    assert(dg.unk5 == 7 && dg.unk7C == 0x1E && misc_objects[3].active == 0 && visual_objects[3].active == 0);
    dg.unk7C = 2;
    engine_obj.unkF = 0;
    magma_dragoon_death(&dg);
    assert(dg.unk7C == 1 && engine_obj.unkF == 0);
    magma_dragoon_death(&dg);
    assert(engine_obj.unkF == 1);
}
static void (*const dg_cases[])(void) = {
    dg_init_stage,
    dg_init_rematch,
    dg_intro_warning_rematch,
    dg_intro_leap_descend,
    dg_intro_land_pose,
    dg_intro_ready_fill,
    dg_dive_kick_jump_rise,
    dg_dive_kick_dive,
    dg_flame_burst_breath_start,
    dg_leap_center_land_recover,
    dg_leap_wall,
    dg_fireball,
    dg_fireball_low,
    dg_rising_punch,
    dg_rising_punch_recover,
    dg_stagger,
    dg_fight_hits,
    dg_death_start_wait,
    dg_death_smoke_vanish,
};
static u32 dg_run(u32 row)
{
    dg_cases[row]();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "magma_dragoon_states", 0, 0, COUNT(magma_dragoon_states_cases), test_magma_dragoon_states },
    { "dragoon_breath_link_and_end", NULL, dragoon_breath_link_and_end_cases_expected, COUNT(dragoon_breath_link_and_end_cases_expected), breath_case },
    { "dragoon_flame_allocation_steps", NULL, dragoon_flame_allocation_steps_cases_expected, COUNT(dragoon_flame_allocation_steps_cases_expected), flame_case },
    { "dragoon_leap_context", NULL, dragoon_leap_context_cases_expected, COUNT(dragoon_leap_context_cases_expected), dragoon_leap_context_cases_row },
    { "func_8007FFFC", 0, 0, 3, test_func_8007FFFC },
    { "magma_dragoon_death_flash", magma_dragoon_death_flash_cases, magma_dragoon_death_flash_cases_expected, COUNT(magma_dragoon_death_flash_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "own_burst_animation_odd_even_events_both_facings_full_last_shot_slot", NULL, NULL, 8, burst },
    { "defeat_scene_ride_side_and_pool", NULL, NULL, 24, defeat_scene },
    { "attack_pick_by_health_and_roll", NULL, NULL, 4, think },
    { "actual_Magma_Dragoon_stagger_root_13_own_pose_13_full_misc_pool", NULL, NULL, 1, full },
    { "magma_dragoon_state_steps", NULL, NULL, COUNT(dg_cases), dg_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(magma_dragoon_states_cases) + COUNT(dragoon_breath_link_and_end_cases_expected) + COUNT(dragoon_flame_allocation_steps_cases_expected) + COUNT(dragoon_leap_context_cases_expected) + 3 + COUNT(magma_dragoon_death_flash_cases) + COUNT(pool_full_cases) + 8 + 24 + 4 + 1 + COUNT(dg_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
