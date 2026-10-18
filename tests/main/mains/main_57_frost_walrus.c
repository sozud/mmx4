#include "test_runtime.h"
#include "main/mains/main_57_frost_walrus.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern void* frost_walrus_animations[39];
extern u32* D_80137E08;
void frost_walrus_choose_script(struct MainObj*);
extern u8** frost_walrus_scripts[3];
extern u8 frost_walrus_script_weights[3][4];
extern u8* D_80141EE8[6];

static u32 guarded_tiles[0x802];
static u8 selected_tiles[0x800];

static u32 floor_case(s8 stage, s32 attribute, u8 empty)
{
    u32 i, count, actual;
    u16* list;

    TEST_BG_TILE_ATTRS = (u8*)&guarded_tiles[1];
    engine_obj.stage = stage;
    guarded_tiles[0] = 0xCAFE1234u;
    guarded_tiles[0x801] = 0x5678BEEFu;
    memset(selected_tiles, 0, sizeof(selected_tiles));
    for (i = 0; i < COUNT(selected_tiles); i++)
        guarded_tiles[i + 1] = 0xA1230000u | (i & 0xFF);
    list = stage == 0xC ? frost_walrus_floor_tiles_rush : frost_walrus_floor_tiles;
    if (empty)
        list[0] = 0;
    count = stage == 0xC ? COUNT(frost_walrus_floor_tiles_rush) : COUNT(frost_walrus_floor_tiles);
    for (i = 0; i < count && list[i] != 0; i++) {
        assert(list[i] < COUNT(selected_tiles));
        selected_tiles[list[i]] = 1;
    }
    assert(i < count);

    frost_walrus_set_floor_tiles(attribute);
    actual = guarded_tiles[list[0] + 1];
    if (empty)
        assert(actual == 0xA1230000u);
    else
        assert(actual == (stage == 0xC ? 0xA1230039u : 0xA1230038u));
    for (i = 0; i < COUNT(selected_tiles); i++) {
        if (selected_tiles[i])
            assert(guarded_tiles[i + 1] == (stage == 0xC ? 0xA1230039u : 0xA1230038u));
        else
            assert(guarded_tiles[i + 1] == (0xA1230000u | (i & 0xFF)));
    }
    assert(guarded_tiles[0] == 0xCAFE1234u);
    assert(guarded_tiles[0x801] == 0x5678BEEFu);
    assert(engine_obj.stage == stage);
    return actual;
}

static u32 normal_floor(void) { return floor_case(7, 0x38, 0); }
static u32 boss_rush_floor(void) { return floor_case(0xC, 0x39, 0); }
static u32 empty_floor(void) { return floor_case(7, 0x38, 1); }

static const CTestCase frost_floor_archive_cases[] = {
    normal_floor,
    boss_rush_floor,
    empty_floor,
};
static const u32 frost_floor_archive_cases_expected[] = { 0xA1230038u, 0xA1230039u, 0xA1230000u };

static u32 blizzard_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    struct ShotObj expected_shots[32];
    struct VisualObj expected_visuals[32];
    u32* command_before = D_80137E08;
    const union AnimationStep* steps = frost_walrus_animations[22];
    u32 i, frame = mode < 4 ? 5 : mode == 6 ? 4
                                            : 0;
    u32 visual_free = (mode < 4 && (mode & 1)) || mode >= 6;
    u32 shot_free = (mode < 4 && (mode & 2)) || mode >= 6;
    u32 actual;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0xA5, sizeof(shot_objects));
    memset(visual_objects, 0x5A, sizeof(visual_objects));
    for (i = 0; i < 32; i++)
        shot_objects[i].active = visual_objects[i].active = 1;
    if (shot_free)
        shot_objects[29].active = 0;
    if (visual_free)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk5 = 8;
    obj.unk6 = 3;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk7C = mode == 4 ? 1 : mode == 5 ? 2
                                          : 65;
    obj.unk7E = mode == 5 ? 1 : 7;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    obj.animation_cursor = (const u8*)&steps[frame];
    obj.animation_step = steps[frame];
    obj.unk17 = 22;
    obj.previous_animation_index = 9;
    if (mode < 4)
        obj.animation_step.fields.duration = 2;
    expected = obj;
    memcpy(expected_shots, shot_objects, sizeof(expected_shots));
    memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    if (--expected.animation_step.fields.duration == 0) {
        expected.animation_cursor = (const u8*)&steps[frame + 1];
        expected.animation_step = steps[frame + 1];
    }
    expected.unk7E = mode == 5 ? 24 : 6;
    expected.unk7C--;
    if (mode == 4) {
        expected.unk7C = 128;
        expected.unk6 = 4;
        expected.animation_cursor = (const u8*)&steps[0];
        expected.animation_step = steps[0];
        expected.previous_animation_index = 0xFF;
    }
    if ((mode < 4 || mode == 6) && visual_free) {
        expected_visuals[31].active = 0x41;
        expected_visuals[31].id = 0x18;
        expected_visuals[31].unk2 = 0x30;
        expected_visuals[31].unk15 = obj.unk15;
        expected_visuals[31].unk50 = &obj;
        expected_visuals[31].x_pos.i.hi = obj.x_pos.i.hi + (obj.unk15 ? 21 : -21);
        expected_visuals[31].y_pos.i.hi = obj.y_pos.i.hi;
    }
    if (expected.unk7C == 64 && shot_free) {
        expected_shots[29].unk50.data = NULL;
        expected_shots[29].unk54 = NULL;
        expected_shots[29].unk68 = NULL;
        expected_shots[29].unk98 = NULL;
        expected_shots[29].unk61 = expected_shots[29].unk64 = expected_shots[29].unk65 = 0;
        expected_shots[29].unk66 = expected_shots[29].unk72 = expected_shots[29].unk73 = 0;
        expected_shots[29].unk74 = expected_shots[29].unk76 = expected_shots[29].unk77 = 0;
        expected_shots[29].unk78 = expected_shots[29].unk62 = expected_shots[29].unk63 = 0;
        expected_shots[29].unk7A = expected_shots[29].unk75 = 0;
        expected_shots[29].active = 0x41;
        expected_shots[29].id = 0x23;
        expected_shots[29].unk2 = 0x20;
        expected_shots[29].unk7C = &obj;
        expected.ext.main_57.shot = &shot_objects[29];
    }
    frost_walrus_blizzard_blow(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(expected_shots) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)expected_shots)[i]);
    for (i = 0; i < sizeof(expected_visuals) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)expected_visuals)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(D_80137E08 == command_before);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(steps[0].packed == 0x14010002 && steps[4].packed == 0x1B010101 && steps[5].packed == 0x6B010201);
    actual = (u8)obj.unk6 | ((u32)(u16)obj.unk7C << 8) | ((u32)visual_objects[31].active << 24);
    return actual;
}
#define CASE(m)                                                   \
    static u32 walrus_blizzard_animation_pools_blizzard_##m(void) \
    {                                                             \
        return blizzard_case(m);                                  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) walrus_blizzard_animation_pools_blizzard_##m,
static const CTestCase walrus_blizzard_animation_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 walrus_blizzard_animation_pools_cases_expected[] = { 0x1004003u, 0x41004003u, 0x1004003u, 0x41004003u, 0x1008004u, 0x1000103u, 0x41004003u, 0x4003u };
#undef CASE
#undef ENTRY

static u32 charge_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32* command_before = D_80137E08;
    u32 i, broken = mode >= 2, animation = broken ? 23 : 1;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 0;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.ext.main_57.tusks_broken = broken;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    set_animation(&obj, 0);
    expected = obj;
    expected.y_speed = expected.x_accel = expected.gravity = 0;
    expected.unk6 = broken ? 3 : 1;
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)frost_walrus_animations[animation];
    expected.animation_step = *(union AnimationStep*)frost_walrus_animations[animation];
    if (broken) {
        expected.x_speed = mode & 1 ? 0x18000 : -0x18000;
        expected.hurt_box = (const u8*)&frost_walrus_charge_hurt_box;
        expected.attack_box = (const u8*)&frost_walrus_charge_attack_box;
    } else {
        expected.hurt_box = (const u8*)&frost_walrus_hurt_box;
        expected.attack_box = (const u8*)&frost_walrus_attack_box;
    }
    frost_walrus_charge_start(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(D_80137E08 == command_before);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u16)(obj.x_speed / 32768) << 16);
}
#define CASE(m)                                            \
    static u32 walrus_charge_tusk_context_charge_##m(void) \
    {                                                      \
        return charge_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) walrus_charge_tusk_context_charge_##m,
static const CTestCase walrus_charge_tusk_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 walrus_charge_tusk_context_cases_expected[] = { 0x101u, 0x101u, 0xFFFD1703u, 0x31703u };
#undef CASE
#undef ENTRY

static const s16 distances[7] = { 193, 192, -192, -193, 193, 192, 0 };
static u32 intro_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    const union AnimationStep* walk = frost_walrus_animations[38];
    const union AnimationStep* roar = frost_walrus_animations[1];
    u32 i, actual, close = mode == 1 || mode == 2 || mode == 4 || mode == 6;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 57;
    obj.state = 1;
    obj.unk6 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = mode == 4 ? 65536 : mode == 5 ? -65536
                                                : 0;
    obj.y_speed = 32768;
    obj.x_accel = 123;
    obj.gravity = 456;
    obj.animation_table = (const u8* const*)frost_walrus_animations;
    obj.animation_cursor = (const u8*)walk;
    obj.animation_step = walk[0];
    obj.unk17 = 38;
    obj.previous_animation_index = 9;
    g_Player.x_pos.i.hi = 100 + distances[mode];
    player_before = g_Player;
    expected = obj;
    expected.animation_step.fields.duration = 2;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val -= obj.y_speed;
    if (close) {
        expected.x_speed = 0;
        expected.unk6 = 8;
        expected.unk17 = 1;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)roar;
        expected.animation_step = roar[0];
    }
    frost_walrus_intro_approach(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(walk[0].packed == 0x3E010003 && roar[0].packed == 0x00010002);
    actual = (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
    return actual;
}
#define CASE(m)                                             \
    static u32 walrus_intro_player_boundary_intro_##m(void) \
    {                                                       \
        return intro_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
#define ENTRY(m) walrus_intro_player_boundary_intro_##m,
static const CTestCase walrus_intro_player_boundary_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) };
static const u32 walrus_intro_player_boundary_cases_expected[] = { 0x642607u, 0x640108u, 0x640108u, 0x642607u, 0x650108u, 0x632607u, 0x640108u };
#undef CASE
#undef ENTRY

static u32 script_case(u32 mode)
{
    struct MainObj obj, before;
    u8 weights_before[3][4], sentinel[] = { 0x27, 0x28, 0x29, 0xFF };
    u32 i, result;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 57;
    obj.hp = 0;
    obj.ext.main_57.script = sentinel;
    memcpy(weights_before, frost_walrus_script_weights, sizeof(weights_before));
    if (mode == 1)
        memset(frost_walrus_script_weights[0], 0, 4);
    cur_random = 0;
    before = obj;
    frost_walrus_choose_script(&obj);
    if (mode == 0) {
        assert(obj.ext.main_57.script == frost_walrus_scripts[0][0]);
        before.ext.main_57.script = frost_walrus_scripts[0][0];
    } else
        assert(obj.ext.main_57.script == sentinel);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(cur_random == 0 && sentinel[0] == 0x27 && sentinel[1] == 0x28 && sentinel[2] == 0x29 && sentinel[3] == 0xFF);
    for (i = 0; i < 12; i++)
        assert(((u8*)frost_walrus_script_weights)[i] == (mode == 1 && i < 4 ? 0 : ((u8*)weights_before)[i]));
    result = mode == 0 ? *obj.ext.main_57.script : 0x100 | *obj.ext.main_57.script;
    return result;
}
#define CASE(m)                                          \
    static u32 walrus_script_exhaustion_script_##m(void) \
    {                                                    \
        return script_case(m);                           \
    }
CASE(0)
CASE(1)
#define ENTRY(m) walrus_script_exhaustion_script_##m,
static const CTestCase walrus_script_exhaustion_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 walrus_script_exhaustion_cases_expected[] = { 0x6u, 0x127u };
#undef CASE
#undef ENTRY

static const u32 frost_walrus_blizzard_blow_expected[] = { 0u, 0x40u, 0xFFFFFFFFu, 1u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_frost_walrus_blizzard_blow(u32 row)
{
    u32 observed_values[12];
    struct MainObj obj;
    u8 pool_1_full;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 65;
    obj.animation_step.fields.event = 2;
    pool_1_full = 255;
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_1_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    frost_walrus_blizzard_blow(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.unk7E;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].active;
    observed_values[7] = (u32)visual_objects[0].id;
    observed_values[8] = (u32)visual_objects[0].unk15;
    observed_values[9] = (u32)visual_objects[0].unk2;
    observed_values[10] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[11] = (u32)visual_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, frost_walrus_blizzard_blow_expected, 12);
}

static const u32 frost_walrus_death_explode_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 2u, 0u, 5u };
static u32 test_frost_walrus_death_explode(u32 row)
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
    frost_walrus_death_explode(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.i.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.i.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, frost_walrus_death_explode_expected, 9);
}

static const u32 frost_walrus_intro_approach_expected[] = { 0u, 0u };
static u32 test_frost_walrus_intro_approach(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.x_pos.i.hi = -32764;
    g_Player.x_pos.i.hi = -16368;
    frost_walrus_intro_approach(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, frost_walrus_intro_approach_expected, 2);
}

static const u32 frost_walrus_shards_count_expected[] = { 0u, 4u, 1u, 0u };
static u32 test_frost_walrus_shards_count(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.hp = 24;
    frost_walrus_shards_count(&obj);
    observed_values[0] = (u32)obj.ext.main_57.leap_grounded;
    observed_values[1] = (u32)obj.ext.main_57.shard_count;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, frost_walrus_shards_count_expected, 4);
}

static const u32 frost_walrus_shards_fire_expected[] = { 1u, 2u, 0x20u, 1u, 0u, 0u, 0u };
static u32 test_frost_walrus_shards_fire(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    frost_walrus_shards_fire(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.unk7E;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk7;
    return c_test_observe(0, row, observed_values, frost_walrus_shards_fire_expected, 7);
}

#include "support/pool_full.h"
static u32 pool_full_frost_walrus_start_warning(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    frost_walrus_start_warning(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_frost_walrus_regrow_start(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    frost_walrus_regrow_start(&pf_self);
    pf_expected.collision_data = (const u16*)D_801060F0;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_frost_walrus_intro_burst(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 2;
    pf_event(1, 1);
    pf_snapshot();
    frost_walrus_intro_burst(&pf_self);
    pf_animated();
    pf_expected.unk7C = 1;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_frost_walrus_breath_blow(void)
{
    u32 actual;
    pf_prepare();
    pf_event(2, 1);
    pf_self.unk7C = 0x41;
    pf_snapshot();
    frost_walrus_breath_blow(&pf_self);
    pf_animated();
    pf_expected.unk7C = 0x40;
    pf_expected.unk7E = 4;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_frost_walrus_start_warning,
    pool_full_frost_walrus_regrow_start,
    pool_full_frost_walrus_intro_burst,
    pool_full_frost_walrus_breath_blow,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x10000u, 0x400000u };
const struct CTestGroup c_test_groups[] = {
    { "frost_floor_archive", frost_floor_archive_cases, frost_floor_archive_cases_expected, COUNT(frost_floor_archive_cases), 0 },
    { "walrus_blizzard_animation_pools", walrus_blizzard_animation_pools_cases, walrus_blizzard_animation_pools_cases_expected, COUNT(walrus_blizzard_animation_pools_cases), 0 },
    { "walrus_charge_tusk_context", walrus_charge_tusk_context_cases, walrus_charge_tusk_context_cases_expected, COUNT(walrus_charge_tusk_context_cases), 0 },
    { "walrus_intro_player_boundary", walrus_intro_player_boundary_cases, walrus_intro_player_boundary_cases_expected, COUNT(walrus_intro_player_boundary_cases), 0 },
    { "walrus_script_exhaustion", walrus_script_exhaustion_cases, walrus_script_exhaustion_cases_expected, COUNT(walrus_script_exhaustion_cases), 0 },
    { "frost_walrus_blizzard_blow", 0, 0, 1, test_frost_walrus_blizzard_blow },
    { "frost_walrus_death_explode", 0, 0, 1, test_frost_walrus_death_explode },
    { "frost_walrus_intro_approach", 0, 0, 1, test_frost_walrus_intro_approach },
    { "frost_walrus_shards_count", 0, 0, 1, test_frost_walrus_shards_count },
    { "frost_walrus_shards_fire", 0, 0, 1, test_frost_walrus_shards_fire },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(frost_floor_archive_cases) + COUNT(walrus_blizzard_animation_pools_cases) + COUNT(walrus_charge_tusk_context_cases) + COUNT(walrus_intro_player_boundary_cases) + COUNT(walrus_script_exhaustion_cases) + 1 + 1 + 1 + 1 + 1 + COUNT(pool_full_cases);
