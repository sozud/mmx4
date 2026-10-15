#include "test_runtime.h"

#include "support/pool_full.h"
static u32 pool_full_ride_armor_shot_visual(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    func_80098EA8(WEAPON_OBJECT(&pf_self));
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_ride_armor_shot_visual,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases);
