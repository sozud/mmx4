#include "test_runtime.h"

struct bg_zone_controller_zone_0_scroll_case {
    u32 x_pos_hi, unk14_hi, unk17;
    u32 expected[5];
};
static const struct bg_zone_controller_zone_0_scroll_case bg_zone_controller_zone_0_scroll_cases[] = {
    { -32768, 0, 8, { 0u, 0u, 0u, 0u, 0xFFFFFFF8u } },
    { 16480, -14240, -8, { 0u, 0u, 0u, 0u, 8u } },
};
static u32 test_bg_zone_controller_zone_0_scroll(u32 row)
{
    const struct bg_zone_controller_zone_0_scroll_case* c = &bg_zone_controller_zone_0_scroll_cases[row];
    u32 observed_values[5];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = c->x_pos_hi;
    background_objects[0].unk14.i.hi = c->unk14_hi;
    obj.ext.effect_8.unk17 = c->unk17;
    obj.ext.effect_8.unk16 = 0;
    bg_zone_controller_zone_0_scroll(&obj);
    observed_values[0] = (u32)background_objects[1].unk4C;
    observed_values[1] = (u32)background_objects[1].x_pos.i.hi;
    observed_values[2] = (u32)obj.ext.effect_8.unk16;
    observed_values[3] = (u32)obj.ext.effect_8.unk17;
    observed_values[4] = (u32)obj.ext.effect_8.unk18;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "bg_zone_controller_zone_0_scroll", 0, 0, 2, test_bg_zone_controller_zone_0_scroll },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
