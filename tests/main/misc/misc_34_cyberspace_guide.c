#include "test_runtime.h"
#include "main/misc/misc_34_cyberspace_guide.h"

struct func_800CEFC0_case {
    u32 variant, checkpoint, unk58, unk57, unk17;
    u32 expected[4];
};
static const struct func_800CEFC0_case func_800CEFC0_cases[] = {
    { 2, 0, 0, 0, 0, { 0u, 0u, 0u, 2u } },
    { 240, -115, 0, 254, 0, { 0u, 1u, 0u, 2u } },
    { 242, -117, 60, 31, 3, { 0x20u, 0u, 0u, 0xF2u } },
};
static u32 test_func_800CEFC0(u32 row)
{
    const struct func_800CEFC0_case* c = &func_800CEFC0_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.ext.misc_34.enabled = 255;
    obj.ext.misc_34.variant = c->variant;
    engine_obj.checkpoint = c->checkpoint;
    obj.ext.misc_34.unk58 = c->unk58;
    obj.ext.misc_34.unk57 = c->unk57;
    obj.unk17 = c->unk17;
    func_800CEFC0(&obj);
    observed_values[0] = (u32)obj.ext.misc_34.unk57;
    observed_values[1] = (u32)obj.ext.misc_34.unk58;
    observed_values[2] = (u32)obj.ext.misc_34.unk5A;
    observed_values[3] = (u32)obj.ext.misc_34.variant;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "func_800CEFC0", 0, 0, 3, test_func_800CEFC0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3;
