#include "test_runtime.h"

struct spore_rain_fx_animate_case {
    u32 state, unk2, unk54, x_pos;
    u32 expected[8];
};
static const struct spore_rain_fx_animate_case spore_rain_fx_animate_cases[] = {
    { 2, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, -1, 1, 33554946, { 0u, 0u, 0u, 1u, 0x200u, 0x2000202u, 0u, 0u } },
    { 0, -1, 0, 0, { 0xFFFFFFFFu, 0u, 1u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_spore_rain_fx_animate(u32 row)
{
    const struct spore_rain_fx_animate_case* c = &spore_rain_fx_animate_cases[row];
    u32 observed_values[8];
    struct MiscObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0_present = 255;
    child_0.state = c->state;
    obj.unk2 = c->unk2;
    obj.ext.misc_30.unk54 = c->unk54;
    child_0.x_pos.val = c->x_pos;
    obj.ext.misc_30.owner = child_0_present ? &child_0 : NULL;
    spore_rain_fx_animate(&obj);
    observed_values[0] = (u32)obj.ext.misc_30.unk54;
    observed_values[1] = (u32)obj.ext.misc_30.unk56;
    observed_values[2] = (u32)obj.on_screen;
    observed_values[3] = (u32)obj.state;
    observed_values[4] = (u32)obj.x_pos.i.hi;
    observed_values[5] = (u32)obj.x_pos.val;
    observed_values[6] = (u32)obj.y_pos.i.hi;
    observed_values[7] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

const struct CTestGroup c_test_groups[] = {
    { "spore_rain_fx_animate", 0, 0, 3, test_spore_rain_fx_animate },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3;
