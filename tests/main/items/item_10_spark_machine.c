#include "test_runtime.h"
#include "main/items/item_10_spark_machine.h"

#include "support/pool_full.h"
static u32 pool_full_spark_machine_spawn_spark_a(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spark_machine_spawn_spark_a(&pf_item);
    pf_item_expected.tail_ext.unk2.timer = 10;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_spark_machine_spawn_spark_b(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spark_machine_spawn_spark_b(&pf_item);
    pf_item_expected.tail_ext.unk2.previous_value = 15;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_spark_machine_spawn_spark_c(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spark_machine_spawn_spark_c(&pf_item);
    pf_item_expected.tail_ext.unk2.value = 12;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_spark_machine_spawn_spark_a,
    pool_full_spark_machine_spawn_spark_b,
    pool_full_spark_machine_spawn_spark_c,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases);
