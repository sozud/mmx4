#include "test_runtime.h"
#include "main/shots/shot_44_iris_shot.h"
#include "main/55C4.h"
extern void* iris_animations[37];

static u32 drone_case(u32 burst, u32 observation)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 44;
    obj.state = 1;
    obj.unk5 = burst ? 4 : 1;
    obj.unk61 = 0x27;
    obj.timer = 0x7777;
    obj.unk28 = 0x1000;
    obj.unk2C = 0x1000;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = -32768;
    obj.y_vel.val = 32768;
    obj.animation_table = (u32**)iris_animations;
    set_animation_frame(&obj, 14, burst ? 8 : 0);
    before = obj;
    player_before = g_Player;
    if (burst) {
        iris_drone_burst(&obj);
        before.unk5 = 5;
        before.unk17 = 15;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = iris_animations[15];
        before.animation_step = *(union AnimationStep*)iris_animations[15];
    } else {
        iris_drone_brake(&obj);
        before.x_pos.val -= 32768;
        before.y_pos.val -= 32768;
        before.animation_step.fields.duration = 1;
        before.unk5 = 2;
        before.unk61 = 0;
        before.timer = 0x3C;
        before.x_vel.val = before.y_vel.val = before.unk28 = before.unk2C = 0;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u16)obj.timer << 8) | ((u32)obj.unk17 << 24) : obj.animation_step.packed;
}
#define CASE(m, n)                                                \
    static u32 iris_drone_animation_context_drone_##m##_##n(void) \
    {                                                             \
        return drone_case(m, n);                                  \
    }
CASE(0, 0)
CASE(0, 1)
CASE(1, 0)
CASE(1, 1)
#define ENTRY(m, n) iris_drone_animation_context_drone_##m##_##n,
static const CTestCase iris_drone_animation_context_cases[]
    = { ENTRY(0, 0) ENTRY(0, 1) ENTRY(1, 0) ENTRY(1, 1) };
static const u32 iris_drone_animation_context_cases_expected[] = { 0xE003C02u, 0x47010001u, 0xF777705u, 0x4A010003u };
#undef CASE
#undef ENTRY

static const u32 iris_drone_brake_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0xFFF98000u };
static u32 test_iris_drone_brake(u32 row)
{
    u32 observed_values[7];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.y_vel.val = -1048576;
    iris_drone_brake(&obj);
    observed_values[0] = (u32)obj.timer;
    observed_values[1] = (u32)obj.unk28;
    observed_values[2] = (u32)obj.unk2C;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk61;
    observed_values[5] = (u32)obj.x_vel.val;
    observed_values[6] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, iris_drone_brake_expected, 7);
}

static const u32 iris_drone_burst_expected[] = { 0u };
static u32 test_iris_drone_burst(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    iris_drone_burst(&obj);
    observed_values[0] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, iris_drone_burst_expected, 1);
}

static const u32 iris_drone_explode_0_expected[] = { 0xFF0002u };
static u32 test_iris_drone_explode_0(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj, before;
    u8 marker[] = { 1, 2, 3, 4 };
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 44;
    obj.state = 1;
    obj.unk50.data = marker;
    obj.animation_step.fields.event = 1;
    before = obj;
    iris_drone_explode(&obj);
    before.state = 2;
    before.animation_step.fields.duration = -1;
    c_test_same_words(&obj, &before, sizeof(obj));
    assert(marker[0] == 1 && marker[1] == 2 && marker[2] == 3 && marker[3] == 4);
    observed_values[0] = (u8)obj.state | ((obj.unk50.data == iris_drone_explode_box ? 1u : 0u) << 8) | ((u32)(u8)obj.animation_step.fields.duration << 16);
    return c_test_observe(0, row, observed_values, iris_drone_explode_0_expected, 1);
}
static const u32 iris_drone_explode_1_expected[] = { 0xFF0101u };
static u32 test_iris_drone_explode_1(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj, before;
    u8 marker[] = { 1, 2, 3, 4 };
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 44;
    obj.state = 1;
    obj.unk50.data = marker;
    obj.animation_step.fields.event = 2;
    before = obj;
    iris_drone_explode(&obj);
    before.unk50.data = iris_drone_explode_box;
    before.animation_step.fields.duration = -1;
    c_test_same_words(&obj, &before, sizeof(obj));
    assert(marker[0] == 1 && marker[1] == 2 && marker[2] == 3 && marker[3] == 4);
    observed_values[0] = (u8)obj.state | ((obj.unk50.data == iris_drone_explode_box ? 1u : 0u) << 8) | ((u32)(u8)obj.animation_step.fields.duration << 16);
    return c_test_observe(1, row, observed_values, iris_drone_explode_1_expected, 1);
}
static u32 test_iris_drone_explode(u32 index)
{
    if (index < 1)
        return test_iris_drone_explode_0(index);
    index -= 1;
    return test_iris_drone_explode_1(index);
}

static const u32 iris_drone_move_expected[] = { 0u, 0u, 0xFFFFFu, 0xFFF98000u };
static u32 test_iris_drone_move(u32 row)
{
    u32 observed_values[4];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.y_vel.val = -1048575;
    obj.unk2C = -524287;
    iris_drone_move(&obj);
    observed_values[0] = (u32)obj.x_pos.val;
    observed_values[1] = (u32)obj.x_vel.val;
    observed_values[2] = (u32)obj.y_pos.val;
    observed_values[3] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, iris_drone_move_expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "iris_drone_animation_context", iris_drone_animation_context_cases, iris_drone_animation_context_cases_expected, COUNT(iris_drone_animation_context_cases), 0 },
    { "iris_drone_brake", 0, 0, 1, test_iris_drone_brake },
    { "iris_drone_burst", 0, 0, 1, test_iris_drone_burst },
    { "iris_drone_explode", 0, 0, 2, test_iris_drone_explode },
    { "iris_drone_move", 0, 0, 1, test_iris_drone_move },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(iris_drone_animation_context_cases) + 1 + 1 + 2 + 1;
