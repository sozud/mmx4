#include "test_runtime.h"

static const u32 func_800A9544_expected[] = { 2u, 0xFFFFFFA6u, 0u, 0x30u, 0xFFFFFFE0u };
static u32 test_func_800A9544(u32 row)
{
    u32 observed_values[5];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0_present = 255;
    obj.unk94 = 7;
    obj.unk96 = 1;
    obj.unk15 = 255;
    child_0.y_pos.i.hi = 10;
    child_0.state = 2;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_800A9544(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk90.i.hi;
    observed_values[2] = (u32)obj.unk90.i.lo;
    observed_values[3] = (u32)obj.x_pos.i.hi;
    observed_values[4] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_800A9544_expected, 5);
}

static const u32 inputs_0[2][4] = {
    { 255, 0, 0, 0 },
    { 255, 0, 0, -1 },
};
struct sigma_shot_flash_case {
    u32 expected[3];
};
static const struct sigma_shot_flash_case sigma_shot_flash_cases[] = {
    { { 2u, 0u, 0u } },
    { { 0u, 0u, 0u } },
};
static u32 test_sigma_shot_flash(u32 row)
{
    const struct sigma_shot_flash_case* c = &sigma_shot_flash_cases[row];
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = inputs_0[row][0];
    child_0.x_pos.u.hi = inputs_0[row][1];
    child_0.y_pos.u.hi = inputs_0[row][2];
    obj.animation_step.fields.relative_step = inputs_0[row][3];
    obj.unk7C = child_0_present ? &child_0 : NULL;
    sigma_shot_flash(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.x_pos.u.hi;
    observed_values[2] = (u32)obj.y_pos.u.hi;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

const struct CTestGroup c_test_groups[] = {
    { "func_800A9544", 0, 0, 1, test_func_800A9544 },
    { "sigma_shot_flash", 0, 0, 2, test_sigma_shot_flash },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 2;
