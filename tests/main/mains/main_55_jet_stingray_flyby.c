#include "test_runtime.h"
#include "main/mains/main_55_jet_stingray_flyby.h"
#include "main/55C4.h"
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
        expected.ext.main_55.distance = distance;
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

static const u32 flyby_cruise_states_cases_expected[] = { 0xAB0F24u, 0xA21A24u, 0xA00C14u, 0x601B35u, 0xA21B14u, 0xA01B04u };

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
static const u32 stingray_flyby_rise_boundary_cases_expected[] = { 0x40201u, 0x80000u, 0x80000u, 0x40201u };

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
    obj.ext.main_55.unk84 = inputs_0[row][0];
    obj.ext.main_55.unk85 = inputs_0[row][1];
    obj.unk7C = inputs_0[row][2];
    obj.ext.main_55.unk88 = inputs_0[row][3];
    background_objects[0].unk47 = inputs_0[row][4];
    background_objects[1].unk47 = inputs_0[row][5];
    background_objects[2].unk47 = inputs_0[row][6];
    obj.bg_offset = inputs_0[row][7];
    obj.x_pos.i.hi = inputs_0[row][8];
    func_8006ED44(&obj);
    observed_values[0] = (u32)obj.ext.main_55.unk84;
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
#include "support/state_cases.h"

#define FLY(a, b) state_reset(a, b, 0)
#define LANE(s) (so.ext.main_55.unk84 = s)
static void fs_init_hidden(void)
{
    FLY(0, 0);
    engine_obj.palette_flags = 0x10;
    func_8006EB40(&so);
}
static void fs_init_high(void)
{
    FLY(0, 0);
    func_8006EB40(&so);
}
static void fs_init_low(void)
{
    FLY(0, 0);
    so.unk2 = 1;
    g_Player.y_pos.i.hi = 0x50;
    func_8006EB40(&so);
}
static void fs_main(void)
{
    FLY(2, 0);
    so.state = 1;
    so.x_pos.i.hi = 0x80;
    so.y_pos.i.hi = 0x60;
    jet_stingray_flyby_main(&so);
}
static void fs_main_away(void)
{
    FLY(2, 0);
    so.state = 1;
    so.x_pos.i.hi = 0x2000;
    jet_stingray_flyby_main(&so);
}
static void fs_wait_far(void)
{
    FLY(2, 0);
    jet_stingray_flyby_wait_on_screen(&so);
}
static void fs_lane_start(void)
{
    FLY(1, 0);
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_empty(void)
{
    FLY(1, 0);
    LANE(1);
    so.unk7C = 9;
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_full(void)
{
    FLY(1, 0);
    LANE(1);
    so.unk7C = 0xF0;
    so.ext.main_55.unk85 = 6;
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_count(void)
{
    FLY(1, 0);
    LANE(1);
    so.unk7C = 9;
    so.ext.main_55.unk85 = 6;
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_wait(void)
{
    FLY(1, 0);
    LANE(2);
    so.unk7C = 2;
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_done(void)
{
    FLY(1, 0);
    LANE(2);
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_release(void)
{
    FLY(1, 0);
    LANE(2);
    so.ext.main_55.unk88 = 0x14;
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_attack(void)
{
    FLY(1, 0);
    LANE(3);
    jet_stingray_flyby_enter(&so);
}
static void fs_lane_exit(void)
{
    FLY(1, 0);
    LANE(3);
    so.x_pos.i.hi = 0x1E20;
    jet_stingray_flyby_enter(&so);
}
static void fs_chase_start(void)
{
    FLY(1, 0);
    so.unk2 = 1;
    so.x_pos.i.hi = -0x100;
    jet_stingray_flyby_enter(&so);
}
static void fs_chase_near_a(void)
{
    FLY(1, 1);
    so.unk2 = 1;
    so.unk7C = 3;
    so.x_pos.i.hi = -0x20;
    cur_random = 1;
    jet_stingray_flyby_enter(&so);
}
static void fs_chase_near_b(void)
{
    FLY(1, 1);
    so.unk2 = 1;
    so.unk7C = 3;
    so.x_pos.i.hi = -0x20;
    cur_random = 2;
    jet_stingray_flyby_enter(&so);
}
static void fs_chase_timeout(void)
{
    FLY(1, 1);
    so.unk2 = 1;
    so.x_pos.i.hi = -0x100;
    jet_stingray_flyby_enter(&so);
}
static void fs_chase_exit(void)
{
    FLY(1, 1);
    so.unk2 = 1;
    so.unk7C = 3;
    so.x_pos.i.hi = 0x3920;
    jet_stingray_flyby_enter(&so);
}
static void fs_fire_shot(void)
{
    FLY(4, 1);
    so.animation_step.fields.event = 1;
    jet_stingray_flyby_attack(&so);
}
static void fs_fire_last(void)
{
    FLY(4, 1);
    so.animation_step.fields.event = 2;
    so.unk7E = 1;
    jet_stingray_flyby_attack(&so);
}
static void fs_fire_more(void)
{
    FLY(4, 1);
    so.animation_step.fields.event = 2;
    so.unk7E = 2;
    jet_stingray_flyby_attack(&so);
}
static void fs_fire_wait(void)
{
    FLY(4, 1);
    so.unk7C = 2;
    jet_stingray_flyby_attack(&so);
}
static void fs_end_rise(void)
{
    FLY(4, 2);
    so.unk2 = 1;
    jet_stingray_flyby_attack(&so);
}
static void fs_end(void)
{
    FLY(4, 2);
    jet_stingray_flyby_attack(&so);
}
static void fs_end_wait(void)
{
    FLY(4, 2);
    so.animation_step.fields.relative_step = 1;
    jet_stingray_flyby_attack(&so);
}
static void fs_align(void)
{
    FLY(4, 3);
    jet_stingray_flyby_attack(&so);
}
static void fs_align_far(void)
{
    FLY(4, 3);
    so.y_pos.i.hi = 0x40;
    jet_stingray_flyby_attack(&so);
}
static void fs_windup(void)
{
    FLY(5, 0);
    so.animation_step.fields.event = 1;
    jet_stingray_flyby_charge(&so);
}
static void fs_windup_wait(void)
{
    FLY(5, 0);
    so.unk7 = 1;
    jet_stingray_flyby_charge(&so);
}
static void fs_spray(void)
{
    FLY(5, 1);
    cur_random = 1;
    jet_stingray_flyby_charge(&so);
    state_extra = so.ext.main_55.unk86 | so.ext.main_55.unk88 << 8;
}
static void fs_spray_last(void)
{
    FLY(5, 1);
    so.ext.main_55.unk86 = 7;
    jet_stingray_flyby_charge(&so);
    state_extra = so.ext.main_55.unk86 | so.ext.main_55.unk88 << 8;
}
static void fs_spray_wait(void)
{
    FLY(5, 1);
    so.unk7C = 2;
    jet_stingray_flyby_charge(&so);
}
static void fs_spray_done(void)
{
    FLY(5, 1);
    so.unk7 = 1;
    jet_stingray_flyby_charge(&so);
}
static void fs_spray_hold(void)
{
    FLY(5, 1);
    so.unk7 = 1;
    so.animation_step.fields.relative_step = 1;
    jet_stingray_flyby_charge(&so);
}
static void fs_crash_start(void)
{
    FLY(7, 0);
    cur_random = 7;
    func_8006F86C(&so);
}
static void fs_crash_fall(void)
{
    FLY(7, 1);
    cur_random = 3;
    func_8006F86C(&so);
}
static void fs_crash_dive(void)
{
    FLY(7, 1);
    so.unk2 = 1;
    cur_random = 5;
    func_8006F86C(&so);
}

static void (*const flyby_states_cases[])(void) = {
    fs_init_hidden,
    fs_init_high,
    fs_init_low,
    fs_main,
    fs_main_away,
    fs_wait_far,
    fs_lane_start,
    fs_lane_empty,
    fs_lane_full,
    fs_lane_count,
    fs_lane_wait,
    fs_lane_done,
    fs_lane_release,
    fs_lane_attack,
    fs_lane_exit,
    fs_chase_start,
    fs_chase_near_a,
    fs_chase_near_b,
    fs_chase_timeout,
    fs_chase_exit,
    fs_fire_shot,
    fs_fire_last,
    fs_fire_more,
    fs_fire_wait,
    fs_end_rise,
    fs_end,
    fs_end_wait,
    fs_align,
    fs_align_far,
    fs_windup,
    fs_windup_wait,
    fs_spray,
    fs_spray_last,
    fs_spray_wait,
    fs_spray_done,
    fs_spray_hold,
    fs_crash_start,
    fs_crash_fall,
    fs_crash_dive,
};
static const u32 flyby_states_expected[] = { 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x201u, 0xFF400000u, 0x1B00000u, 0x400000u, 0x40000u, 0u, 0u, 0x60000u, 0u, 0u, 0x201u, 0xFF400100u, 0xFFC00000u, 0x500000u, 0x90000u, 0u, 0u, 0x60000u, 0u, 0u, 0x101u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x202u, 0u, 0x20000000u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x600u, 0u, 0x1E200000u, 0u, 0x80000u, 0u, 0u, 0x40000u, 0u, 0u, 0x10100u, 0x100u, 0xFF000000u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x300u, 0x100u, 0xFFE00000u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x300u, 0x100u, 0xFFE00000u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0x100u, 0xFF000000u, 0u, 0u, 0x20000u, 0u, 0x40000u, 0u, 0u, 0x600u, 0x100u, 0x39200000u, 0u, 0x40000u, 0u, 0u, 0x40000u, 0u, 0u, 0x10400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0x410000u, 0x20400u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x30400u, 0xFF000100u, 0u, 0x20000u, 0u, 0xFFFE0000u, 0u, 0x40000u, 0u, 0u, 0x100u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30400u, 0u, 0u, 0x400000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x1000500u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x1000500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x101u, 0x410000u, 0x1010500u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x8008u, 0x410000u, 0x10500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x1010500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10700u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 0x20700u, 0u, 0x80000u, 0u, 0x80000u, 0u, 0u, 0x40000u, 0u, 0u, 0x20700u, 0x100u, 0x40000u, 0u, 0x40000u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_flyby_states(u32 row)
{
    return object_run(flyby_states_cases[row], row, &flyby_states_expected[row * 10]);
}

#define FB(sub) (state_reset(3, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
static void fb_windup_start(void)
{
    FB(1);
    jet_stingray_flyby_charge_windup(&so);
}
static void fb_windup(void)
{
    FB(1);
    so.unk7 = 1;
    so.animation_step.fields.event = 1;
    so.unk7C = 5;
    jet_stingray_flyby_charge_windup(&so);
}

static void (*const flyby_windup_cases[])(void) = {
    fb_windup_start,
    fb_windup,
};
static const u32 flyby_windup_expected[] = { 0x10103u, 0u, 0x800000u, 0u, 0u, 0u, 4u, 0u, 0u, 0u, 0x203u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_flyby_windup(u32 row)
{
    return state_run(flyby_windup_cases[row], row, &flyby_windup_expected[row * 10]);
}

extern struct AnimationTable12 jet_stingray_flyby_animations;
static const struct {
    s16 dx, dy;
    s32 velocity_y;
    u8 near;
} targets[] = {
    { 80, 0, 0, 0 },
    { 79, 0, 0, 1 },
    { 0, 33, -65536, 0 },
    { 0, 32, -65536, 1 },
    { 0, -33, 65536, 0 },
    { 0, -32, 65536, 1 },
};
static const u16 seeds[] = { 1, 0x1234 }, after_random[] = { 1, 0x366A };
static u32 approach(u32 row)
{
    struct MainObj obj, expected, *current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 aim = row % 6, seed = row / 6 % 2, layer = row / 12;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.unk7C = 2;
    obj.bg_offset = layer;
    obj.x_pos.val = 0x3500 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x12345;
    obj.y_speed = -0x23456;
    obj.x_accel = 0x3456;
    obj.gravity = 0x4567;
    obj.animation_table = (const u8* const*)&jet_stingray_flyby_animations;
    set_animation(&obj, 0);
    assert(obj.animation_step.packed == 0x00010006);
    background_objects[layer].x_pos.i.hi = 0x3460;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    g_Player.hp = 30;
    g_Player.x_pos.val = obj.x_pos.val + targets[aim].dx * 65536;
    g_Player.y_pos.val = obj.y_pos.val + targets[aim].dy * 65536;
    player_before = g_Player;
    expected = obj;
    expected.animation_step.fields.duration = 5;
    expected.x_speed = 0;
    expected.y_speed = targets[aim].velocity_y;
    expected.y_pos.val -= expected.y_speed;
    expected.unk7C = 1;
    if (targets[aim].near && !seed) {
        expected.unk5 = 3;
        expected.unk6 = 0;
    }
    cur_random = seeds[seed];
    SP_CUR_MAIN_OBJ = &obj;
    func_8006EF28(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(cur_random == (targets[aim].near ? after_random[seed] : seeds[seed]));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "flyby_windup", 0, 0, COUNT(flyby_windup_cases), test_flyby_windup },
    { "flyby_states", 0, 0, COUNT(flyby_states_cases), test_flyby_states },
    { "flyby_cruise_states", NULL, flyby_cruise_states_cases_expected, COUNT(flyby_cruise_states_cases_expected), flyby_cruise_states_run },
    { "stingray_flyby_rise_boundary", NULL, stingray_flyby_rise_boundary_cases_expected, COUNT(stingray_flyby_rise_boundary_cases_expected), rise_case },
    { "func_8006ED44", 0, 0, 8, test_func_8006ED44 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "aimed_entry_exact_proximity_edges_and_rng_gate", NULL, NULL, 36, approach },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flyby_windup_cases) + COUNT(flyby_states_cases) + COUNT(flyby_cruise_states_cases_expected) + COUNT(stingray_flyby_rise_boundary_cases_expected) + 8 + COUNT(pool_full_cases) + 36;
