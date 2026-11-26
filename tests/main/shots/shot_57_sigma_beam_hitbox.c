#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_57_sigma_beam_hitbox.h"

static struct WeaponObj beam_owner;
#define ss state_room.shot
#define BEAM(st) (state_reset(0, 0, 0), memset(&beam_owner, 0, sizeof(beam_owner)), beam_owner.bg_offset = 1, ss.state = st, ss.unk7C = &beam_owner)
#define RANGE() (state_extra = ss.unk8C.bytes[0] | ss.unk8C.bytes[1] << 8 | (u32)(u8)ss.bg_offset << 16)
static void sb_init_a(void)
{
    BEAM(0);
    sigma_beam_hitbox_update(&ss);
    RANGE();
}
static void sb_init_b(void)
{
    BEAM(0);
    ss.unk2 = 3;
    sigma_beam_hitbox_update(&ss);
    RANGE();
}
static void sb_pulse_wait(void)
{
    BEAM(1);
    sigma_beam_hitbox_update(&ss);
}
static void sb_pulse(void)
{
    BEAM(1);
    ss.unk8C.bytes[1] = 2;
    beam_owner.unk95 = 1;
    g_Player.x_pos.i.hi = 0x1000;
    sigma_beam_hitbox_update(&ss);
}
static void sb_active(void)
{
    BEAM(2);
    ss.unk8C.bytes[1] = 1;
    beam_owner.unk95 = 1;
    g_Player.x_pos.i.hi = 0x1000;
    sigma_beam_hitbox_update(&ss);
}
static void sb_active_end(void)
{
    BEAM(2);
    sigma_beam_hitbox_update(&ss);
}
static void sb_owner_done(void)
{
    BEAM(1);
    ss.active = 1;
    beam_owner.unk94 = 1;
    sigma_beam_hitbox_update(&ss);
}

static void (*const sigma_beam_hitbox_states_cases[])(void) = {
    sb_init_a,
    sb_init_b,
    sb_pulse_wait,
    sb_pulse,
    sb_active,
    sb_active_end,
    sb_owner_done,
};
static const u32 sigma_beam_hitbox_states_expected[] = { 1u, 0u, 0x4AE0000u, 0x29C0000u, 0u, 0u, 0u, 0x50000u, 0x10416u, 0u, 1u, 0x300u, 0x49B0000u, 0x2310000u, 0u, 0u, 0u, 0x50000u, 0x10600u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_sigma_beam_hitbox_states(u32 row)
{
    return object_run(sigma_beam_hitbox_states_cases[row], row, &sigma_beam_hitbox_states_expected[row * 10]);
}

void func_800AE450(struct ShotObj* self);
extern u16 sigma_beam_hitbox_offsets[6][2];
extern u8 sigma_beam_hitbox_ranges[6][2];
static u32 init_last_segment(u32 row)
{
    BEAM(0);
    ss.unk2 = 5;
    func_800AE450(&ss);
    assert(ss.state == 1 && ss.unk5C == 1 && ss.unk60 == 9 && ss.bg_offset == 1);
    assert(ss.unk8C.bytes[0] == sigma_beam_hitbox_ranges[5][0] && ss.unk8C.bytes[1] == sigma_beam_hitbox_ranges[5][1]);
    assert((u16)ss.x_pos.i.hi == sigma_beam_hitbox_offsets[5][0] && (u16)ss.y_pos.i.hi == sigma_beam_hitbox_offsets[5][1]);
    return ss.unk60;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_beam_hitbox_states", 0, 0, COUNT(sigma_beam_hitbox_states_cases), test_sigma_beam_hitbox_states },
    { "init_last_segment", 0, 0, 1, init_last_segment },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_beam_hitbox_states_cases) + 1;
