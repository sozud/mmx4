#include "test_runtime.h"
#include "main/items/item_05_moving_lift.h"

static const u32 moving_lift_spawn_effect_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_moving_lift_spawn_effect(u32 row)
{
    u32 observed_values[11];
    struct ItemObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    moving_lift_spawn_effect(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].state;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].unk5;
    observed_values[8] = (u32)visual_objects[0].unk6;
    observed_values[9] = (u32)visual_objects[0].x_pos.val;
    observed_values[10] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, moving_lift_spawn_effect_expected, 11);
}

#include "support/pool_full.h"
static u32 pool_full_moving_lift_spawn_all(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    moving_lift_spawn_all();
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_moving_lift_spawn_all,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "moving_lift_spawn_effect", 0, 0, 1, test_moving_lift_spawn_effect },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(pool_full_cases);
