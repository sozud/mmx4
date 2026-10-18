#include "test_runtime.h"
#include "main/shots/shot_51_double_mine.h"
#include "main/object_motion.h"
u8 angle_from_delta(s32 arg0, s32 arg1);

static u32 mine_case(u32 observation)
{
    struct ShotObj obj, before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 51;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.timer = -1;
    obj.unk8C.halves[1] = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 3 * 65536;
    obj.animation_step.fields.duration = 2;
    before = obj;
    func_800AA68C(&obj);
    before.timer = -2;
    before.y_pos.val = 5 * 65536;
    before.animation_step.fields.duration = 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    return observation == 0 ? obj.y_pos.val : (u16)obj.timer | ((u32)obj.animation_step.fields.duration << 16);
}
static const u32 double_mine_negative_timer_cases_expected[] = { 0x50000u, 0x1FFFEu };

#include "support/state_cases.h"

static struct MainObj mine_owner;
#define ss state_room.shot
#define MINE(step) (state_reset(step, 0, 0), memset(&mine_owner, 0, sizeof(mine_owner)), ss.state = 1, ss.unk7C = (struct WeaponObj*)&mine_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define MINE_SEEN() (state_extra = (u16)ss.timer | (u32)(u8)ss.unk84.value << 16 | (u32)(u8)ss.unk8C.halves[1] << 24)
static void dm_rise(void)
{
    MINE(1);
    ss.animation_step.fields.relative_step = 1;
    double_mine_update(&ss);
}
static void dm_rise_high(void)
{
    MINE(1);
    cur_random = 1;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_rise_low(void)
{
    MINE(1);
    cur_random = 2;
    ss.y_pos.i.hi = 0x200;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_climb(void)
{
    MINE(2);
    ss.timer = 4;
    ss.unk8C.halves[1] = 0x40;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_climb_done(void)
{
    MINE(2);
    ss.unk8C.halves[1] = 0x40;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_dash_left(void)
{
    MINE(3);
    g_Player.x_pos.i.hi = 0x20;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_dash_right(void)
{
    MINE(3);
    g_Player.x_pos.i.hi = 0x100;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_dash(void)
{
    MINE(4);
    ss.unk8C.halves[0] = 0x100;
    ss.unk84.value = angle_from_delta(0x800000 - 0x1000000, 0) & 0xFF;
    ss.x_vel.val = 0x80000;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_dash_arrive(void)
{
    MINE(4);
    ss.unk8C.halves[0] = 0x40;
    ss.unk8C.halves[1] = 0x50;
    ss.unk84.value = 0;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_fire(void)
{
    MINE(5);
    ss.animation_step.fields.relative_step = 1;
    ss.animation_step.fields.event = 1;
    double_mine_update(&ss);
}
static void dm_fire_wait(void)
{
    MINE(5);
    ss.animation_step.fields.relative_step = 1;
    double_mine_update(&ss);
}
static void dm_fire_done(void)
{
    MINE(5);
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_cool(void)
{
    MINE(6);
    ss.timer = 2;
    double_mine_update(&ss);
    MINE_SEEN();
}
static void dm_cool_done(void)
{
    MINE(6);
    ss.timer = 1;
    double_mine_update(&ss);
}
static void dm_owner_gone(void)
{
    MINE(6);
    ss.timer = 2;
    mine_owner.state = 2;
    double_mine_update(&ss);
}
static void dm_shot_down(void)
{
    MINE(6);
    ss.timer = 2;
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    double_mine_update(&ss);
}
static void dm_away(void)
{
    MINE(6);
    ss.timer = 2;
    ss.x_pos.i.hi = 0x1000;
    double_mine_update(&ss);
}

static void (*const double_mine_states_cases[])(void) = {
    dm_rise,
    dm_rise_high,
    dm_rise_low,
    dm_climb,
    dm_climb_done,
    dm_dash_left,
    dm_dash_right,
    dm_dash,
    dm_dash_arrive,
    dm_fire,
    dm_fire_wait,
    dm_fire_done,
    dm_cool,
    dm_cool_done,
    dm_owner_gone,
    dm_shot_down,
    dm_away,
};
static const u32 double_mine_states_expected[] = { 0x101u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x201u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x80000009u, 0u, 2u, 0u, 0x800000u, 0x2000000u, 0u, 0u, 0u, 0x40000u, 0x5000006Du, 0u, 0x201u, 0u, 0x800000u, 0x580000u, 0u, 0u, 0u, 0x40000u, 0x40000003u, 0u, 0x301u, 0u, 0x800000u, 0x400000u, 0u, 0u, 0u, 0x40000u, 0x40000000u, 0u, 0x401u, 0u, 0x800000u, 0x600000u, 0xFFF80000u, 0u, 0u, 0x40000u, 0x10003Cu, 0u, 0x401u, 0u, 0x800000u, 0x600000u, 0x80000u, 0u, 0u, 0x40000u, 0x3Cu, 0u, 0x401u, 0u, 0x880000u, 0x600000u, 0x80000u, 0u, 0u, 0x40000u, 0u, 0u, 0x501u, 0xFF000000u, 0x400000u, 0x500000u, 0u, 0u, 0u, 0x40000u, 0x50100000u, 0u, 0x501u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x410000u, 0x501u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x601u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x3Cu, 0u, 0x601u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 0x301u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x602u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x41002100u, 0x602u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x41002100u, 2u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_double_mine_states(u32 row)
{
    return object_run(double_mine_states_cases[row], row, &double_mine_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "double_mine_states", 0, 0, COUNT(double_mine_states_cases), test_double_mine_states },
    { "double_mine_negative_timer", NULL, double_mine_negative_timer_cases_expected, COUNT(double_mine_negative_timer_cases_expected), mine_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_mine_states_cases) + COUNT(double_mine_negative_timer_cases_expected);
