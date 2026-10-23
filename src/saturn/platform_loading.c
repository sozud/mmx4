#include "common.h"
#include "saturn/platform.h"

#define COLOR_OFFSET(offset) (*(s16*)((u8*)saturn_vdp2_shadow + (offset)))
#define COLOR_OFFSET_A_GREEN 0x116
#define COLOR_OFFSET_A_BLUE 0x118
#define COLOR_OFFSET_B_RED 0x11A
#define COLOR_OFFSET_B_GREEN 0x11C
#define COLOR_OFFSET_B_BLUE 0x11E
extern s16 saturn_color_offset_saved[];

#define LOADING_GROUP 11
#define LOADING_CHARACTER_BASE 0xE000
#define LOADING_BANK 1
#define LOADING_PALETTE_WORDS 80
#define LOADING_PALETTE_CRAM ((volatile u16*)0x25F00300)
#define LOADING_BACK_COLOR (*(volatile u16*)0x25E6FFFE)
#define LOADING_VRAM_BANKS 7
#define LOADING_TITLE 0
#define LOADING_STATUS 1
#define LOADING_PROMPT 2
#define LOADING_TITLE_STATUS_PROMPT 3
#define LOADING_TITLE_PROMPT 4
#define LOADING_PALETTE 0x80
#define LOADING_COLOR_TITLE 27
#define LOADING_COLOR_PROMPT 25
#define ENGINE_STAGE 12
#define ENGINE_STAGE_PART 13
#define ENGINE_CHARACTER 67
#define STAGE_LAST 13
#define STAGE_FINAL 12
#define STAGE_NUMBERED_LAST 8
#define INDICATOR_DARK 0xFF00
#define COLOR_OFFSET_A_RED 0x114
#define COLOR_OFFSET_COUNT 6

extern u8 saturn_engine_bytes[];
extern u8 saturn_loading_resource[];
static void loading_palette(void);
void saturn_vdp1_begin_group(u32 group);
void saturn_vdp1_end_group(void);
void saturn_thread_exit(void);
extern u8 saturn_archive_indicator_state;
void saturn_thread_kill(u32 slot);
extern u8 saturn_archive_queue_busy;

static void loading_palette(void)
{
    u16* source = (u16*)(saturn_loading_resource + *(u32*)(saturn_loading_resource + 4));
    volatile u16* destination = LOADING_PALETTE_CRAM;
    s32 count = LOADING_PALETTE_WORDS;
    do {
        count -= 2;
        *destination++ = *source++;
        *destination++ = *source++;
    } while (count != 0);
}

void saturn_loading_draw(u32 mode, u32 no_wait)
{
    struct SaturnHudSprite* sprite = &saturn_hud_sprite;
    saturn_vdp1_begin_group(LOADING_GROUP);
    sprite->frames = saturn_loading_resource + *(u32*)saturn_loading_resource;
    sprite->character_base = (s16)LOADING_CHARACTER_BASE;
    sprite->bank = LOADING_BANK;
    switch (mode) {
    case LOADING_TITLE:
        saturn_loading_draw_title(sprite);
        break;
    case LOADING_STATUS:
        saturn_loading_draw_status(sprite);
        break;
    case LOADING_PROMPT:
        saturn_loading_draw_prompt(sprite);
        break;
    case LOADING_TITLE_STATUS_PROMPT:
        saturn_loading_draw_title(sprite);
        saturn_loading_draw_status(sprite);
        saturn_loading_draw_prompt(sprite);
        break;
    case LOADING_TITLE_PROMPT:
        saturn_loading_draw_title(sprite);
        saturn_loading_draw_prompt(sprite);
        break;
    case LOADING_PALETTE:
        saturn_color_offset_suspend();
        loading_palette();
        saturn_vram_clear_banks(LOADING_VRAM_BANKS);
        LOADING_BACK_COLOR = 0;
        break;
    }
    saturn_vdp1_end_group();
    if (no_wait == 0) {
        saturn_thread_sleep(1);
    }
}

void saturn_color_offset_resume(void)
{
    COLOR_OFFSET(COLOR_OFFSET_A_RED) = saturn_color_offset_saved[0];
    COLOR_OFFSET(COLOR_OFFSET_A_GREEN) = saturn_color_offset_saved[1];
    COLOR_OFFSET(COLOR_OFFSET_A_BLUE) = saturn_color_offset_saved[2];
    COLOR_OFFSET(COLOR_OFFSET_B_RED) = saturn_color_offset_saved[3];
    COLOR_OFFSET(COLOR_OFFSET_B_GREEN) = saturn_color_offset_saved[4];
    COLOR_OFFSET(COLOR_OFFSET_B_BLUE) = saturn_color_offset_saved[5];
    saturn_thread_sleep(1);
}

void saturn_color_offset_suspend(void)
{
    saturn_color_offset_saved[0] = COLOR_OFFSET(COLOR_OFFSET_A_RED);
    saturn_color_offset_saved[1] = COLOR_OFFSET(COLOR_OFFSET_A_GREEN);
    saturn_color_offset_saved[2] = COLOR_OFFSET(COLOR_OFFSET_A_BLUE);
    saturn_color_offset_saved[3] = COLOR_OFFSET(COLOR_OFFSET_B_RED);
    saturn_color_offset_saved[4] = COLOR_OFFSET(COLOR_OFFSET_B_GREEN);
    saturn_color_offset_saved[5] = COLOR_OFFSET(COLOR_OFFSET_B_BLUE);
    COLOR_OFFSET(COLOR_OFFSET_A_RED) = 0;
    COLOR_OFFSET(COLOR_OFFSET_A_GREEN) = 0;
    COLOR_OFFSET(COLOR_OFFSET_A_BLUE) = 0;
    COLOR_OFFSET(COLOR_OFFSET_B_RED) = 0;
    COLOR_OFFSET(COLOR_OFFSET_B_GREEN) = 0;
    COLOR_OFFSET(COLOR_OFFSET_B_BLUE) = 0;
}

void saturn_loading_draw_title(struct SaturnHudSprite* sprite)
{
    sprite->x = 96;
    sprite->y = 96;
    sprite->frame = 4;
    sprite->color = LOADING_COLOR_TITLE;
    saturn_hud_draw_sprite(sprite);
}

void saturn_loading_draw_status(struct SaturnHudSprite* sprite)
{
    if ((s8)saturn_engine_bytes[ENGINE_STAGE] >= STAGE_LAST) {
        return;
    }
    sprite->x = 16;
    sprite->y = 0xC4;
    sprite->frame = (u8)((saturn_engine_bytes[ENGINE_CHARACTER] == 1) + 5);
    sprite->color = LOADING_COLOR_TITLE;
    saturn_hud_draw_sprite(sprite);
    sprite->x = saturn_engine_bytes[ENGINE_CHARACTER] != 0 ? 32 : 16;
    sprite->x += 16;
    sprite->y = 0xC4;
    sprite->frame = 7;
    saturn_hud_draw_sprite(sprite);
    sprite->x = 16;
    sprite->y = 0xD4;
    if ((s8)saturn_engine_bytes[ENGINE_STAGE] == STAGE_FINAL) {
        sprite->frame = 19;
    } else {
        sprite->frame = (u8)(saturn_engine_bytes[ENGINE_STAGE] + 8);
    }
    saturn_hud_draw_sprite(sprite);
    if ((s8)saturn_engine_bytes[ENGINE_STAGE] > STAGE_NUMBERED_LAST) {
        return;
    }
    sprite->x = 116;
    sprite->y = 0xD4;
    sprite->frame = (u8)(saturn_engine_bytes[ENGINE_STAGE_PART] + 20);
    saturn_hud_draw_sprite(sprite);
}

void saturn_loading_draw_prompt(struct SaturnHudSprite* sprite)
{
    sprite->x = 0xC8;
    sprite->y = 0xC0;
    sprite->frame = 1;
    sprite->color = LOADING_COLOR_PROMPT;
    saturn_hud_draw_sprite(sprite);
    sprite->x = 0xF8;
    sprite->y = 0xC0;
    sprite->frame = 2;
    sprite->color = LOADING_COLOR_PROMPT;
    saturn_hud_draw_sprite(sprite);
}

void saturn_archive_start_indicator(void)
{
    saturn_archive_indicator_state = 0;
    saturn_thread_kill(3);
    saturn_thread_create(4, (u32)saturn_loading_indicator_thread);
}

void saturn_loading_indicator_thread(void)
{
    struct SaturnHudSprite* sprite;
    u16* offsets;
    u32 i;
    while (saturn_archive_queue_busy != 0) {
        if (saturn_archive_indicator_state == 0) {
            saturn_archive_indicator_state = 1;
            saturn_color_offset_suspend();
            saturn_stage_commit_video();
            loading_palette();
            saturn_vram_clear_banks(LOADING_VRAM_BANKS);
            LOADING_BACK_COLOR = 0;
        } else {
            offsets = (u16*)((u8*)saturn_vdp2_shadow + COLOR_OFFSET_A_RED);
            for (i = 0; i < COLOR_OFFSET_COUNT; i++) {
                offsets[i] = 0;
            }
            saturn_vdp1_begin_group(LOADING_GROUP);
            sprite = &saturn_hud_sprite;
            sprite->frames = saturn_loading_resource + *(u32*)saturn_loading_resource;
            sprite->character_base = (s16)LOADING_CHARACTER_BASE;
            sprite->bank = LOADING_BANK;
            saturn_loading_draw_title(sprite);
            saturn_loading_draw_prompt(sprite);
            saturn_vdp1_end_group();
        }
        saturn_thread_sleep(1);
    }
    offsets = (u16*)((u8*)saturn_vdp2_shadow + COLOR_OFFSET_A_RED);
    for (i = 0; i < COLOR_OFFSET_COUNT; i++) {
        offsets[i] = INDICATOR_DARK;
    }
    offsets = (u16*)((u8*)saturn_vdp2_shadow_copy + COLOR_OFFSET_A_RED);
    for (i = 0; i < COLOR_OFFSET_COUNT; i++) {
        offsets[i] = INDICATOR_DARK;
    }
    saturn_stage_commit_video();
    saturn_thread_exit();
}
