#include "test_runtime.h"

struct item_scatter_spawn_case {
    u32 id, pool_0_full;
    u32 expected[6];
};
static const struct item_scatter_spawn_case item_scatter_spawn_cases[] = {
    { 255, 0, { 0u, 0u, 0u, 0u, 0u, 1u } },
    { 0, 255, { 1u, 0u, 0u, 0u, 0u, 1u } },
};
static u32 test_item_scatter_spawn(u32 row)
{
    const struct item_scatter_spawn_case* c = &item_scatter_spawn_cases[row];
    u32 observed_values[6];
    struct EffectObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&item_objects, 0, sizeof(item_objects));
    edge_spawner_items[0].id = c->id;
    pool_0_full = c->pool_0_full;
    edge_spawner_items[0].x = 0;
    edge_spawner_items[0].y = 0;
    obj.state = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_0_full ? 1 : 0;
    }
    item_scatter_spawn(&obj);
    observed_values[0] = (u32)item_objects[0].active;
    observed_values[1] = (u32)item_objects[0].id;
    observed_values[2] = (u32)item_objects[0].unk2;
    observed_values[3] = (u32)item_objects[0].x_pos.i.hi;
    observed_values[4] = (u32)item_objects[0].y_pos.i.hi;
    observed_values[5] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "item_scatter_spawn", 0, 0, 2, test_item_scatter_spawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
