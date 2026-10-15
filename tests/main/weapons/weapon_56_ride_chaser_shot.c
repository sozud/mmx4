#include "test_runtime.h"

static const u32 ride_chaser_shot_follow_scroll_expected[] = { 0u, 0u };
static u32 test_ride_chaser_shot_follow_scroll(u32 row)
{
    u32 observed_values[2];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    background_objects[0].unk4 = 0;
    background_objects[0].x_pos.u.hi = 0;
    background_objects[0].unk14.u.hi = 0;
    background_objects[0].y_pos.u.hi = 0;
    background_objects[0].unk18.u.hi = 0;
    ride_chaser_shot_follow_scroll(&obj);
    observed_values[0] = (u32)obj.x_pos.u.hi;
    observed_values[1] = (u32)obj.y_pos.u.hi;
    return c_test_observe(0, row, observed_values, ride_chaser_shot_follow_scroll_expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "ride_chaser_shot_follow_scroll", 0, 0, 1, test_ride_chaser_shot_follow_scroll },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
