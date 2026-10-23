#include "common.h"
#include "saturn/platform.h"

#define FADE_IDLE 0
#define FADE_IN 1
#define FADE_OUT 2
#define FADE_THREAD_SLOT 4
#define FADE_STEP 15
#define FADE_DARKEST -0x100
#define FADE_OUT_BIAS 0x100
#define FADE_ALL_SCREENS 127
#define COLOR_OFFSET_SELECT 0x112
#define COLOR_OFFSET_A_RED 0x114
#define COLOR_OFFSET_A_GREEN 0x116
#define COLOR_OFFSET_A_BLUE 0x118
#define COLOR_OFFSET_B_RED 0x11A
#define COLOR_OFFSET_B_GREEN 0x11C
#define COLOR_OFFSET_B_BLUE 0x11E
#define COLOR_OFFSET(offset) (*(s16*)((u8*)saturn_vdp2_shadow + (offset)))
#define VRAM_CLEAR_SOURCE 0
#define VRAM_CLEAR_DESTINATION 1
#define VRAM_CLEAR_ATTRIBUTE 2
#define VRAM_BANK_A0 0x25E70000
#define VRAM_BANK_A1 0x25E74000
#define VRAM_BANK_B0 0x25E78000
#define VRAM_BANK_B1 0x25E7C000
#define VRAM_SMALL_BYTES 0x2000
#define VRAM_LARGE_BYTES 0x4000
#define TEXT_CLEAR_BYTES 0x1FFC
#define DMA_BUSY 2

extern u8 saturn_fade_state;
extern s16 saturn_fade_level_b;
extern s16 saturn_fade_out_step;
void saturn_thread_create(u32 slot, u32 entry);
void saturn_thread_sleep(u32 frames);
void saturn_fade_in_thread(void);
void saturn_fade_out_thread(void);
void saturn_transfer_enqueue(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile(u32 add_a, u32 add_b, u32 attribute_index);
void DMA_CpuMemCopy1(void* destination, void* source, u32 count);
u32 DMA_CpuResult(void);

u8 saturn_vram_clear_source[] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x08,
    0x00,
};

void saturn_fade_start_in(void)
{
    if (saturn_fade_state != FADE_IDLE) {
        return;
    }
    COLOR_OFFSET(COLOR_OFFSET_SELECT) = 0;
    saturn_fade_state = FADE_IN;
    saturn_thread_create(FADE_THREAD_SLOT, (u32)saturn_fade_in_thread);
}

void saturn_fade_start_out(void)
{
    if (saturn_fade_state != FADE_IDLE) {
        return;
    }
    COLOR_OFFSET(COLOR_OFFSET_SELECT) = 0;
    saturn_fade_state = FADE_OUT;
    saturn_thread_create(FADE_THREAD_SLOT, (u32)saturn_fade_out_thread);
}

void saturn_fade_in(void)
{
    s16 level;
    while (saturn_fade_level_b < 0) {
        saturn_fade_level_b += FADE_STEP;
        if (saturn_fade_level_b > 0) {
            saturn_fade_level_b = 0;
        }
        saturn_vdp2_set_display(1);
        level = COLOR_OFFSET(COLOR_OFFSET_A_RED);
        if (level != 0) {
            if (level > 0) {
                level -= FADE_STEP;
                if (level < 0) {
                    level = 0;
                }
            } else {
                level += FADE_STEP;
                if (level > 0) {
                    level = 0;
                }
            }
        }
        COLOR_OFFSET(COLOR_OFFSET_A_RED) = level;
        COLOR_OFFSET(COLOR_OFFSET_A_GREEN) = level;
        COLOR_OFFSET(COLOR_OFFSET_A_BLUE) = level;
        COLOR_OFFSET(COLOR_OFFSET_B_RED) = saturn_fade_level_b;
        COLOR_OFFSET(COLOR_OFFSET_B_GREEN) = saturn_fade_level_b;
        COLOR_OFFSET(COLOR_OFFSET_B_BLUE) = saturn_fade_level_b;
        saturn_thread_sleep(1);
    }
    saturn_fade_set(FADE_ALL_SCREENS, 0);
    saturn_thread_sleep(1);
    saturn_fade_state = FADE_IDLE;
}

void saturn_fade_out(void)
{
    s16 level;
    saturn_fade_out_step = -FADE_STEP;
    if ((u16)COLOR_OFFSET(COLOR_OFFSET_A_RED) != 0) {
        saturn_fade_out_step = (s16)(((u16)COLOR_OFFSET(COLOR_OFFSET_A_RED) + FADE_OUT_BIAS) >> 4);
    }
    while (saturn_fade_level_b > FADE_DARKEST) {
        saturn_fade_level_b -= FADE_STEP;
        if (saturn_fade_level_b < FADE_DARKEST) {
            saturn_fade_level_b = FADE_DARKEST;
        }
        saturn_vdp2_set_display(0);
        level = (s16)(COLOR_OFFSET(COLOR_OFFSET_A_RED) - FADE_STEP);
        if (level < FADE_DARKEST) {
            level = FADE_DARKEST;
        }
        COLOR_OFFSET(COLOR_OFFSET_A_RED) = level;
        COLOR_OFFSET(COLOR_OFFSET_A_GREEN) = level;
        COLOR_OFFSET(COLOR_OFFSET_A_BLUE) = level;
        COLOR_OFFSET(COLOR_OFFSET_B_RED) = saturn_fade_level_b;
        COLOR_OFFSET(COLOR_OFFSET_B_GREEN) = saturn_fade_level_b;
        COLOR_OFFSET(COLOR_OFFSET_B_BLUE) = saturn_fade_level_b;
        saturn_thread_sleep(1);
    }
    saturn_fade_set(FADE_ALL_SCREENS, FADE_DARKEST);
    saturn_thread_sleep(1);
    saturn_fade_state = FADE_IDLE;
}

void saturn_fade_in_thread(void)
{
    saturn_fade_in();
    saturn_thread_exit();
}

void saturn_fade_out_thread(void)
{
    saturn_fade_out();
    saturn_thread_exit();
}

void saturn_vram_clear_banks(u32 banks)
{
    if (banks & 1) {
        saturn_transfer_profile(VRAM_CLEAR_SOURCE, VRAM_CLEAR_DESTINATION, VRAM_CLEAR_ATTRIBUTE);
        saturn_transfer_enqueue((u32)saturn_vram_clear_source, VRAM_BANK_A0, VRAM_SMALL_BYTES);
    }
    if (banks & 2) {
        saturn_transfer_profile(VRAM_CLEAR_SOURCE, VRAM_CLEAR_DESTINATION, VRAM_CLEAR_ATTRIBUTE);
        saturn_transfer_enqueue((u32)saturn_vram_clear_source, VRAM_BANK_A1, VRAM_SMALL_BYTES);
    }
    if (banks & 4) {
        saturn_transfer_profile(VRAM_CLEAR_SOURCE, VRAM_CLEAR_DESTINATION, VRAM_CLEAR_ATTRIBUTE);
        saturn_transfer_enqueue((u32)saturn_vram_clear_source, VRAM_BANK_B0, VRAM_LARGE_BYTES);
    }
    if (banks & 8) {
        saturn_transfer_profile(VRAM_CLEAR_SOURCE, VRAM_CLEAR_DESTINATION, VRAM_CLEAR_ATTRIBUTE);
        saturn_transfer_enqueue((u32)saturn_vram_clear_source, VRAM_BANK_B1, VRAM_LARGE_BYTES);
    }
}

void saturn_text_layers_clear(u32 layers)
{
    if (layers & 4) {
        *(u32*)saturn_text_cells = 0;
        DMA_CpuMemCopy1(saturn_text_cells + 4, saturn_text_cells, TEXT_CLEAR_BYTES);
        while (DMA_CpuResult() == DMA_BUSY) {
        }
        saturn_text_dirty_a = 1;
    }
    if (layers & 8) {
        *(u32*)saturn_debug_text = 0;
        DMA_CpuMemCopy1(saturn_debug_text + 4, saturn_debug_text, TEXT_CLEAR_BYTES);
        while (DMA_CpuResult() == DMA_BUSY) {
        }
        saturn_text_dirty_b = 1;
    }
}

void saturn_fade_set(s16 select, s16 level)
{
    saturn_vdp2_set_display(1);
    if (select != 0) {
        COLOR_OFFSET(COLOR_OFFSET_SELECT) = (s16)(~select & FADE_ALL_SCREENS);
    }
    COLOR_OFFSET(COLOR_OFFSET_A_RED) = level;
    COLOR_OFFSET(COLOR_OFFSET_A_GREEN) = level;
    COLOR_OFFSET(COLOR_OFFSET_A_BLUE) = level;
    COLOR_OFFSET(COLOR_OFFSET_B_RED) = saturn_fade_level_b;
    COLOR_OFFSET(COLOR_OFFSET_B_GREEN) = saturn_fade_level_b;
    COLOR_OFFSET(COLOR_OFFSET_B_BLUE) = saturn_fade_level_b;
}
