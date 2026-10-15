#include "test_runtime.h"

static const u32 inputs_0[5][6] = {
    { -1, 2, 0, 0, 0, 0 },
    { -1, 0, -1, 255, 0, 0 },
    { -1, 0, -1, 0, 255, 0 },
    { -1, 0, -1, 0, 0, 0 },
    { -1, 0, -1, 0, 0, 255 },
};
struct func_8008A8E4_case {
    u32 expected[4];
};
static const struct func_8008A8E4_case func_8008A8E4_cases[] = {
    { { 0u, 0u, 2u, 0xFFFFFFFFu } },
    { { 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 0u, 0xFFFFFFFFu } },
    { { 0u, 0u, 0u, 0u } },
};
static u32 test_func_8008A8E4(u32 row)
{
    const struct func_8008A8E4_case* c = &func_8008A8E4_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk6 = inputs_0[row][0];
    obj.ext.main_71.unk8D = inputs_0[row][1];
    obj.animation_step.fields.relative_step = inputs_0[row][2];
    obj.ext.main_71.unk86 = inputs_0[row][3];
    obj.ext.main_71.unk87 = inputs_0[row][4];
    obj.ext.main_71.unk8A = inputs_0[row][5];
    func_8008A8E4(&obj);
    observed_values[0] = (u32)obj.contact_damage;
    observed_values[1] = (u32)obj.ext.main_71.unk84;
    observed_values[2] = (u32)obj.ext.main_71.unk8D;
    observed_values[3] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

static const u32 ride_armor_pilot_spawn_dust_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_ride_armor_pilot_spawn_dust(u32 row)
{
    u32 observed_values[9];
    struct VisualObj obj;
    u8 pool_0_full;
    u8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    ride_armor_pilot_spawn_dust(&obj, arg1);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].unk15;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].x_pos.val;
    observed_values[8] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, ride_armor_pilot_spawn_dust_expected, 9);
}

const struct CTestGroup c_test_groups[] = {
    { "func_8008A8E4", 0, 0, 5, test_func_8008A8E4 },
    { "ride_armor_pilot_spawn_dust", 0, 0, 1, test_ride_armor_pilot_spawn_dust },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 5 + 1;
