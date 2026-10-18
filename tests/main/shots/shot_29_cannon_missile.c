#include "test_runtime.h"
#include "main/shots/shot_29_cannon_missile.h"

static const u32 cannon_missile_slow_expected[] = { 0u, 0u, 0u, 0u, 0xFFu, 0u, 0u };
static u32 test_cannon_missile_slow(u32 row)
{
    u32 observed_values[7];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk8C.shot_29.timer = 1;
    obj.unk90.bytes[1] = 255;
    obj.unk2 = -1;
    obj.y_vel.val = 1048576;
    cannon_missile_slow(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk8C.shot_29.timer;
    observed_values[3] = (u32)obj.unk8C.shot_29.unk8D;
    observed_values[4] = (u32)obj.unk90.bytes[1];
    observed_values[5] = (u32)obj.x_vel.val;
    observed_values[6] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, cannon_missile_slow_expected, 7);
}

static const u32 inputs_0[3][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 255, 0, 255, 0 },
    { 0, 0, 0, 0, 255, 255, 0, 0 },
};
struct cannon_missile_track_case {
    u32 expected[14];
};
static const struct cannon_missile_track_case cannon_missile_track_cases[] = {
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0x21u, 0u, 0x17u, 0u, 7u, 0u, 1u, 0xFFFFFFF0u, 0u, 0u, 0u, 0u, 1u, 0u } },
    { { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u } },
};
static u32 test_cannon_missile_track(u32 row)
{
    const struct cannon_missile_track_case* c = &cannon_missile_track_cases[row];
    u32 observed_values[14];
    struct ShotObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.unk8C.bytes[1] = inputs_0[row][0];
    obj.y_pos.i.hi = inputs_0[row][1];
    g_Player.y_pos.i.hi = inputs_0[row][2];
    obj.unk8C.bytes[2] = inputs_0[row][3];
    obj.unk90.bytes[1] = inputs_0[row][4];
    pool_0_full = inputs_0[row][5];
    obj.unk15 = inputs_0[row][6];
    obj.x_pos.i.hi = inputs_0[row][7];
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    cannon_missile_track(&obj);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].ext.misc_5.animation;
    observed_values[2] = (u32)misc_objects[0].id;
    observed_values[3] = (u32)misc_objects[0].unk15;
    observed_values[4] = (u32)misc_objects[0].unk16;
    observed_values[5] = (u32)misc_objects[0].unk2;
    observed_values[6] = (u32)misc_objects[0].unk7;
    observed_values[7] = (u32)misc_objects[0].x_pos.i.hi;
    observed_values[8] = (u32)misc_objects[0].x_vel.val;
    observed_values[9] = (u32)misc_objects[0].y_pos.i.hi;
    observed_values[10] = (u32)misc_objects[0].y_vel.val;
    observed_values[11] = (u32)obj.unk8C.bytes[1];
    observed_values[12] = (u32)obj.unk8C.bytes[2];
    observed_values[13] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

const struct CTestGroup c_test_groups[] = {
    { "cannon_missile_slow", 0, 0, 1, test_cannon_missile_slow },
    { "cannon_missile_track", 0, 0, 3, test_cannon_missile_track },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 3;
