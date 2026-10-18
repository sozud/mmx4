#include "test_runtime.h"
#include "main/engine.h"
extern struct MiscObj* D_801396C0;
extern struct MiscObj* D_801396C4;
s32 func_8001F8FC(struct GameInfo*);

static const u32 func_8001F6E8_expected[] = { 1u, 4u, 1u, 4u, 1u, 0u, 6u };
static u32 test_func_8001F6E8(u32 row)
{
    u32 observed_values[7];
    struct EngineObj obj;
    struct MiscObj child_0;
    u8 child_0_present;
    struct MiscObj child_1;
    u8 child_1_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&controller_input, 0, sizeof(controller_input));
    child_0_present = 255;
    child_1_present = 255;
    controller_input.pressed = 255;
    D_801396C0 = child_0_present ? &child_0 : NULL;
    D_801396C4 = child_1_present ? &child_1 : NULL;
    func_8001F6E8(&obj);
    observed_values[0] = (u32)child_0.state;
    observed_values[1] = (u32)child_0.unk5;
    observed_values[2] = (u32)child_1.state;
    observed_values[3] = (u32)child_1.unk5;
    observed_values[4] = (u32)obj.unk2;
    observed_values[5] = (u32)obj.unk3;
    observed_values[6] = (u32)obj.unk4;
    return c_test_observe(0, row, observed_values, func_8001F6E8_expected, 7);
}
#undef controller_input

struct func_8001F8FC_case {
    u32 unk6;
    u32 expected[2];
};
static const struct func_8001F8FC_case func_8001F8FC_cases[] = {
    { 0, { 1u, 0xFFFFFFFFu } },
    { 1, { 0u, 0u } },
};
static u32 test_func_8001F8FC(u32 row)
{
    const struct func_8001F8FC_case* c = &func_8001F8FC_cases[row];
    u32 observed_values[2];
    struct GameInfo obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80139520, 0, sizeof(D_80139520));
    memset(&D_80139524, 0, sizeof(D_80139524));
    memset(&D_80139528, 0, sizeof(D_80139528));
    memset(&D_80139530, 0, sizeof(D_80139530));
    memset(&D_8013955C, 0, sizeof(D_8013955C));
    memset(&D_80139564, 0, sizeof(D_80139564));
    memset(&D_80139568, 0, sizeof(D_80139568));
    memset(&D_80141BD4, 0, sizeof(D_80141BD4));
    memset(&D_80171EA9, 0, sizeof(D_80171EA9));
    memset(&D_80173C84, 0, sizeof(D_80173C84));
    obj.unk6 = c->unk6;
    return_value = func_8001F8FC(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct func_8001FA24_case {
    u32 boss_flags;
    u32 expected[22];
};
static const struct func_8001FA24_case func_8001FA24_cases[] = {
    { -1, { 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0u } },
    { 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0u } },
};
static u32 test_func_8001FA24(u32 row)
{
    const struct func_8001FA24_case* c = &func_8001FA24_cases[row];
    u32 observed_values[22];
    struct EngineObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.character_state.bytes[0] = 17;
    g_Player.boss_flags = c->boss_flags;
    func_8001FA24(&obj);
    observed_values[0] = (u32)g_Player.boss_flags;
    observed_values[1] = (u32)obj.character_state.bytes[0];
    observed_values[2] = (u32)obj.character_state.bytes[10];
    observed_values[3] = (u32)obj.character_state.bytes[11];
    observed_values[4] = (u32)obj.character_state.bytes[12];
    observed_values[5] = (u32)obj.character_state.bytes[13];
    observed_values[6] = (u32)obj.character_state.bytes[14];
    observed_values[7] = (u32)obj.character_state.bytes[15];
    observed_values[8] = (u32)obj.character_state.bytes[1];
    observed_values[9] = (u32)obj.character_state.bytes[2];
    observed_values[10] = (u32)obj.character_state.bytes[3];
    observed_values[11] = (u32)obj.character_state.bytes[4];
    observed_values[12] = (u32)obj.character_state.bytes[5];
    observed_values[13] = (u32)obj.character_state.bytes[6];
    observed_values[14] = (u32)obj.character_state.bytes[7];
    observed_values[15] = (u32)obj.character_state.bytes[8];
    observed_values[16] = (u32)obj.character_state.bytes[9];
    observed_values[17] = (u32)obj.palette_flags;
    observed_values[18] = (u32)obj.state;
    observed_values[19] = (u32)obj.unk1;
    observed_values[20] = (u32)obj.unk2;
    observed_values[21] = (u32)obj.unk5F;
    return c_test_observe(0, row, observed_values, c->expected, 22);
}

const struct CTestGroup c_test_groups[] = {
    { "func_8001F6E8", 0, 0, 1, test_func_8001F6E8 },
    { "func_8001F8FC", 0, 0, 2, test_func_8001F8FC },
    { "func_8001FA24", 0, 0, 2, test_func_8001FA24 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 2 + 2;
