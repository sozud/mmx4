#include "test_runtime.h"

static u32 launch_case(u32 observation)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before;
    u32 i, script_before, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 39;
    obj.state = 5;
    obj.unk5 = 5;
    obj.timer = 1;
    obj.x_pos.val = 100 * 65536 + 0x1357;
    obj.y_pos.val = 100 * 65536 + 0x2468;
    obj.x_vel.val = 0x1234;
    obj.y_vel.val = 0x5678;
    obj.unk2C = 0x2468;
    obj.animation_table = (u32**)split_mushroom_animations;
    obj.animation_cursor = split_mushroom_animations[16];
    obj.animation_step.packed = *(u32*)split_mushroom_animations[16];
    g_Player.x_pos.val = obj.x_pos.val;
    g_Player.y_pos.val = obj.y_pos.val + 400 * 65536;
    before = obj;
    player_before = g_Player;
    script_before = *(u32*)split_mushroom_animations[16];
    func_800A5194(&obj);
    before.unk5 = obj.unk5;
    before.timer = obj.timer;
    before.x_vel = obj.x_vel;
    before.y_vel = obj.y_vel;
    before.unk2C = obj.unk2C;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(obj.animation_table == (u32**)split_mushroom_animations && obj.animation_cursor == split_mushroom_animations[16]);
    assert(*(u32*)split_mushroom_animations[16] == script_before);
    if (observation == 0)
        actual = obj.x_vel.val;
    else if (observation == 1)
        actual = obj.y_vel.val;
    else if (observation == 2)
        actual = obj.unk2C;
    else if (observation == 3)
        actual = (u16)obj.timer | ((u32)(u8)obj.unk5 << 16);
    else
        actual = obj.animation_step.packed;
    return actual;
}
#define LAUNCH_CASE(n)          \
    static u32 launch_##n(void) \
    {                           \
        return launch_case(n);  \
    }
LAUNCH_CASE(0)
LAUNCH_CASE(1)
LAUNCH_CASE(2)
LAUNCH_CASE(3)
LAUNCH_CASE(4)
#define LAUNCH_ENTRY(n) launch_##n,
static const CTestCase mushroom_launch_context_cases[]
    = { LAUNCH_ENTRY(0) LAUNCH_ENTRY(1) LAUNCH_ENTRY(2) LAUNCH_ENTRY(3) LAUNCH_ENTRY(4) };
static const u32 mushroom_launch_context_cases_expected[] = { 0x0u, 0xFFFA23EDu, 0x1000u, 0x60000u, 0x3D010001u };
#undef LAUNCH_CASE
#undef LAUNCH_ENTRY

const struct CTestGroup c_test_groups[] = {
    { "mushroom_launch_context", mushroom_launch_context_cases, mushroom_launch_context_cases_expected, COUNT(mushroom_launch_context_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(mushroom_launch_context_cases);
