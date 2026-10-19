#include "test_runtime.h"
#include "main/effects/effect_43_sigma_collapse.h"
#include "support/state_cases.h"

static const u32 sigma_collapse_init_expected[] = { 2u };
static u32 test_sigma_collapse_init(u32 row)
{
    u32 observed_values[1];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = -1;
    sigma_collapse_init(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, sigma_collapse_init_expected, 1);
}

#define se state_room.effect
#define RUMBLE(step, a, b) (state_reset(0, 0, 0), se.active = 1, se.state = 2, se.unk5 = step, se.ext.effect_43.unk14 = a, se.ext.effect_43.unk16 = b, sigma_collapse_update(&se))
static void sc_rumble_start(void)
{
    RUMBLE(0, 5, 5);
}
static void sc_rumble(void) { RUMBLE(1, 5, 5); }
static void sc_rumble_shake(void) { RUMBLE(1, 1, 5); }
static void sc_rumble_crash(void) { RUMBLE(1, 5, 1); }

static void (*const sigma_collapse_states_cases[])(void) = {
    sc_rumble_start,
    sc_rumble,
    sc_rumble_shake,
    sc_rumble_crash,
};
static const u32 sigma_collapse_states_expected[] = { 0x102u, 0x10001u, 0u, 0x102u, 0x40004u, 0u, 0x100102u, 0x4000Au, 0x1020Au, 0x102u, 0x280004u, 0u };

static u32 test_sigma_collapse_states(u32 row)
{
    u32 seen[3];
    sigma_collapse_states_cases[row]();
    seen[0] = (u8)se.state | (u8)se.unk5 << 8 | (u32)background_objects[0].unk34 << 16;
    seen[1] = se.ext.effect_43.unk14 | (u32)se.ext.effect_43.unk16 << 16;
    seen[2] = (u8)background_objects[0].unk36 | (u8)background_objects[0].unk45 << 8 | (u32)(u8)background_objects[0].unk3C << 16;
    return c_test_observe(0, row, seen, &sigma_collapse_states_expected[row * 3], 3);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_collapse_states", 0, 0, COUNT(sigma_collapse_states_cases), test_sigma_collapse_states },
    { "sigma_collapse_init", 0, 0, 1, test_sigma_collapse_init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_collapse_states_cases) + 1;
