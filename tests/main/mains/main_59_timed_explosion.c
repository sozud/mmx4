#include "test_runtime.h"
#include "main/mains/main_59_timed_explosion.h"

static const u32 timed_explosion_explode_expected[] = { 1u };
static u32 test_timed_explosion_explode(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    obj.animation_step.fields.relative_step = -128;
    timed_explosion_explode(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, timed_explosion_explode_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "timed_explosion_explode", 0, 0, 1, test_timed_explosion_explode },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
