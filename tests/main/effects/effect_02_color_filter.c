#include "test_runtime.h"
#include "main/effects/effect_02_color_filter.h"
#include "main/1AC84.h"

static u32 filter_case(u32 mode, u32 observation)
{
    struct EffectObj before[32];
    struct EffectObj* self = &effect_objects[2];
    u8 owners[2] = { 0xAB, 0xFF };
    u32 i, j, actual;
    memset(effect_objects, 0x5A, sizeof(effect_objects));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 0x41;
        effect_objects[i].id = 2;
        effect_objects[i].unk2 = 7;
        effect_objects[i].backref = NULL;
        effect_objects[i].ext.scaling_x.unk14 = NULL;
    }
    self->unk2 = mode ? -1 : 2;
    if (mode) {
        effect_objects[0].unk2 = 2;
        effect_objects[31].unk2 = 2;
        effect_objects[0].backref = &owners[0];
        effect_objects[31].backref = &owners[1];
    }
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 0x24680000 + i;
    g_FilterAmountR = 0x1234;
    g_FilterAmountG = 0x5678;
    g_FilterAmountB = 0x9ABC;
    g_FilterModeR = 0x12;
    g_FilterModeG = 0x34;
    g_FilterModeB = 0x56;
    memcpy(before, effect_objects, sizeof(before));
    color_filter_init(self);
    if (!mode) {
        before[2].state = self->state;
        before[2].ext.scaling_x.unk14 = self->ext.scaling_x.unk14;
        before[2].ext.scaling_x.unk18 = self->ext.scaling_x.unk18;
        assert(self->ext.scaling_x.unk14 == color_filter_scripts[2]);
        assert(owners[0] == 0xAB && owners[1] == 0xFF);
    } else {
        for (i = 0; i < 32; i++) {
            if (i == 0 || i == 2 || i == 31) {
                memcpy(&before[i], &effect_objects[i], 8);
                assert(((u32*)&effect_objects[i])[0] == 0);
                assert(((u32*)&effect_objects[i])[1] == 0);
            }
        }
    }
    for (i = 0; i < 32; i++) {
        for (j = 0; j < sizeof(struct EffectObj) / 4; j++)
            assert(((u32*)&effect_objects[i])[j] == ((u32*)&before[i])[j]);
    }
    switch (observation) {
    case 0:
        actual = g_FilterAmountR | ((u32)g_FilterAmountG << 16);
        break;
    case 1:
        actual = g_FilterAmountB | ((u32)g_FilterModeR << 16) | ((u32)g_FilterModeG << 24);
        break;
    case 2:
        actual = g_FilterModeB | ((u32)(u8)self->ext.scaling_x.unk18 << 8) | ((u32)owners[0] << 16) | ((u32)owners[1] << 24);
        break;
    case 3:
        actual = C_TEST_LE_WORD(self);
        break;
    case 4:
        actual = C_TEST_LE_WORD((u8*)self + 4);
        break;
    default:
        actual = D_8013E188[observation - 5];
        break;
    }
    return actual;
}
#ifdef MMX4_SATURN
#define FILTER_WORDS 2u, 0x24680001u, 0x24680002u, 0x24680003u
#else
#define FILTER_WORDS 0x0u, 0x0u, 0x3FF80u, 0x0u
#endif
static const u32 color_filter_pool_cases_expected[] = { 0x200001u, 0x2010400u, 0xFFAB0004u, 0x5A020241u, 0x5A5A5A5Bu, FILTER_WORDS, 0x0u, 0x0u, 0x70205A00u, 0x0u, 0x0u, 0x24680000u, 0x24680001u, 0x24680002u, 0x24680003u };
static u32 color_filter_pool_cases_row(u32 row)
{
    return filter_case(row / 9, row % 9);
}

extern struct Unk14 color_filter_script_0[13], color_filter_script_2[2];
static struct EffectObj cf;
static u32 cf_step(struct Unk14* entry, s8 frames)
{
    memset(&cf, 0, sizeof(cf));
    cf.active = 1;
    cf.id = 2;
    cf.state = 1;
    cf.ext.scaling_x.unk14 = entry;
    cf.ext.scaling_x.unk18 = frames;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0x7777;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 9;
    need_palette_load = 0;
    TitleScalingXUpdate(&cf);
    return (u32)(u8)(cf.ext.scaling_x.unk14 - entry) | (u32)(u8)cf.ext.scaling_x.unk18 << 8 | (u32)need_palette_load << 16 | (u32)cf.active << 24;
}
static u32 cf_wait(void)
{
    u32 seen = cf_step(color_filter_script_0, 3);
    assert(g_FilterAmountR == 0x7777 && g_FilterModeR == 9);
    return seen;
}
static u32 cf_next(void)
{
    u32 seen = cf_step(color_filter_script_0, 0);
    assert(g_FilterAmountR == 1 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    return seen;
}
static u32 cf_loop(void)
{
    u32 seen = cf_step(&color_filter_script_0[11], 0);
    assert(cf.ext.scaling_x.unk14 == color_filter_script_0 && g_FilterAmountR == 0 && g_FilterModeR == 0);
    return seen;
}
static u32 cf_end(void)
{
    u32 seen = cf_step(color_filter_script_2, 0);
    assert(g_FilterAmountR == 0x7777 && g_FilterModeR == 9);
    return seen;
}
static const CTestCase color_filter_steps_cases[] = {
    cf_wait,
    cf_next,
    cf_loop,
    cf_end,
};
static const u32 color_filter_steps_cases_expected[] = { 0x01000200u, 0x01050C01u, 0x01050CF5u, 0x0000FF01u };

const struct CTestGroup c_test_groups[] = {
    { "color_filter_pool", NULL, color_filter_pool_cases_expected, COUNT(color_filter_pool_cases_expected), color_filter_pool_cases_row },
    { "color_filter_steps", color_filter_steps_cases, color_filter_steps_cases_expected, COUNT(color_filter_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(color_filter_pool_cases_expected) + COUNT(color_filter_steps_cases);
