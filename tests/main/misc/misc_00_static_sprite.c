#include "test_runtime.h"

#include "support/pool_full.h"
static u32 pool_full_spawn_common_effect(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spawn_common_effect(&pf_self, 0);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_spawn_common_effect,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases);
