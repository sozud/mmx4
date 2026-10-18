#include "test_runtime.h"
#include "main/1EC20.h"

static u32 briefing_case(u32 mode)
{
    struct MiscObj linked, linked_expected, misc_expected[64];
    struct EffectObj effects_expected[32];
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    u8 script[2];
    u32 i, free_misc = mode == 3 ? 1 : mode == 4 ? 2
                                                 : 0;
    u32 free_effect = mode == 2 || mode == 4;
    u8 command = mode == 0 ? 0 : mode <= 4 ? 0x40
        : mode == 5                        ? 0xFF
        : mode == 6                        ? 7
                                           : 0x45;
    memset(&linked, 0, sizeof(linked));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - free_misc ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].unk7 = 5;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = i >= 32 - free_effect ? 0 : 1;
        effect_objects[i].id = 26;
        effect_objects[i].state = 7;
        effect_objects[i].unk2 = 4;
        effect_objects[i].x_pos.val = 70 * 65536 + 0x1234;
        effect_objects[i].y_pos.val = 80 * 65536 + 0x5678;
    }
    linked.active = 0x41;
    linked.id = 13;
    linked.unk2 = 1;
    linked.on_screen = 1;
    linked.state = 3;
    linked.unk5 = 4;
    linked.unk6 = 5;
    linked.unk7 = 6;
    linked.x_pos.val = 100 * 65536 + 0x1234;
    linked.y_pos.val = 200 * 65536 + 0x5678;
    linked_expected = linked;
    engine_expected = engine_obj;
    script[0] = command;
    script[1] = 0xFF;
    D_8013B80C = script;
    D_8013B808 = &linked;
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    memcpy(effects_expected, effect_objects, sizeof(effects_expected));
    if (command == 0x40) {
        if (free_effect) {
            effects_expected[31].active = 1;
            effects_expected[31].id = 3;
            effects_expected[31].unk2 = 0;
        }
        if (free_misc) {
            misc_expected[64 - free_misc].active = 0x41;
            misc_expected[64 - free_misc].id = 13;
            misc_expected[64 - free_misc].unk2 = 1;
        }
        if (free_misc == 2) {
            misc_expected[63].active = 0x41;
            misc_expected[63].id = 12;
            misc_expected[63].unk2 = 8;
            misc_expected[63].ext.pointer.unk50 = &misc_objects[62];
        }
    } else if (mode >= 6) {
        engine_expected.unk40 = command & 0x3F;
        if (mode == 7)
            memset(&linked_expected, 0, 8);
    }
    func_8002F048();
    assert(D_8013B80C == script + (mode == 5 ? 0 : 1));
    assert(D_8013B808 == (command == 0x40 ? (free_misc ? &misc_objects[64 - free_misc] : NULL) : &linked));
    assert(script[0] == command && script[1] == 0xFF);
    for (i = 0; i < sizeof(linked) / 4; i++)
        assert(((u32*)&linked)[i] == ((u32*)&linked_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(misc_expected) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)misc_expected)[i]);
    for (i = 0; i < sizeof(effects_expected) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)effects_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    i = (D_8013B80C - script) | ((u32)(u8)misc_objects[63].id << 8) | ((u32)(u8)effect_objects[31].id << 16) | ((u32)(u8)linked.active << 24);
    return i;
}
#define CASE(m)                                         \
    static u32 briefing_script_pools_briefing_##m(void) \
    {                                                   \
        return briefing_case(m);                        \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) briefing_script_pools_briefing_##m,
static const CTestCase briefing_script_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 briefing_script_pools_cases_expected[] = { 0x411A2701u, 0x411A2701u, 0x41032701u, 0x411A0D01u, 0x41030C01u, 0x411A2700u, 0x411A2701u, 0x1A2701u };
#undef CASE
#undef ENTRY

static struct RouteInput {
    u16 held;
    s8 selection;
    u8 progress;
};
static const struct RouteInput inputs[] = {
    { PADLup | PADLright, 0, 4 },
    { PADLup, 0, 4 },
    { PADLup, 4, 4 },
    { PADLup, 8, 5 },
    { PADLup, 0, 5 },
    { PADLdown, 0, 5 },
    { PADLdown, 4, 5 },
    { PADLdown, 4, 4 },
    { PADLright, 3, 4 },
    { PADLleft, 0, 4 },
    { PADLleft, 1, 4 },
};
static u32 route_case(u32 mode, u32 observation)
{
    struct EngineObj obj, before;
    struct PlayerObj player_before;
    struct BackgroundObj bg_before[3];
    struct ControllerInput input_before;
    u32 i, actual;
    const struct RouteInput* input = &inputs[mode];
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&controller_input, 0, sizeof(controller_input));
    controller_input.held = controller_input.previous = input->held;
    obj.unk3 = input->selection;
    obj.unk5F = input->progress;
    obj.unkA = 3;
    obj.stage = 7;
    obj.substage = 2;
    obj.unk1 = 3;
    obj.unk2 = 4;
    obj.cur_character = 1;
    D_8013E198[5] = -1;
    D_8013B814 = 0x27;
    before = obj;
    player_before = g_Player;
    input_before = controller_input;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    func_8002E994(&obj);
    before.unk3 = obj.unk3;
    before.unk8 = obj.unk8;
    before.unkA = obj.unkA;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(controller_input.held == input_before.held && controller_input.previous == input_before.previous && controller_input.pressed == input_before.pressed);
    assert(D_8013E198[5] == -1 && D_8013B814 == 0x27);
    actual = observation == 0 ? (u8)obj.unk3 : (u16)obj.unk8 | ((u32)(u16)obj.unkA << 16);
    return actual;
}
#define CASE(m, n)                                            \
    static u32 mission_route_navigation_route_##m##_##n(void) \
    {                                                         \
        return route_case(m, n);                              \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
MODE(5)
MODE(6)
MODE(7)
MODE(8)
MODE(9)
MODE(10)
#define ENTRY(m, n) mission_route_navigation_route_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase mission_route_navigation_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) ENTRIES(5) ENTRIES(6) ENTRIES(7) ENTRIES(8) ENTRIES(9) ENTRIES(10) };
static const u32 mission_route_navigation_cases_expected[] = { 0x0u, 0x0u, 0x0u, 0x4000Au, 0x0u, 0x4000Au, 0x0u, 0x4000Au, 0x0u, 0x4000Au, 0x8u, 0x4000Au, 0x4u, 0x4000Au, 0x4u, 0x4000Au, 0x3u, 0x4000Au, 0x0u, 0x4000Au, 0x0u, 0x4000Au };
#undef controller_input
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 mission_case(u32 mode)
{
    struct EngineObj obj, expected;
    struct EffectObj owner, owner_before;
    struct MiscObj pool[64];
    struct PlayerObj player_before = g_Player;
    u32 i, available = mode == 0 || mode == 5 ? 3 : mode - 1;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - available ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 7;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    owner.active = 1;
    owner.id = 2;
    owner.state = mode == 0 ? 1 : mode == 5 ? 3
                                            : 2;
    obj.state = 3;
    obj.unk1 = 3;
    obj.unk2 = 2;
    obj.unk3 = 7;
    obj.stage = 13;
    obj.unk3C = &owner;
    expected = obj;
    owner_before = owner;
    memcpy(pool, misc_objects, sizeof(pool));
    if (mode != 0 && mode != 5) {
        expected.unk1 = 4;
        for (i = 0; i < available; i++) {
            pool[64 - available + i].active = 0x41;
            pool[64 - available + i].id = i == 2 ? 0xC : 0xF;
            pool[64 - available + i].unk2 = i == 2 ? 9 : i;
        }
    }
    func_8002E8D4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return obj.unk1 | ((u32)(u8)misc_objects[63].id << 8) | ((u32)(u8)misc_objects[63].unk2 << 16);
}
#define CASE(m)                                                \
    static u32 mission_select_spawn_prefixes_mission_##m(void) \
    {                                                          \
        return mission_case(m);                                \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) mission_select_spawn_prefixes_mission_##m,
static const CTestCase mission_select_spawn_prefixes_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 mission_select_spawn_prefixes_cases_expected[] = { 0x72703u, 0x72704u, 0xF04u, 0x10F04u, 0x90C04u, 0x72703u };
#undef CASE
#undef ENTRY

struct func_8002E7BC_case {
    u32 pool_0_full, pool_1_full;
    u32 expected[11];
};
static const struct func_8002E7BC_case func_8002E7BC_cases[] = {
    { 255, 0, { 1u, 0x110u, 0xFFFFFF81u, 1u, 0u, 1u, 0u, 0u, 1u, 0u, 8u } },
    { 0, 255, { 1u, 0x110u, 1u, 0u, 0u, 0x41u, 0xDu, 0u, 1u, 0u, 8u } },
};
static u32 test_func_8002E7BC(u32 row)
{
    const struct func_8002E7BC_case* c = &func_8002E7BC_cases[row];
    u32 observed_values[11];
    struct EngineObj obj;
    u8 pool_0_full;
    u8 pool_1_full;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(&misc_objects, 0, sizeof(misc_objects));
    controller_input.pressed = 64;
    pool_0_full = c->pool_0_full;
    pool_1_full = c->pool_1_full;
    obj.unk5F = 6;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            g_QuadObjects[slot].active = pool_1_full ? 1 : 0;
    }
    func_8002E7BC(&obj);
    observed_values[0] = (u32)background_objects[0].unk4C;
    observed_values[1] = (u32)background_objects[0].y_pos.i.hi;
    observed_values[2] = (u32)g_QuadObjects[0].active;
    observed_values[3] = (u32)g_QuadObjects[0].id;
    observed_values[4] = (u32)g_QuadObjects[0].unk2;
    observed_values[5] = (u32)misc_objects[0].active;
    observed_values[6] = (u32)misc_objects[0].id;
    observed_values[7] = (u32)misc_objects[0].unk2;
    observed_values[8] = (u32)obj.unk1;
    observed_values[9] = (u32)obj.unk2;
    observed_values[10] = (u32)obj.unk3;
    return c_test_observe(0, row, observed_values, c->expected, 11);
}
#undef controller_input

const struct CTestGroup c_test_groups[] = {
    { "briefing_script_pools", briefing_script_pools_cases, briefing_script_pools_cases_expected, COUNT(briefing_script_pools_cases), 0 },
    { "mission_route_navigation", mission_route_navigation_cases, mission_route_navigation_cases_expected, COUNT(mission_route_navigation_cases), 0 },
    { "mission_select_spawn_prefixes", mission_select_spawn_prefixes_cases, mission_select_spawn_prefixes_cases_expected, COUNT(mission_select_spawn_prefixes_cases), 0 },
    { "func_8002E7BC", 0, 0, 2, test_func_8002E7BC },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(briefing_script_pools_cases) + COUNT(mission_route_navigation_cases) + COUNT(mission_select_spawn_prefixes_cases) + 2;
