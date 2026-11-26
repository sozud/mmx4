#include "test_runtime.h"
#include "main/1AC84.h"
#ifdef MMX4_SATURN
#include "saturn/platform.h"
#include "saturn/game_low.h"
#endif

#ifdef MMX4_SATURN
struct FilterRow {
    u8 fade_state, mode;
    u16 red, green, blue;
};
static const struct FilterRow filter_rows[] = {
    { 1, 0, 4, 0x80, 0x1000 },
    { 0, 0, 4, 0x80, 0x1000 },
    { 0, 1, 4, 0x80, 0x1000 },
    { 0, 1, 0, 0, 0 },
};
static const u32 filter_expected[] = {
    0xFFFFu, 0x5555u, 0x6666u, 0x7777u,
    0xFF85u, 0x0021u, 0x0021u, 0x0021u,
    0xFF85u, 0x01DFu, 0x01DFu, 0x01DFu,
    0xFF85u, 0x0000u, 0x0000u, 0x0000u,
};
static u32 test_filter(u32 row)
{
    const struct FilterRow* in = &filter_rows[row];
    u32 seen[4];
    saturn_fade_state = in->fade_state;
    saturn_color_filter_screens = 0x05;
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_CLOFEN) = 0xFFFF;
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAR) = 0x5555;
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAR + 2) = 0x6666;
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAR + 4) = 0x7777;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = in->mode;
    g_FilterAmountR = in->red;
    g_FilterAmountG = in->green;
    g_FilterAmountB = in->blue;
    func_8002A484();
    saturn_fade_state = 0;
    seen[0] = SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_CLOFEN);
    seen[1] = SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAR);
    seen[2] = SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAR + 2);
    seen[3] = SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAR + 4);
    return c_test_observe(0, row, seen, &filter_expected[row * 4], 4);
}
#else
struct FilterRow {
    u8 need, mode;
    u16 red, green, blue;
    u16 last_red, last_green, last_blue;
};
static const struct FilterRow filter_rows[] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 4, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 4, 0x80, 0x1000, 0, 0, 0 },
    { 0, 0, 4, 0x80, 0x1000, 4, 0, 0x1000 },
    { 0, 0, 4, 0x80, 0x1000, 4, 0x80, 0 },
    { 0, 0, 4, 0x80, 0x1000, 4, 0x80, 0x1000 },
};
static const u32 filter_expected[] = {
    0, 0x00000000u, 0x0000u, 0xBEEFBEEFu, 0xBEEFBEEFu, 0xBEEFBEEFu,
    2, 0x00000000u, 0x0000u, 0x8842BEEFu, 0x7BDE294Au, 0x294A294Au,
    2, 0x00800004u, 0x1000u, 0x8000BEEFu, 0x6B5A18C6u, 0x294A18C6u,
    2, 0x00800004u, 0x1000u, 0x98C6BEEFu, 0x7FFF39CEu, 0x294A39CEu,
    2, 0x00800004u, 0x1000u, 0x98C6BEEFu, 0x7FFF39CEu, 0x294A39CEu,
    0, 0x00800004u, 0x1000u, 0xBEEFBEEFu, 0xBEEFBEEFu, 0xBEEFBEEFu,
};
static u16 filter_palette[128 * 16];
static u32 test_filter(u32 row)
{
    const struct FilterRow* in = &filter_rows[row];
    u32 seen[6], i;
    for (i = 0; i < COUNT(filter_palette); i++) {
        filter_palette[i] = 0x294A;
        D_80141F70[i] = 0xBEEF;
    }
    filter_palette[0] = 0;
    filter_palette[1] = 0x8842;
    filter_palette[3] = 0x7BDE;
    TEST_PALETTE = (u8*)filter_palette;
    D_8013E188[0] = (s32)0x80000000u;
    D_8013E188[1] = D_8013E188[2] = D_8013E188[3] = 0;
    need_palette_load = in->need;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = in->mode;
    g_FilterAmountR = in->red;
    g_FilterAmountG = in->green;
    g_FilterAmountB = in->blue;
    lastFilterAmountR = in->last_red;
    lastFilterAmountG = in->last_green;
    lastFilterAmountB = in->last_blue;
    func_8002A484();
    seen[0] = need_palette_load;
    seen[1] = lastFilterAmountR | (u32)lastFilterAmountG << 16;
    seen[2] = lastFilterAmountB;
    seen[3] = D_80141F70[0] | (u32)D_80141F70[1] << 16;
    seen[4] = D_80141F70[2] | (u32)D_80141F70[3] << 16;
    seen[5] = D_80141F70[4] | (u32)D_80141F70[16] << 16;
    for (i = 5; i < 16; i++)
        assert(D_80141F70[i] == D_80141F70[4]);
    for (i = 17; i < COUNT(filter_palette); i++)
        assert(D_80141F70[i] == D_80141F70[16]);
    need_palette_load = 0;
    return c_test_observe(0, row, seen, &filter_expected[row * 6], 6);
}
#endif

const struct CTestGroup c_test_groups[] = {
    { "stage_colour_filter", 0, 0, COUNT(filter_rows), test_filter },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(filter_rows);
