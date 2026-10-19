#include "test_runtime.h"

#include "support/state_cases.h"
void stage_music_load(struct EffectObj*);

#define MUSIC(step, stage_id, sub, loading, played, setup)                                                                                          \
    do {                                                                                                                                            \
        u8 stage = engine_obj.stage, substage = engine_obj.substage, busy = D_80173C84, seen = D_80171EA8, mode = D_801406AC, pending = D_8013BD40; \
        state_reset(step, 0, 0);                                                                                                                    \
        state_room.effect.active = 1;                                                                                                               \
        state_room.effect.state = 1;                                                                                                                \
        engine_obj.stage = stage_id;                                                                                                                \
        engine_obj.substage = sub;                                                                                                                  \
        D_80173C84 = loading;                                                                                                                       \
        D_80171EA8 = played;                                                                                                                        \
        setup;                                                                                                                                      \
        stage_music_load(&state_room.effect);                                                                                                       \
        engine_obj.stage = stage;                                                                                                                   \
        engine_obj.substage = substage;                                                                                                             \
        D_80173C84 = busy;                                                                                                                          \
        D_80171EA8 = seen;                                                                                                                          \
        D_801406AC = mode;                                                                                                                          \
        D_8013BD40 = pending;                                                                                                                       \
    } while (0)
static void smu_busy(void)
{
    MUSIC(0, 3, 1, 1, 0, 0);
}
static void smu_highway_first(void) { MUSIC(0, 0xA, 0, 0, 0, 0); }
static void smu_highway_again(void) { MUSIC(0, 0xA, 0, 0, 1, 0); }
static void smu_fortress(void) { MUSIC(0, 0xC, 1, 0, 0, 0); }
static void smu_played(void) { MUSIC(0, 3, 0, 0, 1, 0); }
static void smu_stage(void) { MUSIC(0, 3, 1, 0, 0, 0); }
static void smu_intro(void) { MUSIC(0, 3, 0, 0, 0, 0); }
static void smu_wait(void) { MUSIC(2, 3, 1, 0, 0, (D_801406AC = 1, D_8013BD40 = 0)); }
static void smu_ready(void) { MUSIC(2, 3, 1, 0, 0, (D_801406AC = 2, D_8013BD40 = 0)); }
static void smu_pending(void) { MUSIC(2, 3, 1, 0, 0, (D_801406AC = 2, D_8013BD40 = 1)); }
static void smu_done(void) { MUSIC(3, 3, 1, 0, 0, 0); }

static void (*const stage_music_load_states_cases[])(void) = {
    smu_busy,
    smu_highway_first,
    smu_highway_again,
    smu_fortress,
    smu_played,
    smu_stage,
    smu_intro,
    smu_wait,
    smu_ready,
    smu_pending,
    smu_done,
};
static const u32 stage_music_load_states_expected[] = { 1u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x101u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x101u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x201u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x201u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x302u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_stage_music_load_states(u32 row)
{
    return object_run(stage_music_load_states_cases[row], row, &stage_music_load_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "stage_music_load_states", 0, 0, COUNT(stage_music_load_states_cases), test_stage_music_load_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stage_music_load_states_cases);
