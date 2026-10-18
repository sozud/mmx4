#include "test_runtime.h"
#include "main/misc/misc_15_vent.h"

#include "support/pool_full.h"
static u32 pool_full_vent_spawn_mixed_puffs_one(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_mixed_puffs(&pf_misc, 1);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_vent_spawn_mixed_puffs_none(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_mixed_puffs(&pf_misc, 0);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_vent_spawn_puffs_one(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_puffs(&pf_misc, 1);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_vent_spawn_puffs_none(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    vent_spawn_puffs(&pf_misc, 0);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_vent_spawn_mixed_puffs_one,
    pool_full_vent_spawn_mixed_puffs_none,
    pool_full_vent_spawn_puffs_one,
    pool_full_vent_spawn_puffs_none,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u, 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases);
