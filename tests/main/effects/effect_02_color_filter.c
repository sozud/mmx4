#include "test_runtime.h"
#include "main/effects/effect_02_color_filter.h"
#include "main/1A5BC.h"

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
        actual = ((u32*)self)[0];
        break;
    case 4:
        actual = ((u32*)self)[1];
        break;
    default:
        actual = D_8013E188[observation - 5];
        break;
    }
    return actual;
}
#define FILTER_CASE(name, mode, observation)   \
    static u32 name(void)                      \
    {                                          \
        return filter_case(mode, observation); \
    }
FILTER_CASE(COLOR_FILTER_SCRIPT_AMOUNTS_RG, 0, 0)
FILTER_CASE(COLOR_FILTER_SCRIPT_BLUE_AND_MODES, 0, 1)
FILTER_CASE(COLOR_FILTER_SCRIPT_BACKREFS_AND_TIMER, 0, 2)
FILTER_CASE(COLOR_FILTER_SCRIPT_HEADER, 0, 3)
FILTER_CASE(COLOR_FILTER_SCRIPT_STATE, 0, 4)
FILTER_CASE(COLOR_FILTER_SCRIPT_MASK_0, 0, 5)
FILTER_CASE(COLOR_FILTER_SCRIPT_MASK_1, 0, 6)
FILTER_CASE(COLOR_FILTER_SCRIPT_MASK_2, 0, 7)
FILTER_CASE(COLOR_FILTER_SCRIPT_MASK_3, 0, 8)
FILTER_CASE(COLOR_FILTER_CLEANUP_AMOUNTS_RG, 1, 0)
FILTER_CASE(COLOR_FILTER_CLEANUP_BLUE_AND_MODES, 1, 1)
FILTER_CASE(COLOR_FILTER_CLEANUP_BACKREFS_AND_TIMER, 1, 2)
FILTER_CASE(COLOR_FILTER_CLEANUP_HEADER, 1, 3)
FILTER_CASE(COLOR_FILTER_CLEANUP_STATE, 1, 4)
FILTER_CASE(COLOR_FILTER_CLEANUP_MASK_0, 1, 5)
FILTER_CASE(COLOR_FILTER_CLEANUP_MASK_1, 1, 6)
FILTER_CASE(COLOR_FILTER_CLEANUP_MASK_2, 1, 7)
FILTER_CASE(COLOR_FILTER_CLEANUP_MASK_3, 1, 8)
static const CTestCase color_filter_pool_cases[] = {
    COLOR_FILTER_SCRIPT_AMOUNTS_RG,
    COLOR_FILTER_SCRIPT_BLUE_AND_MODES,
    COLOR_FILTER_SCRIPT_BACKREFS_AND_TIMER,
    COLOR_FILTER_SCRIPT_HEADER,
    COLOR_FILTER_SCRIPT_STATE,
    COLOR_FILTER_SCRIPT_MASK_0,
    COLOR_FILTER_SCRIPT_MASK_1,
    COLOR_FILTER_SCRIPT_MASK_2,
    COLOR_FILTER_SCRIPT_MASK_3,
    COLOR_FILTER_CLEANUP_AMOUNTS_RG,
    COLOR_FILTER_CLEANUP_BLUE_AND_MODES,
    COLOR_FILTER_CLEANUP_BACKREFS_AND_TIMER,
    COLOR_FILTER_CLEANUP_HEADER,
    COLOR_FILTER_CLEANUP_STATE,
    COLOR_FILTER_CLEANUP_MASK_0,
    COLOR_FILTER_CLEANUP_MASK_1,
    COLOR_FILTER_CLEANUP_MASK_2,
    COLOR_FILTER_CLEANUP_MASK_3,
};
static const u32 color_filter_pool_cases_expected[] = { 0x200001u, 0x2010400u, 0xFFAB0004u, 0x5A020241u, 0x5A5A5A5Bu, 0x0u, 0x0u, 0x3FF80u, 0x0u, 0x0u, 0x0u, 0x70205A00u, 0x0u, 0x0u, 0x24680000u, 0x24680001u, 0x24680002u, 0x24680003u };
#undef FILTER_CASE

static const u32 copy_animated_palette_expected[] = { 1u };
static u32 test_copy_animated_palette(u32 row)
{
    u32 observed_values[1];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&need_palette_load, 0, sizeof(need_palette_load));
    need_palette_load = 0;
    copy_animated_palette(&obj);
    observed_values[0] = (u32)need_palette_load;
    return c_test_observe(0, row, observed_values, copy_animated_palette_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "color_filter_pool", color_filter_pool_cases, color_filter_pool_cases_expected, COUNT(color_filter_pool_cases), 0 },
    { "copy_animated_palette", 0, 0, 1, test_copy_animated_palette },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(color_filter_pool_cases) + 1;
