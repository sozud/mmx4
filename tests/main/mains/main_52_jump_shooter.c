#include "test_runtime.h"
#include "main/mains/main_52_jump_shooter.h"

static u32 aim_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 52;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = 5;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.main_52.unk84 = 7;
    obj.ext.main_52.unk88 = 9;
    g_Player.x_pos.val = (mode < 2 ? 200 : 0) * 65536 + 0x1234;
    g_Player.y_pos.val = 184 * 65536 + 0x5678;
    expected = obj;
    player_expected = g_Player;
    expected.ext.main_52.unk84 = mode < 2 ? 0 : 16;
    if (mode == 1 || mode == 2)
        expected.ext.main_52.unk88 = 2;
    func_8006AE80(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    return obj.ext.main_52.unk84 | ((u32)obj.ext.main_52.unk88 << 8) | ((u32)obj.y_pos.u.hi << 16);
}
#define CASE(m)                                           \
    static u32 jump_shooter_real_aim_angles_aim_##m(void) \
    {                                                     \
        return aim_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) jump_shooter_real_aim_angles_aim_##m,
static const CTestCase jump_shooter_real_aim_angles_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 jump_shooter_real_aim_angles_cases_expected[] = { 0xC80900u, 0xC80200u, 0xC80210u, 0xC80910u };
#undef CASE
#undef ENTRY

struct jump_shooter_jump_launch_case {
    u32 unk8C, unk15;
    u32 expected[5];
};
static const struct jump_shooter_jump_launch_case jump_shooter_jump_launch_cases[] = {
    { 255, 255, { 1u, 0x4000u, 1u, 0u, 0x5C000u } },
    { 2, 255, { 1u, 0x4000u, 1u, 0xFFFE3334u, 0x5C000u } },
    { 2, 0, { 1u, 0x4000u, 1u, 0x1CCCCu, 0x5C000u } },
};
static u32 test_jump_shooter_jump_launch(u32 row)
{
    const struct jump_shooter_jump_launch_case* c = &jump_shooter_jump_launch_cases[row];
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.animation_step.fields.event = 2;
    obj.ext.main_52.unk8C = c->unk8C;
    obj.unk15 = c->unk15;
    jump_shooter_jump_launch(&obj);
    observed_values[0] = (u32)obj.ext.main_52.unk80;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_speed;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

#include "support/pool_full.h"
static u32 pool_full_jump_shooter_fire_shots(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7E = 1;
    pf_self.unk7C = 2;
    pf_snapshot();
    jump_shooter_fire_shots(&pf_self);
    pf_animation(2);
    pf_expected.unk7C = 1;
    pf_expected.unk7E = 0x10;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_jump_shooter_fire_shots,
};

static const u32 pool_full_cases_expected[] = { 0x10000u };
const struct CTestGroup c_test_groups[] = {
    { "jump_shooter_real_aim_angles", jump_shooter_real_aim_angles_cases, jump_shooter_real_aim_angles_cases_expected, COUNT(jump_shooter_real_aim_angles_cases), 0 },
    { "jump_shooter_jump_launch", 0, 0, 3, test_jump_shooter_jump_launch },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(jump_shooter_real_aim_angles_cases) + 3 + COUNT(pool_full_cases);
