#include "test_runtime.h"
#include "main/charge_glow.h"
#include "main/player_weapon.h"

struct ChargeGlowRow {
    s8 state, unk2;
    PlayerChargeState charge[2];
};
static const struct ChargeGlowRow charge_glow_rows[] = {
    { 0, 0, { PLAYER_CHARGE_FULL, PLAYER_CHARGE_NONE } },
    { 0, 1, { PLAYER_CHARGE_NONE, PLAYER_CHARGE_PARTIAL } },
    { 0, 0, { PLAYER_CHARGE_PARTIAL, PLAYER_CHARGE_PARTIAL } },
    { 1, 0, { PLAYER_CHARGE_NONE, PLAYER_CHARGE_NONE } },
    { 1, 0, { PLAYER_CHARGE_FULL, PLAYER_CHARGE_NONE } },
    { 1, 0, { PLAYER_CHARGE_NONE, PLAYER_CHARGE_FULL } },
};
static const u32 charge_glow_expected[] = {
    0xFF080101u,
    0x00000103u,
    0xFF090101u,
    0x00000206u,
    0x00000000u,
    0x00000004u,
    0x00000000u,
    0x00000004u,
    0x00000101u,
    0x00000003u,
    0x00000101u,
    0x00000003u,
};
static struct BazObj charge_glow;
static u32 charge_glow_steps[3] = { C_TEST_STEP(0x04), C_TEST_STEP(0x03), C_TEST_STEP(0x06) };
static u32* charge_glow_table[10];
static u32 test_charge_glow(u32 row)
{
    const struct ChargeGlowRow* in = &charge_glow_rows[row];
    u32 seen[2], i;
    memset(&charge_glow, 0, sizeof(charge_glow));
    for (i = 0; i < COUNT(charge_glow_table); i++)
        charge_glow_table[i] = &charge_glow_steps[0];
    charge_glow_table[8] = &charge_glow_steps[1];
    charge_glow_table[9] = &charge_glow_steps[2];
    g_Player.x_pos.val = 0x00512345;
    g_Player.y_pos.val = 0x00634567;
    g_Player.charge_state[0] = in->charge[0];
    g_Player.charge_state[1] = in->charge[1];
    charge_glow.state = in->state;
    charge_glow.on_screen = in->state;
    charge_glow.unk2 = in->unk2;
    charge_glow.animation_table = charge_glow_table;
    charge_glow.animation_cursor = &charge_glow_steps[0];
    charge_glow.animation_step.packed = charge_glow_steps[0];
    func_800AE6B4(&charge_glow);
    assert(charge_glow.x_pos.val == 0x00512345 && charge_glow.y_pos.val == 0x00634567);
    seen[0] = (u8)charge_glow.state | (u8)charge_glow.on_screen << 8 | (u32)charge_glow.unk17 << 16 | (u32)charge_glow.previous_animation_index << 24;
    seen[1] = (u8)charge_glow.animation_step.fields.duration | (u32)(charge_glow.animation_cursor - charge_glow_steps) << 8;
    return c_test_observe(0, row, seen, &charge_glow_expected[row * 2], 2);
}

const struct CTestGroup c_test_groups[] = {
    { "buster_charge_glow_states", 0, 0, COUNT(charge_glow_rows), test_charge_glow },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(charge_glow_rows);
