#include "test_runtime.h"
#include "support/state_cases.h"
#include "main/shots/shot_29_cannon_missile.h"

static const u32 cannon_missile_slow_expected[] = { 0u, 0u, 0u, 0u, 0xFFu, 0u, 0u };
static u32 test_cannon_missile_slow(u32 row)
{
    u32 observed_values[7];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk8C.shot_29.timer = 1;
    obj.unk90.bytes[1] = 255;
    obj.unk2 = -1;
    obj.y_vel.val = 1048576;
    cannon_missile_slow(&obj);
    observed_values[0] = (u32)obj.unk28;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk8C.shot_29.timer;
    observed_values[3] = (u32)obj.unk8C.shot_29.unk8D;
    observed_values[4] = (u32)obj.unk90.bytes[1];
    observed_values[5] = (u32)obj.x_vel.val;
    observed_values[6] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, cannon_missile_slow_expected, 7);
}

static const u32 inputs_0[3][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 255, 0, 255, 0 },
    { 0, 0, 0, 0, 255, 255, 0, 0 },
};
struct cannon_missile_track_case {
    u32 expected[14];
};
static const struct cannon_missile_track_case cannon_missile_track_cases[] = {
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0x21u, 0u, 0x17u, 0u, VISUAL_SATURN_LAYER(7), 0u, 1u, 0xFFFFFFF0u, 0u, 0u, 0u, 0u, 1u, 0u } },
    { { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u } },
};
static u32 test_cannon_missile_track(u32 row)
{
    const struct cannon_missile_track_case* c = &cannon_missile_track_cases[row];
    u32 observed_values[14];
    struct ShotObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.unk8C.bytes[1] = inputs_0[row][0];
    obj.y_pos.i.hi = inputs_0[row][1];
    g_Player.y_pos.i.hi = inputs_0[row][2];
    obj.unk8C.bytes[2] = inputs_0[row][3];
    obj.unk90.bytes[1] = inputs_0[row][4];
    pool_0_full = inputs_0[row][5];
    obj.unk15 = inputs_0[row][6];
    obj.x_pos.i.hi = inputs_0[row][7];
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    cannon_missile_track(&obj);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].ext.misc_5.animation;
    observed_values[2] = (u32)misc_objects[0].id;
    observed_values[3] = (u32)misc_objects[0].unk15;
    observed_values[4] = (u32)misc_objects[0].unk16;
    observed_values[5] = (u32)misc_objects[0].unk2;
    observed_values[6] = (u32)misc_objects[0].unk7;
    observed_values[7] = (u32)misc_objects[0].x_pos.i.hi;
    observed_values[8] = (u32)misc_objects[0].x_vel.val;
    observed_values[9] = (u32)misc_objects[0].y_pos.i.hi;
    observed_values[10] = (u32)misc_objects[0].y_vel.val;
    observed_values[11] = (u32)obj.unk8C.bytes[1];
    observed_values[12] = (u32)obj.unk8C.bytes[2];
    observed_values[13] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

void func_8009F89C(struct ShotObj*);
static struct MainObj cm_owner;
#define cm state_room.shot
#define CM(st, step, kind, face) (state_reset(step, 0, 0), memset(&cm_owner, 0, sizeof(cm_owner)), memset(weapon_objects, 0, sizeof(weapon_objects)), memset(misc_objects, 0, sizeof(misc_objects)), cm_owner.x_pos.i.hi = 0x100, cm_owner.y_pos.i.hi = 0x80, cm.active = 1, cm.state = st, cm.unk2 = kind, cm.unk15 = face, cm.unk7C = (struct WeaponObj*)&cm_owner, cm.x_pos.i.hi = 0x80, cm.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x400, g_Player.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1))
#define CMX() (state_extra = C_TEST_LE_WORD(&cm.unk8C) ^ C_TEST_LE_WORD(&cm.unk90) << 4)
static void cm_init_upper_left(void)
{
    CM(0, 0, 0, 0), cannon_missile_update(&cm), CMX();
}
static void cm_init_upper_right(void) { CM(0, 0, 0, PLAYER_FACING_RIGHT), cannon_missile_update(&cm), CMX(); }
static void cm_init_lower_left(void) { CM(0, 0, 1, 0), cannon_missile_update(&cm), CMX(); }
static void cm_init_lower_right(void) { CM(0, 0, 1, PLAYER_FACING_RIGHT), cannon_missile_update(&cm), CMX(); }
#define CMMAIN(setup) (CM(1, 0, 0, 0), cm.unk8C.bytes[3] = 0x20, cm.unk90.bytes[0] = 2, setup, cannon_missile_update(&cm), CMX())
static void cm_destroyed(void)
{
    CMMAIN((((struct MainObj*)&cm)->hp = 1, state_hit((struct MainObj*)&cm, 0, 0, 1)));
}
static void cm_fast_on_screen(void) { CMMAIN((cm.x_vel.val = -0x50000, cm.unk28 = 0x100)); }
static void cm_off_screen(void) { CMMAIN(cm.x_pos.i.hi = 0x200); }
static void cm_launch_left_up(void) { CM(1, 0, 0, 0), func_8009F89C(&cm), CMX(); }
static void cm_launch_right_down(void) { CM(1, 0, 1, PLAYER_FACING_RIGHT), func_8009F89C(&cm), CMX(); }
static void cm_blink_reload(void) { CM(1, 0, 0, 0), cm.unk8C.bytes[3] = 5, func_8009F89C(&cm), CMX(); }
static void cm_slow_stops(void) { CM(1, 1, 0, 0), cm.unk8C.shot_29.timer = 1, cm.x_vel.val = 0x5000, cannon_missile_slow(&cm), CMX(); }
static void cm_slow_lower_early(void) { CM(1, 1, 1, 0), cm.unk8C.shot_29.timer = 0x20, cm.y_vel.val = 0x10000, cannon_missile_slow(&cm), CMX(); }
static void cm_slow_lower_level(void) { CM(1, 1, 1, 0), cm.unk8C.shot_29.timer = 5, cannon_missile_slow(&cm), CMX(); }
#define TRACK(vt, py, setup) (CM(1, 2, 0, 0), cm.unk8C.bytes[1] = vt, cm.unk8C.bytes[2] = 3, cm.y_vel.val = 0x1234, g_Player.y_pos.i.hi = py, setup, cannon_missile_track(&cm), CMX())
static void cm_track_level_below(void)
{
    TRACK(4, 0x6A, 0);
}
static void cm_track_down(void) { TRACK(4, 0x90, 0); }
static void cm_track_level_above(void) { TRACK(4, 0x66, 0); }
static void cm_track_up(void) { TRACK(4, 0x30, 0); }
static void cm_track_puff_left(void) { TRACK(0, 0x60, (cm.unk8C.bytes[2] = 0, cm.unk90.bytes[1] = 1)); }
static void (*const cm_cases[])(void) = {
    cm_init_upper_left,
    cm_init_upper_right,
    cm_init_lower_left,
    cm_init_lower_right,
    cm_destroyed,
    cm_fast_on_screen,
    cm_off_screen,
    cm_launch_left_up,
    cm_launch_right_down,
    cm_blink_reload,
    cm_slow_stops,
    cm_slow_lower_early,
    cm_slow_lower_level,
    cm_track_level_below,
    cm_track_down,
    cm_track_level_above,
    cm_track_up,
    cm_track_puff_left,
};
static const u32 cm_expected[] = {
    0x1u,
    0xFF000001u,
    0x11A0000u,
    0x5D0000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2000003Eu,
    0x0u,
    0x1u,
    0xFF400001u,
    0xE60000u,
    0x5D0000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2000003Eu,
    0x0u,
    0x1u,
    0xFF000101u,
    0x11A0000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20000012u,
    0x0u,
    0x1u,
    0xFF400101u,
    0xE60000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20000012u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x48000u,
    0x1F000010u,
    0x2100u,
    0x1u,
    0x1u,
    0x7B0000u,
    0x600000u,
    0xFFFAFF00u,
    0x0u,
    0x0u,
    0x48000u,
    0x1F000010u,
    0x0u,
    0x2u,
    0x1u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x48000u,
    0x1F000010u,
    0x0u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x5000u,
    0x10000u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x101u,
    0x400101u,
    0x800000u,
    0x600000u,
    0xFFFFB000u,
    0xFFFF0000u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x4000020u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x3000u,
    0x50000u,
    0x3800u,
    0x0u,
    0x101u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x10000u,
    0x0u,
    0x50000u,
    0x1Fu,
    0x0u,
    0x101u,
    0x101u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x4u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20300u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0xFFFE0000u,
    0x0u,
    0x50000u,
    0x20300u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20300u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x20000u,
    0x0u,
    0x50000u,
    0x20300u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x11000u,
    0x21000000u,
};
static u32 test_cm(u32 row)
{
    return object_run(cm_cases[row], row, &cm_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "cannon_missile_slow", 0, 0, 1, test_cannon_missile_slow },
    { "cannon_missile_track", 0, 0, 3, test_cannon_missile_track },
    { "cannon_missile_states", 0, 0, COUNT(cm_cases), test_cm },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 3 + COUNT(cm_cases);
