#include "test_runtime.h"
#include "main/effects/effect_43_sigma_collapse.h"

static const u32 sigma_collapse_init_expected[] = { 2u };
static u32 test_sigma_collapse_init(u32 row)
{
    u32 observed_values[1];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = -1;
    sigma_collapse_init(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, sigma_collapse_init_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_collapse_init", 0, 0, 1, test_sigma_collapse_init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
