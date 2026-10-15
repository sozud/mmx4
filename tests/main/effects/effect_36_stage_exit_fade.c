#include "test_runtime.h"

#include "support/pool_full.h"
static u32 pool_full_stage_exit_fade_init(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    stage_exit_fade_init(&pf_effect);
    pf_effect_expected.ext.effect_36.timer = 0x1E;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_stage_exit_fade_init,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases);
