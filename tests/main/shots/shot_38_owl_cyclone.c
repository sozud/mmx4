#include "test_runtime.h"

#include "support/pool_full.h"
static u32 pool_full_owl_cyclone_spawn_trail(void)
{
    u32 actual;
    pf_prepare();
    pf_shot.unk84.value = 0;
    pf_snapshot();
    owl_cyclone_spawn_trail(&pf_shot);
    pf_shot_expected.unk84.value = 5;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_owl_cyclone_spawn_trail,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases);
