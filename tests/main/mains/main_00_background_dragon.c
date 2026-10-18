#include "test_runtime.h"
#include "main/mains/main_00_background_dragon.h"
extern u8 background_dragon_attack_map[128];
void background_dragon_spawn_trail(struct PlayerObj*, s8);
void background_dragon_multi_shot_update(struct MainObj*);

static struct DragonInput {
    s16 index;
    u16 seed;
    u8 raw_kind;
};
static const struct DragonInput inputs[] = {
    { -1, 0, 0 },
    { 32, 3, 0 },
    { 104, 3, 0 },
    { 0, 1, 9 },
    { 0, 2, 9 },
    { 0, 3, 9 },
};
static u32 dragon_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u8 map_before[128];
    u8* ext;
    const struct DragonInput* input = &inputs[mode];
    s32 choice;
    u32 i, hash = 2166136261U;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.state = 1;
    obj.unk2 = 0x27;
    obj.x_pos.val = (input->index < 0 ? 100 : (80 + input->index) * 16) * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.x_pos = obj.x_pos;
    cur_random = input->seed;
    memcpy(map_before, background_dragon_attack_map, sizeof(map_before));
    assert(map_before[32] == 0 && map_before[104] == 8);
    if (input->raw_kind)
        background_dragon_attack_map[input->index] = input->raw_kind;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    choice = func_80040ABC(&obj);
    ext = (u8*)&obj.ext;
    before.unk2 = obj.unk2;
    ((u8*)&before.ext)[1] = ext[1];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < COUNT(map_before); i++) {
        assert(background_dragon_attack_map[i] == (input->raw_kind && i == input->index ? input->raw_kind : map_before[i]));
        background_dragon_attack_map[i] = map_before[i];
        hash = (hash ^ background_dragon_attack_map[i]) * 16777619U;
    }
    if (observation == 0)
        return choice;
    if (observation == 1)
        return (u8)obj.unk2 | ((u32)ext[1] << 8);
    if (observation == 2)
        return cur_random;
    return hash;
}
#define CASE(m, n)                                          \
    static u32 dragon_attack_context_dragon_##m##_##n(void) \
    {                                                       \
        return dragon_case(m, n);                           \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2) CASE(m, 3)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
#define ENTRY(m, n) dragon_attack_context_dragon_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3)
static const CTestCase dragon_attack_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) };
static const u32 dragon_attack_context_cases_expected[] = { 0xCu, 0x0u, 0x0u, 0x13D3C53Eu, 0x5u, 0x1u, 0x3u, 0x13D3C53Eu, 0xCu, 0x1u, 0x3u, 0x13D3C53Eu, 0x3u, 0x301u, 0x1u, 0x13D3C53Eu, 0x5u, 0x0u, 0x2u, 0x13D3C53Eu, 0x2u, 0x1u, 0x3u, 0x13D3C53Eu };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 background_dragon_spawn_trail_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_background_dragon_spawn_trail(u32 row)
{
    u32 observed_values[9];
    struct PlayerObj obj;
    u8 pool_0_full;
    s8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    background_dragon_spawn_trail(&obj, arg1);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].state;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].unk5;
    observed_values[8] = (u32)visual_objects[0].unk6;
    return c_test_observe(0, row, observed_values, background_dragon_spawn_trail_expected, 9);
}

#include "support/pool_full.h"

static u32 pool_full_background_dragon_visual(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    background_dragon_multi_shot_update(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    pf_expected.on_screen = 1;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_background_dragon_shot(void)
{
    u32 actual;
    pf_prepare();
    pf_event(2, 1);
    pf_snapshot();
    background_dragon_multi_shot_update(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    pf_expected.on_screen = 1;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_background_dragon_visual,
    pool_full_background_dragon_shot,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "dragon_attack_context", dragon_attack_context_cases, dragon_attack_context_cases_expected, COUNT(dragon_attack_context_cases), 0 },
    { "background_dragon_spawn_trail", 0, 0, 1, test_background_dragon_spawn_trail },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dragon_attack_context_cases) + 1 + COUNT(pool_full_cases);
