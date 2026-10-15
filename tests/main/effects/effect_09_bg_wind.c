#include "test_runtime.h"

static const u32 bg_wind_delay_expected[] = { 0u, 0xFFFFFFFFu, 0u, 0u };
static u32 test_bg_wind_delay(u32 row)
{
    u32 observed_values[4];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    bg_wind_delay(&obj);
    observed_values[0] = (u32)obj.ext.effect_9.direction;
    observed_values[1] = (u32)obj.ext.effect_9.transition_timer;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, bg_wind_delay_expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "bg_wind_delay", 0, 0, 1, test_bg_wind_delay },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
