#include "test_runtime.h"

struct colonel_beam_widen_case {
    u32 v_2_x_hi, v_3_x_hi;
    u32 expected[5];
};
static const struct colonel_beam_widen_case colonel_beam_widen_cases[] = {
    { 6, -62, { 0u, 3u, 0xFFFFFFFDu, 0u, 0xFFFFFFC8u } },
    { -2170, 32762, { 1u, 3u, 0xFFFFFFFDu, 0xFFFFF780u, 0xFFFF8000u } },
};
static u32 test_colonel_beam_widen(u32 row)
{
    const struct colonel_beam_widen_case* c = &colonel_beam_widen_cases[row];
    u32 observed_values[5];
    struct QuadObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.vertices[2].x.i.hi = c->v_2_x_hi;
    obj.vertices[3].x.i.hi = c->v_3_x_hi;
    colonel_beam_widen(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.vertices[0].x.i.hi;
    observed_values[2] = (u32)obj.vertices[1].x.i.hi;
    observed_values[3] = (u32)obj.vertices[2].x.i.hi;
    observed_values[4] = (u32)obj.vertices[3].x.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "colonel_beam_widen", 0, 0, 2, test_colonel_beam_widen },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
