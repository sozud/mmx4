// 8002A484..8002A6FC
#include "common.h"
#ifdef MMX4_SATURN
#include "saturn/platform.h"
#include "saturn/game_low.h"
#endif
#include "main/1AC84.h"

#ifdef MMX4_SATURN
static u16 color_filter_offset(u16 scaled, u8 subtract)
{
    if (subtract && scaled != 0) {
        scaled = -scaled | SATURN_COLOR_OFFSET_SIGN;
    }
    return scaled & SATURN_COLOR_OFFSET_MASK;
}

void func_8002A484(void)
{
    u16 red;
    u16 green;
    u16 blue;

    if (saturn_fade_state != 0) {
        return;
    }
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_CLOFEN) = (SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_CLOFEN) & 0xFF80) | saturn_color_filter_screens;
    red = color_filter_offset((g_FilterAmountR << 3) | (g_FilterAmountR >> 2), g_FilterModeR && g_FilterAmountR);
    green = color_filter_offset((g_FilterAmountG >> 2) | (g_FilterAmountG >> 7), g_FilterModeG && g_FilterAmountG);
    blue = color_filter_offset((g_FilterAmountB >> 7) | (g_FilterAmountB >> 12), g_FilterModeB && g_FilterAmountB);
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAR) = red;
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAG) = green;
    SATURN_VDP2_SHADOW_WORD(SATURN_VDP2_COAB) = blue;
}
#else
void func_8002A484(void)
{
    u32 mask;
    u32 color;
    u16* dst;
    u16* src;
    u32 component;
    u32 blue;
    u32 green;
    u32 color_index;
    u32 red;
    u32 palette_index;

    if (((g_FilterAmountR | g_FilterAmountG | g_FilterAmountB) != 0) || (need_palette_load & 4)) {
        if ((lastFilterAmountR != g_FilterAmountR) || (lastFilterAmountG != g_FilterAmountG) || (lastFilterAmountB != g_FilterAmountB) || (need_palette_load != 0)) {
            src = dst = SP_PALETTE;
            dst = D_80141F70;
            for (palette_index = 0; palette_index < 128; palette_index++) {
                if (!(palette_index & 0x1F)) {
                    mask = D_8013E188[palette_index >> 5];
                }
                color_index = 0;
                if ((s32)mask <= -1) {
                    do {
                        color = *src;
                        src++;
                        if (color != 0) {
                            if (g_FilterModeR != 0) {
                                red = (color & 0x1F) < g_FilterAmountR ? 0 : (color & 0x1F) - g_FilterAmountR;
                            } else {
                                component = (color & 0x1F) + g_FilterAmountR;
                                red = 0x1F;
                                if (component < 0x20U) {
                                    red = component;
                                }
                            }
                            if (g_FilterModeG != 0) {
                                green = (color & 0x3E0) < g_FilterAmountG ? 0 : (color & 0x3E0) - g_FilterAmountG;
                            } else {
                                component = (color & 0x3E0) + g_FilterAmountG;
                                green = 0x3E0;
                                if (component < 0x3E1U) {
                                    green = component;
                                }
                            }
                            if (g_FilterModeB != 0) {
                                blue = (color & 0x7C00) < g_FilterAmountB ? 0 : (color & 0x7C00) - g_FilterAmountB;
                            } else {
                                component = (color & 0x7C00) + g_FilterAmountB;
                                if (component < 0x7C01U) {
                                    blue = component;
                                } else {
                                    blue = 0x7C00;
                                }
                            }
                            *dst = red | green | blue | (color & 0x8000);
                        }
                        color_index += 1;
                        dst++;
                    } while (color_index < 0x10U);
                } else {
                    do {
                        *dst = *src;
                        src++;
                        color_index += 1;
                        dst++;
                    } while (color_index < 0x10U);
                }
                mask <<= 1;
            }
            lastFilterAmountR = g_FilterAmountR;
            lastFilterAmountG = g_FilterAmountG;
            lastFilterAmountB = g_FilterAmountB;
            need_palette_load = 2;
        }
    }
}
#endif
