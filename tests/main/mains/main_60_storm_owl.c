#include "test_runtime.h"
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
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(cur_random == 0 && sentinel[0] == 0x27 && sentinel[1] == 0x28 && sentinel[2] == 0x29 && sentinel[3] == 0xFF);
    for (i = 0; i < 12; i++)
        assert(((u8*)storm_owl_pattern_weights)[i] == (mode == 1 && i < 3 ? 0 : ((u8*)weights_before)[i]));
    result = mode == 0 ? *obj.ext.main_60.pattern : 0x100 | *obj.ext.main_60.pattern;
    return result;
}
#define CASE(m)                                              \
    static u32 storm_owl_pattern_exhaustion_script_##m(void) \
    {                                                        \
        return script_case(m);                               \
    }
CASE(0)
CASE(1)
#define ENTRY(m) storm_owl_pattern_exhaustion_script_##m,
static const CTestCase storm_owl_pattern_exhaustion_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 storm_owl_pattern_exhaustion_cases_expected[] = { 0xCu, 0x127u };
#undef CASE
#undef ENTRY

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
    obj.unk15 = c->unk15;
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
    observed_values[6] = (u32)visual_objects[0].unk15;
    observed_values[7] = (u32)visual_objects[0].unk16;
    observed_values[8] = (u32)visual_objects[0].unk2;
    observed_values[9] = (u32)visual_objects[0].unk40;
    observed_values[10] = (u32)visual_objects[0].unk42;
    observed_values[11] = (u32)visual_objects[0].unk5C.fields.mode;
    observed_values[12] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[13] = (u32)visual_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_80078314_expected, 14);
}

static const u32 storm_owl_death_explode_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 2u, 0u, 5u };
static u32 test_storm_owl_death_explode(u32 row)
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
    storm_owl_death_explode(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.i.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.i.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, storm_owl_death_explode_expected, 9);
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
    observed_values[1] = (u32)obj.unk15;
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
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    storm_owl_spawn_hit_flash(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].unk15;
    observed_values[4] = (u32)visual_objects[0].unk16;
    observed_values[5] = (u32)visual_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].unk40;
    observed_values[7] = (u32)visual_objects[0].unk42;
    observed_values[8] = (u32)visual_objects[0].x_pos.val;
    observed_values[9] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, storm_owl_spawn_hit_flash_expected, 10);
}

struct storm_owl_storm_rain_again_case {
    u32 storm_timer;
    u32 expected[3];
};
static const struct storm_owl_storm_rain_again_case storm_owl_storm_rain_again_cases[] = {
    { 0, { 1u, 0u, 0x14u } },
    { 127, { 0x80u, 1u, 0x3Cu } },
};
static u32 test_storm_owl_storm_rain_again(u32 row)
{
    const struct storm_owl_storm_rain_again_case* c = &storm_owl_storm_rain_again_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7C = 1;
    obj.ext.main_60.storm_timer = c->storm_timer;
    storm_owl_storm_rain_again(&obj);
    observed_values[0] = (u32)obj.ext.main_60.storm_timer;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 3);
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
const struct CTestGroup c_test_groups[] = {
    { "storm_owl_pattern_exhaustion", storm_owl_pattern_exhaustion_cases, storm_owl_pattern_exhaustion_cases_expected, COUNT(storm_owl_pattern_exhaustion_cases), 0 },
    { "func_8007651C", 0, 0, 6, test_func_8007651C },
    { "func_80078314", 0, 0, 1, test_func_80078314 },
    { "storm_owl_death_explode", 0, 0, 1, test_storm_owl_death_explode },
    { "storm_owl_reenter_warp", 0, 0, 1, test_storm_owl_reenter_warp },
    { "storm_owl_spawn_hit_flash", 0, 0, 1, test_storm_owl_spawn_hit_flash },
    { "storm_owl_storm_rain_again", 0, 0, 2, test_storm_owl_storm_rain_again },
    { "storm_owl_death_flash", storm_owl_death_flash_cases, storm_owl_death_flash_cases_expected, COUNT(storm_owl_death_flash_cases), 0 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "storm_owl_clear_shots_pool", storm_owl_clear_shots_pool_cases, storm_owl_clear_shots_pool_cases_expected, COUNT(storm_owl_clear_shots_pool_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(storm_owl_pattern_exhaustion_cases) + 6 + 1 + 1 + 1 + 1 + 2 + COUNT(storm_owl_death_flash_cases) + COUNT(pool_full_cases) + COUNT(storm_owl_clear_shots_pool_cases);
