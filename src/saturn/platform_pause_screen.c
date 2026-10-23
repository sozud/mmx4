#include "common.h"
#include "saturn/platform.h"

#define SHADOW16(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SHADOW32(offset) (*(u32*)((u8*)saturn_vdp2_shadow + (offset)))

#define PAUSE_PALETTE_WORDS 0x200
#define PAUSE_SHADOW_WORDS 0x90
#define PAUSE_SPRITE_COUNT_BYTES 20
#define PAUSE_SPRITE_LIST_WORDS (0xC80 / 4)
#define PAUSE_ARCHIVE ((s32*)0x002D0000)
#define PAUSE_GRAPHICS_VRAM 0x25E70000
#define PAUSE_GRAPHICS_BYTES 0x200
#define PAUSE_GRAPHICS_BANK_SHIFT 14
#define PAUSE_PRIORITY_MASK 0x0F00
#define PAUSE_PRIORITY_TEXT 4
#define DMA_BUSY 2

extern u16 saturn_vdp2_shadow[];
extern u16 saturn_color_ram_shadow[];
extern u16 saturn_pause_palette_save[];
extern u16 saturn_pause_shadow_save[];
extern u8 saturn_pause_sprite_counts_save[];
extern u32 saturn_pause_sprite_lists_save[];
extern u8 saturn_sprite_list_counts[];
extern u32 saturn_sprite_object_lists[];
extern u8 saturn_pause_player_visible;
void saturn_frame_dma_copy(u32 destination, u32 source, u32 count);
u32 saturn_frame_dma_result(void);

const u8 saturn_pause_graphics_banks[] = {
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x00,
    0x00,
    0x43,
    0x41,
    0x50,
    0x43,
    0x4F,
    0x4D,
    0x20,
    0x53,
    0x65,
    0x70,
    0x20,
    0x30,
    0x31,
    0x20,
    0x31,
    0x39,
    0x39,
    0x37,
    0x20,
    0x31,
    0x33,
    0x3A,
    0x35,
    0x33,
    0x3A,
    0x31,
    0x33,
    0x20,
    0x43,
    0x41,
    0x50,
    0x43,
    0x4F,
    0x4D,
    0x00,
};

u8 saturn_sound_output = 0x56;

static void pause_reset_layers(void)
{
    SHADOW32(0x70) = 0;
    SHADOW32(0x74) = 0;
    SHADOW32(0x80) = 0;
    SHADOW32(0x84) = 0;
    SHADOW16(0x90) = 0;
    SHADOW16(0x92) = 0;
}

static void pause_upload_graphics(u32 bank)
{
    s32* archive = PAUSE_ARCHIVE;
    saturn_frame_dma_copy(PAUSE_GRAPHICS_VRAM + (bank << PAUSE_GRAPHICS_BANK_SHIFT),
        (u32)((u8*)archive + archive[1]), PAUSE_GRAPHICS_BYTES);
    while (saturn_frame_dma_result() == DMA_BUSY) { }
}

static u32 pause_graphics_bank(void)
{
    return saturn_pause_graphics_banks[engine_obj.stage * 2 + engine_obj.substage];
}

void saturn_pause_enter(void)
{
    s32* archive = PAUSE_ARCHIVE;
    u16* palette;
    u32 bank;
    u32 i;
    for (i = 0; i < PAUSE_PALETTE_WORDS; i++)
        saturn_pause_palette_save[i] = saturn_color_ram_shadow[i];
    palette = (u16*)((u8*)archive + archive[0]);
    for (i = 0; i < PAUSE_PALETTE_WORDS; i++)
        saturn_color_ram_shadow[i] = palette[i];
    bank = pause_graphics_bank();
    pause_upload_graphics(bank);
    need_palette_load |= 1;
    for (i = 0; i < PAUSE_SHADOW_WORDS; i++)
        saturn_pause_shadow_save[i] = saturn_vdp2_shadow[i];
    SHADOW16(0xFA) = (u16)((SHADOW16(0xFA) & PAUSE_PRIORITY_MASK) | PAUSE_PRIORITY_TEXT);
    pause_reset_layers();
    SHADOW16(0x20) = (u16)(1 << bank);
    for (i = 0; i < PAUSE_SPRITE_COUNT_BYTES; i++)
        saturn_pause_sprite_counts_save[i] = saturn_sprite_list_counts[i];
    for (i = 0; i < PAUSE_SPRITE_LIST_WORDS; i++)
        saturn_pause_sprite_lists_save[i] = saturn_sprite_object_lists[i];
    saturn_pause_player_visible = g_Player.on_screen;
    g_Player.on_screen = 0;
}

void saturn_pause_reload(void)
{
    u32 bank = pause_graphics_bank();
    pause_upload_graphics(bank);
    pause_reset_layers();
    SHADOW16(0xFA) = (u16)((SHADOW16(0xFA) & PAUSE_PRIORITY_MASK) | PAUSE_PRIORITY_TEXT);
    SHADOW16(0x20) = (u16)(1 << bank);
}

void saturn_pause_leave(void)
{
    u32 i;
    for (i = 0; i < PAUSE_PALETTE_WORDS; i++)
        saturn_color_ram_shadow[i] = saturn_pause_palette_save[i];
    need_palette_load |= 1;
    for (i = 0; i < PAUSE_SHADOW_WORDS; i++)
        saturn_vdp2_shadow[i] = saturn_pause_shadow_save[i];
    for (i = 0; i < PAUSE_SPRITE_COUNT_BYTES; i++)
        saturn_sprite_list_counts[i] = saturn_pause_sprite_counts_save[i];
    for (i = 0; i < PAUSE_SPRITE_LIST_WORDS; i++)
        saturn_sprite_object_lists[i] = saturn_pause_sprite_lists_save[i];
    g_Player.on_screen = saturn_pause_player_visible;
    saturn_background_refresh();
}
