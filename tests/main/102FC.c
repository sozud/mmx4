#include "test_runtime.h"
#include "main/102FC.h"

static u32 outcome_case(u32 mode)
{
    struct EngineObj expected;
    struct PlayerObj player_expected;
    struct EffectObj pool_expected[32];
    u32 i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(effect_objects, 0, sizeof(effect_objects));
    engine_obj.state = 3;
    engine_obj.unk1 = 9;
    engine_obj.unkF = mode < 2 ? 1 : -1;
    engine_obj.stage = mode == 1 ? 10 : mode == 5 ? 11
                                                  : 12;
    engine_obj.substage = mode < 2 || mode >= 4 ? 1 : 0;
    engine_obj.checkpoint = mode == 3 ? 9 : 10;
    engine_obj.unk1E = 4;
    engine_obj.unk42 = 0x22;
    engine_obj.unk5F = 0x66;
    engine_obj.checkpoint_hp = 0x33;
    engine_obj.unk60 = 0x44;
    g_Player.hp = 27;
    g_Player.weapon = 5;
    for (i = 0; i < 16; i++) {
        g_Player.weapon_energy[i] = 3 + i;
        engine_obj.player_initial_data[i] = 0x88 + i;
        engine_obj.character_state.bytes[i] = 0xA0 + i;
    }
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = i == 2 ? 0 : 0x41;
        effect_objects[i].id = i == 1 ? 3 : 2;
        effect_objects[i].unk2 = i == 3 ? 15 : 14;
        effect_objects[i].on_screen = 9;
        effect_objects[i].state = 7;
        effect_objects[i].unk5 = 8;
        effect_objects[i].unk6 = 9;
        effect_objects[i].unk7 = 10;
    }
    expected = engine_obj;
    player_expected = g_Player;
    memcpy(pool_expected, effect_objects, sizeof(pool_expected));
    expected.unk1 = 0;
    expected.unkF = 0;
    if (mode < 2) {
        expected.unk1E = 0;
        expected.state = mode == 0 ? 11 : 9;
        if (mode == 1)
            expected.unk5F = 7;
    } else {
        expected.unk1E = -1;
        expected.state = 5;
        expected.checkpoint_hp = 27;
        expected.unk60 = 5;
        for (i = 0; i < 16; i++)
            expected.player_initial_data[i] = 3 + i;
        if (mode == 2 || mode == 5)
            expected.unk42 = 1;
        for (i = 0; i < 32; i++)
            if (i != 1 && i != 2 && i != 3) {
                ((u32*)&pool_expected[i])[0] = 0;
                ((u32*)&pool_expected[i])[1] = 0;
            }
    }
    func_800200D4(&engine_obj);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_expected)[i]);
    i = (u8)engine_obj.state | ((u32)(u8)engine_obj.unk1E << 8) | ((u32)(u8)engine_obj.unk42 << 16) | ((u32)(u8)engine_obj.unk5F << 24);
    return i;
}
#define CASE(m)                                                    \
    static u32 engine_outcome_transition_context_outcome_##m(void) \
    {                                                              \
        return outcome_case(m);                                    \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) engine_outcome_transition_context_outcome_##m,
static const CTestCase engine_outcome_transition_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 engine_outcome_transition_context_cases_expected[] = { 0x6622000Bu, 0x7220009u, 0x6601FF05u, 0x6622FF05u, 0x6622FF05u, 0x6601FF05u };
#undef CASE
#undef ENTRY

struct func_8001FDBC_case {
    u32 stage, checkpoint, substage, cur_character, pool_1_full, pool_0_full;
    u32 expected[6];
};
static const struct func_8001FDBC_case func_8001FDBC_cases[] = {
    { 5, -1, 0, 0, 0, 255, { 1u, 0u, 1u, 0u, 0u, 0u } },
    { 12, -1, -1, 0, 0, 255, { 1u, 0u, 1u, 0u, 0u, 0u } },
    { 12, 0, -1, -1, 255, 0, { 0u, 0u, 0xFFFFFFFEu, 1u, 0u, 0u } },
};
static u32 test_func_8001FDBC(u32 row)
{
    const struct func_8001FDBC_case* c = &func_8001FDBC_cases[row];
    u32 observed_values[6];
    u8 pool_1_full;
    u8 pool_0_full;
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    engine_obj.stage = c->stage;
    engine_obj.checkpoint = c->checkpoint;
    engine_obj.substage = c->substage;
    engine_obj.cur_character = c->cur_character;
    pool_1_full = c->pool_1_full;
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_1_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8001FDBC();
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)engine_obj.unk1E;
    observed_values[3] = (u32)misc_objects[0].active;
    observed_values[4] = (u32)misc_objects[0].id;
    observed_values[5] = (u32)misc_objects[0].unk2;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "engine_outcome_transition_context", engine_outcome_transition_context_cases, engine_outcome_transition_context_cases_expected, COUNT(engine_outcome_transition_context_cases), 0 },
    { "func_8001FDBC", 0, 0, 3, test_func_8001FDBC },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(engine_outcome_transition_context_cases) + 3;
