#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_49_double_aerial.h"

static struct MainObj aerial_owner;
#define ss state_room.shot
#define AERIAL(st, step) (state_reset(step, 0, 0), memset(&aerial_owner, 0, sizeof(aerial_owner)), ss.state = st, ss.unk7C = (struct WeaponObj*)&aerial_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define TIMER() (state_extra = (u16)ss.timer | (u32)ss.unk60 << 16)
static void da_init_left(void)
{
    AERIAL(0, 0);
    double_aerial_update(&ss);
    TIMER();
}
static void da_init_right(void)
{
    AERIAL(0, 0);
    ss.unk15 = 0x40;
    double_aerial_update(&ss);
    TIMER();
}
static void da_drop(void)
{
    AERIAL(1, 0);
    ss.timer = 3;
    ss.y_vel.val = -0x10000;
    double_aerial_update(&ss);
    TIMER();
}
static void da_drop_done(void)
{
    AERIAL(1, 0);
    ss.timer = 1;
    double_aerial_update(&ss);
    TIMER();
}
static void da_aim_left(void)
{
    AERIAL(1, 1);
    ss.timer = 1;
    double_aerial_update(&ss);
    TIMER();
}
static void da_aim_right(void)
{
    AERIAL(1, 1);
    ss.timer = 1;
    ss.unk15 = 0x40;
    double_aerial_update(&ss);
    TIMER();
}
static void da_aim_wait(void)
{
    AERIAL(1, 1);
    ss.timer = 2;
    double_aerial_update(&ss);
    TIMER();
}
static void da_fly(void)
{
    AERIAL(1, 2);
    ss.x_vel.val = 0x40000;
    double_aerial_update(&ss);
}
static void da_owner_gone(void)
{
    AERIAL(1, 2);
    aerial_owner.state = 2;
    double_aerial_update(&ss);
}
static void da_shot_down(void)
{
    AERIAL(1, 2);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    double_aerial_update(&ss);
}
static void da_away(void)
{
    AERIAL(1, 2);
    ss.x_pos.i.hi = 0x1000;
    double_aerial_update(&ss);
}
static void dt_init_left(void)
{
    AERIAL(0, 0);
    double_toss_init(&ss);
    TIMER();
}
static void dt_init_right(void)
{
    AERIAL(0, 0);
    ss.unk2 = 1;
    double_toss_init(&ss);
    TIMER();
}
static void dt_land_ball(void)
{
    AERIAL(1, 0);
    ss.id = 0x32;
    ss.unk70 = 8;
    double_toss_land(&ss);
    TIMER();
}
static void dt_land_mine(void)
{
    AERIAL(1, 0);
    ss.id = 0x33;
    ss.timer = 1;
    double_toss_land(&ss);
    TIMER();
}
static void dt_land_arc(void)
{
    AERIAL(1, 0);
    ss.timer = 3;
    double_toss_land(&ss);
    TIMER();
}
static void dt_land_spin(void)
{
    AERIAL(1, 0);
    ss.timer = 3;
    ss.animation_step.fields.relative_step = 1;
    ss.y_vel.val = 0x20000;
    double_toss_land(&ss);
    TIMER();
}

static void (*const double_aerial_states_cases[])(void) = {
    da_init_left,
    da_init_right,
    da_drop,
    da_drop_done,
    da_aim_left,
    da_aim_right,
    da_aim_wait,
    da_fly,
    da_owner_gone,
    da_shot_down,
    da_away,
    dt_init_left,
    dt_init_right,
    dt_land_ball,
    dt_land_mine,
    dt_land_arc,
    dt_land_spin,
};
static const u32 double_aerial_states_expected[] = { 1u, 0xFF000000u, 0x800000u, 0x400000u, 0xFFFE0000u, 0u, 0u, 0x50000u, 0x90014u, 0u, 1u, 0xFF400000u, 0x800000u, 0x400000u, 0x20000u, 0u, 0u, 0x50000u, 0x90014u, 0u, 1u, 0u, 0x800000u, 0x610000u, 0u, 0xFFFF0000u, 0u, 0x40000u, 2u, 0u, 0x101u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x1Du, 0u, 0x201u, 0xFF000000u, 0x800000u, 0x600000u, 0xFFFC0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x201u, 0xFF400000u, 0x800000u, 0x600000u, 0x40000u, 0u, 0u, 0x50000u, 0u, 0u, 0x101u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 0x201u, 0u, 0x840000u, 0x600000u, 0x40000u, 0u, 0u, 0x40000u, 0u, 0u, 0x202u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 0x202u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x2100u, 2u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0xFF000000u, 0x800000u, 0x500000u, 0xFFFD0000u, 0x48000u, 0x580000u, 0x50000u, 0x40014u, 0u, 1u, 0xFF000100u, 0x800000u, 0x500000u, 0x30000u, 0x48000u, 0x580000u, 0x50000u, 0x40014u, 0u, 0x101u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x40000u, 0u, 0x101u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x30000u, 0u, 1u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 2u, 0u, 1u, 0u, 0x800000u, 0x5E0000u, 0u, 0x20000u, 0u, 0x40000u, 2u, 0u };

static u32 test_double_aerial_states(u32 row)
{
    return object_run(double_aerial_states_cases[row], row, &double_aerial_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "double_aerial_states", 0, 0, COUNT(double_aerial_states_cases), test_double_aerial_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_aerial_states_cases);
