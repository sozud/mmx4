#include "test_runtime.h"
#include "main/shots/shot_45_colonel_shot.h"
#include "main/55C4.h"
extern void* D_80104770[25];
extern s8 colonel_shot_boxes[14][4];

static u32 bolt_case(u32 observation)
{
    struct ShotObj obj, before;
    u8 box[4] = { 1, 2, 3, 4 };
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 45;
    obj.state = 1;
    obj.unk2 = 1;
    obj.unk5 = 3;
    obj.unk6 = 0x27;
    obj.unk5C = 0x25;
    obj.unk60 = 0x26;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.unk28 = 0x1234;
    obj.unk2C = 0x5678;
    obj.unk58.data = obj.unk54 = obj.unk50.data = box;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)D_80104770;
    set_animation(&obj, 0);
    before = obj;
    colonel_bolt_start(&obj);
    before.unk17 = 15;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = D_80104770[15];
    before.animation_step = *(union AnimationStep*)D_80104770[15];
    before.unk5C = 5;
    before.unk60 = 9;
    before.x_vel.val = 0;
    before.y_vel.val = 8 * 65536;
    before.unk28 = before.unk2C = 0;
    before.unk58.data = before.unk54 = NULL;
    before.unk50.data = (const u8*)colonel_shot_boxes[10];
    before.unk6 = 0x28;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < 4; i++)
        assert(box[i] == i + 1);
    return observation == 0 ? obj.animation_step.packed : (u8)obj.unk6 | ((u32)obj.unk5C << 8) | ((u32)obj.unk60 << 16);
}
#define CASE(n)                                              \
    static u32 colonel_bolt_animation_context_bolt_##n(void) \
    {                                                        \
        return bolt_case(n);                                 \
    }
CASE(0)
CASE(1)
static const CTestCase colonel_bolt_animation_context_cases[] = { colonel_bolt_animation_context_bolt_0, colonel_bolt_animation_context_bolt_1 };
static const u32 colonel_bolt_animation_context_cases_expected[] = { 0x43010001u, 0x90528u };
#undef CASE

static const u32 colonel_marker_wait_expected[] = { 2u, 0u, 0u, 1u, 0u, 0u, 0u };
static u32 test_colonel_marker_wait(u32 row)
{
    u32 observed_values[7];
    struct ShotObj obj;
    struct ShotObj child_0;
    u8 child_0_present;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&shot_objects, 0, sizeof(shot_objects));
    child_0_present = 255;
    child_0.state = 2;
    pool_0_full = 255;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    colonel_marker_wait(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].timer;
    observed_values[6] = (u32)shot_objects[0].unk2;
    return c_test_observe(0, row, observed_values, colonel_marker_wait_expected, 7);
}

static const u32 colonel_slash_start_expected[] = { 5u, 0u, 1u, 9u };
static u32 test_colonel_slash_start(u32 row)
{
    u32 observed_values[4];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = -1;
    colonel_slash_start(&obj);
    observed_values[0] = (u32)obj.timer;
    observed_values[1] = (u32)obj.unk5C;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk60;
    return c_test_observe(0, row, observed_values, colonel_slash_start_expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "colonel_bolt_animation_context", colonel_bolt_animation_context_cases, colonel_bolt_animation_context_cases_expected, COUNT(colonel_bolt_animation_context_cases), 0 },
    { "colonel_marker_wait", 0, 0, 1, test_colonel_marker_wait },
    { "colonel_slash_start", 0, 0, 1, test_colonel_slash_start },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(colonel_bolt_animation_context_cases) + 1 + 1;
