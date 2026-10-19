#include "test_runtime.h"
#include "main/mains/main_71_ride_armor_pilot.h"
#include "support/state_cases.h"
#include "main/55C4.h"
void ride_armor_pilot_despawn_idle(void);
void ride_armor_pilot_despawn_idle2(void);
void ride_armor_pilot_check_dash(struct MainObj*);
void func_80089C7C(struct MainObj*);
void ride_armor_pilot_set_walk_speed(struct MainObj*);

static const u32 inputs_0[5][6] = {
    { -1, 2, 0, 0, 0, 0 },
    { -1, 0, -1, 255, 0, 0 },
    { -1, 0, -1, 0, 255, 0 },
    { -1, 0, -1, 0, 0, 0 },
    { -1, 0, -1, 0, 0, 255 },
};
struct func_8008A8E4_case {
    u32 expected[4];
};
static const struct func_8008A8E4_case func_8008A8E4_cases[] = {
    { { 0u, 0u, 2u, 0xFFFFFFFFu } },
    { { 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 0u, 0xFFFFFFFFu } },
    { { 0u, 0u, 0u, 0u } },
};
static u32 test_func_8008A8E4(u32 row)
{
    const struct func_8008A8E4_case* c = &func_8008A8E4_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk6 = inputs_0[row][0];
    obj.ext.main_71.unk8D = inputs_0[row][1];
    obj.animation_step.fields.relative_step = inputs_0[row][2];
    obj.ext.main_71.unk86 = inputs_0[row][3];
    obj.ext.main_71.unk87 = inputs_0[row][4];
    obj.ext.main_71.unk8A = inputs_0[row][5];
    func_8008A8E4(&obj);
    observed_values[0] = (u32)obj.contact_damage;
    observed_values[1] = (u32)obj.ext.main_71.unk84;
    observed_values[2] = (u32)obj.ext.main_71.unk8D;
    observed_values[3] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#define PILOT(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.terrain_box = &state_hit_box)
#define DASH(step, ready, flags, air, blocked) (PILOT(step, 0), so.ext.main_71.unk88 = ready, so.ext.main_71.unk8D = flags, so.air_state = air, so.ext.main_71.unk86 = blocked, ride_armor_pilot_check_dash(&so))
static void rp_reset(void)
{
    PILOT(5, 1);
    so.ext.main_71.unk88 = 1;
    ride_armor_pilot_reset(&so);
}
static void rp_walk_left(void)
{
    PILOT(3, 0);
    ride_armor_pilot_set_walk_speed(&so);
}
static void rp_walk_right(void)
{
    PILOT(3, 0);
    so.unk15 = 0x40;
    ride_armor_pilot_set_walk_speed(&so);
}
static void rp_dash_idle(void) { DASH(1, 1, 0, 0, 0); }
static void rp_dash_busy(void) { DASH(6, 1, 0, 0, 0); }
static void rp_dash_landing(void) { DASH(7, 1, 0, 0, 0); }
static void rp_dash_punching(void) { DASH(0xB, 1, 0, 0, 0); }
static void rp_dash_not_ready(void) { DASH(2, 0, 0, 0, 0); }
static void rp_dash_locked(void) { DASH(2, 1, 8, 0, 0); }
static void rp_dash_airborne(void) { DASH(2, 1, 0, 1, 0); }
static void rp_dash_blocked(void) { DASH(2, 1, 0, 0, 1); }
static void rp_dash(void) { DASH(2, 1, 0, 0, 0); }
static void rp_idles(void)
{
    PILOT(2, 0);
    ride_armor_pilot_despawn_idle();
    ride_armor_pilot_despawn_idle2();
}
static void rp_sense_idle(void)
{
    PILOT(1, 0);
    func_80089C7C(&so);
    state_extra = so.ext.main_71.unk87;
}
static void rp_sense_partner_far(void)
{
    PILOT(2, 0);
    so.unk2 = 1;
    g_Player.x_pos.i.hi = 0x200;
    func_80089C7C(&so);
    state_extra = so.ext.main_71.unk8A | so.ext.main_71.unk88 << 8;
}
static void rp_charge_held(void)
{
    PILOT(6, 1);
    so.ext.main_71.unk8D = 2;
    func_8008A778(&so);
}

static void (*const ride_armor_pilot_states_cases[])(void) = {
    rp_reset,
    rp_walk_left,
    rp_walk_right,
    rp_dash_idle,
    rp_dash_busy,
    rp_dash_landing,
    rp_dash_punching,
    rp_dash_not_ready,
    rp_dash_locked,
    rp_dash_airborne,
    rp_dash_blocked,
    rp_dash,
    rp_idles,
    rp_sense_idle,
    rp_sense_partner_far,
    rp_charge_held,
};
static const u32 ride_armor_pilot_states_expected[] = { 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 3u, 0u, 0x800000u, 0xFFFEA000u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0x16000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 7u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xBu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000002u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x106u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_ride_armor_pilot_states(u32 row)
{
    return state_run(ride_armor_pilot_states_cases[row], row, &ride_armor_pilot_states_expected[row * 10]);
}

extern void* ride_armor_pilot_animations[];
extern u8 ride_armor_pilot_hurt_box[], ride_armor_pilot_attack_box[];
static const s32 speeds[] = { -0x60000, -0x5E000, 0x10000 };
static u32 fall_interrupts(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 start = row % 2, facing = row / 2 % 2, path = row / 4, ground = path == 0, blocked = path == 1, punch = path == 2;
    u32 kind = path >= 3 && path <= 5 ? path - 2 : 0, script = path >= 6 ? (path - 6) % 3 : 0, speed = path >= 6 ? (path - 6) / 3 : 0;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = kind & 1 ? 0x48 : 71;
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk6 = !start;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x12345;
    obj.y_speed = speeds[speed];
    obj.x_accel = 0;
    obj.gravity = 0x4200;
    obj.air_state = 1;
    obj.unk16 = 5;
    obj.contact_damage = 5;
    obj.hurt_box = ride_armor_pilot_hurt_box;
    obj.attack_box = ride_armor_pilot_attack_box;
    obj.collision_flags = ground ? 8 : 0;
    obj.ext.main_71.unk8A = script;
    obj.ext.main_71.unk84 = 0x160;
    obj.ext.main_71.unk8D = blocked ? 2 : 0;
    obj.ext.main_71.unk87 = punch;
    obj.ext.main_71.unk86 = kind >> 1;
    obj.animation_table = (const u8* const*)ride_armor_pilot_animations;
    set_animation(&obj, 3);
    assert(obj.animation_step.packed == 0x0A000006);
    expected = obj;
    if (start) {
        expected.unk6 = 1;
        expected.x_speed = expected.y_speed = 0;
    }
    if (ground) {
        expected.unk5 = 5;
        expected.unk6 = 0;
    } else if (!blocked) {
        if (punch) {
            expected.unk5 = 10;
            expected.unk6 = 0;
        } else if (kind == 3) {
            expected.unk5 = 12;
            expected.unk6 = 0;
        } else {
            expected.x_speed = script == 0 ? 0 : script == 1 ? 0x16000
                                                             : -0x16000;
            if (script)
                expected.unk15 = script == 1 ? 0x40 : 0;
            if (expected.y_speed < -0x5E000)
                expected.y_speed = -0x5E000;
            expected.x_pos.val += expected.x_speed;
            expected.y_pos.val -= expected.y_speed;
            expected.y_speed -= 0x4200;
        }
    }
    SP_CUR_MAIN_OBJ = &obj;
    func_8008AAF4(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

extern void* ride_armor_pilot_animations[];
extern u8 ride_armor_pilot_hurt_box[], ride_armor_pilot_attack_box[];
extern struct Unk_unk68 ride_armor_pilot_guard_box;
static const u8 animations[] = { 1, 5, 8 };
static const u32 words[] = { 0x01010006, 0x0D010004, 0x11010002 };
static const s8 timers[] = { -1, 0, 1, 30 };
static void (*const callbacks[])(struct MainObj*) = { func_8008A180, func_8008A778, func_8008A9F4 };
static u32 ground_interrupt(u32 row)
{
    struct MainObj obj, expected, *current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct VisualObj visuals_before[32];
    u32 kind = row % 3, ground = row / 3 % 3, blocked = row / 9 % 2, script = row / 18 % 3, timer = row / 54;
    u32 animate = 1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 71;
    obj.state = 1;
    obj.unk5 = kind == 0 ? 3 : kind == 1 ? 6
                                         : 11;
    obj.unk6 = 1;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk15 = 0x40;
    obj.x_speed = kind == 1 ? 0x42000 : 0x16000;
    obj.y_speed = -0x12345;
    obj.x_accel = 0x1234;
    obj.collision_flags = ground == 0 ? 0 : ground == 1 ? 8
                                                        : 9;
    obj.ext.main_71.unk8A = script;
    obj.ext.main_71.unk8E = timers[timer];
    obj.ext.main_71.unk8D = (blocked ? 2 : 0) | (kind == 1 ? 4 : kind == 2 ? 8
                                                                           : 0);
    obj.ext.main_71.unk84 = kind == 1 ? 0x420 : 0x160;
    obj.contact_damage = kind == 2 ? 6 : 5;
    obj.hurt_box = ride_armor_pilot_hurt_box;
    obj.attack_box = kind == 2 ? (void*)&ride_armor_pilot_guard_box : ride_armor_pilot_attack_box;
    obj.animation_table = (const u8* const*)ride_armor_pilot_animations;
    set_animation(&obj, animations[kind]);
    assert(obj.animation_step.packed == words[kind]);
    expected = obj;
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    D_8013E198[2] = -1;
    if (kind == 2)
        expected.ext.main_71.unk8E--;
    if (!ground && !(kind == 1 && blocked)) {
        expected.unk5 = 4;
        expected.unk6 = 0;
        animate = kind == 1;
    } else if (!blocked) {
        if (kind == 0) {
            if (!script) {
                expected.unk5 = 2;
                expected.unk6 = 0;
                expected.ext.main_71.unk88 = expected.ext.main_71.unk86 = expected.ext.main_71.unk87 = 0;
                animate = 0;
            } else {
                expected.unk15 = script == 1 ? 0x40 : 0;
                expected.x_speed = script == 1 ? 0x16000 : -0x16000;
                expected.x_pos.val += expected.x_speed;
            }
        } else if (kind == 1) {
            if (ground == 2) {
                expected.unk5 = 7;
                expected.unk6 = 0;
                animate = 0;
            } else {
                expected.x_pos.val += expected.x_speed;
                expected.ext.main_71.unk8E--;
                if (timers[timer] < 0) {
                    expected.unk5 = 7;
                    expected.unk6 = 0;
                    animate = 0;
                }
            }
        } else if (ground == 2) {
            if (timers[timer] <= 0) {
                expected.unk5 = 7;
                expected.unk6 = 0;
                expected.ext.main_71.unk8D &= ~8;
            } else
                expected.x_pos.val += expected.x_speed;
        }
    }
    if (animate)
        expected.animation_step.fields.duration--;
    SP_CUR_MAIN_OBJ = &obj;
    callbacks[kind](&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_before, sizeof(visuals_before) / 4) == 0);
    assert(D_8013E198[2] == -1);
    return 1;
}

extern void* ride_armor_pilot_animations[];
extern u8 ride_armor_pilot_attack_box[];
static const u32 words_ride_armor_pilot_jump_punch[] = {
    0x09010001, 0x22010001, 0x23010001, 0x24010001, 0x25010001, 0x26010001, 0x27010001, 0x28010001,
    0x29010001, 0x28010001, 0x29010001, 0x28010001, 0x29010006, 0x2A000006
};
static const s32 speeds_ride_armor_pilot_jump_punch[] = { -0x60000, -1, 0, 65536 };
static const u8 flags[] = { 0, 4, 8 };
static u32 jump_punch(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 frame = row % COUNT(words_ride_armor_pilot_jump_punch), collision = row / COUNT(words_ride_armor_pilot_jump_punch) % 3, blocked = row / COUNT(words_ride_armor_pilot_jump_punch) / 3 % 2;
    u32 speed = (frame + collision) % 4, script = (frame + blocked) % 3;
    const union AnimationStep* commands = (const union AnimationStep*)ride_armor_pilot_animations[10];
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 71;
    obj.state = 1;
    obj.unk5 = 9;
    obj.unk6 = 1;
    obj.unk15 = 0x40;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x13579;
    obj.x_accel = 0x1234;
    obj.y_speed = speeds_ride_armor_pilot_jump_punch[speed];
    obj.gravity = 0x4400;
    obj.contact_damage = 5;
    obj.attack_box = ride_armor_pilot_attack_box;
    obj.collision_flags = flags[collision];
    obj.ext.main_71.unk8D = blocked ? 2 : 0;
    obj.ext.main_71.unk8A = script;
    obj.ext.main_71.unk84 = 0x160;
    obj.animation_table = (const u8* const*)ride_armor_pilot_animations;
    set_animation(&obj, 10);
    assert(commands[frame].packed == words_ride_armor_pilot_jump_punch[frame]);
    obj.animation_cursor = (const u8*)&commands[frame];
    obj.animation_step.packed = words_ride_armor_pilot_jump_punch[frame];
    obj.previous_animation_index = 37;
    expected = obj;
    if (collision == 2) {
        expected.unk5 = 5;
        expected.unk6 = 0;
    } else {
        if (!blocked) {
            expected.x_speed = script == 0 ? 0 : script == 1 ? 0x16000
                                                             : -0x16000;
            expected.x_accel = 0;
            if (collision == 1 && expected.y_speed >= 0)
                expected.y_speed = 0;
            if (frame == 13)
                expected.unk5 = expected.y_speed < 0 ? 4 : 8;
            else {
                if (expected.y_speed < -0x5E000)
                    expected.y_speed = -0x5E000;
                expected.x_pos.val += expected.x_speed;
                expected.y_pos.val -= expected.y_speed;
                expected.y_speed -= 0x4400;
            }
        }
        if (frame < 12) {
            expected.animation_cursor = (const u8*)&commands[frame + 1];
            expected.animation_step.packed = words_ride_armor_pilot_jump_punch[frame + 1];
        } else
            expected.animation_step.fields.duration = 5;
    }
    func_8008A60C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "ride_armor_pilot_states", 0, 0, COUNT(ride_armor_pilot_states_cases), test_ride_armor_pilot_states },
    { "func_8008A8E4", 0, 0, 5, test_func_8008A8E4 },
    { "pilot_fall_ground_block_attack_and_speed_edges", NULL, NULL, 60, fall_interrupts },
    { "pilot_walk_dash_and_guard_ground_block_and_timer_edges", NULL, NULL, 117, ground_interrupt },
    { "jump_punch_shipped_frames_and_motion", NULL, NULL, COUNT(words_ride_armor_pilot_jump_punch) * 6, jump_punch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ride_armor_pilot_states_cases) + 5 + 60 + 117 + COUNT(words_ride_armor_pilot_jump_punch) * 6;
