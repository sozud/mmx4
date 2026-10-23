#include "common.h"
#include "saturn/platform.h"
#include "saturn.h"

#define BG_SCREEN_TILE_BYTES 0x10000
#define BG_LOW_SCREEN_TILES ((u16*)0x00200000)
extern u16 saturn_stage_screen_tile_buffer[];

#define SHADOW16(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SHADOW32(offset) (*(u32*)((u8*)saturn_vdp2_shadow + (offset)))
#define BACKUP_UNFORMATTED 0x44
#define BACKUP_FAILED 0x88
#define BACKUP_NO_INTERNAL 0x08
#define BACKUP_UNFORMATTED_CART 0x45
#define BACKUP_UNFORMATTED_BOTH 0x54
#define BACKUP_FULL 0x80
#define PAD_ANY_BUTTON 0x0FF8
#define VRAM_ALL_BANKS 15
#define TEXT_LAYERS_ALL 12
#define DMA_BUSY 2
#define VDP2_VRAM ((u8*)0x25E00000)
#define VDP2_VRAM_BYTES 0x80000
#define VDP2_FONT ((u16*)0x25E60000)
#define VDP1_FONT ((u16*)0x25C7E000)
#define FONT_WORDS 0x1000
#define VDP1_LOW_PALETTE ((u16*)0x25C7FF00)
#define LOW_PALETTE_WORDS 84
#define LOW_IMAGE ((void*)0x00220000)
#define LOADING_FULL 128
#define LOADING_STEP 2
#define BG_COLOR_OFFSET 0x114
#define BG_COLOR_OFFSET_WORDS 6
#define COLOR_OFFSET_BLACK 0xFF00

struct SaturnDmaScuParameters {
    u32 read;
    u32 write;
    u32 count;
    u32 read_add;
    u32 write_add;
    u32 mode;
    u32 read_update;
    u32 write_update;
    u32 factor;
    u32 mask;
};

extern s32 saturn_boot_state;
extern s32 saturn_boot_substate;
extern s32 saturn_boot_timer;
extern u8 saturn_backup_cart_status;
extern u8 saturn_vdp2_ram_control_config[6];
extern u8 saturn_warm_start;
extern s16 saturn_vdp1_local_x;
extern s16 saturn_vdp1_local_y;
extern u8 saturn_fade_state;
extern s16 saturn_fade_level_b;
extern u8 saturn_demo_return;
extern u8 need_palette_load;
extern volatile u16 saturn_pad_pressed;
extern volatile u8 saturn_archive_queue_busy;
extern u8 saturn_text_dirty_a;
extern u8 saturn_reset_inhibit;
extern u8 saturn_engine_bytes[];
extern void (*saturn_cd_error_hook)(void);
s32 saturn_archive_load_blocking(const char* path);
void saturn_archive_queue_push(const char* path, u32 suppress_indicator);
s32 saturn_cd_load_file(const char* name, void* buffer);
void saturn_movie_play(const char* name, u32 mode);
void saturn_stage_select_sound(void);
void saturn_thread_restart(u32 entry);
void func_8001DAF8(void);
void DMA_ScuSetPrm(struct SaturnDmaScuParameters* parameters, u32 channel);
void DMA_ScuStart(u32 channel);
u32 DMA_ScuResult(void);

static void boot_check_backup(void);
static void boot_logo(void);
static void boot_load_low(void);
static void boot_title_prepare(void);
static void boot_title_wait(void);
static void boot_sound_wait(void);
static void boot_fade_wait(void);
static void boot_enable_reset(void);
static void boot_start_low(void);

const char saturn_warning_no_internal[] = "WARNING4.ARC";

const char saturn_warning_full[] = "WARNING1.ARC";

const char saturn_warning_failed[] = "WARNING2.ARC";

const char saturn_warning_unformatted[] = "WARNING3.ARC";

const char saturn_logo_movie[] = "LOGO.CPK";

const char saturn_ascii_archive[] = "ASCII.ARC";

const char saturn_low_image_name[] = "X4LOW.X4";

const char saturn_sound_command_archive[] = "SNDCOM.ARC";

const u16 saturn_low_vdp1_palette[LOW_PALETTE_WORDS] = {
    0x6318,
    0x6318,
    0x6000,
    0x6000,
    0x7FFF,
    0x7FFF,
    0x7084,
    0x7084,
    0x03FF,
    0x7FFF,
    0x7FFF,
    0x03FF,
    0x7FFF,
    0x7F18,
    0x7F18,
    0x7FFF,
    0x001F,
    0x001F,
    0x001F,
    0x001F,
    0x7FFF,
    0x7FFF,
    0x7C00,
    0x7C00,
    0x001B,
    0x001B,
    0x001B,
    0x001B,
    0x0017,
    0x0017,
    0x0017,
    0x0017,
    0x0013,
    0x0013,
    0x0013,
    0x0013,
    0x000F,
    0x000F,
    0x000F,
    0x000F,
    0x000B,
    0x000B,
    0x000B,
    0x000B,
    0x0007,
    0x0007,
    0x0007,
    0x0007,
    0x0003,
    0x0003,
    0x0003,
    0x0003,
    0x7FFF,
    0x03E0,
    0x0200,
    0x03E0,
    0x7FFF,
    0x001F,
    0x0010,
    0x001F,
    0x7FFF,
    0x03FF,
    0x0210,
    0x03FF,
    0x43E8,
    0x43E8,
    0x411F,
    0x411F,
    0x03FF,
    0x03FF,
    0x7FFF,
    0x7FFF,
    0x7FFF,
    0x7FFF,
    0x001F,
    0x001F,
    0x7FFF,
    0x7FFF,
    0x03E0,
    0x03E0,
    0x7FFF,
    0x7FFF,
    0x7C00,
    0x7C00,
};

const u16 saturn_boot_cycle_patterns[8] = {
    0xffff,
    0x4567,
    0x123,
    0x4567,
    0xffff,
    0x4567,
    0x123,
    0x4567,
};

static void (*const boot_handlers[])(void) = {
    boot_check_backup,
    boot_logo,
    boot_load_low,
    boot_title_prepare,
    boot_title_wait,
    boot_sound_wait,
    boot_fade_wait,
    boot_enable_reset,
    boot_start_low,
};

void saturn_background_copy_screen_tiles(void)
{
    u16* source = BG_LOW_SCREEN_TILES;
    u16* destination = saturn_stage_screen_tile_buffer;
    s32 count;
    for (count = BG_SCREEN_TILE_BYTES; count != 0;) {
        count -= 2;
        destination[0] = source[0];
        destination[1] = source[1];
        source += 2;
        destination += 2;
    }
}

static void boot_vdp2_setup(void)
{
    u32 i;
    saturn_vdp2_ram_control_config[0] = 1;
    saturn_vdp2_ram_control_config[2] = 0;
    saturn_vdp2_ram_control_config[3] = 0;
    saturn_vdp2_ram_control_config[1] = 1;
    saturn_vdp2_ram_control_config[4] = 0;
    saturn_vdp2_ram_control_config[5] = 0;
    saturn_vdp2_set_ram_control(saturn_vdp2_ram_control_config);
    SHADOW16(0x28) = 0x0101;
    SHADOW16(0x2A) = 0;
    SHADOW16(0x30) = 0;
    SHADOW16(0x32) = 0;
    SHADOW16(0x34) = 0;
    SHADOW16(0x36) = 0;
    SHADOW16(0x3A) = 5;
    SHADOW16(0x40) = 0x3030;
    SHADOW16(0x42) = 0x3030;
    SHADOW16(0x3C) |= 1;
    SHADOW16(0x44) = 0x3434;
    SHADOW16(0x46) = 0x3434;
    SHADOW16(0x3C) |= 0x10;
    SHADOW16(0x48) = 0x1E1E;
    SHADOW16(0x4A) = 0x1E1E;
    SHADOW16(0x4C) = 0x1F1F;
    SHADOW16(0x4E) = 0x1F1F;
    SHADOW32(0xAC) = 0x12F37FFF;
    SHADOW16(0x9A) = 0;
    SHADOW32(0xA0) = 0;
    for (i = 0; i < 8; i++)
        SHADOW16(0x10 + i * 2) = saturn_boot_cycle_patterns[i];
}

static void boot_check_backup(void)
{
    const char* warning;
    u8 status;
    if (saturn_warm_start) {
        saturn_stage_commit_video();
        saturn_vdp1_local_x = 0;
        saturn_vdp1_local_y = 0;
        saturn_boot_state++;
        saturn_boot_substate = 0;
        return;
    }
    if (saturn_boot_substate == 0) {
        saturn_stage_commit_video();
        saturn_vdp1_local_x = 0;
        saturn_vdp1_local_y = 0;
        saturn_backup_cart_status = (u8)saturn_backup_status();
        if (saturn_backup_cart_status == 0) {
            saturn_boot_state++;
            return;
        }
        status = saturn_backup_cart_status;
        if ((status & BACKUP_UNFORMATTED) != BACKUP_UNFORMATTED && !(status & BACKUP_FAILED)) {
            saturn_boot_state++;
            return;
        }
        saturn_vdp2_set_display(0);
        boot_vdp2_setup();
        SHADOW32(0x70) = 0;
        SHADOW32(0x74) = 0;
        SHADOW16(0x20) = 1;
        switch (saturn_backup_cart_status) {
        case BACKUP_NO_INTERNAL:
            warning = saturn_warning_no_internal;
            break;
        case BACKUP_UNFORMATTED:
        case BACKUP_UNFORMATTED_CART:
        case BACKUP_UNFORMATTED_BOTH:
            warning = saturn_warning_unformatted;
            break;
        case BACKUP_FULL:
            warning = saturn_warning_full;
            break;
        case BACKUP_FAILED:
            warning = saturn_warning_failed;
            break;
        default:
            warning = NULL;
            break;
        }
        if (warning)
            saturn_archive_load_blocking(warning);
        need_palette_load |= 1;
        saturn_thread_sleep(1);
        saturn_vdp2_set_display(1);
        saturn_boot_substate++;
        return;
    }
    if (!(saturn_pad_pressed & PAD_ANY_BUTTON))
        return;
    if (saturn_backup_cart_status & BACKUP_FAILED) {
        ((void (*)(s32))saturn_cd_error_hook)(0);
        return;
    }
    saturn_vdp2_set_display(0);
    saturn_vram_clear_banks(VRAM_ALL_BANKS);
    saturn_text_layers_clear(TEXT_LAYERS_ALL);
    saturn_boot_state++;
    saturn_boot_substate = 0;
}

static void boot_logo(void)
{
    struct SaturnDmaScuParameters dma;
    u32 zero;
    if (!saturn_warm_start) {
        saturn_movie_play(saturn_logo_movie, 0);
        saturn_video_start();
    } else {
        boot_vdp2_setup();
        zero = 0;
        dma.read = (u32)&zero;
        dma.write = (u32)VDP2_VRAM;
        dma.count = VDP2_VRAM_BYTES;
        dma.read_add = 0;
        dma.write_add = 1;
        dma.mode = 0;
        dma.read_update = 0;
        dma.write_update = 1;
        dma.factor = 7;
        dma.mask = 3;
        DMA_ScuSetPrm(&dma, 0);
        DMA_ScuStart(0);
        while (DMA_ScuResult() == DMA_BUSY) { }
        saturn_vram_clear_banks(VRAM_ALL_BANKS);
        saturn_text_layers_clear(TEXT_LAYERS_ALL);
        saturn_stage_commit_video();
    }
    saturn_boot_state++;
}

static void boot_upload_low_palette(void)
{
    u32 i;
    for (i = 0; i < LOW_PALETTE_WORDS; i++)
        VDP1_LOW_PALETTE[i] = saturn_low_vdp1_palette[i];
}

static void boot_load_low(void)
{
    u32 i;
    saturn_archive_load_blocking(saturn_ascii_archive);
    saturn_cd_load_file(saturn_low_image_name, LOW_IMAGE);
    for (i = 0; i < FONT_WORDS; i++)
        VDP1_FONT[i] = VDP2_FONT[i];
    need_palette_load |= 1;
    saturn_thread_sleep(1);
    boot_upload_low_palette();
    saturn_boot_state++;
}

static void boot_title_prepare(void)
{
    saturn_loading_draw(LOADING_FULL, 1);
    saturn_loading_draw(LOADING_STEP, 1);
    saturn_engine_bytes[0x0C] = 0;
    saturn_engine_bytes[0x0D] = 0;
    saturn_stage_select_sound();
    saturn_archive_queue_push(saturn_sound_command_archive, 1);
    SHADOW16(0x20) = 15;
    saturn_fade_in();
    saturn_loading_draw(LOADING_STEP, 1);
    saturn_boot_timer = 1;
    saturn_boot_state++;
}

static void boot_title_wait(void)
{
    if (--saturn_boot_timer == 0)
        saturn_boot_state++;
    saturn_loading_draw(LOADING_STEP, 1);
}

static void boot_sound_wait(void)
{
    saturn_loading_draw(LOADING_STEP, 1);
    if (!saturn_archive_queue_busy) {
        saturn_stage_sound_finalize();
        saturn_fade_start_out();
        saturn_boot_state++;
    }
}

static void boot_fade_wait(void)
{
    saturn_loading_draw(LOADING_STEP, 1);
    if (!saturn_fade_state) {
        need_palette_load |= 1;
        saturn_stage_commit_video();
        saturn_text_layers_clear(TEXT_LAYERS_ALL);
        saturn_text_dirty_a = 1;
        saturn_boot_state++;
    }
}

static void boot_enable_reset(void)
{
    saturn_reset_inhibit = 0;
    saturn_boot_state++;
}

static void boot_start_low(void)
{
    u32 i;
    saturn_boot_substate = 0;
    for (i = 0; i < BG_COLOR_OFFSET_WORDS; i++)
        SHADOW16(BG_COLOR_OFFSET + i * 2) = COLOR_OFFSET_BLACK;
    saturn_fade_level_b = (s16)COLOR_OFFSET_BLACK;
    saturn_thread_sleep(1);
    saturn_thread_restart((u32)func_8001DAF8);
}

void saturn_boot_worker(void)
{
    saturn_fade_state = 0;
    saturn_fade_level_b = 0;
    saturn_boot_state = 0;
    saturn_boot_substate = 0;
    saturn_demo_return = 0;
    for (;;) {
        boot_handlers[saturn_boot_state]();
        saturn_thread_sleep(1);
    }
}

static inline void
decompress_words(const u16* source, u16* destination)
{
    for (;;) {
        unsigned flags = *source++;
        for (unsigned mask = 0x8000; mask; mask >>= 1) {
            if (!(flags & mask)) {
                *destination++ = *source++;
            } else {
                unsigned token = *source++;
                unsigned length = token >> 11;
                unsigned distance = token & 0x7FF;
                if (!length) {
                    length = *source++;
                }
                if (!(length | distance)) {
                    return;
                }
                if (!distance) {
                    do {
                        *destination++ = 0;
                    } while (--length);
                } else {
                    const u16* copy = destination - distance;
                    do {
                        *destination++ = *copy++;
                    } while (--length);
                }
            }
        }
    }
}

void saturn_decompress_gfx(const u16* source, u16* destination)
{
    decompress_words(source, destination);
}

void saturn_decompress_gfx_job(void)
{
    const u16* source = *(const u16* volatile*)((u32)&saturn_gfx_source | 0x20000000U);
    u16* destination = *(u16* volatile*)((u32)&saturn_gfx_destination | 0x20000000U);
    decompress_words((const u16*)((u32)source | 0x20000000U), destination);
}
