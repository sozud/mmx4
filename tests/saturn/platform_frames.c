// saturn-capability: vblank
// saturn-step-budget: 100000000
#include "test_runtime.h"
#include "support/saturn_disc.h"

extern u16 saturn_vblank_count;
extern volatile s32 saturn_smpc_result;

static u32 peripheral_start(u32 row)
{
    saturn_vblank_count = 0;
    saturn_smpc_result = -1;
    test_vblank_startup();
    assert(saturn_vblank_count >= 5);
    assert(saturn_smpc_result == 0);
    return saturn_vblank_count >= 5;
}

const struct CTestGroup c_test_groups[] = {
    { "peripheral_start", 0, 0, 1, peripheral_start },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
