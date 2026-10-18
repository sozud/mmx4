#include "test_runtime.h"
#include "main/effects/effect_24_boss_warning.h"

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

const struct CTestGroup c_test_groups[] = {
    { "boss_warning", boss_warning_cases, boss_warning_cases_expected, COUNT(boss_warning_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(boss_warning_cases);
