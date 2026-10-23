#ifndef SATURN_GAME_LOW_H
#define SATURN_GAME_LOW_H

#define SATURN_BG_WIND_CELL_VRAM 0x25E01000
#define SATURN_BG_WIND_CELL_BYTES 0x200
#define SATURN_DISPLAY_MODE_BG_WIND_CALM 0x0B
#define SATURN_DISPLAY_MODE_BG_WIND_GUST 0x0F
#define SATURN_MUSIC_LIGHT_CAPSULE 0x1D
#define SATURN_SOUND_ZONE_CHANNEL 4
#define SATURN_SOUND_ZONE_SLOT 6
#define SATURN_TITLE_TEXTURE 0x4800
#define SATURN_TITLE_FRAMES ((void*)0x060A7040)
#define SATURN_TITLE_PALETTE ((s32*)0x060A5040)
#define SATURN_PALETTE_ANIMATION_SOURCE ((s32*)0x060A5040)

#define SATURN_PAD_DIALOGUE_SKIP 0x07F8
#define SATURN_OPTION_WINDOW_TEXTURE 0xC600
#define SATURN_OPTION_WINDOW_FRAMES ((void*)0x002C6400)
#define SATURN_OPTION_TITLE_Y 0x10
#define SATURN_OPTION_BACK_ROW 0xF0
#define SATURN_OPTION_EMPTY_ROW 0x80
#define SATURN_OPTION_CURSOR_TEXTURE 0xE000
#define SATURN_OPTION_CURSOR_FRAMES ((void*)0x002D2000)
#define SATURN_OPTION_CURSOR_BACK 3
#define SATURN_OPTION_TITLE_PALETTE 3
#define SATURN_OPTION_SELECTED_PALETTE 2
#define SATURN_OPTION_LOCKED_PALETTE 4
#define SATURN_OPTION_PALETTE 0
#define SATURN_OPTION_CURSOR_PALETTE 6
#define SATURN_OPTION_HINT_PALETTE 0x1B
#define SATURN_SAVE_SLOT_BYTES 42
#define SATURN_SAVE_SLOT_HIDDEN 0xFF
#define SATURN_VDP2_PRINA 0xF8
#define SATURN_VDP2_PRINB 0xFA
#define SATURN_VDP2_SHADOW_WORD(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SATURN_BACK_COLOR ((volatile u16*)0x25E6FFFE)
#define SATURN_INTRO_BACK_COLOR 0x1861
#define SATURN_DIALOGUE_HIGH_TEXTURE 0xB0
#define SATURN_DIALOGUE_TEXTURE_BASE 0x25C24000u
#define SATURN_DIALOGUE_PAD_MASK 0x07F8
#define SATURN_DIALOGUE_TWO_SPEAKERS 4
#define SATURN_DIALOGUE_PALETTE 0xD0
#define SATURN_DIALOGUE_FORTRESS_PALETTE 0x3E0
#define SATURN_DIALOGUE_PORTRAIT_PALETTE 27
#define SATURN_DIALOGUE_WINDOW_PALETTE ((const u16*)0x002C8000)
#define SATURN_DIALOGUE_MESSAGES ((u16*)0x002C8040)
#define SATURN_DIALOGUE_WINDOW_TEXTURE 0xE000
#define SATURN_DIALOGUE_WINDOW_PALETTE_INDEX 0x0E
#define SATURN_DIALOGUE_FORTRESS_WINDOW_PALETTE 0x3F
#define SATURN_DIALOGUE_TOP 1
#define SATURN_DIALOGUE_BOTTOM 2
#define SATURN_DIALOGUE_X_TRACK_FIRST 30
#define SATURN_DIALOGUE_ZERO_TRACK_FIRST 25
#define SATURN_DIALOGUE_CAPSULE_MESSAGE 12
#define SATURN_DIALOGUE_CAPSULE_TRACK 0x20
#define SATURN_DIALOGUE_KEEP_TRACK 0xFE
#define SATURN_DIALOGUE_STOP_TRACK 0xFF
#define SATURN_DIALOGUE_TEXT_TEXTURE 0xC600
#define SATURN_DIALOGUE_ARROW_TEXTURE 0xC980
#define SATURN_DIALOGUE_TEXT_PALETTE 0x0D
#define SATURN_DIALOGUE_FORTRESS_TEXT_PALETTE 0x3E
#define SATURN_TILE_STAGING_BANK_BYTES 0x600
#define SATURN_TILE_TRANSFER_ADD 0x100
#define SATURN_TILE_TRANSFER_ROW 1
#define SATURN_TILE_TRANSFER_COLUMN 7
extern u8 saturn_tile_staging[];
extern u16 saturn_tile_run_length;
extern u32 saturn_tile_run_destination;
extern u32* saturn_tile_staging_cursor;
extern u16 saturn_tile_staging_offset;
extern u16 saturn_tile_column_offset;
extern u16* saturn_tile_column_high;
extern u16* saturn_tile_column_low;
extern u16 saturn_tile_run_start;
extern u16 saturn_tile_column_start;
extern u8 saturn_tile_run_state;
extern u8 saturn_tile_screen_state;
void saturn_transfer_enqueue_secondary(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile_secondary(u32 add_a, u32 add_b, u32 attribute_index);
#define SATURN_VDP2_CLOFEN 0x112
#define SATURN_VDP2_COAR 0x11A
#define SATURN_VDP2_COAG 0x11C
#define SATURN_VDP2_COAB 0x11E
#define SATURN_COLOR_OFFSET_SIGN 0x100
#define SATURN_COLOR_OFFSET_MASK 0x1FF
extern u32 saturn_color_filter_screens;
extern u8 saturn_fade_state;
s32 saturn_get_random_signed(void);
extern u8 saturn_dialogue_flags;
#define SATURN_DIALOGUE_X_TRACKS 24
#define SATURN_DIALOGUE_ZERO_TRACKS 24
extern u8 saturn_dialogue_tracks[SATURN_DIALOGUE_X_TRACKS + SATURN_DIALOGUE_ZERO_TRACKS];
extern u32* saturn_dialogue_window_animations[];
extern u16 saturn_color_ram[];
extern u8 saturn_display_mode;
extern u16 saturn_pad_pressed;
extern u8 saturn_save_slots[];
extern volatile u8 saturn_frame_dma_pending;
extern volatile u32 saturn_frame_dma_count;
extern volatile u32 saturn_frame_dma_arg_0;
extern volatile u32 saturn_frame_dma_arg_1;
extern volatile u32 saturn_stage_work_pointer_3;

void saturn_background_refresh(void);

#endif
