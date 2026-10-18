#include "test_runtime.h"
#include "main/quads/quad_00_search_light.h"

static const u32 search_light_is_visible_expected[] = { 0u };
static u32 test_search_light_is_visible(u32 row)
{
    u32 observed_values[1];
    struct QuadObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.x_pos.u.hi = 35976;
    background_objects[0].x_pos.u.hi = 23552;
    obj.y_pos.u.hi = 57593;
    background_objects[0].y_pos.u.hi = 33792;
    obj.vertices[1].x.i.hi = -28672;
    obj.vertices[0].x.i.hi = 0;
    obj.vertices[3].y.i.hi = 7945;
    obj.vertices[0].y.i.hi = 0;
    obj.vertices[0].x.u.hi = 49408;
    obj.vertices[0].y.u.hi = 16400;
    return_value = search_light_is_visible(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, search_light_is_visible_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "search_light_is_visible", 0, 0, 1, test_search_light_is_visible },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
