#include "test_runtime.h"
extern void* double_animations[31];

static u32 travel_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    u32 i, actual, cursor_index = ~0u;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 48;
    obj.state = 1;
    obj.unk5 = 0;
    obj.unk6 = 0x35;
    obj.unk7 = 0x27;
    obj.unk15 = 0x40;
    obj.unk17 = 12;
    obj.previous_animation_index = 0xA5;
    obj.timer = 0x1234;
    obj.unk8A = mode == 0 ? -1 : mode == 1 ? 2
                                           : 0;
    obj.unk8C.halves[0] = mode == 0 ? 10 : -10;
    obj.unk8C.halves[1] = mode == 0 ? 20 : -20;
    obj.x_pos.val = (s32)obj.unk8C.halves[0] * 65536 + 0x24681;
    obj.y_pos.val = (s32)obj.unk8C.halves[1] * 65536 - 0x35792;
    obj.unk84.value = 0x24681357;
    obj.animation_table = (u32**)double_animations;
    obj.animation_cursor = (u32*)double_animations[12];
    obj.animation_step.packed = *obj.animation_cursor;
    obj.animation_step.fields.duration = mode == 1 ? 2 : 1;
    before = obj;
    double_ball_travel(&obj);
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.unk5 = obj.unk5;
    before.timer = obj.timer;
    before.unk8A = obj.unk8A;
    before.unk84 = obj.unk84;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(obj.animation_table == (u32**)double_animations);
    for (i = 0; i < 4; i++)
        if (obj.animation_cursor == (u32*)double_animations[12] + i)
            cursor_index = i;
    assert(cursor_index != ~0u);
    switch (observation) {
    case 0:
        actual = obj.x_pos.val;
        break;
    case 1:
        actual = obj.y_pos.val;
        break;
    case 2:
        actual = (u16)obj.unk8A | ((u32)(u8)obj.unk5 << 16);
        break;
    case 3:
        actual = (u16)obj.timer;
        break;
    case 4:
        actual = obj.unk84.value;
        break;
    case 5:
        actual = obj.animation_step.packed;
        break;
    default:
        actual = cursor_index;
        break;
    }
    return actual;
}
#define TRAVEL_CASE(m, n)                                   \
    static u32 double_ball_positions_travel_##m##_##n(void) \
    {                                                       \
        return travel_case(m, n);                           \
    }
#define TRAVEL_MODE(m) TRAVEL_CASE(m, 0) TRAVEL_CASE(m, 1) TRAVEL_CASE(m, 2) TRAVEL_CASE(m, 3) TRAVEL_CASE(m, 4) TRAVEL_CASE(m, 5) TRAVEL_CASE(m, 6)
TRAVEL_MODE(0)
TRAVEL_MODE(1)
TRAVEL_MODE(2)
#define TRAVEL_ENTRY(m, n) double_ball_positions_travel_##m##_##n,
#define TRAVEL_ENTRIES(m) TRAVEL_ENTRY(m, 0) TRAVEL_ENTRY(m, 1) TRAVEL_ENTRY(m, 2) TRAVEL_ENTRY(m, 3) TRAVEL_ENTRY(m, 4) TRAVEL_ENTRY(m, 5) TRAVEL_ENTRY(m, 6)
static const CTestCase double_ball_positions_cases[]
    = { TRAVEL_ENTRIES(0) TRAVEL_ENTRIES(1) TRAVEL_ENTRIES(2) };
static const u32 double_ball_positions_cases_expected[] = { 0xE8D02u, 0xD50DCu, 0xFFFEu, 0x1234u, 0x15u, 0x34010001u, 0x1u, 0xFFF72341u, 0xFFEA5437u, 0x1u, 0x1234u, 0x15u, 0x33010001u, 0x0u, 0xFFF60000u, 0xFFEC0000u, 0x10000u, 0x5Au, 0x15u, 0x34010001u, 0x1u };
#undef TRAVEL_CASE
#undef TRAVEL_MODE
#undef TRAVEL_ENTRY
#undef TRAVEL_ENTRIES

static const u32 double_ball_travel_expected[] = { 0u, 0u, 0x10u, 0xFFFFFFFEu, 0x7FFC4804u, 0xFFF3F73Cu };
static u32 test_double_ball_travel(u32 row)
{
    u32 observed_values[6];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.val = -121854;
    obj.unk8C.half = 32768;
    obj.y_pos.val = -787554;
    obj.unk8C.halves[1] = -12;
    obj.unk8A = -1;
    double_ball_travel(&obj);
    observed_values[0] = (u32)obj.timer;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk84.value;
    observed_values[3] = (u32)obj.unk8A;
    observed_values[4] = (u32)obj.x_pos.val;
    observed_values[5] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, double_ball_travel_expected, 6);
}

const struct CTestGroup c_test_groups[] = {
    { "double_ball_positions", double_ball_positions_cases, double_ball_positions_cases_expected, COUNT(double_ball_positions_cases), 0 },
    { "double_ball_travel", 0, 0, 1, test_double_ball_travel },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_ball_positions_cases) + 1;
