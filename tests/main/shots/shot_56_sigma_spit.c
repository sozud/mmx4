#include "test_runtime.h"
#include "main/shots/shot_56_sigma_spit.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern union AnimationStep* ice_block_animations[9];
extern void* sigma_final_animations[39];
extern s8* sigma_spit_boxes[8];

#include "support/state_cases.h"

static struct WeaponObj spit_owner;
#define ss state_room.shot
#define SPIT(st, step) (state_reset(step, 0, 0), memset(&spit_owner, 0, sizeof(spit_owner)), spit_owner.animation_table = (void*)state_table, spit_owner.unk42 = 0x8123, spit_owner.x_pos.i.hi = 0x100, spit_owner.y_pos.i.hi = 0x80, ss.state = st, ss.unk7C = &spit_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
static void sp_init(u8 kind, u16 seed)
{
    SPIT(0, 0);
    ss.unk2 = kind;
    cur_random = seed;
    sigma_spit_update(&ss);
    state_extra = (u16)ss.timer | (u32)ss.animation_step.fields.frame_index << 16;
}
static void sp_init_a(void) { sp_init(0, 1); }
static void sp_init_b(void) { sp_init(0, 2); }
static void sp_init_c(void) { sp_init(0, 3); }
static void sp_init_d(void) { sp_init(0, 4); }
static void sp_init_e(void) { sp_init(0, 5); }
static void sp_init_f(void) { sp_init(0, 6); }
static void sp_init_g(void) { sp_init(0, 7); }
static void sp_init_falling(void) { sp_init(1, 1); }
static void sp_init_falling_b(void) { sp_init(1, 9); }
static void sp_owner_done(void)
{
    SPIT(1, 2);
    spit_owner.unk94 = 1;
    sigma_spit_update(&ss);
}
static void sp_return(void)
{
    SPIT(1, 2);
    cur_random = 1;
    sigma_spit_update(&ss);
    state_extra = ss.unk8C.byte;
}
static void sp_return_arrive(void)
{
    SPIT(1, 2);
    ss.x_pos.i.hi = 0x110;
    ss.y_pos.i.hi = 0x90;
    cur_random = 2;
    sigma_spit_update(&ss);
}
static void sp_fall(void)
{
    SPIT(1, 3);
    ss.y_vel.val = -0x10000;
    sigma_spit_update(&ss);
}
static void sp_fall_away(void)
{
    SPIT(1, 3);
    ss.y_pos.i.hi = 0x800;
    sigma_spit_update(&ss);
}
static void sp_shot(void)
{
    SPIT(1, 3);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    sigma_spit_update(&ss);
}
static void sp_despawn(void)
{
    SPIT(2, 0);
    ss.active = 1;
    sigma_spit_update(&ss);
}

static void (*const sigma_spit_states_cases[])(void) = {
    sp_init_a,
    sp_init_b,
    sp_init_c,
    sp_init_d,
    sp_init_e,
    sp_init_f,
    sp_init_g,
    sp_init_falling,
    sp_init_falling_b,
    sp_owner_done,
    sp_return,
    sp_return_arrive,
    sp_fall,
    sp_fall_away,
    sp_shot,
    sp_despawn,
};
static const u32 sigma_spit_states_expected[] = { 0x201u, 0xFF000000u, 0x1600000u, 0x10000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 0x201u, 0xFF000000u, 0x20000u, 0x1100000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 0x201u, 0xFF000000u, 0xFFE00000u, 0x30000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 0x201u, 0xFF000000u, 0x40000u, 0xFFE00000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 0x201u, 0xFF000000u, 0x1600000u, 0x50000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 0x201u, 0xFF000000u, 0x60000u, 0x1100000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 0x201u, 0xFF000000u, 0xFFE00000u, 0x70000u, 0u, 0u, 0u, 0x50123u, 0u, 0u, 0x301u, 0xFF000100u, 0x800000u, 0x600000u, 0x76418u, 0x3D3A6u, 0x420000u, 0x50123u, 0x1Eu, 0u, 0x301u, 0xFF000100u, 0x800000u, 0x600000u, 0x6A6D8u, 0x58E3Au, 0x420000u, 0x50123u, 0x1Eu, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x201u, 0u, 0x82C589u, 0x6125E5u, 0x2C589u, 0xFFFEDA1Bu, 0u, 0x50000u, 0x1Eu, 0u, 2u, 0u, 0x10C0000u, 0x900000u, 0xFFFC0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x301u, 0u, 0x800000u, 0x610000u, 0u, 0xFFFF0000u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0x800000u, 0x8000000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0x2100u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_sigma_spit_states(u32 row)
{
    return object_run(sigma_spit_states_cases[row], row, &sigma_spit_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_spit_states", 0, 0, COUNT(sigma_spit_states_cases), test_sigma_spit_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_spit_states_cases);
