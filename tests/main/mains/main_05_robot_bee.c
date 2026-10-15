#include "test_runtime.h"
extern union AnimationStep* robot_bee_animations[];
extern s32 D_800FA130[2];

static u32 arc_default(void)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 5;
    obj.state = 1;
    obj.unk6 = 0x27;
    obj.ext.main_5.unk80 = 4;
    obj.unk7C = 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_step.fields.duration = 2;
    before = obj;
    func_80045DD8(&obj);
    before.unk7C = 1;
    before.animation_step.fields.duration = 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    actual = (u16)obj.unk7C | ((u32)obj.ext.main_5.unk80 << 16);
    return actual;
}
static const CTestCase robot_bee_arc_default_cases[] = { arc_default };
static const u32 robot_bee_arc_default_cases_expected[] = { 0x40001u };

static const s16 timers[8] = { 31, 31, 1, 1, 2, 2, 2, 2 };
static const s32 distances[8] = { -0x6FFFFF, 0x6FFFFF, 0, 0, -0x700000, 0x700000, -0x700000, 0x700000 };
static u32 bob_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    u32 i, actual, reversed = mode < 4;
    memset(&obj, 0, sizeof(obj));
    memset(&obj.ext, 0xA5, sizeof(obj.ext));
    obj.active = 0x41;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 9;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.unk7C = timers[mode];
    obj.ext.main_5.unk80 = mode & 1;
    obj.ext.main_5.unk81 = mode & 1;
    obj.x_pos.val = 200 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_speed = 0x18000;
    obj.y_speed = mode & 1 ? 0x2000 : -0x2000;
    obj.x_accel = 0x800;
    obj.gravity = mode & 1 ? 0x1000 : -0x1000;
    obj.animation_table = (const u8* const*)robot_bee_animations;
    obj.animation_cursor = (const u8*)robot_bee_animations[1];
    obj.animation_step = *robot_bee_animations[1];
    obj.unk17 = 1;
    obj.previous_animation_index = 0xFF;
    g_Player.x_pos.val = obj.x_pos.val + obj.x_speed + distances[mode];
    player_expected = g_Player;
    expected = obj;
    expected.animation_cursor += 4;
    expected.animation_step = *(const union AnimationStep*)expected.animation_cursor;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val -= obj.y_speed;
    expected.x_speed += obj.unk15 ? obj.x_accel : -obj.x_accel;
    expected.y_speed -= obj.gravity;
    expected.unk7C--;
    if (reversed) {
        expected.ext.main_5.unk81 = !(mode & 1);
        expected.gravity = -obj.gravity;
        expected.y_speed = mode & 1 ? -0x8000 : 0x8000;
    }
    if (mode == 2 || mode == 3) {
        expected.ext.main_5.unk80 = !(mode & 1);
        expected.x_speed = 0;
        expected.x_accel = -obj.x_accel;
        expected.unk7C = 60;
    }
    if (mode < 4) {
        expected.animation_cursor = (const u8*)robot_bee_animations[2];
        expected.animation_step = *robot_bee_animations[2];
        expected.unk17 = 2;
        expected.previous_animation_index = 0xFF;
        expected.unk5 = 7;
        expected.unk6 = 0;
    }
    func_80046220(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    assert(D_800FA130[0] == -0x8000 && D_800FA130[1] == 0x8000);
    assert(robot_bee_animations[1][0].packed == 0x00010001);
    assert(robot_bee_animations[2][0].packed == 0x10010002);
    actual = (u8)obj.unk5 | ((u32)(u16)obj.unk7C << 8) | ((u32)obj.ext.main_5.unk81 << 24);
    return actual;
}
#define CASE(m)                                            \
    static u32 robot_bee_bob_player_distance_bob_##m(void) \
    {                                                      \
        return bob_case(m);                                \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) robot_bee_bob_player_distance_bob_##m,
static const CTestCase robot_bee_bob_player_distance_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 robot_bee_bob_player_distance_cases_expected[] = { 0x1001E07u, 0x1E07u, 0x1003C07u, 0x3C07u, 0x102u, 0x1000102u, 0x102u, 0x1000102u };
#undef CASE
#undef ENTRY

static const u32 func_80045940_expected[] = { 0xFFu, 0u, 1u, 0u, 0u };
static u32 test_func_80045940(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_5.unk80 = 255;
    obj.unk7C = 2;
    func_80045940(&obj);
    observed_values[0] = (u32)obj.ext.main_5.unk80;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.x_speed;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_80045940_expected, 5);
}

static const u32 func_80045DD8_expected[] = { 0xFFu, 0u, 0x1FFu, 0u, 0u };
static u32 test_func_80045DD8(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_5.unk80 = 255;
    obj.unk7C = 512;
    func_80045DD8(&obj);
    observed_values[0] = (u32)obj.ext.main_5.unk80;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.x_speed;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_80045DD8_expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "robot_bee_arc_default", robot_bee_arc_default_cases, robot_bee_arc_default_cases_expected, COUNT(robot_bee_arc_default_cases), 0 },
    { "robot_bee_bob_player_distance", robot_bee_bob_player_distance_cases, robot_bee_bob_player_distance_cases_expected, COUNT(robot_bee_bob_player_distance_cases), 0 },
    { "func_80045940", 0, 0, 1, test_func_80045940 },
    { "func_80045DD8", 0, 0, 1, test_func_80045DD8 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(robot_bee_arc_default_cases) + COUNT(robot_bee_bob_player_distance_cases) + 1 + 1;
