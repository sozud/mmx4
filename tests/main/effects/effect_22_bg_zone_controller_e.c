#include "test_runtime.h"
#include "main/effects/effect_20_bg_zone_controller_d.h"
#include "main/effects/effect_22_bg_zone_controller_e.h"

struct bg_zone_controller_e_zone_0_scroll_case {
    u32 x_pos_hi, unk14_hi, unk17;
    u32 expected[5];
};
static const struct bg_zone_controller_e_zone_0_scroll_case bg_zone_controller_e_zone_0_scroll_cases[] = {
    { -32768, 0, 8, { 0u, 0u, 0u, 0u, 0xFFFFFFF8u } },
    { -16625, -18673, -8, { 0u, 0u, 0u, 0u, 8u } },
};
static u32 test_bg_zone_controller_e_zone_0_scroll(u32 row)
{
    const struct bg_zone_controller_e_zone_0_scroll_case* c = &bg_zone_controller_e_zone_0_scroll_cases[row];
    u32 observed_values[5];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = c->x_pos_hi;
    background_objects[0].unk14.i.hi = c->unk14_hi;
    obj.ext.effect_22.unk17 = c->unk17;
    obj.ext.effect_22.unk18 = 0;
    obj.ext.effect_22.unk16 = 0;
    bg_zone_controller_e_zone_0_scroll(&obj);
    observed_values[0] = (u32)background_objects[1].unk4C;
    observed_values[1] = (u32)background_objects[1].x_pos.i.hi;
    observed_values[2] = (u32)obj.ext.effect_22.unk16;
    observed_values[3] = (u32)obj.ext.effect_22.unk17;
    observed_values[4] = (u32)obj.ext.effect_22.unk18;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

#include "support/background_zone.h"
ZONE_CASE(1, 0)
ZONE_CASE(1, 1)
static const CTestCase zone_e_dispatch_cases[] = { ZONE_ENTRY(1, 0) ZONE_ENTRY(1, 1) };

static const u32 zone_e_dispatch_cases_expected[] = { 0x77770124u, 0x77770005u };
const struct CTestGroup c_test_groups[] = {
    { "bg_zone_controller_e_zone_0_scroll", 0, 0, 2, test_bg_zone_controller_e_zone_0_scroll },
    { "zone_e_dispatch", zone_e_dispatch_cases, zone_e_dispatch_cases_expected, COUNT(zone_e_dispatch_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + COUNT(zone_e_dispatch_cases);
