#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 armored_walker_check_wall_expected[] = { 0u, 2u, 0u };
static u32 test_armored_walker_check_wall(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk5 = 2;
    obj.unk15 = 255;
    armored_walker_check_wall(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, armored_walker_check_wall_expected, 3);
}

static const u32 inputs_0[2][1] = {
    { 0 },
    { 30 },
};
struct armored_walker_turn_pause_case {
    u32 expected[4];
};
static const struct armored_walker_turn_pause_case armored_walker_turn_pause_cases[] = {
    { { 2u, 0u, 0u, 0u } },
    { { 0u, 0u, 0x1Du, 0u } },
};
static u32 test_armored_walker_turn_pause(u32 row)
{
    const struct armored_walker_turn_pause_case* c = &armored_walker_turn_pause_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = inputs_0[row][0];
    armored_walker_turn_pause(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.x_accel;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "armored_walker_check_wall", 0, 0, 1, test_armored_walker_check_wall },
    { "armored_walker_turn_pause", 0, 0, 2, test_armored_walker_turn_pause },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 2;
