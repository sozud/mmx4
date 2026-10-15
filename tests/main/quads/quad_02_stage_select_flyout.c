#include "test_runtime.h"

struct stage_select_flyout_wait_case {
    u32 unk7;
    u32 expected[2];
};
static const struct stage_select_flyout_wait_case stage_select_flyout_wait_cases[] = {
    { 0, { 0u, 0u } },
    { -1, { 0u, 0xFFFFFFFEu } },
};
static u32 test_stage_select_flyout_wait(u32 row)
{
    const struct stage_select_flyout_wait_case* c = &stage_select_flyout_wait_cases[row];
    u32 observed_values[2];
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7 = c->unk7;
    stage_select_flyout_wait(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk7;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "stage_select_flyout_wait", 0, 0, 2, test_stage_select_flyout_wait },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
