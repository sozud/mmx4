#include "test_runtime.h"

struct falling_icicle_resume_step_case {
    u32 saved_unk5;
    u32 expected[1];
};
static const struct falling_icicle_resume_step_case falling_icicle_resume_step_cases[] = {
    { 0, { 0u } },
    { 4, { 4u } },
};
static u32 test_falling_icicle_resume_step(u32 row)
{
    const struct falling_icicle_resume_step_case* c = &falling_icicle_resume_step_cases[row];
    u32 observed_values[1];
    struct MainObj obj, before;
    memset(&obj, 0, sizeof(obj));
    obj.unk5 = 1;
    obj.x_pos.val = 305419896;
    obj.ext.main_21.saved_unk5 = c->saved_unk5;
    before = obj;
    before.unk5 = before.ext.main_21.saved_unk5;
    falling_icicle_resume_step(&obj);
    c_test_same_words(&obj, &before, sizeof(obj));
    observed_values[0] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "falling_icicle_resume_step", 0, 0, 2, test_falling_icicle_resume_step },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
