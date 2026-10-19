#include "test_runtime.h"
#include "main/effects/effect_24_boss_warning.h"
#include "main/mains/main_69_colonel.h"

#define WARNING_CASE(name, id_value, active_value, last_phase, field)            \
    static u32 name(void)                                                        \
    {                                                                            \
        struct EffectObj controller, spawned, tiles[22];                         \
        u32 i, actual;                                                           \
        memset(&controller, 0, sizeof(controller));                              \
        memset(&spawned, 0, sizeof(spawned));                                    \
        controller.unk5 = 7;                                                     \
        controller.ext.effect_24.unk1B = 21;                                     \
        controller.ext.effect_24.spawned_effect = &spawned;                      \
        spawned.id = id_value;                                                   \
        spawned.active = active_value;                                           \
        for (i = 0; i < COUNT(tiles); i++) {                                     \
            tiles[i].unk5 = (i == COUNT(tiles) - 1) ? last_phase : 1;            \
            boss_warning_tiles[i] = &tiles[i];                                   \
        }                                                                        \
        boss_warning_wait_tiles(&controller);                                    \
        for (i = 0; i < COUNT(tiles); i++) {                                     \
            assert(boss_warning_tiles[i] == &tiles[i]);                          \
            assert(tiles[i].unk5 == ((i == COUNT(tiles) - 1) ? last_phase : 1)); \
        }                                                                        \
        actual = (u32)controller.field;                                          \
        return actual;                                                           \
    }
WARNING_CASE(other_id_phase, 3, 1, 1, unk5)
WARNING_CASE(other_id_index, 3, 1, 1, ext.effect_24.unk1B)
WARNING_CASE(inactive_phase, 4, 0, 1, unk5)
WARNING_CASE(inactive_index, 4, 0, 1, ext.effect_24.unk1B)
WARNING_CASE(active_phase, 4, 1, 1, unk5)
WARNING_CASE(active_index, 4, 1, 1, ext.effect_24.unk1B)
WARNING_CASE(last_pending_phase, 4, 0, 0, unk5)
WARNING_CASE(last_pending_index, 4, 0, 0, ext.effect_24.unk1B)

static const CTestCase boss_warning_cases[] = {
    other_id_phase,
    other_id_index,
    inactive_phase,
    inactive_index,
    active_phase,
    active_index,
    last_pending_phase,
    last_pending_index,
};
static const u32 boss_warning_cases_expected[] = { 0x8u, 0x0u, 0x8u, 0x0u, 0x7u, 0x15u, 0x7u, 0x15u };
#undef WARNING_CASE

static struct EffectObj expected_effects[32];
static struct QuadObj expected_quads[32];
static struct EffectObj* tiles[22];
static u32 full(u32 row)
{
    struct MainObj colonel;
    struct EffectObj* obj = &effect_objects[0];
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    engine_obj.stage = 10;
    engine_obj.substage = 0;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 1; i < COUNT(effect_objects); i++)
        effect_objects[i].active = i == 31 && row ? 0 : 1;
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = 1;
    memcpy(expected_quads, g_QuadObjects, sizeof(expected_quads));
    memcpy(tiles, boss_warning_tiles, sizeof(tiles));
    memset(&colonel, 0, sizeof(colonel));
    colonel.active = 0x41;
    colonel.id = 69;
    colonel.x_pos.i.hi = 4688;
    colonel.y_pos.i.hi = 928;
    colonel_spawn_warning(&colonel);
    assert(colonel.ext.main_69.effect == obj && obj->active == 1 && obj->id == 24 && colonel.unk5 == 1);
    player = g_Player;
    engine = engine_obj;
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    expected_effects[0].state = 1;
    expected_effects[0].ext.effect_24.unk1A = 5;
    if (row) {
        expected_effects[31].active = 1;
        expected_effects[31].id = 4;
        expected_effects[0].ext.effect_24.spawned_effect = &effect_objects[31];
    }
    cur_random = 0x1234;
    boss_warning_update(obj);
    if (row)
        func_800BAC58(obj);
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    c_test_same_words(g_QuadObjects, expected_quads, sizeof(expected_quads));
    c_test_same_words(boss_warning_tiles, tiles, sizeof(tiles));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "boss_warning", boss_warning_cases, boss_warning_cases_expected, COUNT(boss_warning_cases), 0 },
    { "Colonel_actual_warning_factory_full_effect_or_full_quad_pool", NULL, NULL, 2, full },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(boss_warning_cases) + 2;
