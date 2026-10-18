#include "test_runtime.h"
#include "main/mains/main_74_sigma_final.h"
#include "main/55C4.h"
extern void* sigma_final_animations[39];
extern void* D_8013B8B4;
extern u8 D_8013B8A0[4];
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
#define CASE(m)                                               \
    static u32 sigma_final_beam_charge_pools_charge_##m(void) \
    {                                                         \
        return charge_case(m);                                \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) sigma_final_beam_charge_pools_charge_##m,
static const CTestCase sigma_final_beam_charge_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 sigma_final_beam_charge_pools_cases_expected[] = { 0x1D010102u, 0x1010103u, 0x1014103u, 0x1014103u, 0x1010103u };
#undef CASE
#undef ENTRY

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
#define CASE(m)                                              \
    static u32 sigma_final_death_dialogue_dialogue_##m(void) \
    {                                                        \
        return dialogue_case(m);                             \
    }
CASE(0)
CASE(1)
#define ENTRY(m) sigma_final_death_dialogue_dialogue_##m,
static const CTestCase sigma_final_death_dialogue_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 sigma_final_death_dialogue_cases_expected[] = { 0x5802Cu, 0x58025u };
#undef CASE
#undef ENTRY

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
#define CASE(m, n)                                               \
    static u32 sigma_final_laser_aim_heights_aim_##m##_##n(void) \
    {                                                            \
        return aim_case(m, n);                                   \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(m, n) sigma_final_laser_aim_heights_aim_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase sigma_final_laser_aim_heights_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 sigma_final_laser_aim_heights_cases_expected[] = { 0x200303u, 0x4F01001Eu, 0x1D0302u, 0x4F01001Eu, 0x1F0301u, 0x4F01001Eu };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

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
#define CASE(m)                                            \
    static u32 sigma_grab_shot_pool_context_grab_##m(void) \
    {                                                      \
        return grab_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) sigma_grab_shot_pool_context_grab_##m,
static const CTestCase sigma_grab_shot_pool_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 sigma_grab_shot_pool_context_cases_expected[] = { 0x601071Eu, 0x6010701u, 0x6010704u, 0x6410704u, 0x6010700u, 0x9020B00u, 0x9000B00u, 0x9010B00u };
#undef CASE
#undef ENTRY

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
    for (i = 0; i < 4; i++)
        D_8013B8A0[i] = 0x27 + i;
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
    assert(D_8013B8A0[0] == (mode == 0 ? 0x1E : 0x27));
    assert(D_8013B8A0[1] == 0x28 && D_8013B8A0[2] == 0x29 && D_8013B8A0[3] == 0x2A);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(children) / 4; i++)
        assert(((u32*)children)[i] == ((u32*)children_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(box.unk0 == 1 && box.unk1 == 2 && box.unk2 == 3 && box.unk3 == 4);
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)D_8013B8A0[0] << 16) : obj.animation_step.packed;
}
#define CASE(m, n)                                            \
    static u32 sigma_lower_hide_children_hide_##m##_##n(void) \
    {                                                         \
        return hide_case(m, n);                               \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(m, n) sigma_lower_hide_children_hide_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase sigma_lower_hide_children_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 sigma_lower_hide_children_cases_expected[] = { 0x1E0002u, 0x4F000002u, 0x270107u, 0x4F000001u, 0x270107u, 0x4F010001u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

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
    D_8013B8A0[0] = 0;
    D_8013B8A0[1] = 0x27;
    D_8013B8A0[2] = 0x28;
    D_8013B8A0[3] = 0x29;
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
    assert(D_8013B8A0[0] == 0 && D_8013B8A0[1] == 0x27
        && D_8013B8A0[2] == 0x28 && D_8013B8A0[3] == 0x29 && D_8013B8B8 == 0);
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
    observed_values[0] = (u32)D_8013B8A0[0];
    observed_values[1] = (u32)obj.ext.main_74.pattern_index;
    observed_values[2] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static const u32 func_8008E748_expected[] = { 3u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u };
static u32 test_func_8008E748(u32 row)
{
    u32 observed_values[10];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    obj.unk7C = 1;
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8008E748(&obj);
    observed_values[0] = (u32)g_Player.x_pos.u.hi;
    observed_values[1] = (u32)g_Player.y_pos.u.hi;
    observed_values[2] = (u32)obj.contact_damage;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.unk62;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)shot_objects[0].active;
    observed_values[8] = (u32)shot_objects[0].id;
    observed_values[9] = (u32)shot_objects[0].unk2;
    return c_test_observe(0, row, observed_values, func_8008E748_expected, 10);
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
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.animation_step.fields.relative_step = -128;
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    sigma_final_death_collapse(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].unk2;
    observed_values[3] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 sigma_final_death_wait_player_expected[] = { 0u };
static u32 test_sigma_final_death_wait_player(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_801397BC, 0, sizeof(D_801397BC));
    memset(&D_801397C0, 0, sizeof(D_801397C0));
    memset(&D_801397C4, 0, sizeof(D_801397C4));
    memset(&D_801397C8, 0, sizeof(D_801397C8));
    memset(&D_801397CC, 0, sizeof(D_801397CC));
    memset(&D_801397D0, 0, sizeof(D_801397D0));
    memset(&D_801397D4, 0, sizeof(D_801397D4));
    memset(&D_801397D8, 0, sizeof(D_801397D8));
    memset(&D_801397DC, 0, sizeof(D_801397DC));
    memset(&D_801397E0, 0, sizeof(D_801397E0));
    memset(&D_801397E4, 0, sizeof(D_801397E4));
    memset(&D_80139824, 0, sizeof(D_80139824));
    memset(&D_80139828, 0, sizeof(D_80139828));
    memset(&D_8013B8B0, 0, sizeof(D_8013B8B0));
    memset(&D_8013B8B4, 0, sizeof(D_8013B8B4));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&need_palette_load, 0, sizeof(need_palette_load));

    g_Player.script_state = 0;
    engine_obj.cur_character = 0;
    sigma_final_death_wait_player(&obj);
    observed_values[0] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, sigma_final_death_wait_player_expected, 1);
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
    u8 pool_0_full;
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
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
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
const struct CTestGroup c_test_groups[] = {
    { "sigma_final_beam_charge_pools", sigma_final_beam_charge_pools_cases, sigma_final_beam_charge_pools_cases_expected, COUNT(sigma_final_beam_charge_pools_cases), 0 },
    { "sigma_final_death_dialogue", sigma_final_death_dialogue_cases, sigma_final_death_dialogue_cases_expected, COUNT(sigma_final_death_dialogue_cases), 0 },
    { "sigma_final_laser_aim_heights", sigma_final_laser_aim_heights_cases, sigma_final_laser_aim_heights_cases_expected, COUNT(sigma_final_laser_aim_heights_cases), 0 },
    { "sigma_grab_live_shots", sigma_grab_live_shots_cases, sigma_grab_live_shots_cases_expected, COUNT(sigma_grab_live_shots_cases), 0 },
    { "sigma_grab_shot_pool_context", sigma_grab_shot_pool_context_cases, sigma_grab_shot_pool_context_cases_expected, COUNT(sigma_grab_shot_pool_context_cases), 0 },
    { "sigma_lower_hide_children", sigma_lower_hide_children_cases, sigma_lower_hide_children_cases_expected, COUNT(sigma_lower_hide_children_cases), 0 },
    { "sigma_pattern_rng", sigma_pattern_rng_cases, sigma_pattern_rng_cases_expected, COUNT(sigma_pattern_rng_cases), 0 },
    { "func_8008DAE8", 0, 0, 6, test_func_8008DAE8 },
    { "func_8008E748", 0, 0, 1, test_func_8008E748 },
    { "sigma_final_death_blink", 0, 0, 1, test_sigma_final_death_blink },
    { "sigma_final_death_collapse", 0, 0, 2, test_sigma_final_death_collapse },
    { "sigma_final_death_wait_player", 0, 0, 1, test_sigma_final_death_wait_player },
    { "sigma_final_set_target", 0, 0, 1, test_sigma_final_set_target },
    { "sigma_final_spit_fire", 0, 0, 2, test_sigma_final_spit_fire },
    { "sigma_spawn_sequencer", 0, 0, 1, test_sigma_spawn_sequencer },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_final_beam_charge_pools_cases) + COUNT(sigma_final_death_dialogue_cases) + COUNT(sigma_final_laser_aim_heights_cases) + COUNT(sigma_grab_live_shots_cases) + COUNT(sigma_grab_shot_pool_context_cases) + COUNT(sigma_lower_hide_children_cases) + COUNT(sigma_pattern_rng_cases) + 6 + 1 + 1 + 2 + 1 + 1 + 2 + 1 + COUNT(pool_full_cases);
