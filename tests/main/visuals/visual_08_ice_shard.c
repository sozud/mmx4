#include "test_runtime.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "support/state_cases.h"
void ice_shard_idle(struct VisualObj*);

static u32 dust_case(u32 mode, u32 observation)
{
    struct VisualObj before[32];
    u32 i, j, actual;
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < COUNT(visual_objects); i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x35;
        visual_objects[i].unk2 = 0x27;
        visual_objects[i].unk5 = 0x25;
        visual_objects[i].unk6 = 0x26;
        visual_objects[i].unk7 = 0x37;
        visual_objects[i].x_pos.val = 0x13572468;
        visual_objects[i].y_pos.val = 0x24681357;
        visual_objects[i].x_vel.val = 0x23456789;
        visual_objects[i].y_vel.val = 0x3456789A;
        visual_objects[i].unk15 = PLAYER_FACING_RIGHT;
        visual_objects[i].unk5C.value = 0x73;
    }
    if (mode != 0)
        visual_objects[3].active = 0;
    cur_random = 0xACE1;
    memcpy(before, visual_objects, sizeof(before));
    func_800B10E4(0xA0, 10, 20, mode == 2 ? 9 : 10, mode == 2 ? 19 : 20, mode == 0 ? 2 : 1);
    for (i = 0; i < COUNT(visual_objects); i++) {
        struct VisualObj expected = before[i];
        if (mode != 0 && i == 3) {
            expected.active = 0x21;
            expected.id = 9;
            expected.unk2 = 0;
            expected.x_pos.i.hi = visual_objects[i].x_pos.i.hi;
            expected.x_pos.i.lo = 0;
            expected.y_pos.i.hi = visual_objects[i].y_pos.i.hi;
            expected.y_pos.i.lo = 0;
            expected.x_vel.val = 0;
            expected.y_vel.val = 0;
#ifdef VERSION_DEMO
            expected.unk15 = visual_objects[i].unk15 & PLAYER_FACING_RIGHT;
#else
            expected.unk15 = 0;
#endif
            expected.unk5C.value = 10;
            expected.state = 0;
            expected.unk5 = 0;
            expected.unk6 = 0;
        }
        for (j = 0; j < sizeof(expected) / 4; j++)
            assert(((u32*)&visual_objects[i])[j] == ((u32*)&expected)[j]);
    }
    switch (observation) {
    case 0:
        actual = visual_objects[3].x_pos.val;
        break;
    case 1:
        actual = visual_objects[3].y_pos.val;
        break;
    case 2:
        actual = visual_objects[3].x_vel.val;
        break;
    case 3:
        actual = visual_objects[3].y_vel.val;
        break;
    case 4:
        actual = (u8)visual_objects[3].active | ((u32)(u8)visual_objects[3].id << 8) | ((u32)(u8)visual_objects[3].unk2 << 16) | ((u32)visual_objects[3].unk5C.value << 24);
        break;
    default:
        actual = cur_random;
        break;
    }
    return actual;
}
static const u32 dust_rect_context_cases_expected[] = { 0x13572468u, 0x24681357u, 0x23456789u, 0x3456789Au, 0x73273501u, 0xACE1u, 0xA0000u, 0x140000u, 0x0u, 0x0u, 0xA000921u, 0xBAF3u, 0xA0000u, 0x140000u, 0x0u, 0x0u, 0xA000921u, 0xBAF3u };
static u32 dust_rect_context_cases_row(u32 row)
{
    return dust_case(row / 6, row % 6);
}

static struct ShardInput {
    s32 type, mode, radius;
    u8 facing, full;
    u16 seed;
};
static const struct ShardInput inputs[] = {
    { 0x21, 1, 0, 0, 0, 36437 },
    { 0x22, 1, -6, 0x40, 0, 0xACE1 },
    { 0x20, 4, 0, 0x40, 0, 11331 },
    { 0x20, 5, 0, 0, 1, 0xACE1 },
};
static u32 shard_case(u32 mode, u32 observation)
{
    struct MainObj source, source_before;
    struct PlayerObj player_before;
    struct VisualObj pool_before[32];
    struct Unk_unk68 bounds = { 2, -3, 3, 3 };
    struct Unk_unk68 bounds_before = bounds;
    const struct ShardInput* input = &inputs[mode];
    u32 i, j;
    memset(&source, 0, sizeof(source));
    memset(visual_objects, 0, sizeof(visual_objects));
    source.x_pos.val = 100 * 65536 + 0x1234;
    source.y_pos.val = 200 * 65536 + 0x5678;
    source.unk15 = input->facing;
    source.terrain_box = &bounds;
    for (i = 0; i < COUNT(visual_objects); i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x35;
        visual_objects[i].unk2 = 0x27;
        visual_objects[i].state = 0x26;
        visual_objects[i].unk5 = 0x25;
        visual_objects[i].unk6 = 0x24;
        visual_objects[i].unk15 = PLAYER_FACING_RIGHT;
        visual_objects[i].unk5C.value = 0x73;
        visual_objects[i].x_pos.val = 0x13572468;
        visual_objects[i].y_pos.val = 0x24681357;
        visual_objects[i].x_vel.val = 0x23456789;
        visual_objects[i].y_vel.val = 0x3456789A;
    }
    if (!input->full)
        visual_objects[3].active = 0;
    source_before = source;
    player_before = g_Player;
    memcpy(pool_before, visual_objects, sizeof(pool_before));
    cur_random = input->seed;
    func_800B0CA0(input->type, input->mode, &source, input->radius, 1);
    for (i = 0; i < sizeof(source) / 4; i++)
        assert(((u32*)&source)[i] == ((u32*)&source_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(bounds.unk0 == bounds_before.unk0 && bounds.unk1 == bounds_before.unk1
        && bounds.unk2 == bounds_before.unk2 && bounds.unk3 == bounds_before.unk3);
    for (i = 0; i < COUNT(visual_objects); i++) {
        struct VisualObj expected = pool_before[i];
        if (!input->full && i == 3) {
            expected.active = 0x21;
            expected.id = 9;
            expected.unk2 = 0;
            expected.x_pos = visual_objects[i].x_pos;
            expected.y_pos = visual_objects[i].y_pos;
            expected.x_vel = visual_objects[i].x_vel;
            expected.y_vel = visual_objects[i].y_vel;
#ifdef VERSION_DEMO
            expected.unk15 = visual_objects[i].unk15 & PLAYER_FACING_RIGHT;
#else
            expected.unk15 = 0;
#endif
            expected.state = 0;
            expected.unk5 = 0;
            expected.unk6 = 0;
            expected.unk5C.value = 2;
        }
        for (j = 0; j < sizeof(expected) / 4; j++)
            assert(((u32*)&visual_objects[i])[j] == ((u32*)&expected)[j]);
    }
    switch (observation) {
    case 0:
        return visual_objects[3].x_pos.val;
    case 1:
        return visual_objects[3].y_pos.val;
    case 2:
        return visual_objects[3].x_vel.val;
    case 3:
        return visual_objects[3].y_vel.val;
    case 4:
        return (u8)visual_objects[3].active | ((u32)(u8)visual_objects[3].id << 8)
            | ((u32)(u8)visual_objects[3].unk2 << 16) | ((u32)(u8)visual_objects[3].unk5C.value << 24);
    case 5:
        return visual_objects[3].state | ((u32)(u8)visual_objects[3].unk5 << 8)
            | ((u32)(u8)visual_objects[3].unk6 << 16) | ((u32)C_TEST_PSX_FACING(visual_objects[3].unk15) << 24);
    default:
        return cur_random;
    }
}
static const u32 ice_shard_context_cases_expected[] = { 0x630000u, 0xC20000u, 0x0u, 0x10000u, 0x2000921u, DEMO_ALT(0x0u, 0x40000000u), DEMO_ALT(0x607u, 0x1219u), 0x650000u, 0xCC0000u, 0x18000u, 0x0u, 0x2000921u, 0x0u, DEMO_ALT(0xBAF3u, 0x3023u), 0x5F0000u, 0xC20000u, 0x0u, 0x0u, 0x2000921u, 0x0u, DEMO_ALT(0xFFu, 0x201u), 0x13572468u, 0x24681357u, 0x23456789u, 0x3456789Au, 0x73273501u, 0x40242526u, 0xACE1u };
static u32 ice_shard_context_cases_row(u32 row)
{
    return shard_case(row / 7, row % 7);
}

static const u32 inputs_0[2][10] = {
    { 255, 0, 0, 255, 0, 0, 0, 3, 0, 0 },
    { 255, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
struct func_800B0CA0_case {
    u32 expected[14];
};
static const struct func_800B0CA0_case func_800B0CA0_cases[] = {
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800B0CA0(u32 row)
{
    const struct func_800B0CA0_case* c = &func_800B0CA0_cases[row];
    u32 observed_values[14];
    struct MainObj argument_obj_2;
    struct Unk_unk68 child_0;
    u8 child_0_present;
    u8 pool_0_full;
    s32 type;
    s32 mode;
    s32 radius;
    s32 count;
    memset(&argument_obj_2, 0, sizeof(argument_obj_2));
    memset(&child_0, 0, sizeof(child_0));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    child_0_present = inputs_0[row][0];
    argument_obj_2.x_pos.i.hi = inputs_0[row][1];
    argument_obj_2.y_pos.i.hi = inputs_0[row][2];
    argument_obj_2.unk15 = inputs_0[row][3];
    pool_0_full = inputs_0[row][4];
    visual_objects[0].x_pos.i.hi = inputs_0[row][5];
    type = inputs_0[row][6];
    mode = inputs_0[row][7];
    radius = inputs_0[row][8];
    count = inputs_0[row][9];
    argument_obj_2.terrain_box = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_800B0CA0(type, mode, &argument_obj_2, radius, count);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].state;
    observed_values[3] = (u32)visual_objects[0].unk15;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk5;
    observed_values[6] = (u32)visual_objects[0].unk5C.value;
    observed_values[7] = (u32)visual_objects[0].unk6;
    observed_values[8] = (u32)visual_objects[0].x_pos.i.hi;
    observed_values[9] = (u32)visual_objects[0].x_pos.u.lo;
    observed_values[10] = (u32)visual_objects[0].x_vel.val;
    observed_values[11] = (u32)visual_objects[0].y_pos.i.hi;
    observed_values[12] = (u32)visual_objects[0].y_pos.u.lo;
    observed_values[13] = (u32)visual_objects[0].y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

static void ish_idle(void)
{
    state_reset(0, 0, 0);
    state_room.visual.active = 1;
    ice_shard_idle(&state_room.visual);
}

static void (*const ice_shard_misc_cases[])(void) = {
    ish_idle,
};
static const u32 ice_shard_misc_expected[] = { 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_ice_shard_misc(u32 row)
{
    return object_run(ice_shard_misc_cases[row], row, &ice_shard_misc_expected[row * 10]);
}

static u32 shard_paths(u32 index);
const struct CTestGroup c_test_groups[] = {
    { "shard_paths", 0, 0, 12, shard_paths },
    { "ice_shard_misc", 0, 0, COUNT(ice_shard_misc_cases), test_ice_shard_misc },
    { "dust_rect_context", NULL, dust_rect_context_cases_expected, COUNT(dust_rect_context_cases_expected), dust_rect_context_cases_row },
    { "ice_shard_context", NULL, ice_shard_context_cases_expected, COUNT(ice_shard_context_cases_expected), ice_shard_context_cases_row },
    { "func_800B0CA0", 0, 0, 2, test_func_800B0CA0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ice_shard_misc_cases) + COUNT(dust_rect_context_cases_expected) + COUNT(ice_shard_context_cases_expected) + 2 + 12;

void func_800B08CC(struct VisualObj*);
void func_800B0B48(struct VisualObj*);
void func_800B10E4(u8, s32, s32, s32, s32, s32);
#include "main/object_motion.h"
extern s8 ice_shard_offsets[4][2];
static const struct Unk_unk68 dust_box = { 4, -8, 6, 10 };
static u32 shard_paths(u32 index)
{
    static const u8 scenarios[] = { 0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12 };
    u32 row = scenarios[index];
    static const s16 parent_dx[] = { 40, 0, -40, 0 }, parent_dy[] = { 0, -40, 0, 40 };
    struct VisualObj obj;
    struct MainObj parent;
    struct MovingObj reference;
    u32 i, left = 0, right = 0;
    s32 direction;
    memset(&obj, 0, sizeof(obj));
    memset(&parent, 0, sizeof(parent));
    memset(&reference, 0, sizeof(reference));
    memset(background_objects, 0, sizeof(background_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    cur_random = 0x1234;
    obj.active = 0x21;
    obj.id = 8;
    obj.state = 1;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.unk50 = PLAYER_OBJECT(&parent);
    for (i = 0; i < COUNT(state_table); i++)
        state_table[i] = state_step;
    obj.animation_table = (u32**)state_table;
    obj.animation_cursor = state_step;
    obj.animation_step.packed = state_step[0];
    parent.x_pos.i.hi = 100;
    parent.y_pos.i.hi = 100;
    if (row <= 3) {
        obj.state = 0;
        obj.unk2 = row;
        func_800B08CC(&obj);
        assert(obj.state == 1 && obj.on_screen == 1 && obj.unk17 >= 0xE && obj.unk17 <= 0x10);
        assert(obj.x_pos.i.hi >= 100 + ice_shard_offsets[row][0] && obj.x_pos.i.hi < 100 + ice_shard_offsets[row][0] + 32);
        assert(obj.y_pos.i.hi >= 100 + ice_shard_offsets[row][1] && obj.y_pos.i.hi < 100 + ice_shard_offsets[row][1] + 32);
        return 1;
    }
    if (row <= 9) {
        if (row <= 7) {
            parent.x_pos.i.hi = 100 + parent_dx[row - 4];
            parent.y_pos.i.hi = 100 + parent_dy[row - 4];
        }
        parent.ext.main_14.unk8C = row == 8;
        if (row == 9)
            obj.x_pos.i.hi = parent.x_pos.i.hi = 0x400;
        func_800B0B48(&obj);
        assert(obj.state == (row >= 8 ? 2 : 1));
        if (row <= 7) {
            reference.x_pos = obj.x_pos;
            reference.y_pos = obj.y_pos;
            direction = angle_to_object((struct ObjectHeader*)&reference, OBJECT_HEADER(&parent));
            assert(direction / 8 == (s32)row - 4);
            set_velocity_from_angle(&reference, direction);
            assert(obj.x_vel.val == reference.y_vel.val * -24 && obj.y_vel.val == reference.x_vel.val * 24);
        }
        return 1;
    }
    if (row <= 11) {
        parent.terrain_box = &dust_box;
        func_800B0CA0(0, row == 10 ? 3 : 4, &parent, 0, 2);
        for (i = 0; i < 2; i++) {
            assert(visual_objects[i].active == 0x21 && visual_objects[i].id == 9);
            assert(visual_objects[i].x_pos.i.hi == (row == 10 ? 100 + 4 - 6 : 100 + 4 + 6));
            assert(visual_objects[i].y_pos.i.hi >= 100 - 8 - 10 && visual_objects[i].y_pos.i.hi <= 100 - 8 + 10);
        }
        return 1;
    }
    func_800B10E4(2, 60, 80, 140, 120, 16);
    for (i = 0; i < 16; i++) {
        assert(visual_objects[i].active == 0x21 && visual_objects[i].y_vel.val == 0);
        assert(visual_objects[i].x_vel.val == (visual_objects[i].x_pos.i.hi < 100 ? -0x18000 : 0x18000));
        left += visual_objects[i].x_pos.i.hi < 100;
        right += visual_objects[i].x_pos.i.hi >= 100;
    }
    assert(left != 0 && right != 0);
    return 1;
}
