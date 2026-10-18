#include "test_runtime.h"
#include "main/mains/main_52_jump_shooter.h"
#include "support/state_cases.h"
void jump_shooter_fire_aim(struct MainObj*);
void jump_shooter_fire_end(struct MainObj*);
void jump_shooter_resume_step(struct MainObj* arg0);

static u32 aim_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 52;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = 5;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.main_52.unk84 = 7;
    obj.ext.main_52.unk88 = 9;
    g_Player.x_pos.val = (mode < 2 ? 200 : 0) * 65536 + 0x1234;
    g_Player.y_pos.val = 184 * 65536 + 0x5678;
    expected = obj;
    player_expected = g_Player;
    expected.ext.main_52.unk84 = mode < 2 ? 0 : 16;
    if (mode == 1 || mode == 2)
        expected.ext.main_52.unk88 = 2;
    func_8006AE80(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    return obj.ext.main_52.unk84 | ((u32)obj.ext.main_52.unk88 << 8) | ((u32)obj.y_pos.u.hi << 16);
}
static const u32 jump_shooter_real_aim_angles_cases_expected[] = { 0xC80900u, 0xC80200u, 0xC80210u, 0xC80910u };

#include "support/pool_full.h"
static u32 pool_full_jump_shooter_fire_shots(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7E = 1;
    pf_self.unk7C = 2;
    pf_snapshot();
    jump_shooter_fire_shots(&pf_self);
    pf_animation(2);
    pf_expected.unk7C = 1;
    pf_expected.unk7E = 0x10;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_jump_shooter_fire_shots,
};

static const u32 pool_full_cases_expected[] = { 0x10000u };
#define JS(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x40, so.terrain_box = &state_hit_box, so.animation_table = (void*)jump_shooter_animations, g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x40, cur_random = 0x1234)
#define WALK(attr, facing, px, py, timer, flags) (JS(3, 1), state_terrain(attr), so.unk15 = facing, so.collision_flags = flags, so.unk7C = timer, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, func_8006AAB4(&so), so.unk7E = so.ext.main_52.unk8C)
#define AIM(facing, px, py, air) (JS(2, 0), so.unk15 = facing, so.ext.main_52.unk80 = air, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, jump_shooter_fire_aim(&so), so.unk7E = so.ext.main_52.unk84 | so.ext.main_52.unk88 << 8)
#define LAUNCH(facing, dir) (JS(4, 0), so.unk15 = facing, so.ext.main_52.unk8C = dir, so.animation_table = (void*)state_table, so.animation_step.fields.event = 2, jump_shooter_jump_launch(&so))
static void js_walk_edge(void)
{
    WALK(0, 0, 0x80, 0x40, 5, 0);
}
static void js_walk_turn_right(void) { WALK(0x38, 0, 0x100, 0x40, 5, 0); }
static void js_walk_wall_left(void) { WALK(0x38, 0, 0x80, 0x40, 5, 2); }
static void js_walk_left(void) { WALK(0x38, 0, 0x80, 0x40, 5, 0); }
static void js_walk_turn_left(void) { WALK(0x38, 0x40, 0x10, 0x40, 5, 0); }
static void js_walk_wall_right(void) { WALK(0x38, 0x40, 0x80, 0x40, 5, 1); }
static void js_walk_right(void) { WALK(0x38, 0x40, 0x80, 0x40, 5, 0); }
static void js_walk_jump_far(void) { WALK(0x38, 0, 0x80, 0x100, 1, 0); }
static void js_walk_fire(void) { WALK(0x38, 0, 0x80, 0x40, 1, 0); }
static void js_walk_fire_roll(void)
{
    cur_random = 0;
    WALK(0x38, 0, 0x80, 0x40, 1, 0);
}
static void js_aim_left_low(void) { AIM(0, 0x40, 0x60, 0); }
static void js_aim_left_level(void) { AIM(0, 0x40, 0x30, 0); }
static void js_aim_left_up(void) { AIM(0, 0x50, 0x00, 0); }
static void js_aim_left_high(void) { AIM(0, 0x70, 0x00, 1); }
static void js_aim_left_down(void) { AIM(0, 0x70, 0x80, 0); }
static void js_aim_left_behind(void) { AIM(0, 0xC0, 0x30, 0); }
static void js_aim_right_level(void) { AIM(0x40, 0xC0, 0x30, 0); }
static void js_aim_right_low(void) { AIM(0x40, 0xC0, 0x50, 0); }
static void js_aim_right_down(void) { AIM(0x40, 0x90, 0x80, 1); }
static void js_aim_right_up(void) { AIM(0x40, 0xC0, 0x08, 0); }
static void js_aim_right_high(void) { AIM(0x40, 0x90, 0x00, 0); }
static void js_aim_right_behind(void) { AIM(0x40, 0x40, 0x30, 0); }
static void js_aim_left_top(void) { AIM(0, 0x7A, 0x00, 0); }
static void js_aim_right_top(void) { AIM(0x40, 0x88, 0x00, 0); }
static void js_aim_right_under(void) { AIM(0x40, 0xC0, 0x70, 0); }
static void js_resume(void)
{
    JS(1, 0);
    so.ext.main_52.saved_unk5 = 3;
    jump_shooter_resume_step(&so);
}
static void js_fire_end_wait(void)
{
    JS(2, 3);
    so.unk7C = 2;
    jump_shooter_fire_end(&so);
}
static void js_fire_end_walk(void)
{
    JS(2, 3);
    so.unk7C = 1;
    jump_shooter_fire_end(&so);
}
static void js_fire_end_fall(void)
{
    JS(2, 3);
    so.unk7C = 1;
    so.ext.main_52.unk80 = 1;
    jump_shooter_fire_end(&so);
}
static void js_launch_wait(void)
{
    JS(4, 0);
    so.animation_table = (void*)state_table;
    jump_shooter_jump_launch(&so);
}
static void js_launch_forward(void) { LAUNCH(0, 0); }
static void js_launch_forward_right(void) { LAUNCH(0x40, 0); }
static void js_launch_up(void) { LAUNCH(0, 1); }
static void js_launch_back(void) { LAUNCH(0, 2); }
static void js_launch_back_right(void) { LAUNCH(0x40, 2); }
static void js_launch_other(void) { LAUNCH(0, 3); }

static void (*const jump_shooter_states_cases[])(void) = {
    js_walk_edge,
    js_walk_turn_right,
    js_walk_wall_left,
    js_walk_left,
    js_walk_turn_left,
    js_walk_wall_right,
    js_walk_right,
    js_walk_jump_far,
    js_walk_fire,
    js_walk_fire_roll,
    js_aim_left_low,
    js_aim_left_level,
    js_aim_left_up,
    js_aim_left_high,
    js_aim_left_down,
    js_aim_left_behind,
    js_aim_right_level,
    js_aim_right_low,
    js_aim_right_down,
    js_aim_right_up,
    js_aim_right_high,
    js_aim_right_behind,
    js_aim_left_top,
    js_aim_right_top,
    js_aim_right_under,
    js_resume,
    js_fire_end_wait,
    js_fire_end_walk,
    js_fire_end_fall,
    js_launch_wait,
    js_launch_forward,
    js_launch_forward_right,
    js_launch_up,
    js_launch_back,
    js_launch_back_right,
    js_launch_other,
};
static const u32 jump_shooter_states_expected[] = { 4u, 5u, 0x800000u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0x103u, 4u, 0x800000u, 0x1CCCCu, 0u, 0u, 0x4000u, 0u, 0u, 0u, 4u, 4u, 0x800000u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0x103u, 4u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 4u, 0x800000u, 0xFFFE3334u, 0u, 0u, 0u, 0u, 0u, 0u, 4u, 4u, 0x800000u, 0u, 0u, 0u, 0x4001u, 0u, 0u, 0u, 0x103u, 4u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 2u, 0x10000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 4u, 0x10000u, 0x800000u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 4u, 0x10000u, 0x800000u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0x102u, 0x3130000u, 0x800000u, 0u, 0u, 0u, 0x15u, 0u, 0u, 0u, 0x102u, 0x2100000u, 0x800000u, 0u, 0u, 0u, 0x14u, 0u, 0u, 0u, 0x102u, 0x10C0000u, 0x800000u, 0u, 0u, 0u, 0x13u, 0u, 0u, 0u, 0x102u, 0x10A0000u, 0x800000u, 0u, 0u, 0u, 0x18u, 0u, 0u, 0u, 0x102u, 0x4170000u, 0x800000u, 0u, 0u, 0u, 0x16u, 0u, 0u, 0u, 0x102u, 0x2000000u, 0x800000u, 0u, 0u, 0u, 0x4014u, 0u, 0u, 0u, 0x102u, 0x2000000u, 0x800000u, 0u, 0u, 0u, 0x4014u, 0u, 0u, 0u, 0x102u, 0x21E0000u, 0x800000u, 0u, 0u, 0u, 0x4014u, 0u, 0u, 0u, 0x102u, 0x4190000u, 0x800000u, 0u, 0u, 0u, 0x401Bu, 0u, 0u, 0u, 0x102u, 0x1030000u, 0x800000u, 0u, 0u, 0u, 0x4013u, 0u, 0u, 0u, 0x102u, 0x1060000u, 0x800000u, 0u, 0u, 0u, 0x4013u, 0u, 0u, 0u, 0x102u, 0x2100000u, 0x800000u, 0u, 0u, 0u, 0x14u, 0u, 0u, 0u, 0x102u, 0x90000u, 0x800000u, 0u, 0u, 0u, 0x12u, 0u, 0u, 0u, 0x102u, 0x70000u, 0x800000u, 0u, 0u, 0u, 0x4012u, 0u, 0u, 0u, 0x102u, 0x31C0000u, 0x800000u, 0u, 0u, 0u, 0x4015u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x302u, 1u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0x5Au, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0x5Au, 0x800000u, 0u, 0u, 0x400000u, 0u, 0u, 0u, 0u, 4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0x7E3334u, 0xFFFE3334u, 0x5C000u, 0x400000u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0x81CCCCu, 0x1CCCCu, 0x5C000u, 0x400000u, 0x4000u, 0u, 0u, 0u, 0x104u, 0u, 0x800000u, 0u, 0x5C000u, 0x400000u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0x81CCCCu, 0x1CCCCu, 0x5C000u, 0x400000u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0x7E3334u, 0xFFFE3334u, 0x5C000u, 0x400000u, 0x4000u, 0u, 0u, 0u, 0x104u, 0u, 0x800000u, 0u, 0x5C000u, 0x400000u, 0u, 0u, 0u, 0u };

static u32 test_jump_shooter_states(u32 row)
{
    return state_run(jump_shooter_states_cases[row], row, &jump_shooter_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "jump_shooter_states", 0, 0, COUNT(jump_shooter_states_cases), test_jump_shooter_states },
    { "jump_shooter_real_aim_angles", NULL, jump_shooter_real_aim_angles_cases_expected, COUNT(jump_shooter_real_aim_angles_cases_expected), aim_case },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(jump_shooter_states_cases) + COUNT(jump_shooter_real_aim_angles_cases_expected) + COUNT(pool_full_cases);
