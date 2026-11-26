#include "test_runtime.h"
#include "main/quads/quad_09_aiming_laser_beam.h"
#include "main/visuals/visual_18_aiming_laser_scope.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
void func_800D69A8(struct QuadObj*, struct PlayerObj*, struct PlayerObj*);

static const u32 func_800D69A8_expected[] = { 0u, 0u, 0xFFFFFFF7u, 6u, 3u, 6u, 3u, 0xFFFFFFFAu, 3u, 0u };
static u32 test_func_800D69A8(u32 row)
{
    u32 observed_values[10];
    struct QuadObj obj;
    struct PlayerObj argument_obj_1;
    struct PlayerObj argument_obj_2;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&argument_obj_2, 0, sizeof(argument_obj_2));
    func_800D69A8(&obj, &argument_obj_1, &argument_obj_2);
    observed_values[0] = (u32)obj.vertices[0].x.val;
    observed_values[1] = (u32)obj.vertices[0].y.val;
    observed_values[2] = (u32)obj.vertices[1].x.i.hi;
    observed_values[3] = (u32)obj.vertices[1].y.i.hi;
    observed_values[4] = (u32)obj.vertices[2].x.i.hi;
    observed_values[5] = (u32)obj.vertices[2].y.i.hi;
    observed_values[6] = (u32)obj.vertices[3].x.i.hi;
    observed_values[7] = (u32)obj.vertices[3].y.i.hi;
    observed_values[8] = (u32)obj.x_pos.i.hi;
    observed_values[9] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_800D69A8_expected, 10);
}

#include "support/aiming_cancellation.h"
AIMING_CANCEL_SIX(2)
AIMING_CANCEL_MODE(2, 6)
static const CTestCase aiming_laser_beam_cancellation_cases[] = { AIMING_CANCEL_SIX_ENTRIES(2) AIMING_CANCEL_ENTRIES(2, 6) };

static const u32 aiming_laser_beam_cancellation_cases_expected[] = { 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u };
static struct QuadObj lb;
static struct MainObj lb_target;
static u32 beam_step(u8 state, u8 timer, u8 target_hp)
{
    memset(&lb, 0, sizeof(lb));
    memset(&lb_target, 0, sizeof(lb_target));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.weapon = 6;
    g_Player.hp = 16;
    g_Player.unk15 = PLAYER_FACING_RIGHT;
    g_Player.x_pos.i.hi = 0x100;
    g_Player.y_pos.i.hi = 0x80;
    lb_target.active = 1;
    lb_target.hp = target_hp;
    lb_target.x_pos.i.hi = 0xC0;
    lb_target.y_pos.i.hi = 0x60;
    lb.active = 1;
    lb.id = 9;
    lb.state = state;
    lb.unk2 = 1;
    lb.on_screen = 1;
    lb.unk5C = (struct PlayerObj*)&lb_target;
    lb.ext.unk_ext3.unk38 = timer;
    aiming_laser_beam_update(&lb);
    return (u8)lb.active | (u32)lb.state << 8 | (u32)lb.ext.unk_ext3.unk38 << 16 | (u32)(u8)lb.on_screen << 24;
}
#define BEAM_SHAPE() ((u16)lb.x_pos.i.hi ^ (u32)(u16)lb.y_pos.i.hi << 16 ^ (u16)lb.vertices[1].x.i.hi << 8 ^ (u32)(u16)lb.vertices[3].y.i.hi << 24)
static u32 lb_target_dead(void)
{
    return beam_step(1, 5, 0);
}
static u32 lb_start(void)
{
    u32 seen = beam_step(0, 0, 4);
    assert(lb.unk34 == 0xE && lb.unk36 == 1 && lb.vertices[1].x.i.hi == lb_target.x_pos.i.hi - (lb.x_pos.i.hi - 6));
    assert(lb.vertices[1].y.i.hi == lb_target.y_pos.i.hi - (lb.y_pos.i.hi + 6) && lb.vertices[3].y.i.hi == lb_target.y_pos.i.hi - (lb.y_pos.i.hi - 6));
    return seen ^ BEAM_SHAPE();
}
static u32 lb_blink(void) { return beam_step(1, 2, 4); }
static u32 lb_steady(void) { return beam_step(1, 1, 4); }
static const CTestCase aiming_laser_beam_steps_cases[] = {
    lb_target_dead,
    lb_start,
    lb_blink,
    lb_steady,
};
static const u32 aiming_laser_beam_steps_cases_expected[] = { 0x50000u, 0xE743C87Eu, 0x10101u, 0x1000101u };

const struct CTestGroup c_test_groups[] = {
    { "func_800D69A8", 0, 0, 1, test_func_800D69A8 },
    { "aiming_laser_beam_cancellation", aiming_laser_beam_cancellation_cases, aiming_laser_beam_cancellation_cases_expected, COUNT(aiming_laser_beam_cancellation_cases), 0 },
    { "aiming_laser_beam_steps", aiming_laser_beam_steps_cases, aiming_laser_beam_steps_cases_expected, COUNT(aiming_laser_beam_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(aiming_laser_beam_cancellation_cases) + COUNT(aiming_laser_beam_steps_cases);
