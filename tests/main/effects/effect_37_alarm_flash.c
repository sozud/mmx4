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

const struct CTestGroup c_test_groups[] = {
    { "alarm_flash_red", 0, 0, 1, test_alarm_flash_red },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
