#include "test_runtime.h"
#include "main/shots/shot_50_double_bouncer.h"

static const u32 double_bouncer_bounce_expected[] = { 1u, 0u, 1u };
static u32 test_double_bouncer_bounce(u32 row)
{
    u32 observed_values[3];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk70 = 15;
    obj.y_vel.val = -1;
    double_bouncer_bounce(&obj);
    observed_values[0] = (u32)obj.unk84.value;
    observed_values[1] = (u32)obj.x_vel.val;
    observed_values[2] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, double_bouncer_bounce_expected, 3);
}

const struct CTestGroup c_test_groups[] = {
    { "double_bouncer_bounce", 0, 0, 1, test_double_bouncer_bounce },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
