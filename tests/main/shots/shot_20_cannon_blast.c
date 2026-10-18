#include "test_runtime.h"
#include "main/shots/shot_20_cannon_blast.h"

struct func_8009D048_case {
    u32 value, unk2, v_0_x_pos_hi, child_0_x_pos_hi;
    u32 expected[3];
};
static const struct func_8009D048_case func_8009D048_cases[] = {
    { 1, -1, 0, 32940, { 1u, 0u, 0x181u } },
    { 70, 0, -8192, 1024, { 1u, 0x45u, 0xFFFFE129u } },
};
static u32 test_func_8009D048(u32 row)
{
    const struct func_8009D048_case* c = &func_8009D048_cases[row];
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    child_0_present = 255;
    obj.unk84.value = c->value;
    obj.unk2 = c->unk2;
    background_objects[0].x_pos.i.hi = c->v_0_x_pos_hi;
    child_0.x_pos.u.hi = c->child_0_x_pos_hi;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_8009D048(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk84.value;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

const struct CTestGroup c_test_groups[] = {
    { "func_8009D048", 0, 0, 2, test_func_8009D048 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
