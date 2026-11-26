#include "test_runtime.h"
#include "main/effects/effect_16_autoscroll_segment.h"

struct Effect16Coordinate {
    s16 primary;
    s16 secondary;
};
extern struct Effect16Coordinate autoscroll_segment_bounds[];
static u32 autoscroll(s16 behind)
{
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = autoscroll_segment_bounds[0].primary - behind;
    obj.active = 1;
    obj.state = 1;
    autoscroll_segment_update(&obj);
    return obj.state;
}
static u32 as_scrolling(void) { return autoscroll(1); }
static u32 as_reached(void) { return autoscroll(0); }
static const CTestCase autoscroll_segment_wait_cases[] = {
    as_scrolling,
    as_reached,
};
static const u32 autoscroll_segment_wait_cases_expected[] = { 1u, 2u };

const struct CTestGroup c_test_groups[] = {
    { "autoscroll_segment_wait", autoscroll_segment_wait_cases, autoscroll_segment_wait_cases_expected, COUNT(autoscroll_segment_wait_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(autoscroll_segment_wait_cases);
