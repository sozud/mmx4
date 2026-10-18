#include "test_runtime.h"
#include "main/character_select.h"

static u32 select_case(u32 available)
{
    static const u8 variants[] = { 2, 7, 4, 3, 8, 5, 6 };
    struct EngineObj obj, expected;
    struct MiscObj pool[64];
    struct PlayerObj player_before = g_Player;
    u32 i, actual = 0;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    obj.state = 1;
    obj.unk1 = 4;
    obj.unk2 = 2;
    obj.unk3 = 7;
    obj.stage = 13;
    obj.substage = 1;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - available ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].unk7 = 5;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    expected = obj;
    expected.unk1 = 5;
    expected.unk2 = 0;
    memcpy(pool, misc_objects, sizeof(pool));
    for (i = 0; i < available; i++) {
        struct MiscObj* child = &pool[64 - available + i];
        child->active = 0x41;
        child->id = 0x1C;
        child->unk2 = variants[i];
    }
    character_select_spawn_objects(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 57; i < 64; i++)
        if (misc_objects[i].active == 0x41)
            actual |= 1 << (i - 57);
    return actual | ((u32)obj.unk1 << 8);
}
#define CASE(m)                                                   \
    static u32 character_select_allocation_steps_select_##m(void) \
    {                                                             \
        return select_case(m);                                    \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) character_select_allocation_steps_select_##m,
static const CTestCase character_select_allocation_steps_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 character_select_allocation_steps_cases_expected[] = { 0x500u, 0x540u, 0x560u, 0x570u, 0x578u, 0x57Cu, 0x57Eu, 0x57Fu };
#undef CASE
#undef ENTRY

struct func_80029A48_case {
    u32 secret_code_phase, pressed, secret_code_index;
    u32 expected[3];
};
static const struct func_80029A48_case func_80029A48_cases[] = {
    { -1, 0, 0, { 0u, 0xFFFFFFFFu, 0u } },
    { 0, 32, 0, { 0u, 0u, 0u } },
    { 1, 32, 1, { 1u, 0u, 0u } },
    { 2, 1, 4, { 4u, 0u, 0u } },
    { 2, 255, 0, { 0u, 0u, 0u } },
};
static u32 test_func_80029A48(u32 row)
{
    const struct func_80029A48_case* c = &func_80029A48_cases[row];
    u32 observed_values[3];
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.character_state.fields.secret_code_phase = c->secret_code_phase;
    controller_input.pressed = c->pressed;
    engine_obj.character_state.fields.secret_code_index = c->secret_code_index;
    func_80029A48();
    observed_values[0] = (u32)engine_obj.character_state.fields.secret_code_index;
    observed_values[1] = (u32)engine_obj.character_state.fields.secret_code_phase;
    observed_values[2] = (u32)engine_obj.unk37;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}
#undef controller_input

struct func_80029BD8_case {
    u32 secret_code_phase, pressed, held, secret_code_index;
    u32 expected[3];
};
static const struct func_80029BD8_case func_80029BD8_cases[] = {
    { -1, 0, 0, 0, { 0u, 0xFFFFFFFFu, 0u } },
    { 1, 255, 0, 0, { 0u, 0u, 0u } },
    { 0, 8192, 0, 0, { 0u, 0u, 0u } },
    { 2, 0, 16384, 3, { 3u, 0u, 0u } },
    { 2, 255, 255, 6, { 6u, 0u, 0u } },
    { 3, 1024, 0, 6, { 6u, 0u, 0u } },
    { 3, 255, 0, 0, { 0u, 0u, 0u } },
    { 1, 32, 0, 6, { 6u, 0u, 0u } },
};
static u32 test_func_80029BD8(u32 row)
{
    const struct func_80029BD8_case* c = &func_80029BD8_cases[row];
    u32 observed_values[3];
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.character_state.fields.secret_code_phase = c->secret_code_phase;
    controller_input.pressed = c->pressed;
    controller_input.held = c->held;
    engine_obj.character_state.fields.secret_code_index = c->secret_code_index;
    func_80029BD8();
    observed_values[0] = (u32)engine_obj.character_state.fields.secret_code_index;
    observed_values[1] = (u32)engine_obj.character_state.fields.secret_code_phase;
    observed_values[2] = (u32)engine_obj.unk37;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}
#undef controller_input

static u32 code_default(s8 phase, void (*update)(void))
{
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&controller_input, 0, sizeof(controller_input));
    engine_obj.character_state.fields.secret_code_phase = phase;
    engine_obj.character_state.fields.secret_code_index = 5;
    engine_obj.unk37 = 0x55;
    update();
    assert(engine_obj.character_state.fields.secret_code_phase == phase);
    assert(engine_obj.character_state.fields.secret_code_index == 5);
    assert(engine_obj.unk37 == 0x55);
    return (u8)engine_obj.character_state.fields.secret_code_phase | ((u32)(u8)engine_obj.character_state.fields.secret_code_index << 8) | ((u32)(u8)engine_obj.unk37 << 16);
}
static u32 x_high_default(void)
{
    return code_default(3, func_80029A48);
}
static u32 zero_high_default(void)
{
    return code_default(4, func_80029BD8);
}
static const CTestCase secret_code_defaults_cases[] = {
    x_high_default,
    zero_high_default,
};
static const u32 secret_code_defaults_cases_expected[] = { 0x550503u, 0x550504u };
#undef controller_input

const struct CTestGroup c_test_groups[] = {
    { "character_select_allocation_steps", character_select_allocation_steps_cases, character_select_allocation_steps_cases_expected, COUNT(character_select_allocation_steps_cases), 0 },
    { "func_80029A48", 0, 0, 5, test_func_80029A48 },
    { "func_80029BD8", 0, 0, 8, test_func_80029BD8 },
    { "secret_code_defaults", secret_code_defaults_cases, secret_code_defaults_cases_expected, COUNT(secret_code_defaults_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(character_select_allocation_steps_cases) + 5 + 8 + COUNT(secret_code_defaults_cases);
