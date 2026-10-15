#include "test_runtime.h"
s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);

static u32 overlap_left(u8 facing)
{
    struct MainObj first, second;
    struct Unk_unk68 first_box = { 0, 0, 4, 4 };
    struct Unk_unk68 second_box = { 0, 0, 4, 4 };
    s16 x = -100, y = 100;
    s32 hit;
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    first.attack_box = &first_box;
    second.hurt_box = &second_box;
    first.unk15 = second.unk15 = facing;
    first.x_pos.i.hi = first.y_pos.i.hi = 10;
    second.x_pos.i.hi = second.y_pos.i.hi = 8;
    hit = func_8002BD58(&first, &second, &x, &y);
    assert(hit == 1);
    assert(first.attack_box == &first_box && second.hurt_box == &second_box);
    assert(first.x_pos.i.hi == 10 && first.y_pos.i.hi == 10);
    assert(second.x_pos.i.hi == 8 && second.y_pos.i.hi == 8);
    return (u16)x | ((u32)(u16)y << 16);
}
static u32 normal_left(void)
{
    return overlap_left(0);
}
static u32 mirrored_left(void)
{
    return overlap_left(0x40);
}
static const CTestCase collision_output_edges_cases[] = {
    normal_left,
    mirrored_left,
};
static const u32 collision_output_edges_cases_expected[] = { 0xB000Bu, 0xB0009u };

struct func_8002C36C_case {
    u32 slot;
    u32 expected[8];
};
static const struct func_8002C36C_case func_8002C36C_cases[] = {
    { 1, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 255, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_8002C36C(u32 row)
{
    const struct func_8002C36C_case* c = &func_8002C36C_cases[row];
    u32 observed_values[8];
    struct PlayerObj obj;
    struct PlayerObj argument_obj_1;
    struct Unk_unk68 child_0;
    u8 child_0_present;
    struct Unk_unk68 child_1;
    u8 child_1_present;
    s32 slot;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    child_0_present = 0;
    child_1_present = 0;
    slot = c->slot;
    obj.unk68 = child_0_present ? &child_0 : NULL;
    argument_obj_1.unk68 = child_1_present ? &child_1 : NULL;
    func_8002C36C(&obj, &argument_obj_1, slot);
    observed_values[0] = (u32)argument_obj_1.unk71;
    observed_values[1] = (u32)argument_obj_1.wall_climbable;
    observed_values[2] = (u32)obj.unk72;
    observed_values[3] = (u32)obj.unk73;
    observed_values[4] = (u32)obj.unk74;
    observed_values[5] = (u32)obj.unk76;
    observed_values[6] = (u32)obj.unk77;
    observed_values[7] = (u32)obj.unk78;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

const struct CTestGroup c_test_groups[] = {
    { "collision_output_edges", collision_output_edges_cases, collision_output_edges_cases_expected, COUNT(collision_output_edges_cases), 0 },
    { "func_8002C36C", 0, 0, 2, test_func_8002C36C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(collision_output_edges_cases) + 2;
