#include "test_runtime.h"
#include "support/platform_fixture.h"
#ifndef VERSION_DEMO
#include "main/mains/main_60_storm_owl.h"
#include "main/effects/effect_38_cyberspace_trial.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
void func_800751AC(struct MainObj*);
void func_80077580(struct MainObj*);
void storm_owl_cyclone(struct MainObj* arg0);
void storm_owl_grab(struct MainObj* arg0);
void storm_owl_intro(struct MainObj* arg0);
void storm_owl_resume_step(struct MainObj* arg0);
void storm_owl_stagger(struct MainObj* arg0);
void storm_owl_start(struct MainObj* arg0);
void storm_owl_death_finish(struct MainObj* arg0);
void storm_owl_ground_cyclone(struct MainObj* arg0);
void storm_owl_hover(struct MainObj* arg0);
void storm_owl_storm(struct MainObj* arg0);
extern void* storm_owl_patterns[3];
extern u8 storm_owl_pattern_weights[12];
void storm_owl_spawn_hit_flash(struct PlayerObj*);

static u32 script_case(u32 mode)
{
    struct MainObj obj, before;
    u8 weights_before[12], sentinel[] = { 0x27, 0x28, 0x29, 0xFF };
    u32 i, result;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 60;
    obj.hp = 0;
    obj.ext.main_60.pattern = sentinel;
    memcpy(weights_before, storm_owl_pattern_weights, sizeof(weights_before));
    if (mode == 1)
        memset(storm_owl_pattern_weights, 0, 3);
    cur_random = 0;
    before = obj;
    storm_owl_choose_pattern(&obj);
    if (mode == 0) {
        assert(obj.ext.main_60.pattern == ((u8**)storm_owl_patterns[0])[0]);
        before.ext.main_60.pattern = ((u8**)storm_owl_patterns[0])[0];
    } else
        assert(obj.ext.main_60.pattern == sentinel);
    c_test_same_words(&obj, &before, sizeof(obj));
    assert(cur_random == 0 && sentinel[0] == 0x27 && sentinel[1] == 0x28 && sentinel[2] == 0x29 && sentinel[3] == 0xFF);
    for (i = 0; i < 12; i++)
        assert(((u8*)storm_owl_pattern_weights)[i] == (mode == 1 && i < 3 ? 0 : ((u8*)weights_before)[i]));
    result = mode == 0 ? *obj.ext.main_60.pattern : 0x100 | *obj.ext.main_60.pattern;
    return result;
}
static const u32 storm_owl_pattern_exhaustion_cases_expected[] = { 0xCu, 0x127u };

struct func_8007651C_case {
    u32 g_Player_x_pos_hi, obj_x_pos_hi, v_0_x_pos_hi, x_speed, unk15;
    u32 expected[4];
};
static const struct func_8007651C_case func_8007651C_cases[] = {
    { -32, 32752, 0, -1048576, 0, { 0u, 0u, 0xFFF00000u, 0u } },
    { 19031, 19047, 32704, -589824, 0, { 1u, 0x3Cu, 0u, 0x10000u } },
    { 32760, 32748, -25340, 1048576, 0, { 1u, 0x3Cu, 0u, 0x10000u } },
    { -1046, -1058, -64, 1048576, 0, { 1u, 0x3Cu, 0u, 0x10000u } },
    { 32760, 32767, 0, -65536, 0, { 1u, 0x3Cu, 0xFFFF0000u, 0x10000u } },
    { 42, 60, -160, -917504, 255, { 1u, 0x3Cu, 0u, 0x10000u } },
};
static u32 test_func_8007651C(u32 row)
{
    const struct func_8007651C_case* c = &func_8007651C_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    background_objects[0].x_pos.i.hi = c->v_0_x_pos_hi;
    obj.x_speed = c->x_speed;
    obj.unk15 = TEST_FACING(c->unk15);
    func_8007651C(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 func_80078314_expected[] = { 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_80078314(u32 row)
{
    u32 observed_values[14];
    struct MainObj obj;
    u8 pool_1_full;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
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
    func_80078314(&obj);
    observed_values[0] = (u32)shot_objects[0].timer;
    observed_values[1] = (u32)shot_objects[0].x_pos.i.hi;
    observed_values[2] = (u32)shot_objects[0].y_pos.i.hi;
    observed_values[3] = (u32)visual_objects[0].active;
    observed_values[4] = (u32)visual_objects[0].bg_offset;
    observed_values[5] = (u32)visual_objects[0].id;
    observed_values[6] = C_TEST_PSX_FACING(visual_objects[0].unk15);
    observed_values[7] = TEST_PSX_LAYER(visual_objects[0].unk16);
    observed_values[8] = (u32)visual_objects[0].unk2;
    observed_values[9] = (u32)visual_objects[0].unk40;
    observed_values[10] = (u32)visual_objects[0].unk42;
    observed_values[11] = (u32)visual_objects[0].unk5C.fields.mode;
    observed_values[12] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[13] = (u32)visual_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_80078314_expected, 14);
}

static const u32 storm_owl_reenter_warp_expected[] = { 0x41u, 0x40u, 1u, 0x3Cu, 0u, 0u };
static u32 test_storm_owl_reenter_warp(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.ext.main_60.corner = 255;
    storm_owl_reenter_warp(&obj);
    observed_values[0] = (u32)obj.active;
    observed_values[1] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.x_pos.i.hi;
    observed_values[5] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, storm_owl_reenter_warp_expected, 6);
}

static const u32 storm_owl_spawn_hit_flash_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_storm_owl_spawn_hit_flash(u32 row)
{
    u32 observed_values[10];
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    FILL_ACTIVE(visual_objects, 32, 255 ? 1 : 0);
    storm_owl_spawn_hit_flash(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = C_TEST_PSX_FACING(visual_objects[0].unk15);
    observed_values[4] = TEST_PSX_LAYER(visual_objects[0].unk16);
    observed_values[5] = (u32)visual_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].unk40;
    observed_values[7] = (u32)visual_objects[0].unk42;
    observed_values[8] = (u32)visual_objects[0].x_pos.val;
    observed_values[9] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, storm_owl_spawn_hit_flash_expected, 10);
}

#include "support/boss_death_flash.h"
BOSS_DEATH_FLASH_TESTS(storm_owl_death_flash, storm_owl_death_explode, 1)

#include "support/pool_full.h"
static u32 pool_full_storm_owl_start_warning(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    storm_owl_start_warning(&pf_self);
    pf_expected.unk5++;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_storm_owl_spawn_roar(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    storm_owl_spawn_roar(ANIMATED_OBJECT(&pf_self));
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_storm_owl_spawn_intro_wind(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    storm_owl_spawn_intro_wind(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_storm_owl_spawn_feather(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    storm_owl_spawn_feather(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_storm_owl_spawn_volley_feather(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    storm_owl_spawn_volley_feather(&pf_self, 1);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_storm_owl_spawn_cyclones(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    storm_owl_spawn_cyclones(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_storm_owl_spawn_storm_charge(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    storm_owl_spawn_storm_charge(ANIMATED_OBJECT(&pf_self));
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_storm_owl_start_warning,
    pool_full_storm_owl_spawn_roar,
    pool_full_storm_owl_spawn_intro_wind,
    pool_full_storm_owl_spawn_feather,
    pool_full_storm_owl_spawn_volley_feather,
    pool_full_storm_owl_spawn_cyclones,
    pool_full_storm_owl_spawn_storm_charge,
};
static const u32 pool_full_cases_expected[] = { 0x50001u, 0x50000u, 0x50000u, 0x50000u, 0x50000u, 0x50000u, 0x50000u };

#include "support/pool_cleanup.h"
CLEANUP_OWL_CASE(owl_matches, 1, 0x1u)
CLEANUP_OWL_CASE(owl_others, 0, 0x1u)
static const CTestCase storm_owl_clear_shots_pool_cases[] = {
    owl_matches,
    owl_others,
};

static const u32 storm_owl_death_flash_cases_expected[] = { 0x10501u, 0x10502u, 0x10502u, 0x50001u, 0xF0F01u, 0x5FB01u, 0x50001u };
static const u32 storm_owl_clear_shots_pool_cases_expected[] = { 0x1u, 0x1u };
#include "support/state_cases.h"

#define STORM(n) state_reset(9, n, 0)
#define GROUND(n) state_reset(12, n, 0)
static u8 owl_hover_next[1] = { 3 };
static u8 owl_fly_next[1];
static void o_storm_start_down(void)
{
    STORM(0);
    so.y_pos.val = 0x2000000;
    storm_owl_storm(&so);
}
static void o_storm_start_level(void)
{
    STORM(0);
    so.y_pos.val = 0x700000;
    storm_owl_storm(&so);
}
static void o_storm_fly_far(void)
{
    STORM(1);
    storm_owl_storm(&so);
}
static void o_storm_fly_arrive(void)
{
    STORM(1);
    so.x_pos.val = 0xA00000;
    so.y_pos.val = 0x700000;
    storm_owl_storm(&so);
}
static void o_storm_charge(void)
{
    STORM(2);
    storm_owl_storm(&so);
}
static void o_storm_begin(void)
{
    STORM(3);
    so.unk7C = 1;
    storm_owl_storm(&so);
}
static void o_storm_begin_wait(void)
{
    STORM(3);
    so.unk7C = 2;
    storm_owl_storm(&so);
}
static void o_storm_rain_done(void)
{
    STORM(4);
    so.unk7C = 1;
    so.ext.main_60.storm_timer = 1;
    storm_owl_storm(&so);
}
static void o_storm_rain_more(void)
{
    STORM(4);
    so.unk7C = 1;
    so.ext.main_60.storm_timer = 2;
    storm_owl_storm(&so);
}
static void o_storm_rain_wait(void)
{
    STORM(4);
    so.unk7C = 2;
    storm_owl_storm(&so);
}
static void o_storm_flap_a(void)
{
    STORM(5);
    so.unk7C = 1;
    cur_random = 1;
    storm_owl_storm(&so);
}
static void o_storm_flap_b(void)
{
    STORM(5);
    so.unk7C = 1;
    cur_random = 2;
    storm_owl_storm(&so);
}
static void o_storm_flap_wait(void)
{
    STORM(5);
    so.unk7C = 2;
    storm_owl_storm(&so);
}
static void o_storm_rain_again_done(void)
{
    STORM(6);
    so.unk7C = 1;
    so.ext.main_60.storm_timer = 0xF;
    storm_owl_storm(&so);
}
static void o_storm_rain_again_more(void)
{
    STORM(6);
    so.unk7C = 1;
    storm_owl_storm(&so);
}
static void o_storm_end_left(void)
{
    STORM(7);
    so.unk7C = 1;
    so.x_pos.val = -0x10000;
    storm_owl_storm(&so);
}
static void o_storm_end_right(void)
{
    STORM(7);
    so.unk7C = 1;
    storm_owl_storm(&so);
}
static void o_storm_end_wait(void)
{
    STORM(7);
    so.unk7C = 2;
    storm_owl_storm(&so);
}
static void o_storm_leave_away(void)
{
    STORM(8);
    so.x_pos.val = 0x10000000;
    cur_random = 1;
    storm_owl_storm(&so);
}
static void o_storm_leave_near(void)
{
    STORM(8);
    so.x_pos.val = 0x800000;
    so.y_pos.val = 0x800000;
    storm_owl_storm(&so);
}
static void o_storm_shots(void)
{
    STORM(3);
    so.unk7C = 2;
    so.unk7E = 1;
    so.ext.main_60.storm_active = 1;
    storm_owl_storm(&so);
}
static void o_storm_shots_wait(void)
{
    STORM(3);
    so.unk7C = 2;
    so.unk7E = 2;
    so.ext.main_60.storm_active = 1;
    storm_owl_storm(&so);
}
static void o_hover_start(void)
{
    state_reset(10, 0, 0);
    storm_owl_hover(&so);
}
static void o_hover_done(void)
{
    state_reset(10, 1, 0);
    so.unk7C = 1;
    storm_owl_hover(&so);
}
static void o_hover_wait(void)
{
    state_reset(10, 1, 0);
    so.unk7C = 2;
    storm_owl_hover(&so);
}
static void o_ground_start_even(void)
{
    GROUND(0);
    storm_owl_ground_cyclone(&so);
}
static void o_ground_start_odd(void)
{
    GROUND(0);
    so.ext.main_60.corner = 3;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_drop_land(void)
{
    GROUND(1);
    so.collision_flags = 8;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_land(void)
{
    GROUND(2);
    so.unk7C = 1;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_land_wait(void)
{
    GROUND(2);
    so.unk7C = 2;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_fire(void)
{
    GROUND(3);
    so.unk7C = 1;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_fire_wait(void)
{
    GROUND(3);
    so.unk7C = 2;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_wait(void)
{
    GROUND(4);
    so.unk7C = 1;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_wait_count(void)
{
    GROUND(4);
    so.unk7C = 2;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_takeoff_left(void)
{
    GROUND(5);
    so.unk7C = 1;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_takeoff_right(void)
{
    GROUND(5);
    so.unk7C = 1;
    so.unk15 = PLAYER_FACING_RIGHT;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_takeoff_wait(void)
{
    GROUND(5);
    so.unk7C = 2;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_leave_away(void)
{
    GROUND(6);
    so.x_pos.val = -0x10000000;
    cur_random = 2;
    storm_owl_ground_cyclone(&so);
}
static void o_ground_leave_near(void)
{
    GROUND(6);
    so.x_pos.val = 0x800000;
    so.y_pos.val = 0x800000;
    storm_owl_ground_cyclone(&so);
}
static void o_death_blink(void)
{
    state_reset(2, 0, 0);
    so.ext.main_60.effect = &effect_objects[0];
    effect_objects[0].active = 1;
    storm_owl_death_finish(&so);
}
static void o_death_exploding(void)
{
    state_reset(2, 0, 0);
    so.ext.main_60.effect = &effect_objects[0];
    effect_objects[0].active = 1;
    effect_objects[0].unk7 = 1;
    storm_owl_death_finish(&so);
}
static void o_death_done(void)
{
    state_reset(2, 0, 0);
    so.ext.main_60.effect = &effect_objects[0];
    engine_obj.stage = 7;
    storm_owl_death_finish(&so);
}
static void o_death_done_rematch(void)
{
    state_reset(2, 0, 0);
    so.ext.main_60.effect = &effect_objects[0];
    engine_obj.stage = 0xC;
    engine_obj.checkpoint = 1;
    storm_owl_death_finish(&so);
}
static void o_cyclone_finish_ground(void)
{
    state_reset(8, 2, 0);
    so.unk7C = 1;
    so.ext.main_60.pattern = owl_hover_next;
    storm_owl_cyclone(&so);
}
static void o_cyclone_finish_fly(void)
{
    state_reset(8, 2, 0);
    so.unk7C = 1;
    so.ext.main_60.pattern = owl_fly_next;
    so.x_pos.val = -0x10000;
    storm_owl_cyclone(&so);
}
static void o_wait_player_far(void)
{
    state_reset(0, 0, 0);
    engine_obj.stage = 7;
    g_Player.x_pos.i.hi = 0xA00;
    storm_owl_start(&so);
}
static void o_wait_player_near(void)
{
    state_reset(0, 0, 0);
    engine_obj.stage = 7;
    storm_owl_start(&so);
}
static void o_wait_player_high(void)
{
    state_reset(0, 0, 0);
    engine_obj.stage = 0xC;
    g_Player.y_pos.i.hi = 0;
    storm_owl_start(&so);
}
static void o_wait_player_low(void)
{
    state_reset(0, 0, 0);
    engine_obj.stage = 0xC;
    g_Player.y_pos.i.hi = 0x700;
    storm_owl_start(&so);
}
static void o_resume_step(void)
{
    state_reset(1, 0, 0);
    so.ext.main_60.saved_unk5 = 6;
    storm_owl_resume_step(&so);
}
static void o_grab_dive(void)
{
    state_reset(4, 0, 0);
    so.x_pos.val = -0x200000;
    storm_owl_grab(&so);
}
static void o_intro_enter_highway(void)
{
    state_reset(2, 0, 0);
    engine_obj.stage = 7;
    storm_owl_intro(&so);
}
static void o_intro_enter_rematch(void)
{
    state_reset(2, 0, 0);
    engine_obj.stage = 0xC;
    storm_owl_intro(&so);
}
static void o_intro_pose_dialogue(void)
{
    state_reset(2, 3, 0);
    so.unk7C = 1;
    engine_obj.stage = 7;
    abc_object.unkC = 0x80;
    storm_owl_intro(&so);
}
static void o_intro_pose_rematch(void)
{
    state_reset(2, 3, 0);
    so.unk7C = 1;
    engine_obj.stage = 0xC;
    storm_owl_intro(&so);
}
static void o_stagger_recover_wait(void)
{
    state_reset(11, 1, 0);
    so.unk7C = 2;
    storm_owl_stagger(&so);
}

static void (*const owl_cases[])(void) = {
    o_storm_start_down,
    o_storm_start_level,
    o_storm_fly_far,
    o_storm_fly_arrive,
    o_storm_charge,
    o_storm_begin,
    o_storm_begin_wait,
    o_storm_rain_done,
    o_storm_rain_more,
    o_storm_rain_wait,
    o_storm_flap_a,
    o_storm_flap_b,
    o_storm_flap_wait,
    o_storm_rain_again_done,
    o_storm_rain_again_more,
    o_storm_end_left,
    o_storm_end_right,
    o_storm_end_wait,
    o_storm_leave_away,
    o_storm_leave_near,
    o_storm_shots,
    o_storm_shots_wait,
    o_hover_start,
    o_hover_done,
    o_hover_wait,
    o_ground_start_even,
    o_ground_start_odd,
    o_ground_drop_land,
    o_ground_land,
    o_ground_land_wait,
    o_ground_fire,
    o_ground_fire_wait,
    o_ground_wait,
    o_ground_wait_count,
    o_ground_takeoff_left,
    o_ground_takeoff_right,
    o_ground_takeoff_wait,
    o_ground_leave_away,
    o_ground_leave_near,
    o_death_blink,
    o_death_exploding,
    o_death_done,
    o_death_done_rematch,
    o_cyclone_finish_ground,
    o_cyclone_finish_fly,
    o_wait_player_far,
    o_wait_player_near,
    o_wait_player_high,
    o_wait_player_low,
    o_resume_step,
    o_grab_dive,
    o_intro_enter_highway,
    o_intro_enter_rematch,
    o_intro_pose_dialogue,
    o_intro_pose_rematch,
    o_stagger_recover_wait,
};
static const u32 owl_expected[] = { 0x109u, 0xA0000u, 0u, 0xC3EEu, 0x1D906u, 0u, 0x4001u, 0u, 0u, 0u, 0x109u, 0xA0000u, 0u, 0x20000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0x109u, 0xA0000u, 0u, 0x1A9B6u, 0xFFFEE38Eu, 0u, 0u, 0u, 0u, 0u, 0x209u, 0xA0000u, 0xA00000u, 0xFFFE0000u, 0u, 0u, 6u, 0u, 0u, 0u, 0x309u, 0xA003Cu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x4100u, 0x409u, 0xA005Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x309u, 0xA0001u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x509u, 0xA003Cu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x409u, 0xA0014u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x409u, 0xA0001u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x609u, 0xA001Eu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x609u, 0xA001Eu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x509u, 0xA0001u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x709u, 0xA003Cu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x609u, 0xA0014u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x809u, 0xA0000u, 0xFFFF0000u, 0xFFFE0000u, 0x30000u, 0u, 1u, 0u, 0u, 0u, 0x809u, 0xA0000u, 0u, 0x20000u, 0x30000u, 0u, 0x4001u, 0u, 0u, 0u, 0x709u, 0xA0001u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 5u, 0xA0000u, 0x10000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x809u, 0xA0000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x309u, 0xA0001u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x410000u, 0x309u, 0x10001u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10Au, 0x5Au, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10Au, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10Cu, 0u, 0u, 0u, 0xFFFD0000u, 0u, 0x4001u, 0u, 0u, 0u, 0x20Cu, 0xAu, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0x10Cu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30Cu, 0x1Eu, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0x20Cu, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40Cu, 0xAu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x414100u, 0x30Cu, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50Cu, 0x5Fu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40Cu, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x60Cu, 0u, 0u, 0xFFFE0000u, 0x30000u, 0u, 1u, 0u, 0u, 0u, 0x60Cu, 0u, 0u, 0x20000u, 0x30000u, 0u, 0x4001u, 0u, 0u, 0u, 0x50Cu, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 5u, 0u, 0xF0000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x60Cu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x50000u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0u, 1u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x80000000u, 0u, 0xAu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x308u, 0u, 0xFFFF0000u, 0xFFFE0000u, 0x30000u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1401u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1401u, 0u, 6u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0xFFE00000u, 0u, 0u, 0u, 7u, 2u, 0u, 0u, 0x102u, 0u, 0x200000u, 0u, 0xFFFE0000u, 0u, 0x4000u, 0u, 0u, 0x4100u, 0x102u, 0u, 0x1200000u, 0u, 0xFFFE0000u, 0u, 0u, 0u, 0u, 0x4100u, 0x402u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x402u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10Bu, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_storm_owl_states(u32 row)
{
    return state_run(owl_cases[row], row, &owl_expected[row * 10]);
}

static u32 owl_pages[8];
#define OWL_INIT(stage_id, px)             \
    do {                                   \
        u8 stage = engine_obj.stage;       \
        u32* pages = D_801406A8;           \
        u8* frames = TEST_MENU_FRAMES;     \
        state_reset(0, 0, 0);              \
        so.x_pos.i.hi = 0x80;              \
        so.y_pos.i.hi = 0x60;              \
        g_Player.x_pos.i.hi = px;          \
        engine_obj.stage = stage_id;       \
        test_stage_graphics(owl_pages);            \
        TEST_MENU_FRAMES = (u8*)owl_pages; \
        func_800751AC(&so);                \
        so.unk42 = 0;                      \
        engine_obj.stage = stage;          \
        test_stage_graphics(pages);                \
        TEST_MENU_FRAMES = frames;         \
    } while (0)
static void sow_init(void)
{
    OWL_INIT(0, 0x40);
}
static void sow_init_rematch(void) { OWL_INIT(0xC, 0x100); }
static void sow_rain_wait(void)
{
    state_reset(6, 1, 0);
    so.unk7C = 2;
    func_80077580(&so);
}
static void sow_rain_again(void)
{
    state_reset(6, 1, 0);
    so.unk7C = 1;
    cur_random = 0;
    func_80077580(&so);
}
static void sow_rain_done(void)
{
    state_reset(6, 1, 0);
    so.unk7C = 1;
    cur_random = 0x5B;
    func_80077580(&so);
}

static void (*const storm_owl_init_rain_cases[])(void) = {
    sow_init,
    sow_init_rematch,
    sow_rain_wait,
    sow_rain_again,
    sow_rain_done,
};
static const u32 storm_owl_init_rain_expected[] = { 0x280002u, 0u, 0x800000u, 0u, 0u, 0u, 1u, 3u, 0u, 0u, 0x280002u, 0u, 0x800000u, 0u, 0u, 0u, 0x4001u, 3u, 0u, 0u, 0x106u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x206u, 0x1Eu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x306u, 0x1Eu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_storm_owl_init_rain(u32 row)
{
    return state_run(storm_owl_init_rain_cases[row], row, &storm_owl_init_rain_expected[row * 10]);
}

static const struct {
    s8 weapon;
    u8 character, step, flash_mode, flash_timer, fatal;
    u8 expected_step, expected_mode, expected_timer;
} owl_damage_cases[] = {
    { -1, 0, 10, 0, 0, 0, 10, 0, 0 },
    { -1, 0, 10, 1, 2, 0, 10, 1, 1 },
    { -1, 0, 10, 1, 1, 0, 10, 0, 0 },
    { -1, 0, 10, 2, 2, 0, 10, 2, 1 },
    { -1, 0, 10, 2, 1, 0, 10, 0, 0 },
    { 0, 0, 10, 0, 0, 0, 10, 1, 0x40 },
    { 6, 0, 10, 0, 0, 0, 11, 0, 0 },
    { 15, 0, 10, 0, 0, 0, 11, 0, 0 },
    { 6, 0, 11, 0, 0, 0, 11, 0, 0 },
    { 25, 1, 10, 0, 0, 0, 10, 1, 0x40 },
    { 27, 1, 10, 0, 0, 0, 10, 1, 0x40 },
    { 29, 1, 10, 0, 0, 0, 10, 1, 0x40 },
    { 31, 1, 10, 0, 0, 0, 10, 1, 0x40 },
    { 32, 1, 10, 0, 0, 0, 10, 1, 0x40 },
    { 33, 1, 10, 0, 0, 0, 10, 1, 0x40 },
    { 34, 1, 10, 0, 0, 0, 10, 2, 8 },
    { 35, 1, 10, 0, 0, 0, 10, 2, 8 },
    { 34, 1, 10, 2, 4, 0, 10, 1, 0x40 },
    { 36, 1, 10, 0, 0, 0, 11, 0, 0 },
    { 36, 1, 11, 0, 0, 0, 11, 0, 0 },
    { 0, 1, 10, 0, 0, 0, 10, 0, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 0, 0 },
};

static u32 test_owl_damage(u32 row)
{
    u32 i, flashes = 0;
    const u8 expected_hp = owl_damage_cases[row].fatal ? 0 : owl_damage_cases[row].weapon < 0 ? 32
                                                                                              : 31;
    state_reset(owl_damage_cases[row].step, 1, 2);
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    engine_obj.cur_character = owl_damage_cases[row].character;
    g_Player.unk2 = owl_damage_cases[row].character;
    SPIKE_IMMUNE_SET(g_Player, owl_damage_cases[row].fatal ? 0 : 1);
    so.active = 0x41;
    so.state = 1;
    so.hp = 32;
    so.bg_offset = -1;
    so.x_pos.val = FIXED(100);
    so.y_pos.val = FIXED(100);
    so.unk17 = 2;
    so.unk7C = 20;
    so.collision_data = D_80107B78;
    so.ext.main_60.saved_unk5 = 0x55;
    so.ext.main_60.flash_mode = owl_damage_cases[row].flash_mode;
    so.ext.main_60.flash_timer = owl_damage_cases[row].flash_timer;
    if (owl_damage_cases[row].weapon >= 0)
        state_hit(&so, owl_damage_cases[row].weapon, 0, owl_damage_cases[row].fatal ? 32 : 1);

    func_80075320(&so);

    assert(so.hp == expected_hp);
    assert(so.unk5 == owl_damage_cases[row].expected_step);
    assert(so.ext.main_60.flash_mode == owl_damage_cases[row].expected_mode);
    assert(so.ext.main_60.flash_timer == owl_damage_cases[row].expected_timer);
    assert(so.ext.main_60.saved_unk5 == (owl_damage_cases[row].step ? owl_damage_cases[row].step : 0x55));
    assert(so.state == (owl_damage_cases[row].fatal ? 2 : 1));
    if (owl_damage_cases[row].fatal) {
        assert(so.unk6 == 0 && SPIKE_IMMUNE(g_Player) == 1 && (so.unk42 & 0x8000) == 0);
    } else if (owl_damage_cases[row].character == 0 && (owl_damage_cases[row].weapon == 6 || owl_damage_cases[row].weapon == 15)) {
        assert(so.active == 0x45);
        if (owl_damage_cases[row].weapon == 15)
            assert(so.collision_data == D_80106070);
    }
    for (i = 0; i < COUNT(visual_objects); i++)
        if (visual_objects[i].active && visual_objects[i].id == 0x1C && visual_objects[i].unk50 == (void*)&so)
            flashes++;
    assert(flashes == (owl_damage_cases[row].expected_mode == 1 && owl_damage_cases[row].expected_timer == 0x40));
    return (u8)so.hp;
}

static u32 test_owl_voice_timer(u32 row)
{
    state_reset(10, 1, 0);
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    SPIKE_IMMUNE_SET(g_Player, 1);
    so.active = 1;
    so.hp = 32;
    so.bg_offset = -1;
    so.collision_data = D_80107B78;
    so.unk7 = row == 0 ? 2 : 1;
    so.unk7C = 20;
    cur_random = row == 2 ? 1 : 0;
    func_80075320(&so);
    assert(so.unk7 == (row == 0 ? 1 : 0x28));
    assert(so.unk5 == 10 && so.unk6 == 1 && so.unk7C == 19);
    assert(so.hp == 32);
    return (u8)so.unk7;
}

void storm_owl_feather_start(struct MainObj*);
void storm_owl_feather_takeoff(struct MainObj*);
void storm_owl_stagger_recover(struct MainObj*);
void storm_owl_storm_start(struct MainObj*);
extern void* storm_owl_animations[30];
extern struct Unk_unk68 D_80107B78[];
static const u16 seeds[] = { 1, 0x1234 }, next_seeds[] = { 1, 0x366A };
static void animation(struct MainObj* obj, u8 index, u32 word)
{
    obj->unk17 = index;
    obj->previous_animation_index = 255;
    obj->animation_cursor = (const u8*)storm_owl_animations[index];
    obj->animation_step.packed = C_TEST_STEP(word);
}
static u32 entry(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 mode = row % 4, side = row / 4 % 2, seed = row / 8 % 2, wait = row / 16 % 2, camera = row / 32, initial = mode == 1 ? 3 : mode == 3 ? 12
                                                                                                                                            : 1;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = camera * 256;
    background_objects[0].y_pos.i.hi = camera * 256;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 0x41;
    obj.id = 60;
    obj.state = 1;
    obj.unk5 = mode < 2 ? 6 : mode == 2 ? 9
                                        : 11;
    obj.unk6 = mode == 1 ? 2 : mode == 3 ? 1
                                         : 0;
    obj.unk15 = side ? PLAYER_FACING_RIGHT : 0;
    obj.unk7C = 1 + wait;
    obj.x_pos.val = (camera * 256 + 160 + (side ? 16 : -16)) * 65536;
    obj.y_pos.val = (camera * 256 + 112) * 65536;
    obj.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&obj, initial);
    assert(obj.animation_step.packed == C_TEST_STEP(mode == 1 ? 0x13010004 : mode == 3 ? 0x68010003
                                                                            : 0x00010004));
    g_Player.x_pos.val = obj.x_pos.val + (side ? 1 : -1) * 65536;
    player_before = g_Player;
    expected = obj;
    expected.animation_step.fields.duration--;
    if (!mode) {
        animation(&expected, 3, 0x13010004);
        expected.unk15 = side ? PLAYER_FACING_RIGHT : 0;
        expected.unk7C = 31;
        expected.unk6++;
    } else if (mode == 2) {
        animation(&expected, 0, 0x06010006);
        expected.x_speed = side ? -0x20000 : 0x20000;
        expected.y_speed = 0;
        expected.unk15 = side ? 0 : PLAYER_FACING_RIGHT;
        expected.unk6++;
    } else {
        expected.unk7C--;
        if (!wait) {
            animation(&expected, 1, 0x00010004);
            expected.unk6++;
            expected.y_speed = 0x30000;
            if (mode == 1) {
                expected.ext.main_60.corner = (side ? 0 : 2) + seed;
                expected.unk15 = side ? 0 : PLAYER_FACING_RIGHT;
                expected.x_speed = side ? -0x20000 : 0x20000;
            } else {
                expected.collision_data = D_80107B78;
                expected.x_speed = side ? 0x20000 : -0x20000;
            }
        }
    }
    cur_random = seeds[seed];
    if (!mode)
        storm_owl_feather_start(&obj);
    else if (mode == 1)
        storm_owl_feather_takeoff(&obj);
    else if (mode == 2)
        storm_owl_storm_start(&obj);
    else
        storm_owl_stagger_recover(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(cur_random == (mode == 1 && !wait ? next_seeds[seed] : seeds[seed]));
    return 1;
}

extern void* storm_owl_animations[30];
extern struct Unk_unk68 storm_owl_grab_terrain_box, storm_owl_grab_attack_box, storm_owl_slam_terrain_box, storm_owl_attack_box;
static const s16 player_dx[] = { -8, -7, 0, 7, 8 };
static u32 swoop(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 dx = row % COUNT(player_dx), low = row / COUNT(player_dx) % 2, stunned = row / COUNT(player_dx) / 2 % 2;
    u32 far = row / COUNT(player_dx) / 4 % 2, facing = row / COUNT(player_dx) / 8;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 60;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 3;
    obj.unk16 = VISUAL_SATURN_LAYER(2);
    obj.unk62 = 3;
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    obj.terrain_box = &storm_owl_grab_terrain_box;
    obj.attack_box = &storm_owl_grab_attack_box;
    obj.x_pos.val = (far ? 384 : 160) * 65536 + 0x1234 - 0x18000;
    obj.y_pos.val = 120 * 65536 + 0x5678 + 0x14000;
    obj.x_speed = 0x18000;
    obj.y_speed = 0x14000;
    obj.x_accel = 0x1234;
    obj.gravity = 0x2345;
    obj.ext.main_60.corner = 7;
    obj.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&obj, 7);
    assert(obj.animation_step.packed == C_TEST_STEP(0x0C010002));
    g_Player.hp = 24;
    g_Player.stun_timer = stunned ? 5 : 0;
    g_Player.x_pos.val = (far ? 384 : 160) * 65536 + 0x1234 + player_dx[dx] * 65536;
    g_Player.y_pos.val = (low ? 140 : 141) * 65536 + 0x5678;
    player_expected = g_Player;
    expected = obj;
    expected.animation_step.fields.duration = 1;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val -= obj.y_speed;
    if (low) {
        expected.x_speed = facing ? 0x20000 : -0x20000;
        expected.y_speed = -0x10000;
        expected.unk6 = 5;
        expected.unk17 = 1;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)storm_owl_animations[1];
        expected.animation_step.packed = C_TEST_STEP(0x00010004);
    } else if (stunned) {
        expected.x_speed = dx == 0 ? -65536 : dx == 4 ? 65536
                                                      : 0;
        expected.y_speed = 0;
        expected.unk6++;
    } else if (far) {
        expected.ext.main_60.corner = dx > 2 ? 1 : 3;
        expected.unk5 = 5;
        expected.unk6 = 0;
    }
    if (low || (!stunned && far)) {
        player_expected.stun_timer = 0;
        expected.contact_damage = 6;
        expected.terrain_box = &storm_owl_slam_terrain_box;
        expected.attack_box = &storm_owl_attack_box;
        expected.unk62 = 0;
        expected.unk16 = VISUAL_SATURN_LAYER(5);
    }
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    func_80076364(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(cur_random == (!low && !stunned && far ? 0x366A : 0x1234));
    return 1;
}

void func_80078180(struct MainObj* arg0);
void storm_owl_storm(struct MainObj* arg0);
extern void* storm_owl_animations[30];
static struct ShotObj pool_expected[32];
static u32 rain(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 slots = row % 3, face = row / 3 % 2, layer = row / 6, available = slots == 2 ? 4 : slots, i;
    engine_obj.stage = 7;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 60;
    obj.state = 1;
    obj.hp = 16;
    obj.unk5 = 9;
    obj.unk6 = 3;
    obj.unk7C = 1;
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.bg_offset = layer;
    obj.x_pos.i.hi = 2384;
    obj.y_pos.i.hi = 640;
    obj.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&obj, 6);
    D_8013E198[2] = -1;
    storm_owl_storm(&obj);
    for (i = 0; i < 9; i++)
        storm_owl_storm(&obj);
    assert(obj.unk6 == 4 && obj.ext.main_60.storm_active == 1 && obj.unk7E == 1 && obj.unk7C == 81);
    expected = obj;
    expected.unk7E = 10;
    for (i = 0; i < available; i++) {
        struct ShotObj* s = &pool_expected[32 - available + i];
        s->active = 0x41;
        s->id = 37;
        s->unk2 = i + 5;
        s->unk7C = WEAPON_OBJECT(&obj);
        s->unk42 = obj.unk42;
        s->animation_table = (u32**)storm_owl_animations;
        s->unk3C = (void*)obj.sprite_frames;
        s->unk40 = obj.unk40;
        s->bg_offset = layer;
        s->unk16 = VISUAL_SATURN_LAYER(5);
        s->unk15 = obj.unk15;
    }
    func_80078180(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_8013E198[2] == -1);
    return 1;
}

void storm_owl_feather_volley_wait(struct MainObj*);
void storm_owl_storm_fly_to_center(struct MainObj*);
extern void* storm_owl_animations[30];
static const s16 heights[] = { -5, -4, -3, 3, 4, 5 };
static u32 owl(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 center = row >= 12, index = center ? (row - 12) % 6 : row % 3, variant = center ? (row - 12) / 6 : row / 3, mask = variant % 2;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 60;
    obj.state = 1;
    obj.unk5 = center ? 9 : 7;
    obj.unk6 = center ? 1 : 4;
    obj.unk15 = variant & 2 ? PLAYER_FACING_RIGHT : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = (112 + (center ? heights[index] : 0)) * 65536 + 0x5678;
    background_objects[0].x_pos.val = 0x1234;
    background_objects[0].y_pos.val = 0x5678;
    if (center) {
        obj.x_pos.val = (160 + variant * 256) * 65536;
        obj.y_pos.val = (112 + variant * 256 + heights[index]) * 65536;
        background_objects[0].x_pos.i.hi = background_objects[0].y_pos.i.hi = variant * 256;
    }
    obj.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&obj, 1);
    assert(obj.animation_step.packed == C_TEST_STEP(0x00010004));
    obj.ext.main_60.feather_mask = center ? 0 : mask;
    obj.ext.main_60.feathers_holding = 1;
    obj.x_speed = obj.y_speed = 0;
    g_Player.x_pos.val = obj.x_pos.val + ((s32)index - 1) * 65536;
    player_before = g_Player;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    expected = obj;
    expected.animation_step.fields.duration = 3;
    if (center) {
        expected.y_speed = heights[index] < 0 ? -0x20000 : 0x20000;
        if (index == 2 || index == 3) {
            expected.animation_cursor = (const u8*)storm_owl_animations[6];
            expected.animation_step.packed = C_TEST_STEP(0x26010006);
            expected.previous_animation_index = 0xFF;
            expected.unk17 = 6;
            expected.unk6++;
        }
    } else if (!mask) {
        expected.ext.main_60.feathers_holding = 0;
        expected.animation_step.packed = C_TEST_STEP(0x00010004);
        expected.animation_cursor = (const u8*)storm_owl_animations[1];
        expected.previous_animation_index = 0xFF;
        expected.unk15 = index == 2 ? 0 : PLAYER_FACING_RIGHT;
        expected.x_speed = index == 2 ? -0x20000 : 0x20000;
        expected.y_speed = 0x30000;
        expected.unk6++;
    }
    if (center)
        storm_owl_storm_fly_to_center(&obj);
    else
        storm_owl_feather_volley_wait(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

void storm_owl_grab_slam(struct MainObj*);
extern void* storm_owl_animations[30];
extern struct Unk_unk68 storm_owl_grab_terrain_box, storm_owl_grab_attack_box, storm_owl_slam_terrain_box, storm_owl_attack_box;
static const s16 player_x[] = { 15, 16, 17, 303, 304, 305 };
static u8 map[256];
static u16 pixels[2][16][16];
static u32 attributes[2];
static u32 slam(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_expected[3];
    u32 edge = row % 6, floor = row / 6 % 2, face = row / 12 % 2, armor = row / 24, i;
    memset(map, 1, sizeof(map));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = 0;
    attributes[1] = C_TEST_PSX_WORD(0x38);
    if (floor)
        for (i = 8 * 16; i < 16 * 16; i++)
            ((u16*)pixels[1])[i] = 1;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    obj.active = 0x41;
    obj.id = 60;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = 4;
    obj.unk62 = 3;
    obj.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    obj.air_state = -1;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 75 * 65536 + 0x5678;
    obj.unk18 = obj.x_pos;
    obj.unk1C = obj.y_pos;
    obj.x_speed = face ? 65536 : -65536;
    obj.y_speed = -65536;
    obj.x_accel = 0x1000;
    obj.terrain_box = &storm_owl_grab_terrain_box;
    obj.attack_box = &storm_owl_grab_attack_box;
    obj.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&obj, 8);
    assert(obj.animation_step.packed == C_TEST_STEP(0x0E010002));
    g_Player.hp = 30;
    g_Player.armor_parts = armor ? 2 : 0;
    g_Player.stun_timer = 3;
    g_Player.x_pos.val = player_x[edge] * 65536 + 0xAAAA;
    g_Player.y_pos.val = 104 * 65536 + 0xBBBB;
    player_expected = g_Player;
    expected = obj;
    expected.animation_step.fields.duration = 1;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val += 65536;
    if (edge < 2 || edge > 3)
        expected.x_speed = expected.x_accel = 0;
    player_expected.x_pos.i.hi = expected.x_pos.i.hi;
    player_expected.y_pos.i.hi = 104;
    expected.unk6C = expected.x_pos.i.hi & 15;
    expected.unk6E = 0;
    expected.collision_flags = floor ? 8 : 0;
    if (floor) {
        expected.y_pos.u.lo = 0;
        expected.unk6 = 5;
        expected.unk62 = 0;
        expected.unk17 = 1;
        expected.previous_animation_index = 255;
        expected.animation_cursor = (const u8*)storm_owl_animations[1];
        expected.animation_step.packed = C_TEST_STEP(0x00010004);
        expected.x_speed = face ? 0x20000 : -0x20000;
        expected.y_speed = -0x10000;
        expected.terrain_box = &storm_owl_slam_terrain_box;
        expected.attack_box = &storm_owl_attack_box;
        player_expected.hp = (armor ? 24 : 21) | 0x80;
        player_expected.stun_timer = 0;
        backgrounds_expected[0].unk37 = 8;
        backgrounds_expected[0].unk46 = backgrounds_expected[0].unk3E.bytes[1] = 4;
        backgrounds_expected[0].unk3D = backgrounds_expected[0].unk3B = 1;
        backgrounds_expected[0].unk34 = 1;
    }
    D_8013E198[2] = -1;
    D_8013B7D8 = D_8013B7DC = D_8013B800 = D_8013B804 = 0;
    cur_random = 0x1234;
    storm_owl_grab_slam(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    assert(cur_random == 0x1234 && D_8013B7D8 == 0 && D_8013B7DC == (floor ? 8 : 0) && D_8013B800 == 0 && D_8013B804 == 0);
    for (i = 0; i < 256; i++)
        assert(map[i] == 1 && pixels[0][i / 16][i % 16] == 0 && pixels[1][i / 16][i % 16] == (floor && i >= 128));
    assert(attributes[0] == 0 && attributes[1] == C_TEST_PSX_WORD(0x38) && SP_BG_TILEMAP == map && TEST_BG_TILE_PIXELS == (u8*)pixels && TEST_BG_TILE_ATTRS == (u8*)attributes && layout_width == 16 && layout_height == 16 && layout_size == 256);
    return 1;
}

void storm_owl_patrol(struct MainObj*);
void storm_owl_reenter(struct MainObj*);
void storm_owl_feather(struct MainObj*);
void storm_owl_feather_volley(struct MainObj*);
extern u8 storm_owl_pattern_0[4];
extern struct Unk_unk68 storm_owl_grab_attack_box, storm_owl_grab_terrain_box;

static struct MainObj ow;
#define OW_IS(a, b) ((const void*)(a) == (const void*)(b))
static void ow_reset(u8 unk5, u8 unk6)
{
    memset(&ow, 0, sizeof(ow));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    background_objects[0].x_pos.i.hi = 0x900;
    background_objects[0].y_pos.i.hi = 0x600;
    D_80141F50[2] = state_sound_rows;
    engine_obj.stage = 7;
    cur_random = 0;
    ow.active = 0x41;
    ow.id = 60;
    ow.state = 1;
    ow.unk5 = unk5;
    ow.unk6 = unk6;
    ow.hp = 0x30;
    ow.x_pos.i.hi = 0x980;
    ow.y_pos.i.hi = 0x660;
    ow.animation_table = (const u8* const*)storm_owl_animations;
    set_animation(&ow, 1);
}
static void ow_ground(u8 solid)
{
    u32 i;
    memset(map, 1, sizeof(map));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = 0;
    attributes[1] = C_TEST_PSX_WORD(0x38);
    for (i = 8 * 16; i < 16 * 16; i++)
        ((u16*)pixels[1])[i] = solid;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    background_objects[0].x_pos.i.hi = 0;
    background_objects[0].y_pos.i.hi = 0;
}
static void ow_floor(s16 y)
{
    ow_ground(1);
    ow.terrain_box = &storm_owl_slam_terrain_box;
    ow.x_pos.i.hi = 160;
    ow.y_pos.i.hi = y;
    ow.unk18 = ow.x_pos;
    ow.unk1C = ow.y_pos;
    ow.air_state = -1;
    ow.x_speed = 0;
    ow.y_speed = -0x10000;
}

static void sox_death(void)
{
    struct EngineObj engine = engine_obj;
    ow_reset(0, 0);
    ow.state = 2;
    ow.unk42 = 0x8123;
    g_Player.unk15 = PLAYER_FACING_RIGHT;
    storm_owl_update(&ow);
    assert(ow.unk5 == 1 && ow.unk17 == 0xB && ow.unk7C == 0x7F && ow.unk7E == 0x19 && ow.invincibility_timer == 0x19 && ow.unk42 == 0x123);
    assert(g_Player.script_action == 0x14 && g_Player.script_facing == PLAYER_FACING_RIGHT);
    ow.unk5 = 2;
    ow.unk7E = 3;
    ow.ext.main_60.effect = &effect_objects[0];
    effect_objects[0].active = 1;
    storm_owl_update(&ow);
    assert(ow.unk7E == 2 && ow.unk42 == 0x123 && ow.active == 0x41);
    engine_obj = engine;
}
static void sox_start(void)
{
    struct EngineObj engine = engine_obj;
    ow_reset(1, 0);
    ow.state = 0;
    storm_owl_update(&ow);
    assert(ow.unk5 == 2 && effect_objects[0].active == 1 && effect_objects[0].id == 0x18 && ow.ext.main_60.effect == &effect_objects[0]);
    storm_owl_update(&ow);
    assert(ow.unk5 == 2);
    effect_objects[0].active = 0;
    storm_owl_update(&ow);
    assert(ow.unk5 == 3);
    engine_obj = engine;
}
static void sox_intro(void)
{
    struct EngineObj engine = engine_obj;
    ow_reset(2, 1);
    ow_floor(40);
    storm_owl_intro(&ow);
    assert(ow.unk6 == 1 && ow.y_pos.i.hi == 41);
    ow_floor(103);
    storm_owl_intro(&ow);
    assert(ow.unk6 == 2 && ow.unk17 == 9 && ow.unk7C == 0x49);
    background_objects[0].x_pos.i.hi = 0x900;
    background_objects[0].y_pos.i.hi = 0x600;
    ow.x_pos.i.hi = 0x980;
    ow.y_pos.i.hi = 0x661;
    ow.unk7C = 2;
    storm_owl_intro(&ow);
    assert(ow.unk6 == 2 && ow.unk7C == 1 && visual_objects[0].active == 0);
    storm_owl_intro(&ow);
    assert(ow.unk6 == 3 && ow.unk7C == 0x2F && background_objects[0].unk37 == 0x18 && visual_objects[0].active == 0x41 && visual_objects[0].id == 0x1C && visual_objects[0].unk2 == 0);
    engine_obj.stage = 0xC;
    abc_object.unkC = 0;
    ow.unk7C = 2;
    storm_owl_intro(&ow);
    assert(ow.unk6 == 3 && ow.unk7C == 1);
    storm_owl_intro(&ow);
    assert(ow.unk6 == 4 && abc_object.unkC == 0);
    abc_object.unkC = 0x80;
    storm_owl_intro(&ow);
    assert(ow.unk6 == 4 && engine_obj.boss_ptr != &ow);
    abc_object.unkC = 0;
    engine_obj.unk36.value = 0;
    storm_owl_intro(&ow);
    assert(ow.unk6 == 5 && engine_obj.boss_ptr == &ow && engine_obj.enable_boss == 1 && engine_obj.unk25 == 1 && ow.unk7C == 3 && engine_obj.unk36.value == 0x3C);
    ow.hp = 0x10;
    D_80173C84 = 0;
    engine_obj.unk36.timer = 2;
    storm_owl_intro(&ow);
    assert(ow.hp == 0x10 && engine_obj.unk36.timer == 1);
    engine_obj.unk36.timer = 0;
    ow.unk7C = 2;
    storm_owl_intro(&ow);
    assert(ow.hp == 0x11 && ow.unk7C == 1);
    ow.hp = 0x2F;
    g_Player.script_state = 1;
    storm_owl_intro(&ow);
    assert(ow.hp == 0x30 && ow.unk7C == 3 && ow.unk6 == 6 && g_Player.script_state == 0 && ow.ext.main_60.pattern == storm_owl_pattern_0);
    storm_owl_intro(&ow);
    assert(ow.unk6 == 7 && ow.ext.main_60.corner == 2 && ow.unk17 == 1);
    engine_obj.stage = 7;
    ow.unk6 = 6;
    storm_owl_intro(&ow);
    assert(ow.unk6 == 7 && ow.ext.main_60.corner == 0 && ow.x_speed < 0);
    ow.x_speed = 0;
    ow.y_speed = 0x10000;
    storm_owl_intro(&ow);
    assert(ow.unk6 == 7 && ow.y_pos.i.hi == 0x660);
    ow.y_pos.i.hi = 0x628;
    storm_owl_intro(&ow);
    assert(ow.unk5 == 3 && ow.unk6 == 2 && ow.y_speed == 0 && ow.y_pos.i.hi == 0x627);
    engine_obj = engine;
}
static void sox_patrol_fly(void)
{
    static u8 used_up[1] = { 0xFF };
    ow_reset(3, 0);
    g_Player.x_pos.i.hi = 0xA00;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 1 && ow.unk15 == PLAYER_FACING_RIGHT && ow.unk17 == 1);
    ow.unk6 = 0;
    g_Player.x_pos.i.hi = 0x900;
    storm_owl_patrol(&ow);
    assert(ow.unk15 == 0);
    ow.unk6 = 1;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 1 && ow.unk5 == 3 && ow.x_speed < 0);
    ow.x_pos.i.hi = 0x918;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 1 && ow.unk5 == 3 && ow.x_speed == 0);
    ow.ext.main_60.pattern = used_up;
    ow.x_pos.i.hi = 0x915;
    ow.y_pos.i.hi = 0x625;
    storm_owl_patrol(&ow);
    assert(ow.unk5 == 3 && ow.unk6 == 2 && ow.x_speed == 0 && ow.y_speed == 0 && ow.ext.main_60.pattern == &storm_owl_pattern_0[1]);
    ow.unk6 = 1;
    ow.ext.main_60.pattern = &storm_owl_pattern_0[2];
    ow.x_pos.i.hi = 0x91B;
    ow.y_pos.i.hi = 0x62B;
    storm_owl_patrol(&ow);
    assert(ow.unk5 == 8 && ow.unk6 == 0 && ow.ext.main_60.pattern == &storm_owl_pattern_0[3]);
}
static void sox_patrol_swoop(void)
{
    ow_reset(3, 2);
    ow.ext.main_60.patrol_delay = 2;
    ow.ext.main_60.corner = 1;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 2 && ow.ext.main_60.patrol_delay == 1);
    ow.ext.main_60.patrol_delay = 0;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 3 && ow.x_speed == 0x28000 && ow.y_speed == 0x800 && ow.x_accel == FIXED(0.015625) && ow.unk15 == PLAYER_FACING_RIGHT);
    ow.unk6 = 2;
    ow.ext.main_60.corner = 2;
    storm_owl_patrol(&ow);
    assert(ow.x_speed == -0x20000 && ow.unk15 == 0);
    ow.x_speed = 0;
    ow.y_speed = 0;
    ow.x_accel = 0;
    g_Player.x_pos.i.hi = 0x9C0;
    g_Player.y_pos.i.hi = 0x6C0;
    storm_owl_patrol(&ow);
    assert(ow.unk5 == 3 && ow.unk6 == 3 && ow.y_speed == 0x400);
    g_Player.x_pos.i.hi = 0x9B0;
    storm_owl_patrol(&ow);
    assert(ow.unk5 == 4 && ow.unk6 == 0 && ow.y_speed == 0);
    ow.unk5 = 3;
    ow.unk6 = 3;
    g_Player.x_pos.i.hi = 0x960;
    g_Player.y_pos.i.hi = 0x600;
    storm_owl_patrol(&ow);
    assert(ow.unk5 == 6 && ow.unk6 == 0);
    ow.unk5 = 3;
    ow.unk6 = 3;
    cur_random = 5;
    storm_owl_patrol(&ow);
    assert(ow.unk5 == 3 && ow.unk6 == 4 && ow.ext.main_60.corner == 0);
    ow.x_speed = 0;
    ow.y_speed = 0;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 4 && ow.y_speed == FIXED(0.015625));
    ow.x_pos.i.hi = 0x938;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 0 && ow.ext.main_60.patrol_delay == 0x14 && ow.y_speed == 0);
    ow.unk6 = 4;
    ow.ext.main_60.patrol_delay = 0;
    ow.x_pos.i.hi = 0x8F8;
    storm_owl_patrol(&ow);
    assert(ow.unk6 == 0 && ow.ext.main_60.patrol_delay == 0x14);
}
static void sox_grab(void)
{
    ow_reset(4, 0);
    ow_ground(0);
    ow.x_pos.i.hi = 0x80;
    ow.y_pos.i.hi = 0x40;
    g_Player.x_pos.i.hi = 0x40;
    g_Player.y_pos.i.hi = 0x80;
    storm_owl_grab(&ow);
    assert(ow.unk6 == 1 && ow.x_speed < 0 && ow.unk17 == 7 && ow.unk62 == 3 && ow.contact_damage == 0 && OW_IS(ow.attack_box, &storm_owl_grab_attack_box));
    ow.unk6 = 0;
    ow.unk15 = PLAYER_FACING_RIGHT;
    g_Player.x_pos.i.hi = 0xC0;
    storm_owl_grab(&ow);
    assert(ow.unk6 == 1 && ow.x_speed > 0);
    ow.unk6 = 2;
    ow.unk15 = PLAYER_FACING_RIGHT;
    ow.x_speed = 0x10000;
    ow.y_speed = 0;
    g_Player.x_pos.i.hi = 0x83;
    storm_owl_grab(&ow);
    assert(ow.unk6 == 3 && ow.x_speed == 0x10000 && ow.y_speed == 0x10000 && ow.unk7C == 0x3C);
    ow.unk15 = 0;
    ow.unk7C = 2;
    ow.x_speed = 0;
    storm_owl_grab(&ow);
    assert(ow.unk6 == 3 && ow.unk7C == 1 && ow.y_speed == 0x10000 && g_Player.x_pos.i.hi == 0x77 && g_Player.y_pos.i.hi == 0x5D);
    ow.unk15 = PLAYER_FACING_RIGHT;
    storm_owl_grab(&ow);
    assert(ow.unk6 == 4 && ow.unk17 == 8 && ow.y_speed == FIXED(-4) && g_Player.x_pos.i.hi == 0x8B);
    ow.unk6 = 5;
    ow.x_speed = 0;
    ow.y_speed = 0;
    ow.unk62 = 3;
    ow.contact_damage = 0;
    storm_owl_grab(&ow);
    assert(ow.unk6 == 5 && ow.y_speed == FIXED(0.125));
    ow.y_speed = FIXED(3);
    ow.y_pos.i.hi = 0x500;
    storm_owl_grab(&ow);
    assert(ow.y_speed == FIXED(3) && ow.unk5 == 5 && ow.unk6 == 0 && ow.unk62 == 0 && ow.contact_damage == 6 && OW_IS(ow.attack_box, &storm_owl_attack_box));
    ow_reset(4, 3);
    ow_floor(128);
    ow.terrain_box = &storm_owl_grab_terrain_box;
    ow.y_speed = 0x10000;
    ow.gravity = 0x1000;
    ow.unk7C = 5;
    storm_owl_grab(&ow);
    assert(ow.unk6 == 3 && ow.unk7C == 4 && ow.y_speed == 0 && ow.gravity == 0 && ow.y_pos.i.hi == 127);
}
static void sox_reenter(void)
{
    static const s16 spots[][2] = { { -0x40, 0x10 }, { -0x40, 0xC8 }, { 0x180, 0x10 }, { 0x180, 0xC8 } };
    u32 i;
    for (i = 0; i < COUNT(spots); i++) {
        ow_reset(5, 0);
        g_Player.x_pos.i.hi = 0x900;
        ow.ext.main_60.corner = i;
        storm_owl_reenter(&ow);
        assert(ow.x_pos.i.hi == 0x900 + spots[i][0] && ow.y_pos.i.hi == 0x600 + spots[i][1] && ow.unk6 == 1 && ow.unk7C == 0x3C);
        assert(ow.unk15 == (i >= 2 ? 0 : PLAYER_FACING_RIGHT));
    }
    ow.ext.main_60.flash_mode = 1;
    ow.unk7C = 2;
    storm_owl_reenter(&ow);
    assert(ow.unk7C == 1 && OW_IS(ow.collision_data, D_801060F0));
    ow.ext.main_60.flash_mode = 0;
    storm_owl_reenter(&ow);
    assert(ow.unk5 == 3 && ow.unk6 == 0 && OW_IS(ow.collision_data, D_80107B78));
}
static void sox_feather(void)
{
    ow_reset(6, 1);
    ow.unk7C = 2;
    storm_owl_feather(&ow);
    assert(ow.unk6 == 1 && ow.unk7C == 1 && shot_objects[0].active == 0);
    storm_owl_feather(&ow);
    assert(ow.unk6 == 2 && ow.unk7C == 0x1C && shot_objects[0].active == 0x41 && shot_objects[0].id == 0x25 && shot_objects[0].unk2 == 0 && shot_objects[0].unk7C == (struct WeaponObj*)&ow);
    ow.unk6 = 3;
    storm_owl_feather(&ow);
    assert(ow.unk5 == 6 && ow.unk6 == 3);
    ow.x_pos.i.hi = 0x800;
    storm_owl_feather(&ow);
    assert(ow.unk5 == 5 && ow.unk6 == 0);
}
static void sox_volley(void)
{
    ow_reset(7, 0);
    ow.ext.main_60.corner = 2;
    ow.ext.main_60.shot_count = 3;
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 1 && ow.unk15 == 0 && ow.unk7C == 0x1C && ow.ext.main_60.shot_count == 0 && ow.unk17 == 3 && OW_IS(ow.collision_data, D_80107B78));
    ow.unk6 = 0;
    ow.ext.main_60.corner = 1;
    storm_owl_feather_volley(&ow);
    assert(ow.unk15 == PLAYER_FACING_RIGHT);
    ow.unk7C = 2;
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 1 && ow.unk7C == 1);
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 1 && ow.unk7C == 0x3D && ow.ext.main_60.shot_count == 1 && shot_objects[0].id == 0x25 && shot_objects[0].unk2 == 1);
    ow.unk7C = 1;
    ow.ext.main_60.shot_count = 3;
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 2 && ow.unk7C == 0x3C && ow.ext.main_60.shot_count == 4 && shot_objects[1].unk2 == 4);
    ow.unk7C = 2;
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 2 && ow.unk7C == 1);
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 3 && ow.unk7C == 0x3C && ow.unk17 == 6);
    ow.unk7C = 2;
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 3 && ow.unk7C == 1 && ow.ext.main_60.feathers_holding == 0);
    storm_owl_feather_volley(&ow);
    assert(ow.unk6 == 4 && ow.unk7C == 0x78 && ow.ext.main_60.feathers_holding == 1);
    ow.unk6 = 5;
    storm_owl_feather_volley(&ow);
    assert(ow.unk5 == 7 && ow.unk6 == 5);
    ow.x_pos.i.hi = 0x800;
    g_Player.x_pos.i.hi = 0x900;
    storm_owl_feather_volley(&ow);
    assert(ow.unk5 == 5 && ow.unk6 == 0 && ow.ext.main_60.corner == 0);
}
static void sox_cyclone(void)
{
    ow_reset(8, 0);
    storm_owl_cyclone(&ow);
    assert(ow.unk6 == 1 && ow.unk17 == 4 && ow.unk15 == PLAYER_FACING_RIGHT && ow.unk7C == 0x63);
    ow.unk6 = 0;
    ow.ext.main_60.corner = 3;
    storm_owl_cyclone(&ow);
    assert(ow.unk17 == 5 && ow.unk15 == 0);
    ow.unk7C = 0x30;
    storm_owl_cyclone(&ow);
    assert(ow.unk7C == 0x2F && shot_objects[0].active == 0);
    ow.unk7C = 0x29;
    storm_owl_cyclone(&ow);
    assert(ow.unk7C == 0x28 && shot_objects[0].active == 0);
    storm_owl_cyclone(&ow);
    assert(ow.unk6 == 1 && ow.unk7C == 0x27 && shot_objects[2].id == 0x26 && shot_objects[0].unk2 == 0 && shot_objects[2].unk2 == 2 && shot_objects[3].active == 0);
    ow.unk7C = 1;
    storm_owl_cyclone(&ow);
    assert(ow.unk6 == 2 && ow.unk7C == 0x1E && shot_objects[5].active == 0x41);
    ow.unk7C = 2;
    storm_owl_cyclone(&ow);
    assert(ow.unk6 == 2 && ow.unk7C == 1);
    ow.ext.main_60.pattern = &storm_owl_pattern_0[2];
    g_Player.x_pos.i.hi = 0x900;
    storm_owl_cyclone(&ow);
    assert(ow.unk6 == 3 && ow.unk15 == PLAYER_FACING_RIGHT && ow.x_speed == FIXED(2) && ow.y_speed == FIXED(3));
    ow.x_speed = 0;
    ow.y_speed = 0;
    storm_owl_cyclone(&ow);
    assert(ow.unk5 == 8 && ow.unk6 == 3);
    ow.x_pos.i.hi = 0xB00;
    storm_owl_cyclone(&ow);
    assert(ow.unk5 == 5 && ow.unk6 == 0 && ow.ext.main_60.corner == 2);
}
static void sox_stagger(void)
{
    ow_reset(0xB, 0);
    ow.collision_data = (const u16*)D_80107B78;
    shot_objects[0].active = 0x41;
    shot_objects[0].id = 0x25;
    shot_objects[1].active = 0x41;
    shot_objects[1].id = 0x26;
    shot_objects[1].unk2 = 5;
    ow.ext.main_60.feather_mask = 3;
    storm_owl_stagger(&ow);
    assert(ow.unk6 == 1 && ow.unk7C == 0x28 && ow.unk17 == 0xC && ow.ext.main_60.feather_mask == 0 && shot_objects[0].active == 0 && shot_objects[1].active == 0x41);
    ow.unk6 = 2;
    storm_owl_stagger(&ow);
    assert(ow.unk5 == 0xB && ow.unk6 == 2);
    ow.x_pos.i.hi = 0x800;
    ow.ext.main_60.feather_mask = 1;
    storm_owl_stagger(&ow);
    assert(ow.unk5 == 0xB && ow.unk6 == 2);
    ow.ext.main_60.feather_mask = 0;
    storm_owl_stagger(&ow);
    assert(ow.unk5 == 5 && ow.unk6 == 0);
}
static void sox_ground_cyclone(void)
{
    ow_reset(0xC, 1);
    ow_floor(103);
    storm_owl_ground_cyclone(&ow);
    assert(ow.unk6 == 2 && ow.unk17 == 9 && ow.unk7C == 0x1E);
    background_objects[0].x_pos.i.hi = 0x900;
    background_objects[0].y_pos.i.hi = 0x600;
    ow.unk6 = 3;
    ow.unk7C = 1;
    g_Player.x_pos.i.hi = 0x9A0;
    storm_owl_ground_cyclone(&ow);
    assert(ow.unk6 == 4 && ow.unk7C == 0xA && visual_objects[0].x_pos.i.hi == 0x9A0 && visual_objects[1].x_pos.i.hi == 0x970 && visual_objects[2].x_pos.i.hi == 0x9D0 && visual_objects[2].y_pos.i.hi == 0x660);
    assert(shot_objects[0].id == 0x26 && shot_objects[0].unk2 == 5 && shot_objects[0].timer == 0x20 && shot_objects[2].x_pos.i.hi == 0x9D0 && shot_objects[2].timer == 0x28 && shot_objects[2].y_pos.i.hi == 0x750);
    ow_reset(9, 6);
    ow.unk7C = 2;
    ow.unk7E = 5;
    storm_owl_storm(&ow);
    assert(ow.unk6 == 6 && ow.unk7C == 1 && ow.unk7E == 0xA);
}
static void (*const sox_cases[])(void) = {
    sox_death,
    sox_start,
    sox_intro,
    sox_patrol_fly,
    sox_patrol_swoop,
    sox_grab,
    sox_reenter,
    sox_feather,
    sox_volley,
    sox_cyclone,
    sox_stagger,
    sox_ground_cyclone,
};
static u32 sox_run(u32 row)
{
    sox_cases[row]();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "owl_voice_timer", 0, 0, 3, test_owl_voice_timer },
    { "storm_owl_init_rain", 0, 0, COUNT(storm_owl_init_rain_cases), test_storm_owl_init_rain },
    { "storm_owl_states", 0, 0, COUNT(owl_cases), test_storm_owl_states },
    { "storm_owl_pattern_exhaustion", NULL, storm_owl_pattern_exhaustion_cases_expected, COUNT(storm_owl_pattern_exhaustion_cases_expected), script_case },
    { "func_8007651C", 0, 0, 6, test_func_8007651C },
    { "func_80078314", 0, 0, 1, test_func_80078314 },
    { "storm_owl_reenter_warp", 0, 0, 1, test_storm_owl_reenter_warp },
    { "storm_owl_spawn_hit_flash", 0, 0, 1, test_storm_owl_spawn_hit_flash },
    { "storm_owl_death_flash", storm_owl_death_flash_cases, storm_owl_death_flash_cases_expected, COUNT(storm_owl_death_flash_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "storm_owl_clear_shots_pool", storm_owl_clear_shots_pool_cases, storm_owl_clear_shots_pool_cases_expected, COUNT(storm_owl_clear_shots_pool_cases), 0 },
    { "feather_takeoff_center_approach_and_recovery_facing", NULL, NULL, 96, entry },
    { "release_height_stun_tracking_and_escape", NULL, NULL, COUNT(player_dx) * 16, swoop },
    { "own_Owl_storm_begin_nine_rain_ticks_then_full_partial_four_shot_pool", NULL, NULL, 18, rain },
    { "release_facing_and_center_vertical_four_pixel_edges", NULL, NULL, 30, owl },
    { "actual_floor_landing_arena_edges_facing_and_armor_damage", NULL, NULL, 48, slam },
    { "owl_damage", 0, 0, COUNT(owl_damage_cases), test_owl_damage },
    { "storm_owl_state_steps", NULL, NULL, COUNT(sox_cases), sox_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + COUNT(storm_owl_init_rain_cases) + COUNT(owl_cases) + COUNT(storm_owl_pattern_exhaustion_cases_expected) + 6 + 1 + 1 + 1 + COUNT(storm_owl_death_flash_cases) + COUNT(pool_full_cases) + COUNT(storm_owl_clear_shots_pool_cases) + 96 + COUNT(player_dx) * 16 + 18 + 30 + 48 + COUNT(owl_damage_cases) + COUNT(sox_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
