#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 func_800204CC_expected[] = { 0u };
static u32 test_func_800204CC(u32 row)
{
    u32 observed_values[1];
    s8 obj;
    s32 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    controller_input.pressed = 20560;
    obj = 0;
    arg1 = 0;
    func_800204CC(&obj, arg1);
    observed_values[0] = (u32)obj;
    return c_test_observe(0, row, observed_values, func_800204CC_expected, 1);
}
#undef controller_input

const struct CTestGroup c_test_groups[] = {
    { "func_800204CC", 0, 0, 1, test_func_800204CC },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
