#include "test_runtime.h"
#include "main/mains/main_22_bee_hive.h"
#include "main/55C4.h"
void func_800559BC(struct MainObj*);

static const u32 inputs_0[2][2] = {
    { 1, 0 },
    { 0, 0 },
};
struct bee_hive_wait_watch_case {
    u32 expected[3];
};
static const struct bee_hive_wait_watch_case bee_hive_wait_watch_cases[] = {
    { { 0u, 0u, 0u } },
    { { 0x28u, 0u, 0u } },
};
static u32 test_bee_hive_wait_watch(u32 row)
{
    const struct bee_hive_wait_watch_case* c = &bee_hive_wait_watch_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_22.unk84 = inputs_0[row][0];
    obj.ext.main_22.unk8C = inputs_0[row][1];
    bee_hive_wait_watch(&obj);
    observed_values[0] = (u32)obj.ext.main_22.unk84;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

static struct MainObj func_80055358_0_hive_pool_expected[48];
static const u32 func_80055358_expected[] = { 8u };
static u32 test_func_80055358(u32 row)
{
    u32 observed_values[1];
    struct EngineObj engine_expected;
    struct PlayerObj player_expected;
    struct MainObj* obj;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    obj = &main_objects[0];
    memset(obj, 0, sizeof(*obj));
    obj->active = 0x41;
    obj->id = 22;
    obj->x_pos.i.hi = 104;
    obj->y_pos.i.hi = 132;
    func_80055024(obj);
    main_objects[1] = *obj;
    main_objects[2] = *obj;
    main_objects[3] = *obj;
    main_objects[4] = *obj;
    main_objects[5] = *obj;
    main_objects[6] = *obj;
    main_objects[7] = *obj;
    main_objects[8] = *obj;
    main_objects[9] = *obj;
    main_objects[10] = *obj;
    main_objects[11] = *obj;
    main_objects[12] = *obj;
    main_objects[13] = *obj;
    main_objects[14] = *obj;
    main_objects[15] = *obj;
    main_objects[16] = *obj;
    main_objects[17] = *obj;
    main_objects[18] = *obj;
    main_objects[19] = *obj;
    main_objects[20] = *obj;
    main_objects[21] = *obj;
    main_objects[22] = *obj;
    main_objects[23] = *obj;
    main_objects[24] = *obj;
    main_objects[25] = *obj;
    main_objects[26] = *obj;
    main_objects[27] = *obj;
    main_objects[28] = *obj;
    main_objects[29] = *obj;
    main_objects[30] = *obj;
    main_objects[31] = *obj;
    main_objects[32] = *obj;
    main_objects[33] = *obj;
    main_objects[34] = *obj;
    main_objects[35] = *obj;
    main_objects[36] = *obj;
    main_objects[37] = *obj;
    main_objects[38] = *obj;
    main_objects[39] = *obj;
    main_objects[40] = *obj;
    main_objects[41] = *obj;
    main_objects[42] = *obj;
    main_objects[43] = *obj;
    main_objects[44] = *obj;
    main_objects[45] = *obj;
    main_objects[46] = *obj;
    main_objects[47] = *obj;
    bee_hive_open_start(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    func_80055358(obj);
    memcpy(func_80055358_0_hive_pool_expected, main_objects, sizeof(main_objects));
    animate_object(ANIMATED_OBJECT(&func_80055358_0_hive_pool_expected[0]));
    func_80055358_0_hive_pool_expected[0].ext.main_22.unk84 = 8;
    engine_expected = engine_obj;
    player_expected = g_Player;
    func_80055358(obj);
    assert(c_test_word_difference((const u32*)main_objects, (const u32*)func_80055358_0_hive_pool_expected, sizeof(main_objects) / 4) == 0);
    assert(c_test_word_difference((const u32*)&engine_obj, (const u32*)&engine_expected, sizeof(engine_obj) / 4) == 0);
    assert(c_test_word_difference((const u32*)&g_Player, (const u32*)&player_expected, sizeof(g_Player) / 4) == 0);
    observed_values[0] = obj->ext.main_22.unk84;
    return c_test_observe(0, row, observed_values, func_80055358_expected, 1);
}

static struct MainObj func_800559BC_0_hive_pool_expected[48];
static const u32 func_800559BC_expected[] = { 0x1Eu };
static u32 test_func_800559BC(u32 row)
{
    u32 observed_values[1];
    struct EngineObj engine_expected;
    struct PlayerObj player_expected;
    struct MainObj* obj;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    obj = &main_objects[0];
    memset(obj, 0, sizeof(*obj));
    obj->active = 0x41;
    obj->id = 22;
    obj->x_pos.i.hi = 104;
    obj->y_pos.i.hi = 132;
    func_80055024(obj);
    main_objects[1] = *obj;
    main_objects[2] = *obj;
    main_objects[3] = *obj;
    main_objects[4] = *obj;
    main_objects[5] = *obj;
    main_objects[6] = *obj;
    main_objects[7] = *obj;
    main_objects[8] = *obj;
    main_objects[9] = *obj;
    main_objects[10] = *obj;
    main_objects[11] = *obj;
    main_objects[12] = *obj;
    main_objects[13] = *obj;
    main_objects[14] = *obj;
    main_objects[15] = *obj;
    main_objects[16] = *obj;
    main_objects[17] = *obj;
    main_objects[18] = *obj;
    main_objects[19] = *obj;
    main_objects[20] = *obj;
    main_objects[21] = *obj;
    main_objects[22] = *obj;
    main_objects[23] = *obj;
    main_objects[24] = *obj;
    main_objects[25] = *obj;
    main_objects[26] = *obj;
    main_objects[27] = *obj;
    main_objects[28] = *obj;
    main_objects[29] = *obj;
    main_objects[30] = *obj;
    main_objects[31] = *obj;
    main_objects[32] = *obj;
    main_objects[33] = *obj;
    main_objects[34] = *obj;
    main_objects[35] = *obj;
    main_objects[36] = *obj;
    main_objects[37] = *obj;
    main_objects[38] = *obj;
    main_objects[39] = *obj;
    main_objects[40] = *obj;
    main_objects[41] = *obj;
    main_objects[42] = *obj;
    main_objects[43] = *obj;
    main_objects[44] = *obj;
    main_objects[45] = *obj;
    main_objects[46] = *obj;
    main_objects[47] = *obj;
    bee_hive_wait_start(obj);
    bee_hive_wait_watch(obj);
    bee_hive_release_start(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    bee_hive_release_wait(obj);
    memcpy(func_800559BC_0_hive_pool_expected, main_objects, sizeof(main_objects));
    animate_object(ANIMATED_OBJECT(&func_800559BC_0_hive_pool_expected[0]));
    func_800559BC_0_hive_pool_expected[0].ext.main_22.unk84 = 30;
    func_800559BC_0_hive_pool_expected[0].unk6 = func_800559BC_0_hive_pool_expected[0].unk6 + 1;
    engine_expected = engine_obj;
    player_expected = g_Player;
    bee_hive_release_wait(obj);
    assert(c_test_word_difference((const u32*)main_objects, (const u32*)func_800559BC_0_hive_pool_expected, sizeof(main_objects) / 4) == 0);
    assert(c_test_word_difference((const u32*)&engine_obj, (const u32*)&engine_expected, sizeof(engine_obj) / 4) == 0);
    assert(c_test_word_difference((const u32*)&g_Player, (const u32*)&player_expected, sizeof(g_Player) / 4) == 0);
    observed_values[0] = obj->ext.main_22.unk84;
    return c_test_observe(0, row, observed_values, func_800559BC_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "bee_hive_wait_watch", 0, 0, 2, test_bee_hive_wait_watch },
    { "func_80055358", 0, 0, 1, test_func_80055358 },
    { "func_800559BC", 0, 0, 1, test_func_800559BC },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 1 + 1;
