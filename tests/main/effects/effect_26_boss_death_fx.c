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

const struct CTestGroup c_test_groups[] = {
    { "boss_death_quad_allocation_steps", NULL, boss_death_quad_allocation_steps_cases_expected, COUNT(boss_death_quad_allocation_steps_cases_expected), death_case },
    { "normal_burst_and_sixteen_ray_transitions_full_partial_available_quads", NULL, NULL, 6, late_quads },
    { "boss_death_actual_spark_angles_zero_to_three_quad_slots", NULL, NULL, 12, spark },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(boss_death_quad_allocation_steps_cases_expected) + 6 + 12;
