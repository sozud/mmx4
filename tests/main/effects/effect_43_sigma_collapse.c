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

void sigma_collapse_debris_drop(struct EffectObj*);
static u32 debris_drop(u16 timer, u8 music)
{
    struct EffectObj obj;
    u8 music_before = D_80171EA8;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(background_objects, 0, sizeof(background_objects));
    D_8013E198[5] = -1;
    D_80171EA8 = music;
    obj.active = 1;
    obj.ext.effect_9.transition_timer = timer;
    obj.ext.effect_16.saved_background_2A = 0x77;
    cur_random = 0x1234;
    sigma_collapse_debris_drop(&obj);
    D_80171EA8 = music_before;
    return (u8)obj.active | (u32)(u16)obj.ext.effect_9.transition_timer << 8 | (u32)misc_objects[0].id << 24;
}
static u32 scd_waiting(void) { return debris_drop(3, 0); }
static u32 scd_drop(void)
{
    u32 seen = debris_drop(1, 0);
    assert(misc_objects[0].active == 0x41 && misc_objects[0].unk2 < 6 && misc_objects[0].unk40 == 0x77);
    assert(background_objects[0].unk37 == 5);
    return seen;
}
static u32 scd_music_started(void) { return debris_drop(3, 1); }
static const CTestCase sigma_collapse_debris_cases[] = {
    scd_waiting,
    scd_drop,
    scd_music_started,
};
static const u32 sigma_collapse_debris_cases_expected[] = { 0x201u, 0x39000501u, 0x300u };

const struct CTestGroup c_test_groups[] = {
    { "sigma_collapse_states", 0, 0, COUNT(sigma_collapse_states_cases), test_sigma_collapse_states },
    { "sigma_collapse_init", 0, 0, 1, test_sigma_collapse_init },
    { "sigma_collapse_debris", sigma_collapse_debris_cases, sigma_collapse_debris_cases_expected, COUNT(sigma_collapse_debris_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_collapse_states_cases) + 1 + COUNT(sigma_collapse_debris_cases);
