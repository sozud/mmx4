#include "test_runtime.h"
#include "main/14A60.h"
#include "main/1A5BC.h"

static u32 subtract_all_channels(void)
{
    POLY_F4 primitive;
    struct DrawInfo draw;
    u32 actual;
    memset(&primitive, 0, sizeof(primitive));
    memset(&draw, 0, sizeof(draw));
    memset(&engine_obj, 0, sizeof(engine_obj));
    cur_draw_info = &draw;
    SP_AUX_CURSOR = &primitive;
    setaddr(&draw.ordering_table.unk3, 0x00543210);
    g_FilterAmountR = 1;
    g_FilterAmountG = 1 << 5;
    g_FilterAmountB = 1 << 10;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    func_80025588(-17, 319, -3, 239, 0);
    assert(primitive.x0 == -17 && primitive.x2 == -17);
    assert(primitive.x1 == 319 && primitive.x3 == 319);
    assert(primitive.y0 == -3 && primitive.y1 == -3);
    assert(primitive.y2 == 239 && primitive.y3 == 239);
    assert(getcode(&primitive) == 0x28 && getlen(&primitive) == 5);
    assert(getaddr(&primitive) == 0x00543210);
    assert(nextPrim(&draw.ordering_table.unk3) == &primitive);
    assert(SP_AUX_POLY_F4_CURSOR == &primitive + 1);
    actual = primitive.r0 | ((u32)primitive.g0 << 8) | ((u32)primitive.b0 << 16);
    return actual;
}

static const CTestCase hud_color_subtraction_cases[] = {
    subtract_all_channels,
};
static const u32 hud_color_subtraction_cases_expected[] = { 0x39CE00u };

static const u32 func_80025588_expected[] = { 0x42u, 0x28u, 0xD6u, 8u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_80025588(u32 row)
{
    u32 observed_values[12];
    POLY_F4 child_0;
    u8 child_0_present;
    struct DrawInfo child_1;
    u8 child_1_present;
    s16 arg0;
    s16 arg1;
    s16 arg2;
    s16 arg3;
    s32 arg4;
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_FilterAmountB, 0, sizeof(g_FilterAmountB));
    memset(&g_FilterAmountG, 0, sizeof(g_FilterAmountG));
    memset(&g_FilterAmountR, 0, sizeof(g_FilterAmountR));
    memset(&g_FilterModeB, 0, sizeof(g_FilterModeB));
    memset(&g_FilterModeG, 0, sizeof(g_FilterModeG));
    memset(&g_FilterModeR, 0, sizeof(g_FilterModeR));
    child_0_present = 255;
    g_FilterAmountB = 65535;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    engine_obj.stage = 2;
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    child_1_present = 255;
    arg0 = 0;
    arg1 = 0;
    arg2 = 0;
    arg3 = 0;
    arg4 = 0;
    SP_AUX_CURSOR = child_0_present ? &child_0 : NULL;
    cur_draw_info = child_1_present ? &child_1 : NULL;
    func_80025588(arg0, arg1, arg2, arg3, arg4);
    observed_values[0] = (u32)child_0.b0;
    observed_values[1] = (u32)child_0.code;
    observed_values[2] = (u32)child_0.g0;
    observed_values[3] = (u32)child_0.r0;
    observed_values[4] = (u32)child_0.x0;
    observed_values[5] = (u32)child_0.x1;
    observed_values[6] = (u32)child_0.x2;
    observed_values[7] = (u32)child_0.x3;
    observed_values[8] = (u32)child_0.y0;
    observed_values[9] = (u32)child_0.y1;
    observed_values[10] = (u32)child_0.y2;
    observed_values[11] = (u32)child_0.y3;
    return c_test_observe(0, row, observed_values, func_80025588_expected, 12);
}

const struct CTestGroup c_test_groups[] = {
    { "hud_color_subtraction", hud_color_subtraction_cases, hud_color_subtraction_cases_expected, COUNT(hud_color_subtraction_cases), 0 },
    { "func_80025588", 0, 0, 1, test_func_80025588 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hud_color_subtraction_cases) + 1;
