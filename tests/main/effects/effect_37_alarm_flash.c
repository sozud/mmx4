#include "test_runtime.h"
#include "main/effects/effect_37_alarm_flash.h"
#include "main/1AC84.h"

static const u32 alarm_flash_red_expected[] = { 0u, 0u, 0u, 5u, 0u, 0u, 0u, 0u };
static u32 test_alarm_flash_red(u32 row)
{
    u32 observed_values[8];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_FilterAmountB, 0, sizeof(g_FilterAmountB));
    memset(&g_FilterAmountG, 0, sizeof(g_FilterAmountG));
    memset(&g_FilterAmountR, 0, sizeof(g_FilterAmountR));
    memset(&need_palette_load, 0, sizeof(need_palette_load));
    obj.ext.effect_37.unk19 = 1;
    need_palette_load = 0;
    obj.ext.effect_37.unk1E = 0;
    obj.ext.effect_37.unk1F = 0;
    obj.ext.effect_37.unk22 = 255;
    obj.ext.effect_37.action = 0;
    alarm_flash_red(&obj);
    observed_values[0] = (u32)g_FilterAmountB;
    observed_values[1] = (u32)g_FilterAmountG;
    observed_values[2] = (u32)g_FilterAmountR;
    observed_values[3] = (u32)need_palette_load;
    observed_values[4] = (u32)obj.ext.effect_37.action;
    observed_values[5] = (u32)obj.ext.effect_37.finished;
    observed_values[6] = (u32)obj.ext.effect_37.timer;
    observed_values[7] = (u32)obj.ext.effect_37.unk19;
    return c_test_observe(0, row, observed_values, alarm_flash_red_expected, 8);
}

void alarm_flash_white(struct EffectObj*);
static u32 flash_step(void (*step)(struct EffectObj*), u8 count)
{
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    need_palette_load = 0;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0x1234;
    obj.ext.effect_37.unk19 = count;
    obj.ext.effect_37.unk1E = 0x11;
    obj.ext.effect_37.unk1F = 0x22;
    obj.ext.effect_37.unk21 = 0x33;
    obj.ext.effect_37.finished = 1;
    step(&obj);
    return (u32)(g_FilterAmountR | g_FilterAmountG | g_FilterAmountB) | (u32)obj.ext.effect_37.action << 16 | (u32)obj.ext.effect_37.timer << 20 | (u32)need_palette_load << 28;
}
static u32 af_red_glow(void) { return flash_step(alarm_flash_red, 3); }
static u32 af_red_switch(void) { return flash_step(alarm_flash_red, 1); }
static u32 af_white_switch(void) { return flash_step(alarm_flash_white, 1); }
static const CTestCase alarm_flash_steps_cases[] = {
    af_red_glow,
    af_red_switch,
    af_white_switch,
};
static const u32 alarm_flash_steps_cases_expected[] = { 0x1Fu, 0x51110000u, 0x53310000u };

const struct CTestGroup c_test_groups[] = {
    { "alarm_flash_red", 0, 0, 1, test_alarm_flash_red },
    { "alarm_flash_steps", alarm_flash_steps_cases, alarm_flash_steps_cases_expected, COUNT(alarm_flash_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(alarm_flash_steps_cases);
