#include "test_runtime.h"
extern struct AnimationTable12 jet_stingray_flyby_animations;

enum { START,
    CRUISE,
    CRUISE_END,
    APPROACH_DONE,
    APPROACH_MOVE,
    IDLE };
static u32 steps[1];
static u32* table[2];
static struct MainObj flyby, expected;

static void animation(u32 index)
{
    expected.animation_cursor = table[index];
    expected.unk17 = index;
    expected.previous_animation_index = 0xFF;
    expected.animation_step.packed = *table[index];
}

static u32 flyby_cruise_states_run(u32 mode)
{
    union AnimationStep step;
    u32 i, distance, difference = 0;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.val = 0x00400000;
    step.packed = 0;
    step.fields.duration = 5;
    step.fields.relative_step = 1;
    step.fields.frame_index = 4;
    steps[0] = step.packed;
    table[0] = table[1] = &steps[0];
    memset(&flyby, 0, sizeof(flyby));
    flyby.active = 0x41;
    flyby.id = 0x37;
    flyby.x_pos.val = mode == APPROACH_DONE ? 0x00601234 : 0x00A01234;
    flyby.y_pos.val = 0x00605678;
    flyby.x_speed = 0x20000;
    flyby.y_speed = 0x8000;
    flyby.unk6 = mode == START ? 0 : mode == CRUISE || mode == CRUISE_END ? 1
        : mode == IDLE                                                    ? 3
                                                                          : 2;
    flyby.unk7C = mode == CRUISE_END ? 0 : 9;
    flyby.animation_table = table;
    flyby.animation_cursor = &steps[0];
    flyby.animation_step.packed = steps[0];
    expected = flyby;
    func_8006F0DC(&flyby);

    switch (mode) {
    case START:
        expected.unk6 = 1;
        expected.x_speed = FIXED(11);
        expected.y_speed = 0;
        animation(1);
        expected.x_pos.val += FIXED(11);
        expected.unk7C = 29;
        break;
    case CRUISE:
        expected.x_pos.val += expected.x_speed;
        expected.y_pos.val -= expected.y_speed;
        expected.unk7C = 8;
        break;
    case CRUISE_END:
        distance = (u32)expected.x_pos.val - 0x00400000;
        expected.x_speed = FIXED(4);
        expected.unk7C = 30;
        expected.unk6 = 2;
        memcpy(expected.ext.main_55.pad80, &distance, sizeof(distance));
        animation(0);
        break;
    case APPROACH_DONE:
        expected.unk5 = 1;
        expected.unk6 = 0;
        break;
    case APPROACH_MOVE:
        expected.x_pos.val += expected.x_speed;
        expected.y_pos.val -= expected.y_speed;
        break;
    }
    expected.animation_step.fields.duration--;
    for (i = 0; i < sizeof(flyby) / 4; i++)
        difference |= ((u32*)&flyby)[i] ^ ((u32*)&expected)[i];
    assert(difference == 0);
    return (u32)flyby.x_pos.val ^ ((u8)flyby.unk5 | ((u8)flyby.unk6 << 4) | ((u32)(u16)flyby.unk7C << 8));
}

#define CASE(name)                                     \
    static u32 flyby_cruise_states_##name##_case(void) \
    {                                                  \
        return flyby_cruise_states_run(name);          \
    }
CASE(START)
CASE(CRUISE)
CASE(CRUISE_END)
CASE(APPROACH_DONE)
CASE(APPROACH_MOVE)
CASE(IDLE)
#define ENTRY(name) flyby_cruise_states_##name##_case,
static const CTestCase flyby_cruise_states_cases[]
    = {
          ENTRY(START) ENTRY(CRUISE) ENTRY(CRUISE_END) ENTRY(APPROACH_DONE) ENTRY(APPROACH_MOVE) ENTRY(IDLE)
      };
static const u32 flyby_cruise_states_cases_expected[] = { 0xAB0F24u, 0xA21A24u, 0xA00C14u, 0x601B35u, 0xA21B14u, 0xA01B04u };
#undef CASE
#undef ENTRY

static struct AnimationTable12 {
    union AnimationStep* entries[12];
    s32 count;
};

static u32 rise_case(u32 mode)
{
    struct MainObj obj, expected;
    struct BackgroundObj backgrounds[3];
    struct PlayerObj player_before = g_Player;
    union AnimationStep** animations = jet_stingray_flyby_animations.entries;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++) {
        background_objects[i].unk44 = 1;
        background_objects[i].y_pos.val = (100 + i) * 65536 + 0x4321;
    }
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 0;
    obj.unk2 = mode == 3 ? 0 : 1;
    obj.bg_offset = 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = backgrounds[2].y_pos.val + 64 * 65536 + (mode == 0 ? -1 : mode == 1 ? 0
                                                                                        : 1);
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.unk7C = 9;
    obj.unk7E = 8;
    obj.animation_table = (const u8* const*)animations;
    set_animation(&obj, 0);
    expected = obj;
    if (mode == 0 || mode == 3) {
        expected.unk6 = 1;
        if (mode == 0)
            expected.y_speed = 0;
        expected.unk7C = 0;
        expected.unk7E = 4;
        expected.unk17 = 2;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)animations[2];
        expected.animation_step = animations[2][0];
    }
    expected.animation_step.fields.duration--;
    assert(expected.animation_step.fields.duration != 0);
    jet_stingray_flyby_attack_rise(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(backgrounds) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.unk7E << 16);
}
#define CASE(m)                                            \
    static u32 stingray_flyby_rise_boundary_rise_##m(void) \
    {                                                      \
        return rise_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) stingray_flyby_rise_boundary_rise_##m,
static const CTestCase stingray_flyby_rise_boundary_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 stingray_flyby_rise_boundary_cases_expected[] = { 0x40201u, 0x80000u, 0x80000u, 0x40201u };
#undef CASE
#undef ENTRY

static const u32 inputs_0[8][9] = {
    { 255, 0, 0, 0, 0, 0, 0, 0, 8192 },
    { 3, 0, 0, 0, 0, 0, 0, 0, 8192 },
    { 2, 0, -256, 0, 0, 0, 0, 0, 8192 },
    { 1, 0, 240, 0, 0, 0, 0, 0, 8192 },
    { 2, 0, 0, 0, 0, 0, 0, 0, 8192 },
    { 2, 0, 0, 255, 0, 0, 0, 0, 8192 },
    { 1, 255, 0, 0, 0, 0, 0, 0, 8192 },
    { 1, 4, 0, 0, 0, 0, 0, 0, 8192 },
};
struct func_8006ED44_case {
    u32 expected[9];
};
static const struct func_8006ED44_case func_8006ED44_cases[] = {
    { { 0xFFu, 0u, 0u, 6u, 0u, 0u, 0u, 0x80000u, 0u } },
    { { 0u, 0u, 0u, 6u, 0u, 0u, 0u, 0x80000u, 0u } },
    { { 2u, 0u, 0u, 6u, 0u, 0u, 0xFFFFFEFFu, 0x80000u, 0u } },
    { { 2u, 1u, 0u, 6u, 0u, 0u, 0x14u, 0x80000u, 0u } },
    { { 3u, 0u, 0u, 6u, 0u, 0u, 0u, 0x80000u, 0u } },
    { { 2u, 0u, 0xFEu, 6u, 0u, 0u, 0x1Eu, 0x80000u, 0u } },
    { { 1u, 0u, 0u, 6u, 0u, 0u, 1u, 0x80000u, 0u } },
    { { 2u, 1u, 0u, 6u, 0u, 0u, 0x14u, 0x80000u, 0u } },
};
static u32 test_func_8006ED44(u32 row)
{
    const struct func_8006ED44_case* c = &func_8006ED44_cases[row];
    u32 observed_values[9];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.ext.main_55.pad80[4] = inputs_0[row][0];
    obj.ext.main_55.unk85 = inputs_0[row][1];
    obj.unk7C = inputs_0[row][2];
    obj.ext.main_55.unk88 = inputs_0[row][3];
    background_objects[0].unk47 = inputs_0[row][4];
    background_objects[1].unk47 = inputs_0[row][5];
    background_objects[2].unk47 = inputs_0[row][6];
    obj.bg_offset = inputs_0[row][7];
    obj.x_pos.i.hi = inputs_0[row][8];
    func_8006ED44(&obj);
    observed_values[0] = (u32)obj.ext.main_55.pad80[4];
    observed_values[1] = (u32)obj.ext.main_55.unk87;
    observed_values[2] = (u32)obj.ext.main_55.unk88;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.unk7;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.x_speed;
    observed_values[8] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 9);
}

static const u32 func_8006EF28_expected[] = { 6u, 0u, 0u, 0x40000u, 0x20000u };
static u32 test_func_8006EF28(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.unk6 = -1;
    background_objects[2].unk47 = -116;
    obj.bg_offset = 2;
    g_Player.x_pos.i.hi = 20464;
    obj.x_pos.i.hi = 20499;
    func_8006EF28(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.x_speed;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_8006EF28_expected, 5);
}

#include "support/pool_full.h"
static u32 pool_full_jet_stingray_flyby_attack_fire(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 0;
    pf_event(1, 1);
    pf_snapshot();
    jet_stingray_flyby_attack_fire(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_flyby_volley_shot(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 0;
    pf_snapshot();
    func_8006F5F4(&pf_self);
    pf_expected.unk7C = 7;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_jet_stingray_flyby_attack_fire,
    pool_full_flyby_volley_shot,
};

static const u32 pool_full_cases_expected[] = { 0x0u, 0x70000u };
const struct CTestGroup c_test_groups[] = {
    { "flyby_cruise_states", flyby_cruise_states_cases, flyby_cruise_states_cases_expected, COUNT(flyby_cruise_states_cases), 0 },
    { "stingray_flyby_rise_boundary", stingray_flyby_rise_boundary_cases, stingray_flyby_rise_boundary_cases_expected, COUNT(stingray_flyby_rise_boundary_cases), 0 },
    { "func_8006ED44", 0, 0, 8, test_func_8006ED44 },
    { "func_8006EF28", 0, 0, 1, test_func_8006EF28 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flyby_cruise_states_cases) + COUNT(stingray_flyby_rise_boundary_cases) + 8 + 1 + COUNT(pool_full_cases);
