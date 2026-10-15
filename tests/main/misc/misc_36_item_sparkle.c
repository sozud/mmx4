#include "test_runtime.h"

static const u32 func_800CF300_expected[] = { 0u, 0u, 1u, 5u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_800CF300(u32 row)
{
    u32 observed_values[10];
    struct MiscObj obj;
    struct AnimatedObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&cur_random, 0, sizeof(cur_random));
    child_0_present = 255;
    obj.unk2 = -1;
    obj.ext.pointer.unk50 = child_0_present ? &child_0 : NULL;
    func_800CF300(&obj);
    observed_values[0] = (u32)child_0.unk42;
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk16;
    observed_values[4] = (u32)obj.unk28;
    observed_values[5] = (u32)obj.unk2C;
    observed_values[6] = (u32)obj.unk40;
    observed_values[7] = (u32)obj.unk42;
    observed_values[8] = (u32)obj.x_vel.val;
    observed_values[9] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, func_800CF300_expected, 10);
}

const struct CTestGroup c_test_groups[] = {
    { "func_800CF300", 0, 0, 1, test_func_800CF300 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
