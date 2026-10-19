#include "test_runtime.h"
#include "main/shots/shot_28_melee_hitbox.h"

struct melee_hitbox_active_case {
    u32 state, frame_index;
    u32 expected[1];
};
static const struct melee_hitbox_active_case melee_hitbox_active_cases[] = {
    { 2, 0, { 1u } },
    { 0, 0, { 0u } },
    { -128, 3, { 0u } },
};
static u32 test_melee_hitbox_active(u32 row)
{
    const struct melee_hitbox_active_case* c = &melee_hitbox_active_cases[row];
    u32 observed_values[1];
    struct ShotObj obj;
    struct WeaponObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    child_0.state = c->state;
    child_0.animation_step.fields.frame_index = c->frame_index;
    obj.unk7C = &child_0;
    melee_hitbox_active(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "melee_hitbox_active", 0, 0, 3, test_melee_hitbox_active },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3;
