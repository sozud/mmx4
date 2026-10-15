#include "test_runtime.h"

static const u32 func_8001D698_expected[] = { 0u, 0u, 0u, 0u, 0u, 1u };
static u32 test_func_8001D698(u32 row)
{
    u32 observed_values[6];
    struct GameInfo obj;
    memset(&obj, 0, sizeof(obj));
    obj.unkC = 3;
    func_8001D698(&obj);
    observed_values[0] = (u32)obj.mode;
    observed_values[1] = (u32)obj.unk0;
    observed_values[2] = (u32)obj.unk2;
    observed_values[3] = (u32)obj.unk3;
    observed_values[4] = (u32)obj.unkC;
    observed_values[5] = (u32)obj.unkD;
    return c_test_observe(0, row, observed_values, func_8001D698_expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "func_8001D698", 0, 0, 1, test_func_8001D698 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
