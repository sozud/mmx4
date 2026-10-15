#include "test_runtime.h"

struct func_800BF638_case {
    u32 stage, pool_0_full, arg1;
    u32 expected[7];
};
static const struct func_800BF638_case func_800BF638_cases[] = {
    { 5, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 255, 46, { 1u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800BF638(u32 row)
{
    const struct func_800BF638_case* c = &func_800BF638_cases[row];
    u32 observed_values[7];
    struct BaseObj obj;
    u8 pool_0_full;
    s8 arg1;
    s16 arg2;
    s16 arg3;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    engine_obj.stage = c->stage;
    pool_0_full = c->pool_0_full;
    arg1 = c->arg1;
    arg2 = 0;
    arg3 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_800BF638(&obj, arg1, arg2, arg3);
    observed_values[0] = (u32)item_objects[0].active;
    observed_values[1] = (u32)item_objects[0].bg_offset;
    observed_values[2] = (u32)item_objects[0].id;
    observed_values[3] = (u32)item_objects[0].unk2;
    observed_values[4] = (u32)item_objects[0].unk7C.value;
    observed_values[5] = (u32)item_objects[0].x_pos.i.hi;
    observed_values[6] = (u32)item_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

const struct CTestGroup c_test_groups[] = {
    { "func_800BF638", 0, 0, 2, test_func_800BF638 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
