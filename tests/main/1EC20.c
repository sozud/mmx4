#include "test_runtime.h"
#include "main/323C.h"
#include "main/55C4.h"
#include "main/3D88.h"
extern u8 mission_palette_order[8];
void func_8002F2A0(struct EngineObj* arg0);
#include "main/1EC20.h"
#ifdef MMX4_PC
#include <unistd.h>
#include <stdlib.h>
#include <psyz/cd.h>
#include <psyz/spu.h>
#include "archive_memory.h"
#endif

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
static const u32 briefing_script_pools_cases_expected[] = { 0x411A2701u, 0x411A2701u, 0x41032701u, 0x411A0D01u, 0x41030C01u, 0x411A2700u, 0x411A2701u, 0x1A2701u };

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
static const u32 mission_route_navigation_cases_expected[] = { 0x0u, 0x0u, 0x0u, 0x4000Au, 0x0u, 0x4000Au, 0x0u, 0x4000Au, 0x0u, 0x4000Au, 0x8u, 0x4000Au, 0x4u, 0x4000Au, 0x4u, 0x4000Au, 0x3u, 0x4000Au, 0x0u, 0x4000Au, 0x0u, 0x4000Au };
static u32 mission_route_navigation_cases_row(u32 row)
{
    return route_case(row / 2, row % 2);
}

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
static const u32 mission_select_spawn_prefixes_cases_expected[] = { 0x72703u, 0x72704u, 0xF04u, 0x10F04u, 0x90C04u, 0x72703u };

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

static const struct {
    u8 character, stage, story, video, defeated;
    s8 fade;
    u8 expected_state, expected_step, expected_video;
} mission_entries[] = {
    { 0, 1, 4, 0, 0, 1, 3, 7, 0 },
    { 0, 11, 8, 0, 0, 0, 3, 8, 3 },
    { 0, 11, 9, 0, 0, 0, 4, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 4, 0, 0 },
    { 0, 1, 4, 0, 0, 0, 3, 11, 0 },
    { 0, 8, 4, 0, 0, 0, 3, 11, 0 },
    { 0, 1, 4, 0, 1, 0, 4, 0, 0 },
    { 0, 8, 4, 0, 0x80, 0, 4, 0, 0 },
    { 0, 9, 4, 0, 0, 0, 4, 0, 0 },
    { 1, 8, 3, 9, 0, 0, 3, 8, 4 },
    { 1, 8, 4, 9, 0, 0, 3, 11, 9 },
    { 1, 8, 3, 8, 0, 0, 3, 11, 8 },
    { 1, 9, 5, 0, 0, 0, 9, 0, 0 },
    { 1, 10, 5, 0, 0, 0, 4, 0, 0 },
    { 1, 0, 1, 0, 0, 0, 4, 0, 0 },
    { 1, 1, 4, 0, 1, 0, 4, 0, 0 },
    { 1, 8, 4, 0, 0, 0, 3, 11, 0 },
    { 0, 11, 8, 9, 0, 1, 3, 7, 9 },
};

static void mission_entry_reset(u8 character, u8 stage, u8 story, u8 video, u8 defeated, s8 fade)
{
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 3;
    engine_obj.unk1 = 7;
    engine_obj.unk2 = 4;
    engine_obj.unk3 = 5;
    engine_obj.cur_character = character;
    engine_obj.stage = stage;
    engine_obj.unk5F = story;
    engine_obj.unkE = video;
    engine_obj.palette_flags = defeated;
    main_bss_state.transition.active = fade;
    D_80141BD4 = 0;
}

static u32 test_mission_entry(u32 row)
{
#ifdef MMX4_PC
    unsetenv("MMX4_ORACLE_SCENE");
    unsetenv("MMX4_DIRECT_LOADOUT");
#endif
    mission_entry_reset(mission_entries[row].character, mission_entries[row].stage,
        mission_entries[row].story, mission_entries[row].video, mission_entries[row].defeated, mission_entries[row].fade);
    func_8002EDD4(&engine_obj);
    assert(engine_obj.state == mission_entries[row].expected_state);
    assert(engine_obj.unk1 == mission_entries[row].expected_step);
    assert(engine_obj.unkE == mission_entries[row].expected_video);
    assert(engine_obj.unk2 == (mission_entries[row].fade ? 4 : 0));
    assert(engine_obj.unk3 == (mission_entries[row].fade ? 5 : 0));
    assert(engine_obj.cur_character == mission_entries[row].character);
    assert(engine_obj.stage == mission_entries[row].stage);
    assert(engine_obj.unk5F == mission_entries[row].story);
    assert((u8)engine_obj.palette_flags == mission_entries[row].defeated);
    return (u8)engine_obj.unk1;
}

#ifdef MMX4_PC
static const struct {
    const char* scene;
    const char* loadout;
    u8 stage, expected_flags, expected_step;
} briefing_overrides[] = {
    { NULL, NULL, 1, 0xFF, 0 },
    { "other-scene", "2", 1, 0xFF, 0 },
    { "mission-briefing", NULL, 1, 0xFF, 0 },
    { "mission-briefing", "1", 1, 0xFF, 0 },
    { "mission-briefing", "2", 0, 0xFF, 0 },
    { "mission-briefing", "2", 9, 0xFF, 0 },
    { "mission-briefing", "2", 1, 0xFE, 11 },
    { "mission-briefing", "2", 8, 0x7F, 11 },
    { "mission-briefing", "0x2", 1, 0xFE, 11 },
    { "mission-briefing", "invalid", 1, 0xFF, 0 },
};

static u32 test_briefing_override(u32 row)
{
    int configured;
    unsetenv("MMX4_ORACLE_SCENE");
    unsetenv("MMX4_DIRECT_LOADOUT");
    if (briefing_overrides[row].scene) {
        configured = setenv("MMX4_ORACLE_SCENE", briefing_overrides[row].scene, 1);
        assert(configured == 0);
    }
    if (briefing_overrides[row].loadout) {
        configured = setenv("MMX4_DIRECT_LOADOUT", briefing_overrides[row].loadout, 1);
        assert(configured == 0);
    }
    mission_entry_reset(0, briefing_overrides[row].stage, 4, 0, 0xFF, 0);
    func_8002EDD4(&engine_obj);
    assert((u8)engine_obj.palette_flags == briefing_overrides[row].expected_flags);
    assert(engine_obj.unk1 == briefing_overrides[row].expected_step);
    assert(engine_obj.state == (briefing_overrides[row].expected_step == 11 ? 3 : 4));
    return (u8)engine_obj.palette_flags;
}
#define BRIEFING_OVERRIDE_COUNT COUNT(briefing_overrides)
#else
#define BRIEFING_OVERRIDE_COUNT 0
#endif

static const struct {
    u8 dialogue, video, story, free_misc, free_quads;
    u8 step, phase, route, next_story, stage, substage, icons, quads, fade;
} briefing_exits[] = {
    { 1, 0, 4, 1, 8, 9, 2, 0, 4, 6, 1, 0, 0, 0 },
    { 0x80, 0, 4, 1, 8, 9, 2, 0, 4, 6, 1, 0, 0, 0 },
    { 0xFF, 0, 4, 1, 8, 9, 3, 0, 4, 6, 1, 0, 0, 0 },
    { 0, 3, 4, 1, 8, 3, 0, 3, 6, 6, 1, 1, 8, 0 },
    { 0, 8, 4, 1, 8, 3, 0, 8, 6, 6, 1, 1, 8, 0 },
    { 0, 4, 4, 1, 8, 3, 0, 4, 8, 6, 1, 1, 8, 0 },
    { 0, 9, 4, 1, 8, 3, 0, 9, 8, 6, 1, 1, 8, 0 },
    { 0, 5, 4, 1, 8, 7, 0, 5, 1, 0, 0, 0, 0, 1 },
    { 0, 10, 4, 1, 8, 7, 0, 10, 1, 0, 0, 0, 0, 1 },
    { 0, 7, 4, 1, 8, 7, 0, 9, 4, 6, 1, 0, 0, 1 },
    { 0, 2, 4, 1, 8, 7, 0, 2, 4, 9, 0, 0, 0, 1 },
    { 0, 6, 2, 1, 8, 10, 0, 6, 2, 6, 1, 1, 0, 0 },
    { 0, 6, 4, 1, 8, 3, 0, 6, 4, 6, 1, 1, 8, 0 },
    { 0, 6, 4, 0, 0, 3, 0, 6, 4, 6, 1, 0, 0, 0 },
};

static u32 test_briefing_exit(u32 row)
{
    static u8 script[] = { 0, 0xFF };
    u32 i, icons = 0, quads = 0;
    mission_entry_reset(0, 6, briefing_exits[row].story, briefing_exits[row].video, 0, 0);
    engine_obj.unk1 = 9;
    engine_obj.unk2 = 2;
    engine_obj.unk3 = 3;
    engine_obj.substage = 1;
    abc_object.unkC = briefing_exits[row].dialogue;
    D_8013B80C = script;
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = i >= briefing_exits[row].free_misc;
        misc_objects[i].id = 0x55;
    }
    for (i = 0; i < COUNT(g_QuadObjects); i++) {
        g_QuadObjects[i].active = i >= briefing_exits[row].free_quads;
        g_QuadObjects[i].id = 0x55;
    }
    func_8002F2A0(&engine_obj);
    assert(engine_obj.unk1 == briefing_exits[row].step);
    assert(engine_obj.unk2 == briefing_exits[row].phase);
    assert(engine_obj.unkE == briefing_exits[row].route);
    assert(engine_obj.unk5F == briefing_exits[row].next_story);
    assert(engine_obj.stage == briefing_exits[row].stage && engine_obj.substage == briefing_exits[row].substage);
    assert(main_bss_state.transition.active == (briefing_exits[row].fade ? -1 : 0));
    if (briefing_exits[row].fade)
        assert(main_bss_state.transition.fade_amount == 8);
    for (i = 0; i < COUNT(misc_objects); i++)
        icons += misc_objects[i].active && misc_objects[i].id == 0xD;
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        quads += g_QuadObjects[i].active && g_QuadObjects[i].id == 1;
    assert(icons == briefing_exits[row].icons && quads == briefing_exits[row].quads);
    assert(D_8013B80C == script + (briefing_exits[row].dialogue == 0xFF));
    return (u8)engine_obj.unk1;
}

#ifdef MMX4_PC
static const struct {
    u8 character, story, cleared, video, step, next_story;
} mission_initializations[] = {
    { 0, 0, 0, 0, 8, 0 },
    { 1, 0, 0, 1, 8, 0 },
    { 0, 1, 0, 2, 8, 1 },
    { 1, 2, 0, 2, 8, 2 },
    { 0, 3, 7, 0, 1, 3 },
    { 0, 3, 15, 2, 1, 3 },
    { 1, 3, 15, 7, 1, 3 },
    { 1, 3, 31, 0, 1, 3 },
    { 0, 5, 15, 3, 1, 5 },
    { 1, 5, 15, 8, 1, 5 },
    { 0, 7, 255, 4, 1, 7 },
    { 1, 7, 255, 9, 1, 7 },
    { 0, 8, 255, 0, 1, 8 },
    { 1, 8, 255, 0, 1, 9 },
    { 0, 9, 255, 0, 1, 9 },
    { 1, 10, 255, 0, 1, 10 },
    { 0, 4, 15, 0, 1, 4 },
    { 1, 6, 255, 0, 1, 6 },
};

static u32 test_mission_initialization(u32 row)
{
    char cue[sizeof(__FILE__) + 32];
    char* suffix;
    u32 i;
    int configured;
    strcpy(cue, __FILE__);
    suffix = strstr(cue, "/tests/main/1EC20.c");
    assert(suffix != NULL);
    strcpy(suffix, "/disks/mmx4.us.cue");
    if (access(cue, R_OK) != 0)
        c_test_skip();
    configured = setenv("SDL_AUDIODRIVER", "dummy", 1);
    assert(configured == 0);
    configured = Psyz_CdSetDiskPath(cue);
    assert(configured == 0);
    Psyz_SpuInit();
    ResetGraph(0);
    func_80014DC4();
    func_80013588();
    func_80012E38();
    D_80173C80 = MAIN_ARCHIVE_ARENA;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 3;
    engine_obj.unk1 = 0;
    engine_obj.unk2 = 2;
    engine_obj.unk3 = 3;
    engine_obj.unk1F = engine_obj.enable_boss = 1;
    engine_obj.cur_character = mission_initializations[row].character;
    engine_obj.unk5F = mission_initializations[row].story;
    engine_obj.palette_flags = mission_initializations[row].cleared;
    engine_obj.unk8 = engine_obj.unkA = 0x1234;
    memset(&engine_obj.character_state, 0x25, sizeof(engine_obj.character_state));
    main_bss_state.character_mode = 1;
    D_8013B810 = D_8013B814 = 1;
    D_80171EA8 = 1;
    func_8002E420(&engine_obj);
    assert(engine_obj.state == 3 && engine_obj.unk1 == mission_initializations[row].step);
    assert(engine_obj.unk2 == 0 && engine_obj.unk3 == 0);
    assert(engine_obj.stage == 13 && engine_obj.substage == 0 && engine_obj.checkpoint == 0);
    assert(engine_obj.unkE == mission_initializations[row].video);
    assert(engine_obj.unk5F == mission_initializations[row].next_story);
    assert(engine_obj.cur_character == mission_initializations[row].character);
    assert((u8)engine_obj.palette_flags == mission_initializations[row].cleared);
    assert(engine_obj.unk1F == 0 && engine_obj.enable_boss == 0);
    assert(engine_obj.unk8 == 0 && engine_obj.unkA == 0);
    for (i = 0; i < sizeof(engine_obj.character_state.bytes); i++)
        assert(engine_obj.character_state.bytes[i] == 0);
    assert(main_bss_state.character_mode == 0 && D_8013B810 == 0 && D_8013B814 == 0 && D_80171EA8 == 0);
    assert(SP_BG_TILE_PIXELS != NULL && SP_BG_TILE_ATTRS != NULL && SP_PALETTE != NULL);
    return 1;
}
static const struct {
    u8 initialization, free_slots, icons, next_step;
    s8 video;
} briefing_initializations[] = {
    { 4, 64, 2, 2, -1 },
    { 5, 64, 2, 9, -1 },
    { 8, 64, 2, 9, -1 },
    { 14, 64, 1, 2, -1 },
    { 6, 64, 2, 9, -1 },
    { 9, 64, 2, 9, -1 },
    { 11, 64, 1, 9, -1 },
    { 4, 64, 1, 9, 10 },
    { 6, 64, 1, 9, 5 },
    { 5, 0, 0, 9, -1 },
    { 5, 1, 1, 9, -1 },
    { 5, 2, 2, 9, -1 },
    { 6, 1, 1, 9, -1 },
};

static u32 test_briefing_initialization(u32 row)
{
    u16 palette_before[0x800];
    u32 i, j, spawned = 0;
    u8 story, character, cleared, video;
    test_mission_initialization(briefing_initializations[row].initialization);
    if (briefing_initializations[row].video >= 0)
        engine_obj.unkE = briefing_initializations[row].video;
    story = engine_obj.unk5F;
    character = engine_obj.cur_character;
    cleared = engine_obj.palette_flags;
    video = engine_obj.unkE;
    memcpy(palette_before, SP_PALETTE, sizeof(palette_before));
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = i < COUNT(misc_objects) - briefing_initializations[row].free_slots;
        misc_objects[i].id = 0x55;
    }
    engine_obj.unk2 = 3;
    func_8002E698(&engine_obj);
    assert(engine_obj.unk1 == briefing_initializations[row].next_step && engine_obj.unk2 == 0);
    assert(engine_obj.cur_character == character && engine_obj.unk5F == story && engine_obj.unkE == video);
    assert(main_bss_state.transition.active == 1 && main_bss_state.transition.fade_amount == 8);
    assert(D_80139524 == (story >= 5 ? 0x75 : 0x72));
    for (i = 0; i < COUNT(misc_objects); i++) {
        if (misc_objects[i].id == 0xA) {
            assert(misc_objects[i].active == 0x41 && misc_objects[i].unk2 == spawned);
            spawned++;
        } else
            assert(misc_objects[i].id == 0x55);
    }
    assert(spawned == briefing_initializations[row].icons);
    for (i = 0; i < 8; i++) {
        u16* colors = SP_PALETTES[mission_palette_order[i]];
        u16* original = &palette_before[mission_palette_order[i] * 16];
        for (j = 0; j < 16; j++) {
            if (cleared & (1 << i)) {
                u32 color = original[j];
                u32 grey = ((color & 31) + ((color >> 5) & 31) + ((color >> 10) & 31)) / 3;
                assert(colors[j] == grey * 0x421);
            } else
                assert(colors[j] == original[j]);
        }
    }
    return 1;
}
#define MISSION_INITIALIZATION_COUNT (COUNT(mission_initializations) + COUNT(briefing_initializations))
#else
#define MISSION_INITIALIZATION_COUNT 0
#endif

static struct MiscObj misc_expected[64];
static struct QuadObj quads_expected[32];
static struct BackgroundObj backgrounds_expected[3];
static u32 scroll(u32 row)
{
    struct EngineObj expected;
    struct PlayerObj player = g_Player;
    struct ControllerInput input;
    u32 i;
    (void)row;
    engine_obj.state = 3;
    engine_obj.unk1 = 2;
    engine_obj.unk2 = 0;
    engine_obj.unk3 = 0;
    engine_obj.stage = 13;
    engine_obj.substage = 0;
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.unk5F = 3;
    engine_obj.unkE = 0;
    engine_obj.palette_flags = 1;
    engine_obj.unk3C = NULL;
    expected = engine_obj;
    expected.unk1 = 3;
    expected.unk3C = BASE_OBJECT(&g_QuadObjects[7]);
    memset(&controller_input, 0, sizeof(controller_input));
    input = controller_input;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < 2; i++) {
        misc_objects[i].active = 0x41;
        misc_objects[i].id = 10;
        misc_objects[i].unk2 = i;
    }
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    misc_expected[2].active = 0x41;
    misc_expected[2].id = 13;
    memset(quads_expected, 0, sizeof(quads_expected));
    for (i = 0; i < 8; i++) {
        quads_expected[i].active = -127;
        quads_expected[i].id = 1;
        quads_expected[i].unk2 = i;
    }
    background_objects[0].y_pos.val = 0;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    backgrounds_expected[0].y_pos.i.hi = 272;
    cur_random = 0x1234;
    for (i = 0; i < 272; i++) {
        func_8002E7BC(&engine_obj);
        assert(background_objects[0].y_pos.i.hi == i + 1 && engine_obj.unk1 == 2);
    }
    func_8002E7BC(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player, sizeof(player));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    assert(c_test_word_difference((u32*)misc_objects, (u32*)misc_expected, sizeof(misc_expected) / 4) == 0);
    assert(c_test_word_difference((u32*)g_QuadObjects, (u32*)quads_expected, sizeof(quads_expected) / 4) == 0);
    assert(cur_random == 0x1234);
    return 1;
}

static u32 test_confirm_route(u32 row)
{
    static const u8 stages[] = { 1, 6, 7, 4, 5, 3, 8, 2 };
    static const struct {
        u8 story, stage, flags[2];
    } special[] = {
        { 5, 10, { 0x31, 0x11 } },
        { 6, 10, { 0x31, 0x11 } },
        { 7, 11, { 0x11, 0x11 } },
        { 8, 11, { 0x11, 0x11 } },
        { 9, 11, { 0x11, 0x11 } },
        { 10, 12, { 0x11, 0x11 } },
    };
    struct EngineObj expected;
    struct PlayerObj player_before;
    struct ControllerInput input_before;
    u32 i, index = row < 64 ? row / 8 : (row - 64) / 4;
    u32 character = row < 64 ? (row / 4) & 1 : ((row - 64) / 2) & 1;
    u32 substage = row < 64 ? (row / 2) & 1 : 1;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&controller_input, 0, sizeof(controller_input));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    engine_obj.state = 3;
    engine_obj.unk1 = 4;
    engine_obj.unk2 = 7;
    engine_obj.unk3 = row < 64 ? index : 8;
    engine_obj.unk5F = row < 64 ? 4 : special[index].story;
    engine_obj.cur_character = character;
    engine_obj.stage = 9;
    engine_obj.substage = 1;
    engine_obj.unk40 = 0xFF;
    engine_obj.unk8 = 7;
    engine_obj.unkA = 5;
    g_Player.hp = 21;
    g_Player.unk2 = character;
    D_8013B810 = 1;
    D_8013B814 = substage;
    controller_input.pressed = row & 1 ? PADstart : PAD_CONFIRM;
    controller_input.held = controller_input.pressed;
    input_before = controller_input;
    player_before = g_Player;
    expected = engine_obj;
    expected.unk1 = 5;
    expected.unk2 = 0;
    expected.unk8 = expected.unkA = 0;
    if (row < 64) {
        expected.stage = stages[index];
        expected.substage = substage;
        expected.unk40 = character == 0 ? 0x31 : 0x11;
    } else {
        expected.stage = special[index].stage;
        expected.unk40 = special[index].flags[character];
    }
    func_8002E994(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&controller_input, &input_before, sizeof(input_before));
    assert(D_8013B810 == 1);
    assert(D_8013B814 == (row < 64 ? substage : 0));
    return 1;
}

static u32 test_grid_navigation(u32 row)
{
    static const u8 right_targets[] = { 1, 2, 3, 3, 5, 6, 7, 7 };
    struct EngineObj expected;
    struct PlayerObj player_before;
    struct ControllerInput input_before;
    u32 i, selection = row < 4 ? row : row - 4;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&controller_input, 0, sizeof(controller_input));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    engine_obj.state = 3;
    engine_obj.unk1 = 4;
    engine_obj.unk2 = 7;
    engine_obj.unk3 = selection;
    engine_obj.unk5F = 4;
    controller_input.held = row < 4 ? PADLdown : PADLright;
    input_before = controller_input;
    player_before = g_Player;
    expected = engine_obj;
    expected.unk3 = row < 4 ? selection + 4 : right_targets[selection];
    expected.unk8 = 30;
    expected.unkA = 1;
    func_8002E994(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&controller_input, &input_before, sizeof(input_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "briefing_exit", 0, 0, COUNT(briefing_exits), test_briefing_exit },
    { "briefing_script_pools", NULL, briefing_script_pools_cases_expected, COUNT(briefing_script_pools_cases_expected), briefing_case },
    { "mission_route_navigation", NULL, mission_route_navigation_cases_expected, COUNT(mission_route_navigation_cases_expected), mission_route_navigation_cases_row },
    { "mission_select_spawn_prefixes", NULL, mission_select_spawn_prefixes_cases_expected, COUNT(mission_select_spawn_prefixes_cases_expected), mission_case },
    { "func_8002E7BC", 0, 0, 2, test_func_8002E7BC },
    { "actual_early_briefing_all_272_scroll_frames_without_confirm_then_grid_factory", NULL, NULL, 1, scroll },
    { "confirm_route", 0, 0, 86, test_confirm_route },
    { "grid_navigation", 0, 0, 12, test_grid_navigation },
    { "mission_entry", 0, 0, COUNT(mission_entries), test_mission_entry },
#ifdef MMX4_PC
    { "briefing_override", 0, 0, COUNT(briefing_overrides), test_briefing_override },
#endif
#ifdef MMX4_PC
    { "mission_initialization", 0, 0, COUNT(mission_initializations), test_mission_initialization },
    { "briefing_initialization", 0, 0, COUNT(briefing_initializations), test_briefing_initialization },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(briefing_exits) + COUNT(briefing_script_pools_cases_expected) + COUNT(mission_route_navigation_cases_expected) + COUNT(mission_select_spawn_prefixes_cases_expected) + 2 + 1 + 86 + 12 + COUNT(mission_entries)
#ifdef MMX4_PC
    + COUNT(briefing_overrides)
#endif
#ifdef MMX4_PC
    + COUNT(mission_initializations)
    + COUNT(briefing_initializations)
#endif
    ;
