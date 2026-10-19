#include "test_runtime.h"
#include "main/mains/main_01_armored_walker.h"
void armored_walker_fall(struct MainObj* arg0);
void armored_walker_hop(struct MainObj* arg0);
void armored_walker_land(struct MainObj* arg0);
void armored_walker_turn(struct MainObj* arg0);
void func_800423A0(struct MainObj* arg0);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 inputs_0[2][1] = {
    { 0 },
    { 30 },
};
struct armored_walker_turn_pause_case {
    u32 expected[4];
};
static const struct armored_walker_turn_pause_case armored_walker_turn_pause_cases[] = {
    { { 2u, 0u, 0u, 0u } },
    { { 0u, 0u, 0x1Du, 0u } },
};
static u32 test_armored_walker_turn_pause(u32 row)
{
    const struct armored_walker_turn_pause_case* c = &armored_walker_turn_pause_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = inputs_0[row][0];
    armored_walker_turn_pause(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.x_accel;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#include "support/state_cases.h"

#define AW(a, b) state_reset(a, b, 0)
#define ON_SCREEN() (so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
static void aw_init_left(void)
{
    AW(0, 0);
    so.x_pos.val = 0x100000;
    armored_walker_update(&so);
}
static void aw_init_right(void)
{
    AW(0, 0);
    so.x_pos.val = -0x100000;
    armored_walker_update(&so);
}
static void aw_main_fall(void)
{
    AW(2, 1);
    so.state = 1;
    ON_SCREEN();
    armored_walker_update(&so);
}
static void aw_main_wall_right(void)
{
    AW(2, 1);
    so.state = 1;
    ON_SCREEN();
    so.unk15 = 0x40;
    so.x_pos.i.hi = -0x80;
    so.collision_flags = 9;
    armored_walker_update(&so);
}
static void aw_main_wall_left(void)
{
    AW(2, 1);
    so.state = 1;
    ON_SCREEN();
    so.collision_flags = 0xA;
    armored_walker_update(&so);
}
static void aw_main_behind_right(void)
{
    AW(2, 1);
    so.state = 1;
    ON_SCREEN();
    so.unk15 = 0x40;
    so.collision_flags = 8;
    armored_walker_update(&so);
}
static void aw_main_behind_left(void)
{
    AW(2, 1);
    so.state = 1;
    so.x_pos.i.hi = -0x20;
    so.y_pos.i.hi = 0x60;
    so.collision_flags = 8;
    armored_walker_update(&so);
}
static void aw_main_ahead(void)
{
    AW(2, 1);
    so.state = 1;
    ON_SCREEN();
    so.collision_flags = 8;
    armored_walker_update(&so);
}
static void aw_main_away(void)
{
    AW(1, 0);
    so.state = 1;
    so.x_pos.i.hi = 0x1000;
    armored_walker_update(&so);
}
static void aw_despawn(void)
{
    AW(0, 0);
    so.state = 2;
    so.active = 1;
    armored_walker_update(&so);
}
static void aw_walk_left(void)
{
    AW(2, 0);
    func_800423A0(&so);
}
static void aw_walk_right(void)
{
    AW(2, 0);
    so.unk15 = 0x40;
    func_800423A0(&so);
}
static void aw_walk_on(void)
{
    AW(2, 1);
    so.x_speed = 0x30000;
    func_800423A0(&so);
}
static void aw_hop_left(void)
{
    AW(3, 0);
    so.animation_step.fields.event = 1;
    armored_walker_hop(&so);
}
static void aw_hop_right(void)
{
    AW(3, 0);
    so.animation_step.fields.event = 1;
    so.unk15 = 0x40;
    armored_walker_hop(&so);
}
static void aw_hop_crouch(void)
{
    AW(3, 0);
    armored_walker_hop(&so);
}
static void aw_hop_peak(void)
{
    AW(3, 1);
    so.y_speed = -1;
    armored_walker_hop(&so);
}
static void aw_hop_rise(void)
{
    AW(3, 1);
    so.y_speed = 0x60000;
    armored_walker_hop(&so);
}
static void aw_land_turn_right(void)
{
    AW(4, 0);
    so.animation_step.fields.event = 1;
    so.unk15 = 0x40;
    so.x_pos.val = 0x10000;
    armored_walker_land(&so);
}
static void aw_land_walk_right(void)
{
    AW(4, 0);
    so.unk15 = 0x40;
    so.x_pos.val = -0x10000;
    armored_walker_land(&so);
}
static void aw_land_turn_left(void)
{
    AW(4, 0);
    armored_walker_land(&so);
}
static void aw_land_walk_left(void)
{
    AW(4, 0);
    so.x_pos.val = 0x10000;
    armored_walker_land(&so);
}
static void aw_land_wait(void)
{
    AW(4, 0);
    so.animation_step.fields.relative_step = 1;
    armored_walker_land(&so);
}
static void aw_brake(void)
{
    AW(5, 0);
    armored_walker_turn(&so);
}
static void aw_brake_slide(void)
{
    AW(5, 0);
    so.unk7C = 2;
    so.x_speed = 0x30000;
    armored_walker_turn(&so);
}
static void aw_flip_ground(void)
{
    AW(5, 1);
    so.animation_step.fields.event = 1;
    armored_walker_turn(&so);
}
static void aw_flip_air(void)
{
    AW(5, 1);
    so.animation_step.fields.event = 1;
    so.air_state = 1;
    armored_walker_turn(&so);
}
static void aw_flip_wait(void)
{
    AW(5, 1);
    armored_walker_turn(&so);
}
static void aw_fall_land(void)
{
    AW(6, 0);
    so.collision_flags = 8;
    armored_walker_fall(&so);
}
static void aw_fall(void)
{
    AW(6, 1);
    so.y_speed = -0x10000;
    armored_walker_fall(&so);
}

static void (*const armored_walker_states_cases[])(void) = {
    aw_init_left,
    aw_init_right,
    aw_main_fall,
    aw_main_wall_right,
    aw_main_wall_left,
    aw_main_behind_right,
    aw_main_behind_left,
    aw_main_ahead,
    aw_main_away,
    aw_despawn,
    aw_walk_left,
    aw_walk_right,
    aw_walk_on,
    aw_hop_left,
    aw_hop_right,
    aw_hop_crouch,
    aw_hop_peak,
    aw_hop_rise,
    aw_land_turn_right,
    aw_land_walk_right,
    aw_land_turn_left,
    aw_land_walk_left,
    aw_land_wait,
    aw_brake,
    aw_brake_slide,
    aw_flip_ground,
    aw_flip_air,
    aw_flip_wait,
    aw_fall_land,
    aw_fall,
};
static const u32 armored_walker_states_expected[] = { 2u, 0u, 0x100000u, 0u, 0u, 0u, 1u, 0xF0003u, 0u, 0u, 2u, 0u, 0xFFF00000u, 0u, 0u, 0u, 0x4001u, 0xF0003u, 0u, 0u, 0xFF000106u, 0u, 0x800000u, 0u, 0xFFFFBE00u, 0x420000u, 4u, 0u, 0u, 0u, 0x1000003u, 0u, 0xFF800000u, 0u, 0u, 0u, 0x4003u, 0u, 0u, 0u, 0x1000003u, 0u, 0x800000u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 5u, 9u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 5u, 9u, 0xFFE00000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF000106u, 0u, 0x10000000u, 0u, 0xFFFFBE00u, 0x420000u, 4u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0u, 0xFFFD0000u, 0xFFFD0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x102u, 0u, 0x30000u, 0x30000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 0x102u, 0u, 0x30000u, 0x30000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 0u, 0u, 0x20000u, 0x60000u, 0x420000u, 0u, 0u, 0u, 0u, 0x103u, 0u, 0u, 0xFFFE0000u, 0x60000u, 0x420000u, 0x4000u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 4u, 0u, 0u, 0u, 0x103u, 0u, 0u, 0u, 0x60000u, 0u, 0u, 0u, 0u, 0u, 5u, 0u, 0x10000u, 0u, 0u, 0u, 0x4002u, 0u, 0u, 0u, 2u, 0u, 0xFFFF0000u, 0u, 0u, 0u, 0x4001u, 0u, 0u, 0u, 5u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 2u, 0u, 0x10000u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 4u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x105u, 0u, 0u, 0u, 0u, 0xFFFFE900u, 2u, 0u, 0u, 0u, 5u, 1u, 0x30000u, 0x30000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x205u, 0x1Eu, 0u, 0u, 0u, 0u, 0x4001u, 0u, 0u, 0u, 0x205u, 0u, 0u, 0u, 0u, 0u, 0x4001u, 0u, 0u, 0u, 0x105u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 4u, 0u, 0u, 0u, 0u, 0u, 5u, 0u, 0u, 0u, 0x106u, 0u, 0u, 0u, 0xFFFF0000u, 0u, 0u, 0u, 0u, 0u };

static u32 test_armored_walker_states(u32 row)
{
    return state_run(armored_walker_states_cases[row], row, &armored_walker_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "armored_walker_states", 0, 0, COUNT(armored_walker_states_cases), test_armored_walker_states },
    { "armored_walker_turn_pause", 0, 0, 2, test_armored_walker_turn_pause },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(armored_walker_states_cases) + 2;
