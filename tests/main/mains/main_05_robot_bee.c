#include "test_runtime.h"
#include "main/55C4.h"
void robot_bee_resume_step(struct MainObj* arg0);
void robot_bee_sting(struct MainObj* arg0);
#include "main/mains/main_05_robot_bee.h"
#ifdef MMX4_PC
#include <libspu.h>
#include <psyz/spu.h>
#endif
void robot_bee_wait(struct MainObj*);
void robot_bee_circle(struct MainObj*);
extern u32* D_80137E08;
extern union AnimationStep* robot_bee_animations[];
extern s32 D_800FA130[2];

static u32 arc_default(void)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 5;
    obj.state = 1;
    obj.unk6 = 0x27;
    obj.ext.main_5.unk80 = 4;
    obj.unk7C = 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_step.fields.duration = 2;
    before = obj;
    func_80045DD8(&obj);
    before.unk7C = 1;
    before.animation_step.fields.duration = 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    actual = (u16)obj.unk7C | ((u32)obj.ext.main_5.unk80 << 16);
    return actual;
}
static const CTestCase robot_bee_arc_default_cases[] = { arc_default };
static const u32 robot_bee_arc_default_cases_expected[] = { 0x40001u };

static const s16 timers[8] = { 31, 31, 1, 1, 2, 2, 2, 2 };
static const s32 distances[8] = { -0x6FFFFF, 0x6FFFFF, 0, 0, -0x700000, 0x700000, -0x700000, 0x700000 };
static u32 bob_case_with_sound(u32 mode, u32 loop_sound)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    u32 i, actual, reversed = mode < 4;
    memset(&obj, 0, sizeof(obj));
    memset(&obj.ext, 0xA5, sizeof(obj.ext));
    obj.active = 0x41;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = loop_sound ? 1 : 9;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.unk7C = timers[mode];
    obj.ext.main_5.unk80 = mode & 1;
    obj.ext.main_5.unk81 = mode & 1;
    obj.x_pos.val = 200 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_speed = 0x18000;
    obj.y_speed = mode & 1 ? 0x2000 : -0x2000;
    obj.x_accel = 0x800;
    obj.gravity = mode & 1 ? 0x1000 : -0x1000;
    obj.animation_table = (const u8* const*)robot_bee_animations;
    obj.animation_cursor = (const u8*)robot_bee_animations[1];
    obj.animation_step = *robot_bee_animations[1];
    obj.unk17 = 1;
    obj.previous_animation_index = 0xFF;
    g_Player.x_pos.val = obj.x_pos.val + obj.x_speed + distances[mode];
    player_expected = g_Player;
    expected = obj;
    expected.animation_cursor += 4;
    expected.animation_step = *(const union AnimationStep*)expected.animation_cursor;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val -= obj.y_speed;
    expected.x_speed += obj.unk15 ? obj.x_accel : -obj.x_accel;
    expected.y_speed -= obj.gravity;
    expected.unk7C--;
    if (reversed) {
        expected.ext.main_5.unk81 = !(mode & 1);
        expected.gravity = -obj.gravity;
        expected.y_speed = mode & 1 ? -0x8000 : 0x8000;
    }
    if (mode == 2 || mode == 3) {
        expected.ext.main_5.unk80 = !(mode & 1);
        expected.x_speed = 0;
        expected.x_accel = -obj.x_accel;
        expected.unk7C = 60;
    }
    if (mode < 4) {
        expected.animation_cursor = (const u8*)robot_bee_animations[2];
        expected.animation_step = *robot_bee_animations[2];
        expected.unk17 = 2;
        expected.previous_animation_index = 0xFF;
        expected.unk5 = 7;
        expected.unk6 = 0;
    }
#ifdef MMX4_PC
    if (loop_sound)
        robot_bee_circle(&obj);
    else
#endif
        func_80046220(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    assert(D_800FA130[0] == -0x8000 && D_800FA130[1] == 0x8000);
    assert(robot_bee_animations[1][0].packed == 0x00010001);
    assert(robot_bee_animations[2][0].packed == 0x10010002);
    actual = (u8)obj.unk5 | ((u32)(u16)obj.unk7C << 8) | ((u32)obj.ext.main_5.unk81 << 24);
    return actual;
}
static u32 bob_case(u32 mode)
{
    return bob_case_with_sound(mode, 0);
}
static const u32 robot_bee_bob_player_distance_cases_expected[] = { 0x1001E07u, 0x1E07u, 0x1003C07u, 0x3C07u, 0x102u, 0x1000102u, 0x102u, 0x1000102u };

static const u32 func_80045940_expected[] = { 0xFFu, 0u, 1u, 0u, 0u };
static u32 test_func_80045940(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_5.unk80 = 255;
    obj.unk7C = 2;
    func_80045940(&obj);
    observed_values[0] = (u32)obj.ext.main_5.unk80;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)obj.x_speed;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_80045940_expected, 5);
}

#include "support/state_cases.h"

#define STING(n) state_reset(5, n, 0)
#define ARC() (state_extra = so.ext.main_5.unk80 | (u32)(u16)so.unk7C << 16)
static void rb_start_left(void)
{
    STING(0);
    robot_bee_sting(&so);
}
static void rb_start_right(void)
{
    STING(0);
    so.unk15 = 0x40;
    robot_bee_sting(&so);
}
static void rb_approach_far(void)
{
    STING(1);
    so.x_pos.val = 0x800000;
    so.x_speed = -0x10000;
    robot_bee_sting(&so);
}
static void rb_approach_near(void)
{
    STING(1);
    so.x_pos.val = 0x200000;
    robot_bee_sting(&so);
}
static void rb_approach_near_left(void)
{
    STING(1);
    so.x_pos.val = -0x200000;
    robot_bee_sting(&so);
}
static void rb_brake(void)
{
    STING(2);
    so.unk7C = 9;
    robot_bee_sting(&so);
}
static void rb_brake_left(void)
{
    STING(2);
    so.unk7C = 4;
    robot_bee_sting(&so);
}
static void rb_brake_right(void)
{
    STING(2);
    so.unk7C = 4;
    so.unk15 = 0x40;
    robot_bee_sting(&so);
}
static void rb_lunge(void)
{
    STING(3);
    so.unk7C = 3;
    so.x_speed = 0x40000;
    robot_bee_sting(&so);
}
static void rb_lunge_done(void)
{
    STING(3);
    robot_bee_sting(&so);
    ARC();
}
static void rb_loop_origin(void)
{
    STING(4);
    so.unk7C = 3;
    so.x_pos.val = 0x400000;
    so.y_pos.val = 0x300000;
    robot_bee_sting(&so);
    ARC();
}
static void rb_loop_one(void)
{
    STING(4);
    so.unk7C = 3;
    so.ext.main_5.unk80 = 1;
    robot_bee_sting(&so);
    ARC();
}
static void rb_loop_two(void)
{
    STING(4);
    so.unk7C = 3;
    so.ext.main_5.unk80 = 2;
    so.unk15 = 0x40;
    robot_bee_sting(&so);
    ARC();
}
static void rb_loop_three(void)
{
    STING(4);
    so.unk7C = 3;
    so.ext.main_5.unk80 = 3;
    robot_bee_sting(&so);
    ARC();
}
static void rb_loop_four(void)
{
    STING(4);
    so.unk7C = 3;
    so.ext.main_5.unk80 = 4;
    so.unk15 = 0x40;
    robot_bee_sting(&so);
    ARC();
}
static void rb_loop_next(void)
{
    STING(4);
    so.ext.main_5.unk80 = 2;
    robot_bee_sting(&so);
    ARC();
}
static void rb_loop_exit(void)
{
    STING(4);
    so.ext.main_5.unk80 = 4;
    robot_bee_sting(&so);
    ARC();
}
static void rb_recoil(void)
{
    STING(5);
    so.unk7C = 2;
    so.x_speed = -0x10000;
    robot_bee_sting(&so);
}
static void rb_recoil_done(void)
{
    STING(5);
    robot_bee_sting(&so);
}
static void rb_return_origin(void)
{
    STING(6);
    so.unk7C = 3;
    so.x_pos.val = 0x400000;
    robot_bee_sting(&so);
    ARC();
}
static void rb_return_one(void)
{
    STING(6);
    so.unk7C = 3;
    so.ext.main_5.unk80 = 1;
    so.unk15 = 0x40;
    robot_bee_sting(&so);
    ARC();
}
static void rb_return_two(void)
{
    STING(6);
    so.unk7C = 3;
    so.ext.main_5.unk80 = 2;
    robot_bee_sting(&so);
    ARC();
}
static void rb_return_three(void)
{
    STING(6);
    so.unk7C = 3;
    so.ext.main_5.unk80 = 3;
    so.unk15 = 0x40;
    robot_bee_sting(&so);
    ARC();
}
static void rb_return_next(void)
{
    STING(6);
    so.ext.main_5.unk80 = 1;
    robot_bee_sting(&so);
    ARC();
}
static void rb_return_exit(void)
{
    STING(6);
    so.ext.main_5.unk80 = 3;
    robot_bee_sting(&so);
    ARC();
}
static void rb_fly_off(void)
{
    STING(7);
    so.y_speed = 0x50000;
    robot_bee_sting(&so);
}
static void rb_resume(void)
{
    state_reset(1, 0, 0);
    so.ext.main_5.saved_unk5 = 4;
    robot_bee_resume_step(&so);
}

static void (*const robot_bee_sting_states_cases[])(void) = {
    rb_start_left,
    rb_start_right,
    rb_approach_far,
    rb_approach_near,
    rb_approach_near_left,
    rb_brake,
    rb_brake_left,
    rb_brake_right,
    rb_lunge,
    rb_lunge_done,
    rb_loop_origin,
    rb_loop_one,
    rb_loop_two,
    rb_loop_three,
    rb_loop_four,
    rb_loop_next,
    rb_loop_exit,
    rb_recoil,
    rb_recoil_done,
    rb_return_origin,
    rb_return_one,
    rb_return_two,
    rb_return_three,
    rb_return_next,
    rb_return_exit,
    rb_fly_off,
    rb_resume,
};
static const u32 robot_bee_sting_states_expected[] = { 0x10500u, 0xFF000000u, 0u, 0u, 0xFFFE0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10500u, 0xFF400000u, 0u, 0u, 0x20000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10500u, 0u, 0x7F0000u, 0u, 0xFFFF0000u, 0u, 0u, 0x40000u, 0u, 0u, 0x20500u, 0xFF000000u, 0x200000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20500u, 0xFF000000u, 0xFFE00000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30500u, 0u, 0u, 0u, 0xFFFD0000u, 0u, 0u, 0x40000u, 0u, 0u, 0x30500u, 0x400000u, 0u, 0u, 0x30000u, 0u, 0u, 0x40000u, 0u, 0u, 0x30500u, 0u, 0x40000u, 0u, 0x40000u, 0u, 0u, 0x40000u, 0u, 0u, 0x40500u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x80000u, 0u, 0x40500u, 0u, 0x400000u, 0x300000u, 0u, 0u, 0u, 0x40000u, 0x20001u, 0u, 0x40500u, 0u, 0xFFD51F69u, 0x1F270Du, 0u, 0u, 0u, 0x40000u, 0x20001u, 0u, 0x40500u, 0x400000u, 0x2376BCu, 0xFFD89D2Au, 0u, 0u, 0u, 0x40000u, 0x20002u, 0u, 0x40500u, 0u, 0x2AE097u, 0xFFE0D8F3u, 0u, 0u, 0u, 0x40000u, 0x20003u, 0u, 0x40500u, 0x400000u, 0xFFDC8944u, 0x2762D6u, 0u, 0u, 0u, 0x40000u, 0x20004u, 0u, 0x40500u, 0u, 0xFFFA75D6u, 0xFFCB4A53u, 0u, 0u, 0u, 0x40000u, 0x70003u, 0u, 0x50500u, 0u, 0x58A2Au, 0x34B5ADu, 0xFFF9E000u, 0x40000u, 0u, 0x40000u, 0x170000u, 0u, 0x50500u, 0u, 0xFFFF0000u, 0u, 0xFFFF0000u, 0u, 0u, 0x40000u, 0u, 0u, 0x60500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x60500u, 0u, 0x400000u, 0u, 0u, 0u, 0u, 0x40000u, 0x20001u, 0u, 0x60500u, 0x400000u, 0x2AE097u, 0xFFE0D8F3u, 0u, 0u, 0u, 0x40000u, 0x20001u, 0u, 0x60500u, 0u, 0xFFDC8944u, 0x2762D6u, 0u, 0u, 0u, 0x40000u, 0x20002u, 0u, 0x60500u, 0x400000u, 0xFFD51F69u, 0x1F270Du, 0u, 0u, 0u, 0x40000u, 0x20003u, 0u, 0x60500u, 0u, 0xFFCB4A53u, 0xFFFA75D6u, 0u, 0u, 0u, 0x40000u, 0x70002u, 0u, 0x70500u, 0u, 0x34B5ADu, 0x58A2Au, 0u, 0x50000u, 0u, 0x40000u, 0x70003u, 0u, 0x70500u, 0u, 0u, 0xFFFB0000u, 0u, 0x50000u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_robot_bee_sting_states(u32 row)
{
    return object_run(robot_bee_sting_states_cases[row], row, &robot_bee_sting_states_expected[row * 10]);
}

#ifdef MMX4_PC
static u32 test_wait_active_sound(u32 row)
{
    static const s16 distance[] = { -145, -144, 144, 145 };
    static u32 commands[0x15];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    u32 voice = row & 1 ? 23 : 0;
    u32* command_before = D_80137E08;
    Psyz_SpuInit();
    memset(commands, 0, sizeof(commands));
    commands[0x13] = voice << 24;
    D_80141F50[2] = (u8*)commands;
    SpuSetKey(SPU_ON, 1u << voice);
    assert(SpuGetKeyStatus(1u << voice) != 0);
    memset(&obj, 0, sizeof(obj));
    obj.active = -0x7F;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = obj.unk6 = 1;
    obj.unk15 = row & 1 ? 0x40 : 0;
    obj.x_pos.val = 300 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_speed = 0x18000;
    obj.y_speed = 0x28000;
    obj.animation_table = (const u8* const*)robot_bee_animations;
    obj.animation_cursor = (const u8*)robot_bee_animations[1];
    obj.animation_step = *robot_bee_animations[1];
    obj.unk17 = 1;
    assert(is_sound_finished(0x13, &obj) == 0);
    memset(&g_Player, 0x37, sizeof(g_Player));
    g_Player.x_pos.val = obj.x_pos.val + distance[row / 2] * 65536;
    player_expected = g_Player;
    expected = obj;
    expected.animation_cursor += 4;
    expected.animation_step = *(const union AnimationStep*)expected.animation_cursor;
    if (row / 2 == 1 || row / 2 == 2) {
        expected.unk5 = 3;
        expected.x_speed = row & 1 ? -0x10000 : 0x10000;
        expected.y_speed = 0;
    }
    robot_bee_wait(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    assert(D_80137E08 == command_before);
    assert(SpuGetKeyStatus(1u << voice) != 0);
    assert(commands[0x13] == voice << 24);
    return 1;
}
static u32 test_circle_active_sound(u32 row)
{
    static u32 commands[0x15];
    u32 voice = row & 1 ? 23 : 0;
    u32* before = D_80137E08;
    Psyz_SpuInit();
    memset(commands, 0, sizeof(commands));
    commands[0x13] = voice << 24;
    D_80141F50[2] = (u8*)commands;
    SpuSetKey(SPU_ON, 1u << voice);
    assert(SpuGetKeyStatus(1u << voice) != 0);
    assert(bob_case_with_sound(row, 1) == robot_bee_bob_player_distance_cases_expected[row]);
    assert(D_80137E08 == before);
    assert(SpuGetKeyStatus(1u << voice) != 0);
    assert(commands[0x13] == voice << 24);
    return 1;
}
#define ACTIVE_SOUND_CASES 16
#else
#define ACTIVE_SOUND_CASES 0
#endif

extern union AnimationStep* robot_bee_animations[];
extern s32 D_800F459C[], D_800F45C0[];
extern u32 D_800F45E4[];
extern u32* D_80137E08;
void robot_bee_drop(struct MainObj*);

struct Aim {
    s32 dx, dy;
    s32 x_speed[2], y_speed;
    u8 animation, facing[2];
};
static const struct Aim aims[32] = {
    { -0xC00000, 0x0, { 0x30000, 0x30000 }, 0x0, 0, { 64, 64 } },
    { -0x500000, 0x100000, { 0x2F13C, 0x2F13C }, 0x0, 0, { 64, 64 } },
    { -0x280000, 0x100000, { 0x2C589, 0x2C589 }, 0x0, 0, { 64, 64 } },
    { -0x180000, 0x100000, { 0x27E91, 0x27E91 }, 0x0, 0, { 64, 64 } },
    { -0x100000, 0x100000, { 0x21F0F, 0x21F0F }, 0x0, 0, { 64, 64 } },
    { -0xA0000, 0x100000, { 0x1AAAB, 0x1AAAB }, 0x0, 0, { 64, 64 } },
    { -0x60000, 0x100000, { 0x125E5, 0x125E5 }, 0x0, 0, { 64, 64 } },
    { -0x30000, 0x100000, { 0x95D3, 0x95D3 }, 0x0, 0, { 64, 64 } },
    { 0x0, 0x100000, { -0x30000, 0x30000 }, 0x0, 0, { 0, 64 } },
    { 0x30000, 0x100000, { -0x95D3, -0x95D3 }, 0x0, 0, { 0, 0 } },
    { 0x60000, 0x100000, { -0x125E5, -0x125E5 }, 0x0, 0, { 0, 0 } },
    { 0xA0000, 0x100000, { -0x1AAAB, -0x1AAAB }, 0x0, 0, { 0, 0 } },
    { 0x100000, 0x100000, { -0x21F0F, -0x21F0F }, 0x0, 0, { 0, 0 } },
    { 0x180000, 0x100000, { -0x27E91, -0x27E91 }, 0x0, 0, { 0, 0 } },
    { 0x280000, 0x100000, { -0x2C589, -0x2C589 }, 0x0, 0, { 0, 0 } },
    { 0x500000, 0x100000, { -0x2F13C, -0x2F13C }, 0x0, 0, { 0, 0 } },
    { 0xC00000, 0x0, { -0x30000, -0x30000 }, 0x0, 0, { 0, 0 } },
    { 0x500000, -0x100000, { -0x2F13C, -0x2F13C }, -0x95D3, 15, { 0, 0 } },
    { 0x280000, -0x100000, { -0x2C589, -0x2C589 }, -0x125E5, 14, { 0, 0 } },
    { 0x180000, -0x100000, { -0x27E91, -0x27E91 }, -0x1AAAB, 14, { 0, 0 } },
    { 0x100000, -0x100000, { -0x30000, -0x30000 }, -0x21F0F, 14, { 0, 0 } },
    { 0xA0000, -0x100000, { -0x1AAAB, -0x1AAAB }, -0x27E91, 14, { 0, 0 } },
    { 0x60000, -0x100000, { -0x125E5, -0x125E5 }, -0x2C589, 14, { 0, 0 } },
    { 0x30000, -0x100000, { -0x95D3, -0x95D3 }, -0x2F13C, 13, { 0, 0 } },
    { 0x0, -0x100000, { 0x0, 0x0 }, -0x30000, 12, { 0, 64 } },
    { -0x30000, -0x100000, { 0x95D3, 0x95D3 }, -0x2F13C, 13, { 64, 64 } },
    { -0x60000, -0x100000, { 0x125E5, 0x125E5 }, -0x2C589, 14, { 64, 64 } },
    { -0xA0000, -0x100000, { 0x1AAAB, 0x1AAAB }, -0x27E91, 14, { 64, 64 } },
    { -0x100000, -0x100000, { 0x30000, 0x30000 }, -0x21F0F, 14, { 64, 64 } },
    { -0x180000, -0x100000, { 0x27E91, 0x27E91 }, -0x1AAAB, 14, { 64, 64 } },
    { -0x280000, -0x100000, { 0x2C589, 0x2C589 }, -0x125E5, 14, { 64, 64 } },
    { -0x500000, -0x100000, { 0x2F13C, 0x2F13C }, -0x95D3, 15, { 64, 64 } },
};

struct Boundary {
    s32 ratio;
    u8 directions[4];
};
static const struct Boundary boundaries[] = {
    { 0x1935, { 8, 8, 24, 24 } },
    { 0x1936, { 7, 9, 23, 25 } },
    { 0x1937, { 7, 9, 23, 25 } },
    { 0x4DA7, { 7, 9, 23, 25 } },
    { 0x4DA8, { 6, 10, 22, 26 } },
    { 0x4DA9, { 6, 10, 22, 26 } },
    { 0x88D4, { 6, 10, 22, 26 } },
    { 0x88D5, { 5, 11, 21, 27 } },
    { 0x88D6, { 5, 11, 21, 27 } },
    { 0xD217, { 5, 11, 21, 27 } },
    { 0xD218, { 4, 12, 20, 28 } },
    { 0xD219, { 4, 12, 20, 28 } },
    { 0x137EE, { 4, 12, 20, 28 } },
    { 0x137EF, { 4, 12, 20, 28 } },
    { 0x137F0, { 3, 13, 19, 29 } },
    { 0x1DEF0, { 3, 13, 19, 29 } },
    { 0x1DEF1, { 3, 13, 19, 29 } },
    { 0x1DEF2, { 2, 14, 18, 30 } },
    { 0x34BEA, { 2, 14, 18, 30 } },
    { 0x34BEB, { 2, 14, 18, 30 } },
    { 0x34BEC, { 1, 15, 17, 31 } },
    { 0xA2735, { 1, 15, 17, 31 } },
    { 0xA2736, { 1, 15, 17, 31 } },
    { 0xA2737, { 0, 16, 16, 0 } },
};

struct Fraction {
    s32 dx, dy;
    u8 direction;
};
static const struct Fraction fractions[] = {
    { -65536, -65536, 28 },
    { -65536, -65535, 0 },
    { -65536, -1, 0 },
    { -65536, 0, 0 },
    { -65536, 1, 0 },
    { -65536, 65535, 0 },
    { -65536, 65536, 4 },
    { 65536, -65536, 20 },
    { 65536, -65535, 16 },
    { 65536, -1, 16 },
    { 65536, 0, 16 },
    { 65536, 1, 16 },
    { 65536, 65535, 16 },
    { 65536, 65536, 12 },
    { 0, -65536, 24 },
    { 0, -65535, 16 },
    { 0, 0, 16 },
    { 0, 65536, 8 },
};
static const u32 circle_words[] = {
    0x10010002,
    0x11010009,
    0x12010001,
    0x13010001,
    0x14010001,
    0x15000001,
};
static const u32 drop_words[4][5] = {
    { 0x16010002, 0x25010002, 0x24010002, 0x23010002, 0x22000002 },
    { 0x16010002, 0x25010002, 0x24010002, 0x23000002, 0 },
    { 0x16010002, 0x25010002, 0x24000002, 0, 0 },
    { 0x16010002, 0x25000002, 0, 0, 0 },
};
static const s32 x_table[9] = { 0, 0x31F1, 0x61F7, 0x8E39, 0xB505, 0xD4DB, 0xEC83, 0xFB14, 0x10000 };
static const s32 y_table[9] = { 0x10000, 0xFB14, 0xEC83, 0xD4DB, 0xB505, 0x8E39, 0x61F7, 0x31F1, 0 };
static const u32 ratio_table[10] = { 0, 0x1936, 0x4DA8, 0x88D5, 0xD218, 0x137EF, 0x1DEF1, 0x34BEB, 0xA2736, 0xFFFFFFFF };
static struct MainObj obj, expected;
static struct PlayerObj player_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_before[16];
static struct VisualObj visuals_before[32];
static u32 sound_command;

static void prepare(s32 dx, s32 dy, u32 facing, u32 animation_mode, s16 timer)
{
    u32 i;
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    obj.active = 0x41;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 0;
    obj.unk15 = facing * 0x40;
    obj.bg_offset = facing;
    obj.unk7C = timer;
    obj.x_pos.val = 200 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = -0x12345;
    obj.y_speed = 0x23456;
    obj.x_accel = 0x345;
    obj.gravity = -0x456;
    obj.hp = 6;
    obj.unk40 = 0x4567;
    obj.unk42 = 0x9234;
    obj.unk17 = 2;
    obj.previous_animation_index = 0xFF;
    obj.animation_table = (const u8* const*)robot_bee_animations;
    obj.animation_cursor = (const u8*)robot_bee_animations[2];
    obj.animation_step.packed = animation_mode ? 0x10010001 : 0x10010002;
    obj.ext.main_5.unk80 = 1;
    obj.ext.main_5.unk81 = 1;
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.x_pos.val = obj.x_pos.val - dx;
    g_Player.y_pos.val = obj.y_pos.val - dy;
    g_Player.bg_offset = 2;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    sound_command = 0xA5A51234;
    D_80137E08 = &sound_command;
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)weapons_before, (const u32*)weapon_objects, sizeof(weapons_before) / 4);
    c_test_copy_words((u32*)visuals_before, (const u32*)visual_objects, sizeof(visuals_before) / 4);
}

static void check(void)
{
    u32 i, j;
    static const u8 lengths[4] = { 5, 4, 3, 2 };
    c_test_same_words(&obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)weapon_objects, (const u32*)weapons_before, sizeof(weapons_before) / 4) == 0);
    assert(c_test_word_difference((const u32*)visual_objects, (const u32*)visuals_before, sizeof(visuals_before) / 4) == 0);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(cur_random == 0x1234 && need_palette_load == 0x20);
    assert(D_80137E08 == &sound_command && sound_command == 0xA5A51234);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < 6; i++)
        assert(robot_bee_animations[2][i].packed == circle_words[i]);
    for (i = 0; i < 4; i++)
        for (j = 0; j < lengths[i]; j++)
            assert(robot_bee_animations[12 + i][j].packed == drop_words[i][j]);
    for (i = 0; i < 9; i++)
        assert(D_800F459C[i] == x_table[i] && D_800F45C0[i] == y_table[i]);
    for (i = 0; i < 10; i++)
        assert(D_800F45E4[i] == ratio_table[i]);
}

static void expect_animate(void)
{
    expected.animation_step.fields.duration--;
    if (expected.animation_step.fields.duration == 0) {
        expected.animation_cursor = (const u8*)robot_bee_animations[2] + 4;
        expected.animation_step.packed = 0x11010009;
    }
}

static void expect_launch(u32 direction, u32 facing)
{
    const struct Aim* aim = &aims[direction];
    expected.unk15 = aim->facing[facing];
    expected.x_speed = aim->x_speed[facing];
    expected.y_speed = aim->y_speed;
    expected.x_accel = (expected.x_speed < 0 ? -expected.x_speed : expected.x_speed) / 64;
    expected.gravity = (expected.y_speed < 0 ? -expected.y_speed : expected.y_speed) / 64;
    if (aim->animation) {
        expected.unk17 = aim->animation;
        expected.animation_cursor = (const u8*)robot_bee_animations[aim->animation];
        expected.animation_step.packed = 0x16010002;
        expected.previous_animation_index = 0xFF;
    } else {
        expected.unk5 = 4;
        expected.unk7C = 5;
    }
    expected.unk6 = 1;
}

static u32 launch(s32 dx, s32 dy, u32 direction, u32 variant)
{
    u32 facing = variant & 1;
    prepare(dx, dy, facing, variant >> 1, 4);
    expect_animate();
    expected.unk7C = 3;
    expect_launch(direction, facing);
    robot_bee_drop(&obj);
    check();
    return 1;
}

static u32 test_compass(u32 row)
{
    u32 direction = row % 32;
    return launch(aims[direction].dx, aims[direction].dy, direction, direction % 4);
}

static u32 test_boundaries(u32 row)
{
    u32 boundary = row % COUNT(boundaries);
    u32 quadrant = row / COUNT(boundaries);
    u32 variant = boundary % 4;
    s32 dx = boundaries[boundary].ratio * 16;
    s32 dy = 16 * 65536;
    if (quadrant == 0 || quadrant == 3)
        dx = -dx;
    if (quadrant >= 2)
        dy = -dy;
    return launch(dx, dy, boundaries[boundary].directions[quadrant], variant);
}

static u32 test_fractional_axis(u32 row)
{
    const struct Fraction* f = &fractions[row % COUNT(fractions)];
    return launch(f->dx, f->dy, f->direction, row / COUNT(fractions));
}

static u32 test_wait(u32 row)
{
    static const s16 timers[3] = { 5, 6, 31 };
    s16 timer = timers[row % 3];
    prepare(aims[23].dx, aims[23].dy, (row / 3) & 1, row / 6, timer);
    expect_animate();
    expected.unk7C = timer - 1;
    robot_bee_drop(&obj);
    check();
    return 1;
}

static u32 test_countdown_sequence(u32 row)
{
    u32 direction = row % 32, facing = row / 32, tick;
    prepare(aims[direction].dx, aims[direction].dy, facing, 0, 6);
    for (tick = 0; tick < 3; tick++) {
        expect_animate();
        expected.unk7C--;
        if (tick == 2)
            expect_launch(direction, facing);
        robot_bee_drop(&obj);
        check();
    }
    return 1;
}

void robot_bee_sting(struct MainObj* arg0);
#ifdef MMX4_PC
#include <libspu.h>
#include <psyz/spu.h>
#else
s16 SsUtKeyOnV(s16, s16, s16, s16, s16, s16, s16, s16);
void _SsVmFlush(void);
s32 SpuGetKeyStatus(u32);
#endif
extern union AnimationStep* robot_bee_animations[];
extern u32* D_80137E08;
static u32 commands[21];
static void key_on(u32 voice)
{
#ifdef MMX4_PC
    SpuSetKey(1, 1u << voice);
#else
    u32 bank, program;
    for (bank = 0; bank < 6; bank++)
        if (D_8013E198[bank] >= 0)
            for (program = 0; program < 128; program++)
                if (SsUtKeyOnV(voice, D_8013E198[bank], program, 0, 60, 0, 0, 0) >= 0) {
                    _SsVmFlush();
                    for (program = 0; program < 128; program++)
                        if (SpuGetKeyStatus(1u << voice) != 0)
                            return;
                    assert(0);
                }
    assert(0);
#endif
}
static u32 sting(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 active = row % 4, face = row / 4 % 2, tick = row / 8, voice[2], found = 0, i, sound_command = 0x12345678;
#ifdef MMX4_PC
    Psyz_SpuInit();
#endif
    for (i = 0; i < 24 && found < 2; i++)
        if (SpuGetKeyStatus(1u << i) == 0)
            voice[found++] = i;
    assert(found == 2);
    memset(commands, 0, sizeof(commands));
    commands[20] = voice[0] << 24;
    commands[19] = voice[1] << 24;
    D_80141F50[2] = (u8*)commands;
    D_80137E08 = &sound_command;
    if (active & 1)
        key_on(voice[0]);
    if (active & 2)
        key_on(voice[1]);
    assert((SpuGetKeyStatus(1u << voice[0]) != 0) == !!(active & 1) && (SpuGetKeyStatus(1u << voice[1]) != 0) == !!(active & 2));
    D_8013E198[2] = -1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 5;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 7;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk7C = 7;
    obj.ext.main_5.unk80 = 3;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.y_speed = 5 * 65536;
    obj.animation_table = (const u8* const*)robot_bee_animations;
    set_animation(&obj, 11);
    assert(obj.animation_step.packed == 0x16010002);
    obj.animation_step.fields.duration = tick ? 1 : 2;
    expected = obj;
    expected.y_pos.val -= 5 * 65536;
    if (tick) {
        expected.animation_cursor += 4;
        expected.animation_step.packed = 0x17010002;
    } else
        expected.animation_step.fields.duration = 1;
    robot_bee_sting(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(D_80137E08 == &sound_command && sound_command == 0x12345678 && D_80141F50[2] == (u8*)commands && D_8013E198[2] == -1);
    for (i = 0; i < COUNT(commands); i++)
        assert(commands[i] == (i == 20 ? voice[0] << 24 : i == 19 ? voice[1] << 24
                                                                  : 0));
    assert((SpuGetKeyStatus(1u << voice[0]) != 0) == !!(active & 1) && (SpuGetKeyStatus(1u << voice[1]) != 0) == !!(active & 2));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "robot_bee_sting_states", 0, 0, COUNT(robot_bee_sting_states_cases), test_robot_bee_sting_states },
    { "robot_bee_arc_default", robot_bee_arc_default_cases, robot_bee_arc_default_cases_expected, COUNT(robot_bee_arc_default_cases), 0 },
    { "robot_bee_bob_player_distance", NULL, robot_bee_bob_player_distance_cases_expected, COUNT(robot_bee_bob_player_distance_cases_expected), bob_case },
    { "func_80045940", 0, 0, 1, test_func_80045940 },
    { "compass", 0, 0, 32, test_compass },
    { "ratio_boundaries", 0, 0, COUNT(boundaries) * 4, test_boundaries },
    { "fractional_axis", 0, 0, COUNT(fractions) * 4, test_fractional_axis },
    { "wait", 0, 0, 3, test_wait },
    { "countdown_sequence", 0, 0, 32 * 2, test_countdown_sequence },
    { "SDK_key_on_status_14_then_13_fallback_with_real_sting_exit_animation", NULL, NULL, 16, sting },
#ifdef MMX4_PC
    { "wait_active_sound", 0, 0, 8, test_wait_active_sound },
    { "circle_active_sound", 0, 0, 8, test_circle_active_sound },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(robot_bee_sting_states_cases) + COUNT(robot_bee_arc_default_cases) + COUNT(robot_bee_bob_player_distance_cases_expected) + 1 + 32 + COUNT(boundaries) * 4 + COUNT(fractions) * 4 + 3 + 32 * 2 + 16
#ifdef MMX4_PC
    + 8
    + 8
#endif
    ;
