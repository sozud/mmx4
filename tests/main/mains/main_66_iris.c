#include "test_runtime.h"

#include "support/pool_full.h"
static u32 pool_full_iris_death_explode(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    func_80080DF4(&pf_self);
    pf_expected.unk5 = 2;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_iris_crystal_drop_fire(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_snapshot();
    iris_crystal_drop_fire(&pf_self);
    pf_animated();
    pf_expected.unk7C = 0x86;
    pf_expected.unk6 = 4;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_iris_intro_toss_crystal(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_snapshot();
    iris_intro_toss_crystal(&pf_self);
    pf_animation(0xA);
    pf_expected.unk7C = 0x3E;
    pf_expected.unk6 = 7;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_iris_robot_dash_laser(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_self.x_speed = 0x10000;
    pf_snapshot();
    iris_robot_dash_laser(&pf_self);
    pf_animation(6);
    pf_expected.x_speed = 0;
    pf_expected.unk7C = 0xB4;
    pf_expected.unk6 = 4;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_iris_death_explode,
    pool_full_iris_crystal_drop_fire,
    pool_full_iris_intro_toss_crystal,
    pool_full_iris_robot_dash_laser,
};

static const u32 pool_full_cases_expected[] = { 0x2u, 0x860400u, 0x3E0700u, 0xB40400u };
const struct CTestGroup c_test_groups[] = {
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pool_full_cases);
