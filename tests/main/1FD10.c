#include "test_runtime.h"

static u32 transition_case(u32 mode)
{
    struct EngineObj obj, expected;
    struct AbcObj abc_before;
    struct PlayerObj player_before = g_Player;
    struct MiscObj expected_pool[64];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    obj.unk1 = 3;
    obj.unk2 = 4;
    obj.unk3 = mode == 4 ? 6 : 7;
    obj.unk5F = 9;
    obj.stage = 5;
    obj.substage = 2;
    abc_object.unkC = mode == 3 ? 1 : 0;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 39;
        misc_objects[i].unk2 = 9;
        misc_objects[i].state = 40;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].unk7 = 5;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        misc_objects[i].unk42 = 0x7777;
    }
    if (mode >= 1)
        misc_objects[61].active = 0;
    if (mode >= 2)
        misc_objects[63].active = 0;
    expected = obj;
    abc_before = abc_object;
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    if (mode != 3) {
        if (mode == 4) {
            expected.unk3 = 7;
            expected.unk2 = 1;
        } else {
            expected.unk5F = 3;
            expected.unk1 = 4;
            expected.unk2 = 0;
            expected.unk3 = 0;
            if (mode >= 1) {
                expected_pool[61].active = 0x41;
                expected_pool[61].id = 15;
                expected_pool[61].unk2 = 0;
            }
            if (mode == 2) {
                expected_pool[63].active = 0x41;
                expected_pool[63].id = 15;
                expected_pool[63].unk2 = 1;
            }
        }
    }
    func_8002F5E8(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(expected_pool) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)expected_pool)[i]);
    for (i = 0; i < sizeof(abc_object) / 4; i++)
        assert(((u32*)&abc_object)[i] == ((u32*)&abc_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    actual = (u8)obj.unk1 | ((u32)(u8)obj.unk3 << 8) | ((u32)misc_objects[61].active << 16) | ((u32)misc_objects[63].active << 24);
    return actual;
}
#define CASE(m)                     \
    static u32 transition_##m(void) \
    {                               \
        return transition_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) transition_##m,
static const CTestCase engine_transition_two_misc_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 engine_transition_two_misc_pool_cases_expected[] = { 0x1010004u, 0x1410004u, 0x41410004u, 0x703u, 0x703u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "engine_transition_two_misc_pool", engine_transition_two_misc_pool_cases, engine_transition_two_misc_pool_cases_expected, COUNT(engine_transition_two_misc_pool_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(engine_transition_two_misc_pool_cases);
