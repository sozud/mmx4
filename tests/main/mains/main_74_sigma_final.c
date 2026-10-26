#include "test_runtime.h"
#include "main/mains/main_74_sigma_final.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
void sigma_final_death(struct MainObj* arg0);
void sigma_final_grab(struct MainObj* arg0);
void sigma_final_show_upper(struct MainObj* arg0);
void sigma_final_spit(struct MainObj* arg0);
void sigma_final_summon(struct MainObj* arg0);
void sigma_final_big_beam(struct MainObj* arg0);
void sigma_final_idle(struct MainObj* arg0);
void sigma_final_laser(struct MainObj* arg0);
extern void* sigma_final_animations[39];
extern void* D_8013B8B4;
extern u8 D_8013B8A0;
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 charge_case(u32 mode)
{
    struct MainObj obj, before;
    struct MiscObj misc_before[64];
    struct ShotObj shots_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i, free_misc = mode == 2 || mode == 3, free_shot = mode == 2 || mode == 4;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
        misc_objects[i].state = 0x28;
    }
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    if (free_misc)
        misc_objects[63].active = 0;
    if (free_shot)
        shot_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 2;
    obj.ext.main_74.animation_index = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation_frame(&obj, 29, mode == 0 ? 0 : 6);
    D_8013B8A8 = OBJECT_HEADER(&misc_objects[0]);
    before = obj;
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    sigma_final_big_beam_charge(&obj);
    if (mode == 0) {
        before.animation_step.fields.duration = 29;
        assert(D_8013B8A8 == OBJECT_HEADER(&misc_objects[0]));
    } else {
        before.unk6++;
        before.animation_cursor = (const u8*)sigma_final_animations[29] + 28;
        before.animation_step = *(union AnimationStep*)before.animation_cursor;
        assert(D_8013B8A8 == (free_misc ? OBJECT_HEADER(&misc_objects[63]) : NULL));
    }
    if (free_misc) {
        misc_before[63].active = 0x41;
        misc_before[63].id = 55;
        misc_before[63].unk2 = 1;
        misc_before[63].ext.misc_55.owner = &obj;
    }
    if (free_shot) {
        shots_before[31].active = 1;
        shots_before[31].id = 57;
        shots_before[31].unk2 = 5;
        shots_before[31].unk7C = WEAPON_OBJECT(&obj);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(misc_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)misc_before)[i]);
    for (i = 0; i < sizeof(shots_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)shots_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk6 | ((u32)misc_objects[63].active << 8) | ((u32)shot_objects[31].active << 16) | ((u32)obj.animation_step.fields.duration << 24);
}
static const u32 sigma_final_beam_charge_pools_cases_expected[] = { 0x1D010102u, 0x1010103u, 0x1014103u, 0x1014103u, 0x1010103u };

static u32 dialogue_case(u32 zero)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct AbcObj sigma_final_death_dialogue_dialogue_before;
    struct BackgroundObj bg_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 2;
    obj.ext.main_74.target = 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.attack_box = (void*)sigma_final_animations[0];
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, 0);
    g_Player.script_state = -1;
    g_Player.hp = 0x27;
    engine_obj.cur_character = zero;
    engine_obj.stage = 2;
    engine_obj.unk1F = 0x28;
    abc_object.unkC = 0x80;
    abc_object.unkD = 7;
    abc_object.unkA = 0x25;
    abc_object.unk10 = 0x1234;
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    D_8013B8B0 = (struct Unk_unk68*)sigma_final_animations[0];
    D_8013B8B4 = sigma_final_animations[1];
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    sigma_final_death_dialogue_dialogue_before = abc_object;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    sigma_final_death_wait_player(&obj);
    before.unk5 = 5;
    before.ext.main_74.target = 0;
    before.attack_box = NULL;
    before.on_screen = 1;
    before.animation_step.fields.duration--;
    sigma_final_death_dialogue_dialogue_before.unk10 = (zero ? 0x25 : 0x2C) | 0x8000;
    assert(D_8013B8B0 == NULL && D_8013B8B4 == NULL);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(abc_object) / 4; i++)
        assert(((u32*)&abc_object)[i] == ((u32*)&sigma_final_death_dialogue_dialogue_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(D_801397BC == NULL && D_801397C0 == NULL && D_801397C4 == NULL && D_801397C8 == NULL);
    assert(D_801397CC == NULL && D_801397D0 == NULL && D_801397D4 == NULL);
    return (u16)abc_object.unk10 | ((u32)(u8)obj.unk5 << 16);
}
static const u32 sigma_final_death_dialogue_cases_expected[] = { 0x5802Cu, 0x58025u };

static const s16 heights[] = { 0x24F, 0x26F, 0x28F };
static u32 aim_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk6 = 2;
    obj.ext.main_74.animation_index = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.y_pos.val = heights[mode] * 65536 + 0x2468;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, 0);
    before = obj;
    player_before = g_Player;
    sigma_final_laser_aim(&obj);
    before.ext.main_74.animation_index = 3 - mode;
    before.unk6 = 3;
    before.unk17 = sigma_final_laser_animations[(3 - mode) * 2];
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)sigma_final_animations[before.unk17];
    before.animation_step = *(union AnimationStep*)sigma_final_animations[before.unk17];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    if (observation == 0)
        return obj.ext.main_74.animation_index | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.unk17 << 16);
    return obj.animation_step.packed;
}
static const u32 sigma_final_laser_aim_heights_cases_expected[] = { 0x200303u, 0x4F01001Eu, 0x1D0302u, 0x4F01001Eu, 0x1F0301u, 0x4F01001Eu };
static u32 sigma_final_laser_aim_heights_cases_row(u32 row)
{
    return aim_case(row / 2, row % 2);
}

static u32 live_shots(void)
{
    struct MainObj obj, before;
    struct ShotObj pool_before[32];
    struct PlayerObj player_before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
    }
    shot_objects[2].id = 0x38;
    shot_objects[2].active = 2;
    shot_objects[17].id = 0x38;
    shot_objects[17].active = 0x41;
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk6 = 0x27;
    obj.unk62 = 0x25;
    obj.contact_damage = 3;
    g_Player.stun_timer = 0x26;
    before = obj;
    player_before = g_Player;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    sigma_final_grab_release(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    actual = (u8)obj.unk6 | ((u32)(u8)g_Player.stun_timer << 8);
    return actual;
}
static const CTestCase sigma_grab_live_shots_cases[] = { live_shots };
static const u32 sigma_grab_live_shots_cases_expected[] = { 0x2627u };

static u8 sound_entries[12 * 4];
static u32 grab_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj pool_expected[32];
    struct PlayerObj player_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(sound_entries, 0, sizeof(sound_entries));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141F50[2] = sound_entries;
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = mode == 3 && i == 31 ? 0 : 1;
        shot_objects[i].id = 39;
        shot_objects[i].state = 40;
        shot_objects[i].unk2 = 9;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 4;
        shot_objects[i].unk7 = 5;
        shot_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        shot_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    if (mode >= 4 && mode <= 6) {
        shot_objects[31].id = 0x38;
        shot_objects[31].active = mode == 4 ? 1 : mode == 5 ? 2
                                                            : 0;
    }
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 3;
    obj.unk62 = 2;
    obj.contact_damage = 6;
    obj.unk7C = mode == 0 ? 9 : mode == 1 ? 2
        : mode < 4                        ? 5
                                          : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, 0);
    g_Player.stun_timer = mode == 0 ? 1 : 0;
    g_Player.x_pos.val = (mode & 1 ? 100 : 150) * 65536 + 0xBEEF;
    g_Player.y_pos.val = 180 * 65536 + 0xCAFE;
    expected = obj;
    player_expected = g_Player;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    if (mode == 0) {
        expected.unk7C = 30;
        expected.unk6 = 4;
        expected.unk17 = 5;
        expected.previous_animation_index = 0xFF;
        ANIMATED_OBJECT(&expected)->animation_cursor = sigma_final_animations[5];
        expected.animation_step = *(union AnimationStep*)sigma_final_animations[5];
        player_expected.x_pos.u.hi = 116;
        player_expected.y_pos.u.hi = 216;
    } else {
        player_expected.x_pos.u.hi = mode & 1 ? 103 : 147;
        assert(expected.animation_step.fields.duration > 1);
        expected.animation_step.fields.duration--;
        if (mode < 4) {
            expected.unk7C--;
            if (mode == 3) {
                pool_expected[31].active = 0x41;
                pool_expected[31].id = 0x38;
                pool_expected[31].unk2 = 0;
                pool_expected[31].unk7C = WEAPON_OBJECT(&obj);
            }
        } else if (mode != 4) {
            expected.contact_damage = 9;
            expected.unk62 = 0;
            expected.unk5 = 11;
            expected.unk6 = 0;
        }
    }
    func_8008E748(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < sizeof(sound_entries); i++)
        assert(sound_entries[i] == 0);
    assert(D_80141F50[2] == sound_entries);
    i = (u8)obj.unk7C | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)shot_objects[31].active << 16) | ((u32)(u8)obj.contact_damage << 24);
    return i;
}
static const u32 sigma_grab_shot_pool_context_cases_expected[] = { 0x601071Eu, 0x6010701u, 0x6010704u, 0x6410704u, 0x6010700u, 0x9020B00u, 0x9000B00u, 0x9010B00u };

static u32 hide_case(u32 mode, u32 observation)
{
    struct MainObj obj, before, children[3], children_before[3];
    struct PlayerObj player_before;
    struct BackgroundObj backgrounds_before[3];
    struct Unk_unk68 box = { 1, 2, 3, 4 };
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(children, 0, sizeof(children));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.duration = 2;
    obj.animation_step.fields.relative_step = mode == 2 ? 1 : 0;
    obj.ext.main_74.target = 2;
    obj.attack_box = &box;
    for (i = 0; i < 3; i++) {
        children[i].active = 0x41;
        children[i].id = 74;
        children[i].unk5 = mode == 1 && i == 1 ? 0 : 3;
        children[i].unk6 = 0x27 + i;
        obj.ext.main_74.children[i] = &children[i];
    }
    D_8013B8B0 = &box;
    D_8013B8B4 = &box;
    D_8013B8A0 = 0x27;
    before = obj;
    player_before = g_Player;
    memcpy(children_before, children, sizeof(children));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    sigma_final_hide_lower_wait(&obj);
    if (mode == 0) {
        before.unk5 = 2;
        before.unk6 = 0;
        before.ext.main_74.target = 0;
        before.attack_box = NULL;
        assert(D_8013B8B0 == NULL && D_8013B8B4 == NULL);
    } else {
        before.animation_step.fields.duration = 1;
        if (mode == 1) {
            before.x_pos.i.hi = 0;
            before.y_pos.i.hi = 0;
        } else
            before.on_screen = 1;
        assert(D_8013B8B0 == &box && D_8013B8B4 == &box);
    }
    assert(D_8013B8A0 == (mode == 0 ? 0x1E : 0x27));
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(children) / 4; i++)
        assert(((u32*)children)[i] == ((u32*)children_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(box.unk0 == 1 && box.unk1 == 2 && box.unk2 == 3 && box.unk3 == 4);
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)D_8013B8A0 << 16) : obj.animation_step.packed;
}
static const u32 sigma_lower_hide_children_cases_expected[] = { 0x1E0002u, 0x4F000002u, 0x270107u, 0x4F000001u, 0x270107u, 0x4F010001u };
static u32 sigma_lower_hide_children_cases_row(u32 row)
{
    return hide_case(row / 2, row % 2);
}

static u32 pattern_case(u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.ext.main_74.pattern_index = 7;
    D_8013B8A0 = 0;
    D_8013B8B8 = 0;
    cur_random = 1;
    before = obj;
    player_before = g_Player;
    func_8008DAE8(&obj);
    before.unk5 = obj.unk5;
    before.ext.main_74.pattern_index = 0;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_8013B8A0 == 0 && D_8013B8B8 == 0);
    if (observation == 0)
        return (u8)obj.unk5 | ((u32)obj.ext.main_74.pattern_index << 8);
    return cur_random;
}
static u32 pattern_choice(void)
{
    return pattern_case(0);
}
static u32 pattern_seed(void)
{
    return pattern_case(1);
}
static const CTestCase sigma_pattern_rng_cases[] = {
    pattern_choice,
    pattern_seed,
};
static const u32 sigma_pattern_rng_cases_expected[] = { 0x9u, 0x1u };

struct func_8008DAE8_case {
    u32 pattern_index, D_8013B8B8;
    u32 expected[3];
};
static const struct func_8008DAE8_case func_8008DAE8_cases[] = {
    { 255, 0, { 0u, 0xFFu, 0u } },
    { 6, 0, { 0u, 7u, 4u } },
    { 2, 2, { 0u, 7u, 4u } },
    { 7, 0, { 0u, 0u, 0xAu } },
    { 3, 0, { 0u, 4u, 0xDu } },
    { 6, 1, { 0u, 3u, 6u } },
};
static u32 test_func_8008DAE8(u32 row)
{
    const struct func_8008DAE8_case* c = &func_8008DAE8_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_8013B8A0, 0, sizeof(D_8013B8A0));
    memset(&D_8013B8B8, 0, sizeof(D_8013B8B8));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.ext.main_74.pattern_index = c->pattern_index;
    D_8013B8B8 = c->D_8013B8B8;
    func_8008DAE8(&obj);
    observed_values[0] = (u32)D_8013B8A0;
    observed_values[1] = (u32)obj.ext.main_74.pattern_index;
    observed_values[2] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static const u32 sigma_final_death_blink_expected[] = { 4u, 0u, 0x8000u, 2u, 0x12Cu, 5u };
static u32 test_sigma_final_death_blink(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7E = 1;
    obj.invincibility_timer = 31;
    sigma_final_death_blink(&obj);
    observed_values[0] = (u32)obj.ext.main_74.unk97;
    observed_values[1] = (u32)obj.invincibility_timer;
    observed_values[2] = (u32)obj.unk42;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, sigma_final_death_blink_expected, 6);
}

struct sigma_final_death_collapse_case {
    u32 pool_0_full;
    u32 expected[4];
};
static const struct sigma_final_death_collapse_case sigma_final_death_collapse_cases[] = {
    { 0, { 1u, 0x2Bu, 1u, 4u } },
    { 255, { 1u, 0u, 0u, 4u } },
};
static u32 test_sigma_final_death_collapse(u32 row)
{
    const struct sigma_final_death_collapse_case* c = &sigma_final_death_collapse_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.animation_step.fields.relative_step = -128;
    FILL_ACTIVE(effect_objects, 32, c->pool_0_full ? 1 : 0);
    sigma_final_death_collapse(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].unk2;
    observed_values[3] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 sigma_final_set_target_expected[] = { 0xFFu, 0u, 0u };
static u32 test_sigma_final_set_target(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    s32 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&D_8010535C, 0, sizeof(D_8010535C));
    memset(&D_80105360, 0, sizeof(D_80105360));
    memset(&D_80105368, 0, sizeof(D_80105368));
    memset(&D_8010536C, 0, sizeof(D_8010536C));
    memset(&D_80105370, 0, sizeof(D_80105370));
    arg1 = -1;
    sigma_final_set_target(&obj, arg1);
    observed_values[0] = (u32)obj.ext.main_74.target;
    observed_values[1] = (u32)obj.hp;
    observed_values[2] = (u32)obj.unk5D;
    return c_test_observe(0, row, observed_values, sigma_final_set_target_expected, 3);
}

struct sigma_final_spit_fire_case {
    u32 unk7C, pool_0_full;
    u32 expected[8];
};
static const struct sigma_final_spit_fire_case sigma_final_spit_fire_cases[] = {
    { 1, 0, { 7u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 12651, 255, { 0u, 0u, 0x316Au, 1u, 0u, 0u, 0u, 0u } },
};
static u32 test_sigma_final_spit_fire(u32 row)
{
    const struct sigma_final_spit_fire_case* c = &sigma_final_spit_fire_cases[row];
    u32 observed_values[8];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = c->unk7C;
    FILL_ACTIVE(shot_objects, 32, c->pool_0_full ? 1 : 0);
    sigma_final_spit_fire(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].x_pos.i.hi;
    observed_values[7] = (u32)shot_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

static const u32 sigma_spawn_sequencer_expected[] = { 1u, 0u, 0u, 0u };
static u32 test_sigma_spawn_sequencer(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    u8 pool_0_full;
    s8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    sigma_spawn_sequencer(&obj, arg1);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].unk2;
    observed_values[3] = (u32)obj.ext.main_73_parts.object_id;
    return c_test_observe(0, row, observed_values, sigma_spawn_sequencer_expected, 4);
}

#include "support/pool_full.h"
static u32 pool_full_sigma_final_wind_start(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 11;
    pf_snapshot();
    sigma_final_wind_start(&pf_self);
    pf_expected.unk7C = 10;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_sigma_final_wind_push(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 11;
    pf_snapshot();
    sigma_final_wind_push(&pf_self);
    pf_animated();
    pf_expected.unk7C = 10;
    pf_player_expected.x_pos.i.hi += 3;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_sigma_final_wind_start,
    pool_full_sigma_final_wind_push,
};

static const u32 pool_full_cases_expected[] = { 0xA0000u, 0xA0000u };
#include "support/state_cases.h"

#define CURRENT(on) (D_8013B8A8 = (struct ObjectHeader*)&effect_objects[0], effect_objects[0].active = on)
static void sf_idle(void)
{
    state_reset(1, 0, 0);
    sigma_final_idle(&so);
}
static void sf_laser_start(void)
{
    state_reset(9, 0, 0);
    sigma_final_laser(&so);
}
static void sf_laser_aim_high(void)
{
    state_reset(9, 1, 0);
    g_Player.y_pos.i.hi = 0x240;
    sigma_final_laser(&so);
}
static void sf_laser_aim_mid(void)
{
    state_reset(9, 1, 0);
    g_Player.y_pos.i.hi = 0x260;
    sigma_final_laser(&so);
}
static void sf_laser_aim_low(void)
{
    state_reset(9, 1, 0);
    g_Player.y_pos.i.hi = 0x280;
    sigma_final_laser(&so);
}
static void sf_laser_aim_floor(void)
{
    state_reset(9, 1, 0);
    g_Player.y_pos.i.hi = 0x2A0;
    sigma_final_laser(&so);
}
static void sf_laser_fire(void)
{
    state_reset(9, 2, 0);
    so.animation_step.fields.relative_step = -1;
    so.ext.main_74.animation_index = 2;
    sigma_final_laser(&so);
}
static void sf_laser_fire_wait(void)
{
    state_reset(9, 2, 0);
    sigma_final_laser(&so);
}
static void sf_laser_wait_done(void)
{
    state_reset(9, 3, 0);
    CURRENT(0);
    sigma_final_laser(&so);
}
static void sf_laser_wait(void)
{
    state_reset(9, 3, 0);
    CURRENT(1);
    sigma_final_laser(&so);
}
static void sf_laser_repeat_done(void)
{
    state_reset(9, 4, 0);
    so.unk7C = 1;
    sigma_final_laser(&so);
}
static void sf_laser_repeat_again(void)
{
    state_reset(9, 4, 0);
    so.unk7C = 2;
    sigma_final_laser(&so);
}
static void sf_laser_repeat_wait(void)
{
    state_reset(9, 4, 0);
    so.animation_step.fields.relative_step = 1;
    sigma_final_laser(&so);
}
static void sf_beam_start(void)
{
    state_reset(10, 0, 0);
    sigma_final_big_beam(&so);
}
static void sf_beam_fire(void)
{
    state_reset(10, 2, 0);
    CURRENT(0);
    so.ext.main_74.animation_index = 1;
    sigma_final_big_beam(&so);
}
static void sf_beam_fire_wait(void)
{
    state_reset(10, 2, 0);
    CURRENT(1);
    sigma_final_big_beam(&so);
}
static void sf_beam_wait_low(void)
{
    state_reset(10, 3, 0);
    CURRENT(0);
    sigma_final_big_beam(&so);
}
static void sf_beam_wait_high(void)
{
    state_reset(10, 3, 0);
    CURRENT(0);
    so.ext.main_74.animation_index = 1;
    sigma_final_big_beam(&so);
}
static void sf_beam_wait(void)
{
    state_reset(10, 3, 0);
    CURRENT(1);
    sigma_final_big_beam(&so);
}
static void sf_beam_recover(void)
{
    state_reset(10, 4, 0);
    sigma_final_big_beam(&so);
}
static void sf_beam_recover_wait(void)
{
    state_reset(10, 4, 0);
    so.animation_step.fields.relative_step = 1;
    sigma_final_big_beam(&so);
}
static void sf_show_upper(void)
{
    state_reset(4, 0, 0);
    sigma_final_show_upper(&so);
}
static void sf_show_upper_done(void)
{
    state_reset(4, 1, 0);
    so.animation_step.fields.relative_step = -1;
    sigma_final_show_upper(&so);
}
static void sf_show_upper_wait(void)
{
    state_reset(4, 1, 0);
    sigma_final_show_upper(&so);
}
static void sf_grab_start(void)
{
    state_reset(13, 0, 0);
    so.animation_step.fields.event = 1;
    sigma_final_grab(&so);
}
static void sf_grab_release_count(void)
{
    state_reset(13, 2, 0);
    so.unk7C = 1;
    sigma_final_grab(&so);
}
static void sf_grab_release(void)
{
    state_reset(13, 2, 0);
    sigma_final_grab(&so);
}
static void sf_grab_release_held(void)
{
    state_reset(13, 2, 0);
    shot_objects[3].active = 1;
    shot_objects[3].id = 0x38;
    sigma_final_grab(&so);
}
static void sf_grab_finish(void)
{
    state_reset(13, 3, 0);
    sigma_final_grab(&so);
}
static void sf_spit_open(void)
{
    state_reset(11, 0, 0);
    sigma_final_spit(&so);
}
static void sf_spit_wait_done(void)
{
    state_reset(11, 1, 0);
    so.unk7C = 1;
    sigma_final_spit(&so);
}
static void sf_spit_wait(void)
{
    state_reset(11, 1, 0);
    so.unk7C = 2;
    so.animation_step.fields.event = 1;
    sigma_final_spit(&so);
}
static void sf_spit_fire_done(void)
{
    state_reset(11, 2, 0);
    so.unk7C = 1;
    sigma_final_spit(&so);
}
static void sf_spit_fire_shot(void)
{
    state_reset(11, 2, 0);
    so.unk7C = 11;
    so.x_pos.i.hi = 0x40;
    sigma_final_spit(&so);
}
static void sf_spit_fire_wait(void)
{
    state_reset(11, 2, 0);
    so.unk7C = 3;
    sigma_final_spit(&so);
}
static void sf_summon_a(void)
{
    state_reset(8, 0, 0);
    cur_random = 1;
    sigma_final_summon(&so);
}
static void sf_summon_b(void)
{
    state_reset(8, 0, 0);
    cur_random = 2;
    sigma_final_summon(&so);
}
static void sf_summon_c(void)
{
    state_reset(8, 0, 0);
    cur_random = 3;
    sigma_final_summon(&so);
}
static void sf_summon_d(void)
{
    state_reset(8, 0, 0);
    cur_random = 4;
    sigma_final_summon(&so);
}
static void sf_death_start_lower(void)
{
    state_reset(0, 0, 0);
    so.ext.main_74.target = 2;
    sigma_final_death(&so);
}
static void sf_death_start_first(void)
{
    state_reset(0, 0, 0);
    so.ext.main_74.target = 1;
    D_8013B8B8 = 0;
    sigma_final_death(&so);
}
static void sf_death_start_second(void)
{
    state_reset(0, 0, 0);
    so.ext.main_74.target = 1;
    D_8013B8B8 = 1;
    sigma_final_death(&so);
}
static void sf_death_blink(void)
{
    state_reset(1, 0, 0);
    so.unk7E = 1;
    so.invincibility_timer = 0x19;
    sigma_final_death(&so);
}
static void sf_death_blink_last(void)
{
    state_reset(1, 0, 0);
    so.unk7E = 1;
    so.invincibility_timer = 3;
    sigma_final_death(&so);
}
static void sf_death_blink_wait(void)
{
    state_reset(1, 0, 0);
    so.unk7E = 2;
    sigma_final_death(&so);
}
static void sf_explode_blink(void)
{
    state_reset(2, 0, 0);
    so.unk7C = 3;
    so.ext.main_74.unk97 = 1;
    sigma_final_death(&so);
}
static void sf_explode_turn(void)
{
    state_reset(2, 0, 0);
    so.unk7C = 0x1C;
    so.unk7E = 3;
    so.ext.main_74.unk97 = 3;
    so.ext.main_74.target = 2;
    sigma_final_death(&so);
}
static void sf_explode_turn_upper(void)
{
    state_reset(2, 0, 0);
    so.unk7C = 0x1C;
    so.unk7E = 3;
    so.ext.main_74.unk97 = 3;
    sigma_final_death(&so);
}
static void sf_explode_first(void)
{
    state_reset(2, 0, 0);
    so.unk7C = 1;
    so.ext.main_74.target = 1;
    D_8013B8B8 = 0;
    sigma_final_death(&so);
}
static void sf_explode_second(void)
{
    state_reset(2, 0, 0);
    so.unk7C = 1;
    D_8013B8B8 = 1;
    sigma_final_death(&so);
}
static void sf_collapse(void)
{
    state_reset(3, 0, 0);
    so.animation_step.fields.relative_step = -1;
    sigma_final_death(&so);
}
static void sf_collapse_wait(void)
{
    state_reset(3, 0, 0);
    sigma_final_death(&so);
}
static void sf_explosion(void)
{
    state_reset(5, 0, 0);
    abc_object.unkC = 0;
    so.x_pos.i.hi = 0x30;
    sigma_final_death(&so);
}
static void sf_explosion_wait(void)
{
    state_reset(5, 0, 0);
    abc_object.unkC = 0x80;
    sigma_final_death(&so);
}
static void sf_finish_blink(void)
{
    state_reset(6, 0, 0);
    CURRENT(1);
    sigma_final_death(&so);
}
static void sf_finish_exploding(void)
{
    state_reset(6, 0, 0);
    CURRENT(1);
    effect_objects[0].unk7 = 1;
    sigma_final_death(&so);
}

static void (*const sigma_final_states_cases[])(void) = {
    sf_idle,
    sf_laser_start,
    sf_laser_aim_high,
    sf_laser_aim_mid,
    sf_laser_aim_low,
    sf_laser_aim_floor,
    sf_laser_fire,
    sf_laser_fire_wait,
    sf_laser_wait_done,
    sf_laser_wait,
    sf_laser_repeat_done,
    sf_laser_repeat_again,
    sf_laser_repeat_wait,
    sf_beam_start,
    sf_beam_fire,
    sf_beam_fire_wait,
    sf_beam_wait_low,
    sf_beam_wait_high,
    sf_beam_wait,
    sf_beam_recover,
    sf_beam_recover_wait,
    sf_show_upper,
    sf_show_upper_done,
    sf_show_upper_wait,
    sf_grab_start,
    sf_grab_release_count,
    sf_grab_release,
    sf_grab_release_held,
    sf_grab_finish,
    sf_spit_open,
    sf_spit_wait_done,
    sf_spit_wait,
    sf_spit_fire_done,
    sf_spit_fire_shot,
    sf_spit_fire_wait,
    sf_summon_a,
    sf_summon_b,
    sf_summon_c,
    sf_summon_d,
    sf_death_start_lower,
    sf_death_start_first,
    sf_death_start_second,
    sf_death_blink,
    sf_death_blink_last,
    sf_death_blink_wait,
    sf_explode_blink,
    sf_explode_turn,
    sf_explode_turn_upper,
    sf_explode_first,
    sf_explode_second,
    sf_collapse,
    sf_collapse_wait,
    sf_explosion,
    sf_explosion_wait,
    sf_finish_blink,
    sf_finish_exploding,
};
static const u32 sigma_final_states_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x109u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x209u, 0u, 0u, 0u, 0u, 0u, 0x20u, 0u, 0u, 0u, 0x209u, 0u, 0u, 0u, 0u, 0u, 0x1Du, 0u, 0u, 0u, 0x209u, 0u, 0u, 0u, 0u, 0u, 0x1Fu, 0u, 0u, 0u, 0x209u, 0u, 0u, 0u, 0u, 0u, 0x1Cu, 0u, 0u, 0u, 0x309u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0x209u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x409u, 0u, 0u, 0u, 0u, 0u, 0x21u, 0u, 0u, 0u, 0x309u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x109u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x409u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10Au, 0u, 0u, 0u, 0u, 0u, 0x1Du, 0u, 0u, 1u, 0x30Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x20Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x40Au, 0u, 0u, 0u, 0u, 0u, 0x24u, 0u, 0u, 0u, 0x40Au, 0u, 0u, 0u, 0u, 0u, 0x22u, 0u, 0u, 0u, 0x30Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0x5670000u, 0u, 0u, 0u, 0x18u, 2u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10Du, 0x3Cu, 0u, 0u, 0u, 0u, 2u, 2u, 0u, 1u, 0x20Du, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30Du, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0x20Du, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xBu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10Bu, 0x1Eu, 0u, 0u, 0u, 0u, 3u, 2u, 0u, 0u, 0x20Bu, 0xF1u, 0u, 0u, 0u, 0u, 4u, 0u, 0u, 0u, 0x10Bu, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 7u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x20Bu, 0xAu, 0x400000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 0x20Bu, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x108u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x108u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x108u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0x108u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 1u, 0x19007Fu, 0u, 0u, 0u, 0u, 1u, 0x1900u, 0u, 0u, 1u, 0x19007Fu, 0u, 0u, 0u, 0u, 0u, 0x1900u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0x18u, 0u, 0x1501u, 0u, 2u, 0x14012Cu, 0u, 0u, 0u, 0u, 0x80000000u, 0x1400u, 0u, 0u, 2u, 0x5012Cu, 0u, 0u, 0u, 0u, 0x80000000u, 0xFE00u, 0u, 0u, 1u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x50002u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 0x2100u, 2u, 0x2001Bu, 0u, 0u, 0u, 0u, 0x1Bu, 0u, 0u, 0u, 2u, 0x2001Bu, 0u, 0u, 0u, 0u, 0x19u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x5670000u, 0u, 0u, 0u, 0x18u, 0u, 0x1501u, 0u, 4u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0x300000u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFFF81u, 5u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 6u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u };

static u32 test_sigma_final_states(u32 row)
{
    return state_run(sigma_final_states_cases[row], row, &sigma_final_states_expected[row * 10]);
}

void sigma_final_death_explosion(struct MainObj*);
extern void* sigma_final_animations[39];
static struct EffectObj effects_before[32];
static struct BackgroundObj backgrounds_before[3];
static u32 full(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    struct ObjectHeader* previous;
    u32 i;
    (void)row;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine_obj.enable_boss = 1;
    background_objects[0].x_pos.i.hi = 1104;
    background_objects[0].y_pos.i.hi = 512;
    D_8013E198[2] = -1;
    D_8013B8B8 = 1;
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 2;
    obj.unk5 = 2;
    obj.unk7C = 1;
    obj.ext.main_74.target = 2;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    func_8008F578(&obj);
    assert(obj.unk5 == 3 && obj.unk17 == 24 && obj.x_pos.i.hi == 1383 && obj.y_pos.i.hi == 647);
    for (i = 0; i < 160 && obj.unk5 == 3; i++)
        sigma_final_death_collapse(&obj);
    assert(obj.unk5 == 4 && effect_objects[0].active == 1 && effect_objects[0].id == 43 && effect_objects[0].unk2 == 1);
    sigma_final_death_wait_player(&obj);
    assert(obj.unk5 == 4);
    obj.unk5 = 5;
    g_Player.script_state = -1;
    abc_object.unkC = 0;
    for (i = 1; i < COUNT(effect_objects); i++)
        effect_objects[i].active = 1;
    expected = obj;
    expected.unk5 = 6;
    set_animation(&expected, 0);
    expected.animation_step.fields.duration = 21;
    expected.on_screen = 1;
    player = g_Player;
    engine = engine_obj;
    previous = D_8013B8A8;
    memcpy(effects_before, effect_objects, sizeof(effects_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    cur_random = 0x1234;
    sigma_final_death_explosion(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(c_test_word_difference((u32*)effect_objects, (u32*)effects_before, sizeof(effects_before) / 4) == 0);
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(D_8013B8A8 == previous && cur_random == 0x1234);
    return 1;
}

extern struct Unk_unk68 D_80105374;
extern void* sigma_final_animations[39];
extern void* D_8013B8B4;
extern u8 D_8013B898, D_8013B89C, D_8013B8A4;
extern struct Unk_unk68 D_80105370, D_80108284[], D_80108304[];
void sigma_final_set_target(struct MainObj*, s32);
static const s16 weapons[] = { -1, 0, 24, 25, 35, -2 };
static const u8 flash_times[] = { 0, 1, 2, 3, 30 };
static const u8 damage[2][4] = { { 0, 0, 0, 4 }, { 0, 1, 2, 0 } };
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
static u32 stop_commands[2];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 weapon_regions(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_before[3];
    struct Unk_unk68* vulnerable;
    u8 counters[3][4] = { { 7, 0x25, 0x36, 0x47 }, { 9, 0x58, 0x69, 0x7A }, { 0, 0x8B, 0x9C, 0xAD } };
    u32 target = row % 2 + 1, hit = row / 2 % 6, phase = row / 12, flash = flash_times[phase % 2], prior = phase == 2, facing = phase == 3, i;
    s32 weapon = hit == 5 ? target == 1 ? 35 : 24 : weapons[hit];
    u32 damaging = weapon >= 0 && !flash && (hit == 5 || damage[target - 1][hit - 1] != 0);
    u32 lethal = hit == 5 && !flash, amount = hit == 5 ? target == 1 ? 4 : 1 : hit ? damage[target - 1][hit - 1]
                                                                                   : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    g_Player.hp = 24;
    g_Player.unk15 = facing ? 0x40 : 0;
    player_expected = g_Player;
    if (weapon == 35)
        player_expected.update_delay_request = 1;
    engine_obj.cur_character = weapon == 35;
    engine_expected = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 5;
    obj.bg_offset = 0;
    obj.unk15 = g_Player.unk15;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk42 = 0x9234;
    obj.unk62 = 4;
    obj.ext.main_74.upper_health = obj.ext.main_74.lower_health = hit == 5 ? 1 : 48;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, 0);
    sigma_final_set_target(&obj, target);
    vulnerable = target == 1 ? &D_80105368 : &D_80105374;
    D_8013B8B0 = vulnerable;
    D_8013B8B8 = prior ? 3 - target : 0;
    counters[2][0] = flash;
    D_8013B898 = counters[0][0];
    D_8013B89C = counters[1][0];
    D_8013B8A4 = counters[2][0];
    if (weapon >= 0) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = weapon;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].unk64 = 3;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = (const u8*)vulnerable;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.hurt_box = vulnerable;
    expected.collision_data = flash ? D_801060F0 : target == 1 ? D_80108284
                                                               : D_80108304;
    expected.unk42 = 0x1234;
    expected.unk65 = weapon < 0 ? 0 : 3;
    counters[0][0] = expected.unk65;
    counters[1][0] = 0;
    if (weapon >= 0) {
        ((s16*)&weapons_expected[0].unk80)[0] = 160 + (facing ? -1 : 1) * (target == 1 ? 15 : 24);
        ((s16*)&weapons_expected[0].unk80)[1] = target == 1 ? 120 : 212;
        expected.unk63 = damaging ? 0 : -1;
        if (weapon == 0)
            weapons_expected[0].unk98 = -1;
        if (damaging) {
            expected.hp = lethal ? 0 : 48 - amount;
            expected.unk42 |= 0x8000;
        }
    }
    if (lethal) {
        expected.unk5 = expected.unk6 = expected.unk62 = 0;
        expected.state = 2;
        expected.unk42 &= 0x7FFF;
        expected.ext.main_74.death_kind = prior ? 2 : 1;
        if (prior) {
            player_expected.script_state = 1;
            player_expected.script_action = 0x14;
            player_expected.script_facing = g_Player.unk15;
            player_expected.spike_immune = 1;
            engine_expected.gameplay_locked = 1;
        }
    } else {
        u32 tick = damaging ? weapon == 24 || weapon == 25 ? 2 : 30 : flash;
        if (damaging)
            expected.collision_data = D_801060F0;
        if (tick) {
            counters[2][0] = tick - 1;
            if (tick & 2)
                expected.unk42 |= 0x8000;
            else
                expected.unk42 &= 0x7FFF;
            if (tick == 1)
                expected.collision_data = target == 1 ? D_80108284 : D_80108304;
        }
    }
    stop_commands[0] = stop_commands[1] = 0;
    D_80141F50[2] = (u8*)stop_commands;
    D_8013E198[0] = D_8013E198[1] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    func_8008F1A8(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_expected);
    SAME(engine_obj, engine_expected);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(D_8013B898 == counters[0][0] && D_8013B89C == counters[1][0] && D_8013B8A4 == counters[2][0]);
    assert(D_8013B8B0 == vulnerable && D_8013B8B4 == (target == 1 ? &D_8010536C : &D_80105370) && D_8013B8B8 == (prior ? 3 - target : 0));
    assert(stop_commands[0] == 0 && stop_commands[1] == 0 && D_80141F50[2] == (u8*)stop_commands && cur_random == 0x1234);
    return 1;
}

extern void* sigma_final_animations[39];
static struct ShotObj shots_expected[32];
static struct EffectObj effects_expected[32];
static u32 wind(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 slots = row % 3, layer = row / 3, available = slots == 2 ? 12 : slots, i;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 0; i < COUNT(effect_objects); i++)
        effect_objects[i].active = i != 31;
    memcpy(effects_expected, effect_objects, sizeof(effects_expected));
    sigma_sequencer = NULL;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 12;
    obj.hp = 48;
    obj.x_pos.i.hi = 1473;
    obj.y_pos.i.hi = 707;
    obj.bg_offset = layer;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    expected = obj;
    expected.ext.main_73_parts.object_id = 6;
    expected.unk17 = 2;
    expected.previous_animation_index = 255;
    expected.animation_cursor = sigma_final_animations[2];
    expected.animation_step.packed = 0x06010102;
    expected.unk7C = 60;
    expected.unk6 = 1;
    effects_expected[31].active = 1;
    effects_expected[31].id = 42;
    effects_expected[31].ext.effect_42.owner.main = &obj;
    for (i = 0; i < available; i++) {
        struct ShotObj* s = &shots_expected[32 - available + i];
        s->active = 0x41;
        s->id = 54;
        s->unk2 = 7;
        s->x_pos.i.hi = 1440;
        s->y_pos.i.hi = 552 + i * 16;
        s->unk7C = WEAPON_OBJECT(&obj);
    }
    func_8008EC48(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(effect_objects, effects_expected, sizeof(effects_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(sigma_sequencer == &effect_objects[31]);
    return 1;
}

void sigma_final_laser_fire(struct MainObj*);
extern void* sigma_final_animations[39];
static const u8 animations[] = { 28, 31, 29, 32 }, last_steps[] = { 5, 6, 7, 8 }, final_frames[] = { 94, 97, 95, 98 };
static struct QuadObj quads_expected[32];
static struct ShotObj shots_expected_sigma_laser_pool_exhaustion[32];
static u32 fire(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    struct ObjectHeader* link_before;
    u32 aim = row % 4, quad = row / 4 % 2, shot = row / 8 % 2, event = row / 16, i;
    memset(&obj, 0, sizeof(obj));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        g_QuadObjects[i].active = 1;
        shot_objects[i].active = 1;
    }
    if (quad)
        g_QuadObjects[31].active = 0;
    if (shot)
        shot_objects[31].active = 0;
    memcpy(quads_expected, g_QuadObjects, sizeof(quads_expected));
    memcpy(shots_expected_sigma_laser_pool_exhaustion, shot_objects, sizeof(shots_expected_sigma_laser_pool_exhaustion));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 0x41;
    obj.id = 74;
    obj.state = 1;
    obj.unk5 = 9;
    obj.unk6 = 2;
    obj.ext.main_74.animation_index = aim;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, animations[aim]);
    assert(obj.animation_step.packed == 0x4F01001E);
    if (event) {
        obj.animation_cursor = (const u8*)sigma_final_animations[animations[aim]] + 4 * (last_steps[aim] - 1);
        memcpy(&obj.animation_step, obj.animation_cursor, 4);
        assert(obj.animation_step.fields.duration == 1 && obj.animation_step.fields.relative_step == 1);
    }
    expected = obj;
    D_8013B8A8 = OBJECT_HEADER(&obj);
    link_before = D_8013B8A8;
    if (event) {
        expected.animation_cursor += 4;
        expected.animation_step.packed = ((u32)final_frames[aim] << 24) | 0xFF0001;
        expected.unk6++;
        if (quad) {
            quads_expected[31].active = 1;
            quads_expected[31].id = 16;
            quads_expected[31].unk2 = aim;
            quads_expected[31].unk5C = PLAYER_OBJECT(&obj);
        }
        if (shot) {
            shots_expected_sigma_laser_pool_exhaustion[31].active = 1;
            shots_expected_sigma_laser_pool_exhaustion[31].id = 57;
            shots_expected_sigma_laser_pool_exhaustion[31].unk2 = aim;
            shots_expected_sigma_laser_pool_exhaustion[31].unk7C = WEAPON_OBJECT(&obj);
        }
    } else
        expected.animation_step.fields.duration = 29;
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    sigma_final_laser_fire(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((u32*)g_QuadObjects, (u32*)quads_expected, sizeof(quads_expected) / 4) == 0 && c_test_word_difference((u32*)shot_objects, (u32*)shots_expected_sigma_laser_pool_exhaustion, sizeof(shots_expected_sigma_laser_pool_exhaustion) / 4) == 0);
    assert(D_8013B8A8 == (event ? (quad ? OBJECT_HEADER(&g_QuadObjects[31]) : NULL) : link_before) && cur_random == 0x1234);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_final_states", 0, 0, COUNT(sigma_final_states_cases), test_sigma_final_states },
    { "sigma_final_beam_charge_pools", NULL, sigma_final_beam_charge_pools_cases_expected, COUNT(sigma_final_beam_charge_pools_cases_expected), charge_case },
    { "sigma_final_death_dialogue", NULL, sigma_final_death_dialogue_cases_expected, COUNT(sigma_final_death_dialogue_cases_expected), dialogue_case },
    { "sigma_final_laser_aim_heights", NULL, sigma_final_laser_aim_heights_cases_expected, COUNT(sigma_final_laser_aim_heights_cases_expected), sigma_final_laser_aim_heights_cases_row },
    { "sigma_grab_live_shots", sigma_grab_live_shots_cases, sigma_grab_live_shots_cases_expected, COUNT(sigma_grab_live_shots_cases), 0 },
    { "sigma_grab_shot_pool_context", NULL, sigma_grab_shot_pool_context_cases_expected, COUNT(sigma_grab_shot_pool_context_cases_expected), grab_case },
    { "sigma_lower_hide_children", NULL, sigma_lower_hide_children_cases_expected, COUNT(sigma_lower_hide_children_cases_expected), sigma_lower_hide_children_cases_row },
    { "sigma_pattern_rng", sigma_pattern_rng_cases, sigma_pattern_rng_cases_expected, COUNT(sigma_pattern_rng_cases), 0 },
    { "func_8008DAE8", 0, 0, 6, test_func_8008DAE8 },
    { "sigma_final_death_blink", 0, 0, 1, test_sigma_final_death_blink },
    { "sigma_final_death_collapse", 0, 0, 2, test_sigma_final_death_collapse },
    { "sigma_final_set_target", 0, 0, 1, test_sigma_final_set_target },
    { "sigma_final_spit_fire", 0, 0, 2, test_sigma_final_spit_fire },
    { "sigma_spawn_sequencer", 0, 0, 1, test_sigma_spawn_sequencer },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "Sigma_actual_second_body_death_collapse_rumble_finished_dialogue_full_effect_pool", NULL, NULL, 1, full },
    { "real_body_vulnerable_regions_flash_and_death", NULL, NULL, 48, weapon_regions },
    { "own_Sigma_final_wind_spikes_full_partial_twelve_free_shot_slots", NULL, NULL, 9, wind },
    { "all_aims_shipped_fire_events_and_independent_full_pools", NULL, NULL, 32, fire },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_final_states_cases) + COUNT(sigma_final_beam_charge_pools_cases_expected) + COUNT(sigma_final_death_dialogue_cases_expected) + COUNT(sigma_final_laser_aim_heights_cases_expected) + COUNT(sigma_grab_live_shots_cases) + COUNT(sigma_grab_shot_pool_context_cases_expected) + COUNT(sigma_lower_hide_children_cases_expected) + COUNT(sigma_pattern_rng_cases) + 6 + 1 + 2 + 1 + 2 + 1 + COUNT(pool_full_cases) + 1 + 48 + 9 + 32;
