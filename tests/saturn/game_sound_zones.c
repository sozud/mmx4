#include "test_runtime.h"

struct Effect10Trigger {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    u8 sound_id;
    u8 pad;
};
void func_800B7EE8(struct EffectObj* arg0);
extern struct Effect10Trigger* sound_zone_lists[2];

static struct Effect10Trigger zones[4] = {
    { 0, 200, 0, 1000, 0x30, 0 },
    { 100, 300, 0, 1000, 0x31, 0 },
    { 250, 400, 0, 1000, 0x32, 0 },
    { 450, 600, 0, 1000, 0x33, 0 },
};
static struct EffectObj zone_effect;

static void run(u8 substage, s16 x, u8 active)
{
    c_test_zero_words((u32*)&zone_effect, sizeof(zone_effect) / 4);
    zone_effect.active = 1;
    zone_effect.state = 1;
    zone_effect.ext.unk_effect.unk14 = active;
    engine_obj.substage = substage;
    sound_zone_lists[substage] = zones;
    g_Player.x_pos.val = x << 16;
    g_Player.y_pos.val = 500 << 16;
    func_800B7EE8(&zone_effect);
}

static void init(void) { run(0, 50, 0); zone_effect.state = 0; zone_effect.ext.unk_effect.unk14 = 9; func_800B7EE8(&zone_effect); }
static void s0_leave_zone3(void) { run(0, 700, 8); }
static void s1_enter_silent(void) { run(1, 50, 0); }
static void s1_leave_pair01(void) { run(1, 700, 3); }

static void (*const zone_cases[])(void) = {
    init, s0_leave_zone3,
    s1_enter_silent, s1_leave_pair01,
};

#define WORDS 2
static const u32 zone_expected[][WORDS] = {
#include "game_sound_zones_expected.inc"
};

static u32 zone_run(u32 row)
{
    u32 observed[WORDS];
    zone_cases[row]();
    observed[0] = zone_effect.ext.unk_effect.unk14 | (u32)(u8)zone_effect.state << 8;
    observed[1] = (u32)(u8)engine_obj.substage;
    return c_test_observe(0, row, observed, zone_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_sound_zones", 0, 0, COUNT(zone_cases), zone_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zone_cases);
