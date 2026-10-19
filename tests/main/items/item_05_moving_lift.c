#include "test_runtime.h"
#include "main/items/item_05_moving_lift.h"
#include "support/state_cases.h"
void moving_lift_despawn(struct ItemObj*);

static const u32 moving_lift_spawn_effect_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_moving_lift_spawn_effect(u32 row)
{
    u32 observed_values[11];
    struct ItemObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    FILL_ACTIVE(visual_objects, 32, 255 ? 1 : 0);
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
static u8 lift_record;
static void ml_despawn(void)
{
    state_reset(0, 0, 0);
    lift_record = 0;
    state_room.item.active = 1;
    state_room.item.backref = (void*)&lift_record;
    moving_lift_despawn(&state_room.item);
    state_extra = lift_record;
    state_room.item.backref = NULL;
}

static void (*const moving_lift_misc_cases[])(void) = {
    ml_despawn,
};
static const u32 moving_lift_misc_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_moving_lift_misc(u32 row)
{
    return object_run(moving_lift_misc_cases[row], row, &moving_lift_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "moving_lift_misc", 0, 0, COUNT(moving_lift_misc_cases), test_moving_lift_misc },
    { "moving_lift_spawn_effect", 0, 0, 1, test_moving_lift_spawn_effect },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(moving_lift_misc_cases) + 1 + COUNT(pool_full_cases);
