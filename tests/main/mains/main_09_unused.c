#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/mains/main_09_unused.h"

static void u9_update(void)
{
    state_reset(0, 0, 0);
    unused_main_09_update(&so);
}

static void (*const unused_09_misc_cases[])(void) = {
    u9_update,
};
static const u32 unused_09_misc_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_unused_09_misc(u32 row)
{
    return state_run(unused_09_misc_cases[row], row, &unused_09_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "unused_09_misc", 0, 0, COUNT(unused_09_misc_cases), test_unused_09_misc },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(unused_09_misc_cases);
