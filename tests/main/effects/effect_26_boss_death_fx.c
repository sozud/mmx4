#include "test_runtime.h"
#include "main/effects/effect_26_boss_death_fx.h"

static u32 death_case(u32 available)
{
    static const u8 variants[] = { 24, 2, 13 };
    struct EffectObj obj, expected;
    struct QuadObj pool[32];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    for (i = 0; i < 32; i++) {
        g_QuadObjects[i].active = i >= 32 - available ? 0 : 1;
        g_QuadObjects[i].id = 39;
        g_QuadObjects[i].state = 40;
        g_QuadObjects[i].unk2 = 9;
        g_QuadObjects[i].unk5 = 3;
        g_QuadObjects[i].unk6 = 4;
        g_QuadObjects[i].unk7 = 5;
        g_QuadObjects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        g_QuadObjects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    obj.active = 1;
    obj.id = 26;
    obj.state = 0;
    obj.unk5 = 7;
    obj.unk2 = 9;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    expected = obj;
    memcpy(pool, g_QuadObjects, sizeof(pool));
    cur_random = 119;
    expected.unk2 = 24;
    expected.state = 1;
    expected.ext.effect_26.timer = 8;
    expected.ext.effect_26.quad_timer = 4;
    for (i = 0; i < available; i++) {
        struct QuadObj* child = &pool[32 - available + i];
        child->active = 1;
        child->id = 4;
        child->unk2 = variants[i];
        child->x_pos.u.hi = 100;
        child->y_pos.u.hi = 200;
    }
    boss_death_fx_init(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)g_QuadObjects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == 376);
    return (u8)obj.unk2 | ((u32)(u8)g_QuadObjects[29].unk2 << 8) | ((u32)(u8)g_QuadObjects[30].unk2 << 16) | ((u32)(u8)g_QuadObjects[31].unk2 << 24);
}
static const u32 boss_death_quad_allocation_steps_cases_expected[] = { 0x9090918u, 0x18090918u, 0x2180918u, 0xD021818u };

void boss_death_fx_burst(struct EffectObj*);
void boss_death_fx_rays(struct EffectObj*);
static struct QuadObj expected_pool[32];
static u32 late_quads(u32 row)
{
    struct EffectObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 rays = row % 2, available = row / 2 == 2 ? 16 : row / 2, spawned = rays ? available : available != 0, i;
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(expected_pool, g_QuadObjects, sizeof(expected_pool));
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 26;
    obj.state = rays ? 3 : 2;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    expected = obj;
    expected.state++;
    if (!rays)
        expected.ext.effect_26.timer = 10;
    cur_random = 0x1234;
    for (i = 0; i < spawned; i++) {
        struct QuadObj* q = &expected_pool[32 - available + i];
        q->active = 1;
        q->id = rays ? 6 : 8;
        q->x_pos.i.hi = 160;
        q->y_pos.i.hi = 120;
        if (rays)
            q->unk6 = i;
    }
    if (rays)
        boss_death_fx_rays(&obj);
    else
        boss_death_fx_burst(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(g_QuadObjects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == 0x1234);
    return 1;
}

static struct QuadObj expected_pool_boss_death_spark_capacity[32];
static struct VisualObj visuals_before[32];
static struct EffectObj effects_before[32];
static u32 spark(u32 row)
{
    struct EffectObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 available = row % 4, angle = row / 4 * 15, i;
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(expected_pool_boss_death_spark_capacity, g_QuadObjects, sizeof(expected_pool_boss_death_spark_capacity));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    memcpy(effects_before, effect_objects, sizeof(effects_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 26;
    obj.state = 1;
    obj.unk2 = angle;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.ext.effect_26.timer = 1;
    expected = obj;
    expected.ext.effect_26.timer = 0;
    cur_random = 119;
    for (i = 0; i < available; i++) {
        struct QuadObj* q = &expected_pool_boss_death_spark_capacity[32 - available + i];
        q->active = 1;
        q->id = 4;
        q->unk2 = (angle + (i == 0 ? 0 : i == 1 ? 10
                                                : 21))
            & 31;
        q->x_pos.i.hi = 160;
        q->y_pos.i.hi = 120;
    }
    func_800BB364(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(g_QuadObjects, expected_pool_boss_death_spark_capacity, sizeof(expected_pool_boss_death_spark_capacity));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    c_test_same_words(effect_objects, effects_before, sizeof(effects_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == 376);
    return 1;
}

#include "main/1AC84.h"
void func_800BB750(struct EffectObj*);
void boss_death_fx_finish(struct EffectObj*);
static struct EffectObj ef;
static void ef_reset(u8 state, u16 timer, u8 quad_timer, u16 seed, u32 free_quads)
{
    u32 i;
    memset(&ef, 0, sizeof(ef));
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = i < free_quads ? 0 : 1;
    ef.active = 1;
    ef.id = 26;
    ef.state = state;
    ef.x_pos.i.hi = 0xA0;
    ef.y_pos.i.hi = 0x78;
    ef.ext.effect_26.timer = timer;
    ef.ext.effect_26.quad_timer = quad_timer;
    cur_random = seed;
}
#define EF_SEEN(q) ((u8)ef.state | (u32)(u8)ef.ext.effect_26.timer << 8 | (u32)ef.ext.effect_26.quad_timer << 16 | (u32)(u8)g_QuadObjects[q].id << 24)
static u32 bd_burst_ray(void)
{
    ef_reset(2, 5, 3, 0x1234, 32);
    boss_death_fx_update(&ef);
    assert(g_QuadObjects[0].active == 1 && g_QuadObjects[0].unk2 == 0x0D && g_QuadObjects[0].x_pos.i.hi == 0xA0 && g_QuadObjects[0].y_pos.i.hi == 0x78);
    assert(g_QuadObjects[1].active == 0 && cur_random == 0xA30D);
    return EF_SEEN(0);
}
static u32 bd_burst_ray_full(void)
{
    ef_reset(2, 5, 3, 0x1234, 0);
    boss_death_fx_update(&ef);
    assert(cur_random == 0x366A);
    return EF_SEEN(0);
}
static u32 bd_rays_explosion(void)
{
    u32 i, explosions = 0;
    ef_reset(3, 0, 1, 0x1235, 32);
    ef.ext.effect_9.transition_timer = 5;
    boss_death_fx_update(&ef);
    for (i = 0; i < COUNT(visual_objects); i++)
        explosions += visual_objects[i].active != 0;
    assert(ef.ext.effect_9.transition_timer == 4);
    return EF_SEEN(0) ^ explosions << 28;
}
static u32 bd_sparks_end(void)
{
    ef_reset(1, 0, 3, 0x1234, 32);
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 7;
    engine_obj.unk42 = 5;
    func_800BB364(&ef);
    assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0 && engine_obj.unk42 == 0);
#ifdef MMX4_SATURN
    assert(D_8013E188[0] == 0x7F);
#else
    assert(D_8013E188[0] == -1 && D_8013E188[1] == -1 && D_8013E188[2] == -1 && D_8013E188[3] == -1);
#endif
    return EF_SEEN(2);
}
static u32 bd_whiteout_count(void)
{
    ef_reset(4, 0, 3, 0x1235, 32);
    g_FilterAmountR = 3;
    func_800BB750(&ef);
    assert(g_FilterAmountR == 3 && g_QuadObjects[0].active == 0);
    return EF_SEEN(0);
}
static u32 bd_whiteout_step(void)
{
    ef_reset(4, 4, 3, 0x100, 32);
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    func_800BB750(&ef);
    assert(g_FilterAmountR == 1 && g_FilterAmountG == 0x20 && g_FilterAmountB == 0x400);
    assert(g_QuadObjects[0].active == 1 && g_QuadObjects[0].x_pos.i.hi == 0xA0);
    return EF_SEEN(0);
}
static u32 bd_whiteout_boss(void)
{
    ef_reset(4, 4, 3, 0x1235, 32);
    ef.active = 0x81;
    engine_obj.enable_boss = 1;
    g_FilterAmountR = 0x1E;
    func_800BB750(&ef);
    assert(ef.unk7 == 1 && engine_obj.enable_boss == 0 && g_FilterAmountR == 0x1F);
    return EF_SEEN(0);
}
static u32 bd_finish_boss(void)
{
    ef_reset(7, 0, 0, 0, 32);
    ef.active = 0x81;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.script_state = 1;
    engine_obj.gameplay_locked = 0;
    boss_death_fx_finish(&ef);
    assert(g_Player.script_state == 1 && engine_obj.gameplay_locked == 1 && ef.active == 0);
    return EF_SEEN(0);
}
static const CTestCase boss_death_paths_cases[] = {
    bd_burst_ray,
    bd_burst_ray_full,
    bd_rays_explosion,
    bd_sparks_end,
    bd_whiteout_count,
    bd_whiteout_step,
    bd_whiteout_boss,
    bd_finish_boss,
};
static const u32 boss_death_paths_cases_expected[] = { 0x4020402u, 0x20402u, 0x14040403u, 0x4036402u, 0x20104u, 0x6020504u, 0x2C805u, 0u };

const struct CTestGroup c_test_groups[] = {
    { "boss_death_quad_allocation_steps", NULL, boss_death_quad_allocation_steps_cases_expected, COUNT(boss_death_quad_allocation_steps_cases_expected), death_case },
    { "normal_burst_and_sixteen_ray_transitions_full_partial_available_quads", NULL, NULL, 6, late_quads },
    { "boss_death_actual_spark_angles_zero_to_three_quad_slots", NULL, NULL, 12, spark },
    { "boss_death_paths", boss_death_paths_cases, boss_death_paths_cases_expected, COUNT(boss_death_paths_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(boss_death_quad_allocation_steps_cases_expected) + 6 + 12 + COUNT(boss_death_paths_cases);
