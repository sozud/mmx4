#include "test_runtime.h"
#include "main/object_motion.h"

static u32 minimum_x(void)
{
    return angle_from_delta((s32)0x80000000u, 0);
}
static u32 minimum_y(void)
{
    return angle_from_delta(0, (s32)0x80000000u);
}
static const CTestCase angle_minimum_axes_cases[] = {
    minimum_x,
    minimum_y,
};
static const u32 angle_minimum_axes_cases_expected[] = { 0x0u, 0x18u };

#define ANGLE_CASE(name, x, y)         \
    static u32 name(void)              \
    {                                  \
        return angle_from_delta(x, y); \
    }
ANGLE_CASE(negative_xy, -0x20000, -0x10000)
ANGLE_CASE(negative_x, -0x10000, 0x20000)
ANGLE_CASE(negative_y, 0x10000, -0x20000)
ANGLE_CASE(positive_xy, 0x20000, 0x10000)
ANGLE_CASE(small_y, -1, -1)
ANGLE_CASE(zero_delta, 0, 0)
#define ENTRY(name) name,
static const CTestCase angle_quadrants_cases[] = {
    ENTRY(negative_xy)
        ENTRY(negative_x)
            ENTRY(negative_y)
                ENTRY(positive_xy)
                    ENTRY(small_y)
                        ENTRY(zero_delta)
};
static const u32 angle_quadrants_cases_expected[] = { 0x1Eu, 0x6u, 0x16u, 0xEu, 0x0u, 0x10u };
#undef ANGLE_CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "angle_minimum_axes", angle_minimum_axes_cases, angle_minimum_axes_cases_expected, COUNT(angle_minimum_axes_cases), 0 },
    { "angle_quadrants", angle_quadrants_cases, angle_quadrants_cases_expected, COUNT(angle_quadrants_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(angle_minimum_axes_cases) + COUNT(angle_quadrants_cases);
