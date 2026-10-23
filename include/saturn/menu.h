#ifndef MMX4_SATURN_MENU_H
#define MMX4_SATURN_MENU_H

#include "saturn/player_resources.h"

#define SATURN_PAD_START 0x0800
#define SATURN_PAD_CANCEL 0x0100
#define SATURN_PAD_CONFIRM 0x0600
#define SATURN_PAD_BACK (SATURN_PAD_START | SATURN_PAD_CANCEL)
#define SATURN_PAD_TOGGLE 0xC600
#define SATURN_PAD_ANY 0x0FF8
#define SATURN_PAD_UP 0x1000
#define SATURN_PAD_DOWN 0x2000
#define SATURN_PAD_LEFT 0x4000
#define SATURN_PAD_RIGHT 0x8000
#define SATURN_PAD_A 0x0400
#define SATURN_PAD_C 0x0200
#define SATURN_PAD_B 0x0100
#define SATURN_PAD_R 0x0080
#define SATURN_PAD_X 0x0040
#define SATURN_PAD_Y 0x0020
#define SATURN_PAD_L 0x0008

#define SATURN_SE_CONFIRM 0x27
#define SATURN_SE_TOGGLE 0x0D
#define SATURN_SE_CURSOR 0x0D
#define SATURN_BACKUP_UNAVAILABLE 0x44

struct MemcardSaveSlot;

extern u8 saturn_display_mode;
extern u8 saturn_title_skip;
extern u8 saturn_sound_output;
extern u16 saturn_color_ram[];
extern u16 saturn_title_palette_backup[0x1F0];
extern u16 saturn_title_palette[0x1F0];
extern u16 saturn_title_window_backup[16];
extern s32 saturn_weapon_get_palettes[];
extern s16 saturn_music_fading;
extern volatile u16 saturn_warm_buffer[144];
extern volatile u16 saturn_stage_vram_marker;
extern char* saturn_demo_archives[4];
extern u8 saturn_demo_return;
extern u8 saturn_soft_reset_mode;
extern u8 saturn_controller_refresh;
extern u8 saturn_backup_status;
extern u8 saturn_archive_queue_busy;
extern u16 saturn_pause_request;
extern u16 saturn_pause_latch;

void saturn_sound_set_output(u8 output);
void saturn_title_upload_window(void);
void saturn_background_refresh(void);
void saturn_stage_commit_video(void);
void saturn_sprite_reset_queues(void);
void saturn_save_load(struct MemcardSaveSlot* save, s32 mode);
void saturn_music_start(s32 track, s32 arg);
void saturn_music_stop(void);
void saturn_music_request(s32 track, s32 arg1, s32 arg2, s32 arg3);
s32 saturn_archive_load_blocking(const char* path);
void saturn_vram_clear(u8 banks);
void saturn_vram_clear_alternate(u8 banks);
void saturn_sound_stop_all(void);
void saturn_video_start(void);
void saturn_movie_play(const char* path, s32 mode);
void saturn_sprite_draw_passes(void);
void saturn_stage_sound_finalize(void);
void saturn_archive_queue_cancel(void);
void saturn_frame_dma_copy(u32 arg0, u32 arg1, u32 count);
u32 saturn_frame_dma_result(void);

#endif
