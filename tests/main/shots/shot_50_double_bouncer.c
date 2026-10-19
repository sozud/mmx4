#include "test_runtime.h"
#include "main/shots/shot_50_double_bouncer.h"
#include "support/state_cases.h"

#define ss state_room.shot

static const u32 double_bouncer_bounce_expected[] = { 1u, 0u, 1u };
static u32 test_double_bouncer_bounce(u32 row)
{
    u32 observed_values[3];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk70 = 15;
    obj.y_vel.val = -1;
    double_bouncer_bounce(&obj);
    observed_values[0] = (u32)obj.unk84.value;
    observed_values[1] = (u32)obj.x_vel.val;
    observed_values[2] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, double_bouncer_bounce_expected, 3);
}

static struct MainObj bouncer_owner;
#define BOUNCER(step, flags) (state_reset(step, 0, 0), memset(&bouncer_owner, 0, sizeof(bouncer_owner)), ss.state = 1, ss.unk7C = (struct WeaponObj*)&bouncer_owner, ss.unk70 = flags, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define BOUNCE(flags, vx, vy) (BOUNCER(2, flags), ss.x_vel.val = vx, ss.y_vel.val = vy, double_bouncer_update(&ss), state_extra = ss.unk84.value)
static void db_left_wall(void)
{
    BOUNCE(2, -0x10000, 0);
}
static void db_left_corner(void) { BOUNCE(0xF, -0x10000, 0); }
static void db_right_wall(void) { BOUNCE(1, 0x10000, 0); }
static void db_free(void) { BOUNCE(0, 0x10000, 0x10000); }
static void db_ceiling(void) { BOUNCE(8, 0, -0x10000); }
static void db_ceiling_corner(void) { BOUNCE(0xC, 0, -0x10000); }
static void db_floor(void) { BOUNCE(4, 0, 0x10000); }
static void db_floor_corner(void) { BOUNCE(0xC, 0, 0x10000); }
static void db_owner_gone(void)
{
    BOUNCER(2, 0);
    bouncer_owner.state = 2;
    double_bouncer_update(&ss);
}
static void db_shot_down(void)
{
    BOUNCER(2, 0);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    double_bouncer_update(&ss);
}
static void db_away(void)
{
    BOUNCER(2, 0);
    ss.y_pos.i.hi = 0x1000;
    double_bouncer_update(&ss);
}
static void db_launch_left(void)
{
    BOUNCER(1, 0);
    ss.animation_step.fields.relative_step = 0;
    g_Player.x_pos.i.hi = 0x100;
    double_bouncer_update(&ss);
}
static void db_launch_right(void)
{
    BOUNCER(1, 0);
    ss.animation_step.fields.relative_step = 0;
    double_bouncer_update(&ss);
}
static void db_launch_wait(void)
{
    BOUNCER(1, 0);
    ss.animation_step.fields.relative_step = 1;
    double_bouncer_update(&ss);
}

static void (*const double_bouncer_states_cases[])(void) = {
    db_left_wall,
    db_left_corner,
    db_right_wall,
    db_free,
    db_ceiling,
    db_ceiling_corner,
    db_floor,
    db_floor_corner,
    db_owner_gone,
    db_shot_down,
    db_away,
    db_launch_left,
    db_launch_right,
    db_launch_wait,
};
static const u32 double_bouncer_states_expected[] = { 0x201u, 0u, 0x810000u, 0x600000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x202u, 0u, 0x810000u, 0x600000u, 0x10000u, 0u, 0u, 0x40000u, 1u, 0x41002100u, 0x201u, 0u, 0x7F0000u, 0x600000u, 0xFFFF0000u, 0u, 0u, 0x40000u, 0u, 0u, 0x201u, 0u, 0x810000u, 0x5F0000u, 0x10000u, 0x10000u, 0u, 0x40000u, 0u, 0u, 0x201u, 0u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x40000u, 0u, 0u, 0x202u, 0u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x40000u, 1u, 0x41002100u, 0x201u, 0u, 0x800000u, 0x610000u, 0u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0u, 0x202u, 0u, 0x800000u, 0x610000u, 0u, 0xFFFF0000u, 0u, 0x40000u, 1u, 0x41002100u, 0x202u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x41002100u, 0x202u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x41002100u, 2u, 0u, 0x800000u, 0x10000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x201u, 0xFF000000u, 0x7E0000u, 0x620000u, 0xFFFE0000u, 0xFFFE0000u, 0u, 0x40000u, 0u, 0u, 0x201u, 0xFF000000u, 0x820000u, 0x620000u, 0x20000u, 0xFFFE0000u, 0u, 0x40000u, 0u, 0u, 0x101u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_double_bouncer_states(u32 row)
{
    return object_run(double_bouncer_states_cases[row], row, &double_bouncer_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "double_bouncer_states", 0, 0, COUNT(double_bouncer_states_cases), test_double_bouncer_states },
    { "double_bouncer_bounce", 0, 0, 1, test_double_bouncer_bounce },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_bouncer_states_cases) + 1;
