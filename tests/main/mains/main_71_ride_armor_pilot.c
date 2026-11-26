#include "test_runtime.h"
#ifndef VERSION_DEMO
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
    so.unk15 = PLAYER_FACING_RIGHT;
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
    state_terrain(0);
    func_80089C7C(&so);
    state_extra = so.ext.main_71.unk8A | so.ext.main_71.unk88 << 8;
}
static void rp_charge_held(void)
{
    PILOT(6, 1);
    so.ext.main_71.unk8D = 2;
    func_8008A778(&so);
}

void ride_armor_pilot_despawn(struct MainObj*);
#define RX() (state_extra = so.ext.main_71.unk8A | so.ext.main_71.unk86 << 8 | so.ext.main_71.unk87 << 16 | (u32)so.ext.main_71.unk88 << 24)
#define MAINX() (state_extra = so.state | so.ext.main_71.unk8B << 8)
static void rp_init(void) { PILOT(0, 0), ride_armor_pilot_update(&so), MAINX(); }
static void rp_main(s16 x, u8 hp, u8 hit, u8 timer)
{
    PILOT(1, 0);
    state_terrain(0);
    memset(weapon_objects, 0, sizeof(weapon_objects));
    SPIKE_IMMUNE_SET(g_Player, 1);
    so.state = 1;
    so.ext.main_71.unk8B = timer;
    so.x_pos.i.hi = x;
    so.hp = hp;
    if (hit) {
        so.active = 0x41;
        state_hit(&so, 0, 0, 1);
    }
    cur_random = 1;
    func_8008AC40(&so);
    MAINX();
}
static void rp_main_defeated(void) { rp_main(0x80, 1, 1, 2); }
static void rp_main_hit(void) { rp_main(0x80, 5, 1, 2); }
static void rp_main_off_screen(void) { rp_main(0x200, 5, 0, 0); }
#define SENSE(air, flags, attr) (PILOT(2, 0), g_Player.x_pos.i.hi = 0x200, so.air_state = air, so.ext.main_71.unk8D = flags, state_terrain(attr), func_80089C7C(&so), RX())
static void rp_sense_airborne(void) { SENSE(1, 0, 0); }
static void rp_sense_guarding(void) { SENSE(0, 8, 0); }
static void rp_sense_floor(void) { SENSE(0, 0, 0x38); }
#define STEP(step, sub, run) (PILOT(step, sub), run(&so), RX())
static void rp_walk_start_blocked(void) { PILOT(3, 0), so.ext.main_71.unk8A = 1, so.collision_flags = 8, so.ext.main_71.unk86 = 1, func_8008A180(&so), RX(); }
static void rp_walk_punch(void) { PILOT(3, 1), so.ext.main_71.unk8A = 1, so.collision_flags = 8, so.ext.main_71.unk87 = 1, func_8008A180(&so), RX(); }
static void rp_walk_step(void) { PILOT(3, 1), so.ext.main_71.unk8A = 2, so.collision_flags = 8, so.animation_step.fields.event = 1, func_8008A180(&so), RX(); }
static void rp_walk_partner_stop(void) { PILOT(3, 1), so.unk2 = 1, so.collision_flags = 8, g_Player.x_pos.i.hi = 0x100, func_8008A180(&so), RX(); }
static void rp_walk_partner_stop_left(void) { PILOT(3, 1), so.unk2 = 1, so.unk15 = PLAYER_FACING_RIGHT, so.collision_flags = 8, func_8008A180(&so), RX(); }
static void rp_air_punch_start(void) { STEP(10, 0, func_8008A60C); }
static void rp_air_punch_hit(void) { PILOT(10, 1), so.animation_step.fields.event = 1, so.animation_step.fields.relative_step = 1, func_8008A60C(&so), RX(); }
static void rp_air_punch_recover(void) { PILOT(10, 1), so.animation_step.fields.event = 2, so.animation_step.fields.relative_step = 1, func_8008A60C(&so), RX(); }
static void rp_dash_start_blocked(void) { PILOT(6, 0), so.active = 0x41, so.ext.main_71.unk8A = 1, so.ext.main_71.unk86 = 1, func_8008A778(&so), RX(); }
static void rp_dash_start_left_blocked(void) { PILOT(6, 0), so.ext.main_71.unk8A = 2, so.ext.main_71.unk86 = 1, func_8008A778(&so), RX(); }
static void rp_dash_punch(void) { PILOT(6, 1), so.ext.main_71.unk87 = 1, func_8008A778(&so), RX(); }
static void rp_dash_end_start(void) { STEP(7, 0, func_8008A8E4); }
static void rp_guard_start(void) { PILOT(11, 0), so.collision_flags = 8, func_8008A9F4(&so), RX(); }
static void rp_guard_push(void) { PILOT(11, 1), so.collision_flags = 8, so.animation_step.fields.event = 1, so.ext.main_71.unk8E = 5, so.x_speed = 0x10000, func_8008A9F4(&so), RX(); }
#define IDLEX() (state_extra = so.ext.main_71.unk8C | so.ext.main_71.unk86 << 8 | so.ext.main_71.unk87 << 16 | (u32)so.ext.main_71.unk8A << 24)
static void rp_idle_start(void) { PILOT(2, 0), so.collision_flags = 8, cur_random = 1, func_8008A064(&so), IDLEX(); }
static void rp_idle_airborne(void) { PILOT(2, 1), func_8008A064(&so), IDLEX(); }
static void rp_idle_turn(void) { PILOT(2, 1), so.collision_flags = 8, so.ext.main_71.unk8A = 2, func_8008A064(&so), IDLEX(); }
static void rp_idle_blocked(void) { PILOT(2, 1), so.collision_flags = 8, so.ext.main_71.unk86 = 1, func_8008A064(&so), IDLEX(); }
static void rp_idle_punch(void) { PILOT(2, 1), so.collision_flags = 8, so.ext.main_71.unk87 = 1, func_8008A064(&so), IDLEX(); }
static void rp_idle_wait(void) { PILOT(2, 1), so.collision_flags = 8, func_8008A064(&so), IDLEX(); }
static void rp_idle_held(void) { PILOT(2, 1), so.collision_flags = 8, so.ext.main_71.unk8D = 2, func_8008A064(&so), IDLEX(); }
static void rp_jump_start(void) { PILOT(8, 0), so.active = 0x41, func_8008A3B0(&so), RX(); }
static void rp_jump_punch(void) { PILOT(8, 1), so.ext.main_71.unk87 = 1, func_8008A3B0(&so), RX(); }
static void rp_jump_held(void) { PILOT(8, 1), so.ext.main_71.unk8D = 2, func_8008A3B0(&so), RX(); }
static void rp_jump_ceiling(void) { PILOT(8, 1), so.collision_flags = 4, func_8008A3B0(&so), RX(); }
static void rp_jump_falling(void) { PILOT(8, 1), so.y_speed = -1, func_8008A3B0(&so), RX(); }
static void rp_land_start(void) { STEP(5, 0, func_8008A4D8); }
#define LAND(flags, setup) (PILOT(5, 1), so.animation_step.fields.relative_step = 1, so.collision_flags = flags, setup, func_8008A4D8(&so), RX())
static void rp_land_held(void) { LAND(8, so.ext.main_71.unk8D = 2); }
static void rp_land_slip(void) { LAND(0, 0); }
static void rp_land_punch(void) { LAND(8, so.ext.main_71.unk87 = 1); }
static void rp_land_walk(void) { LAND(8, so.ext.main_71.unk8A = 1); }
static void rp_land_stand(void) { LAND(8, 0); }
static void rp_punch_start(void) { STEP(9, 0, ride_armor_pilot_punch); }
#define PUNCH(ev) (PILOT(9, 1), so.animation_step.fields.relative_step = 1, so.animation_step.fields.event = ev, ride_armor_pilot_punch(&so), RX())
static void rp_punch_hit(void) { PUNCH(1); }
static void rp_punch_recover(void) { PUNCH(2); }
static void rp_punch_wind(void) { PUNCH(0); }
static void rp_despawn(void) { PILOT(0, 0), so.state = 2, so.active = 0x41, so.unk42 = 0x8001, ride_armor_pilot_update(&so), MAINX(); }
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
    rp_init,
    rp_main_defeated,
    rp_main_hit,
    rp_main_off_screen,
    rp_sense_airborne,
    rp_sense_guarding,
    rp_sense_floor,
    rp_walk_start_blocked,
    rp_walk_punch,
    rp_walk_step,
    rp_walk_partner_stop,
    rp_walk_partner_stop_left,
    rp_air_punch_start,
    rp_air_punch_hit,
    rp_air_punch_recover,
    rp_dash_start_blocked,
    rp_dash_start_left_blocked,
    rp_dash_punch,
    rp_dash_end_start,
    rp_guard_start,
    rp_guard_push,
    rp_idle_start,
    rp_idle_airborne,
    rp_idle_turn,
    rp_idle_blocked,
    rp_idle_punch,
    rp_idle_wait,
    rp_idle_held,
    rp_jump_start,
    rp_jump_punch,
    rp_jump_held,
    rp_jump_ceiling,
    rp_jump_falling,
    rp_land_start,
    rp_land_held,
    rp_land_slip,
    rp_land_punch,
    rp_land_walk,
    rp_land_stand,
    rp_punch_start,
    rp_punch_hit,
    rp_punch_recover,
    rp_punch_wind,
    rp_despawn,
};
static const u32 ride_armor_pilot_states_expected[] = { 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 3u, 0u, 0x800000u, 0xFFFEA000u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0x16000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 7u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xBu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000002u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 6u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x106u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0x180003u, 1u, 0u,
    0u, 0u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 3u, 0x102u, 0x41002100u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 0x80000000u, 0x40003u, 0x101u, 0x41002100u,
    0u, 0u, 0x2000000u, 0u, 0u, 0u, 0u, 0x50003u, 2u, 0u,
    0x1000002u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x1000001u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x1000001u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x1000001u, 0u,
    8u, 0u, 0x800000u, 0u, 0u, 0u, 0x4001u, 3u, 0x101u, 0u,
    9u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0x10001u, 0u,
    0x103u, 0u, 0x7EA000u, 0xFFFEA000u, 0u, 0u, 0u, 0u, 2u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 3u, 0u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 3u, 0u, 0u,
    0x108u, 0u, 0x800000u, 0u, 0u, 0u, 0xAu, 0u, 0u, 0u,
    0x10Au, 0u, 0x800000u, 0u, 0u, 0u, 0u, 2u, 0u, 0u,
    0x10Au, 0u, 0x800000u, 0u, 0u, 0u, 0u, 2u, 0u, 0u,
    8u, 0u, 0x800000u, 0x42000u, 0u, 0u, 0x4005u, 0u, 0x101u, 0x41004100u,
    8u, 0u, 0x800000u, 0xFFFBE000u, 0u, 0u, 5u, 0u, 0x102u, 0u,
    0xBu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 6u, 3u, 0u, 0u,
    0x10Bu, 0u, 0x800000u, 0u, 0u, 0u, 8u, 2u, 0u, 0u,
    0x10Bu, 0u, 0x810000u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x102u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    3u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x2000000u, 0u,
    8u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x100u, 0u,
    9u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0u,
    0x102u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x102u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0x1000108u, 0u, 0x800000u, 0u, 0x53E00u, 0x420000u, 2u, 2u, 0u, 0x41004100u,
    0xAu, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0u,
    0x108u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    4u, 0u, 0x800000u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 4u, 3u, 0u, 0u,
    0x105u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    9u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0x10000u, 0u,
    0x105u, 0u, 0x816000u, 0x16000u, 0u, 0u, 0x4000u, 0u, 1u, 0u,
    0x105u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    2u, 0u, 0x800000u, 0u, 0u, 0u, 9u, 3u, 0u, 0u,
    0x109u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 2u, 0u, 0u,
    0x109u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 2u, 0u, 0u,
    0x109u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0x800000u, 0u, 0u, 0u, 0x1u << 16, 0u, 0u, 0u,
};

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
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x12345;
    obj.y_speed = speeds[speed];
    obj.x_accel = 0;
    obj.gravity = 0x4200;
    obj.air_state = 1;
    obj.unk16 = VISUAL_SATURN_LAYER(5);
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
    assert(obj.animation_step.packed == C_TEST_STEP(0x0A000006));
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
                expected.unk15 = script == 1 ? PLAYER_FACING_RIGHT : 0;
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
static const u32 words[] = { C_TEST_STEP(0x01010006), C_TEST_STEP(0x0D010004), C_TEST_STEP(0x11010002) };
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
    obj.unk15 = PLAYER_FACING_RIGHT;
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
                expected.unk15 = script == 1 ? PLAYER_FACING_RIGHT : 0;
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
    C_TEST_STEP(0x09010001), C_TEST_STEP(0x22010001), C_TEST_STEP(0x23010001), C_TEST_STEP(0x24010001), C_TEST_STEP(0x25010001), C_TEST_STEP(0x26010001), C_TEST_STEP(0x27010001), C_TEST_STEP(0x28010001),
    C_TEST_STEP(0x29010001), C_TEST_STEP(0x28010001), C_TEST_STEP(0x29010001), C_TEST_STEP(0x28010001), C_TEST_STEP(0x29010006), C_TEST_STEP(0x2A000006)
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
    obj.unk15 = PLAYER_FACING_RIGHT;
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

static const struct {
    s16 player_x;
    u8 partner, collision, facing, solid;
    u32 expected;
} sense_cases[] = {
    { 0x80, 0, 0, 0, 0, 0x100u },
    { 0x200, 0, 1, 0, 0, 0x01010001u },
    { 0x20, 0, 2, 1, 1, 0u },
    { 0x200, 0, 0, 0, 0, 0x01010001u },
};
static u8 sense_tilemap[16];
static u16 sense_pixels[512];
static u32 sense_attrs[2];
static u32 sense(u32 row)
{
    struct MainObj obj;
    u32 observed, i;
    memset(&obj, 0, sizeof(obj));
    memset(sense_tilemap, sense_cases[row].solid, sizeof(sense_tilemap));
    for (i = 0; i < COUNT(sense_pixels); i++)
        sense_pixels[i] = sense_cases[row].solid;
    sense_attrs[0] = 0;
    sense_attrs[1] = C_TEST_PSX_WORD(0x24);
    SP_BG_TILEMAP = sense_tilemap;
    TEST_BG_TILE_PIXELS = (u8*)sense_pixels;
    TEST_BG_TILE_ATTRS = (u8*)sense_attrs;
    layout_size = 1;
    layout_width = 1;
    obj.active = 0x41;
    obj.id = 71;
    obj.unk5 = 2;
    obj.unk2 = sense_cases[row].partner;
    obj.unk15 = sense_cases[row].facing ? PLAYER_FACING_RIGHT : 0;
    obj.collision_flags = sense_cases[row].collision;
    obj.x_pos.i.hi = 0x80;
    obj.y_pos.i.hi = 0x60;
    obj.terrain_box = &state_hit_box;
    g_Player.x_pos.i.hi = sense_cases[row].player_x;
    func_80089C7C(&obj);
    observed = obj.ext.main_71.unk86 | (u32)obj.ext.main_71.unk87 << 8 | (u32)obj.ext.main_71.unk88 << 16 | (u32)obj.ext.main_71.unk8A << 24;
    return c_test_observe(0, row, &observed, &sense_cases[row].expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "ride_armor_pilot_states", 0, 0, COUNT(ride_armor_pilot_states_cases), test_ride_armor_pilot_states },
    { "func_8008A8E4", 0, 0, 5, test_func_8008A8E4 },
    { "pilot_fall_ground_block_attack_and_speed_edges", NULL, NULL, 60, fall_interrupts },
    { "pilot_walk_dash_and_guard_ground_block_and_timer_edges", NULL, NULL, 117, ground_interrupt },
    { "jump_punch_shipped_frames_and_motion", NULL, NULL, COUNT(words_ride_armor_pilot_jump_punch) * 6, jump_punch },
    { "sense_player_distance_and_way_ahead", NULL, NULL, COUNT(sense_cases), sense },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ride_armor_pilot_states_cases) + 5 + 60 + 117 + COUNT(words_ride_armor_pilot_jump_punch) * 6 + COUNT(sense_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
