#include "common.h"
#include "saturn/platform.h"

#define SHADOW16(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SHADOW32(offset) (*(u32*)((u8*)saturn_vdp2_shadow + (offset)))
#define TVMD_DISPLAY_ON 0x8000
#define SR_IMASK_CLEAR 0xFF0F
#define SR_IMASK_ALL 0xF0
#define SCU_TIMER0 0x43
#define SCU_MASK_ALL -1
#define SCU_MASK_TIMER0 8
#define VRAM_ALL_BANKS 15
#define TEXT_LAYERS_ALL 12
#define DMA_BUSY 2
#define VDP2_VRAM 0x25E00000
#define VDP2_VRAM_BYTES 0x80000

#define PAD_START 0x0800
#define CPK_CPU_DUAL 3
#define CPK_COLOR_24BIT 24
#define CPK_TRMODE_CPU 0
#define CPK_STAT_PLAY_END 5
#define MOVIE_LOAD_SECTORS 20
#define MOVIE_START_TRIGGER_BYTES 0x28800
#define MOVIE_VOLUME 7
#define MOVIE_SILENCE_RATE 4
#define MOVIE_LINE_BYTES 0x500
#define MOVIE_LINES 224
#define MOVIE_TOP 8
#define MOVIE_WORK_BYTES 0x41CC
#define MOVIE_RING_BYTES 0x34800
#define MOVIE_DECODE_BYTES (MOVIE_LINES * MOVIE_LINE_BYTES)
#define MOVIE_PCM_BUFFER 0x25A60000
#define MOVIE_PCM_SAMPLES 0x10000
#ifndef VERSION_SATURN_PROTO
#define MOVIE_INGAME_TOP 24
#define MOVIE_INGAME_DECODE_BYTES (176 * MOVIE_LINE_BYTES)
#endif
#define SCU_T0C (*(volatile u32*)0x25FE0090)
#define SCU_T1MD (*(volatile u32*)0x25FE0098)
#define SCU_T1MD_ENABLE_LINE 0x101
#define VDP2_LINE_SCROLL_TABLE ((volatile u32*)0x25E60000)
#define VDP2_CELL_SCROLL_TABLE ((volatile u32*)0x25E70000)
#define VDP2_BACK_COLOR (*(volatile u16*)0x25E6FFFE)

struct SaturnMovieDma {
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

typedef void* CpkHn;
typedef void* GfsHn;
typedef struct {
    u32* work_addr;
    u32 work_size;
    u32* buf_addr;
    u32 buf_size;
    u16* pcm_addr;
    u32 pcm_size;
} CpkCreatePara;
typedef struct {
    u32 film;
    u32 size_header;
    u32 version;
    u32 reserved;
    u32 fdsc;
    u32 size_fdsc;
    u32 c_type;
    u32 height;
    u32 width;
} CpkHeader;
typedef void (*CpkErrFunc)(void* object, s32 code);
s32 CPK_Init(void);
void CPK_Finish(void);
CpkHn CPK_CreateGfsMovie(CpkCreatePara* para, GfsHn gfs);
void CPK_DestroyGfsMovie(CpkHn cpk);
void CPK_Task(CpkHn cpk);
s32 CPK_IsDispTime(CpkHn cpk);
void CPK_CompleteDisp(CpkHn cpk);
void CPK_Start(CpkHn cpk);
void CPK_SetDecodeAddr(CpkHn cpk, void* address, s32 line_size);
void CPK_SetColor(CpkHn cpk, s32 color);
void CPK_SetLoadNum(CpkHn cpk, s32 sectors);
void CPK_SetVolume(CpkHn cpk, s32 volume);
void CPK_SetSilenceRate(CpkHn cpk, s32 rate);
void CPK_SetTrModeCd(CpkHn cpk, s32 mode);
void CPK_SetTrModePcm(CpkHn cpk, s32 mode);
void CPK_SetStartTrgSize(CpkHn cpk, s32 bytes);
s32 CPK_GetPlayStatus(CpkHn cpk);
CpkHeader* CPK_GetHeader(CpkHn cpk);
s32 CPK_PreloadHeader(CpkHn cpk);
void CPK_SetErrFunc(CpkErrFunc function, void* object);
void CPK_SetCpu(s32 cpu);
s32 GFS_NameToId(const char* name);
GfsHn GFS_Open(s32 id);
void GFS_Close(GfsHn gfs);
void DMA_CpuMemCopy4(void* destination, void* source, u32 count);
u32 DMA_CpuResult(void);
void DMA_ScuMemCopy(void* destination, void* source, u32 count);
void INT_SetScuFunc(s32 vector, void* function);
void DMA_ScuSetPrm(struct SaturnMovieDma* parameters, u32 channel);
void DMA_ScuStart(u32 channel);
u32 DMA_ScuResult(void);
typedef void (*SaturnMovieScuMask)(s32 mask, s32 bits);
extern SaturnMovieScuMask saturn_bios_change_scu_mask;
extern u8 saturn_movie_active;
extern u8 saturn_vdp2_ram_control_config[6];
extern u16 saturn_pad_held;
extern volatile s32 saturn_cd_file_id;
extern volatile u32 saturn_cd_handle;

extern CpkHn saturn_movie_handle;
extern CpkCreatePara saturn_movie_para;
extern CpkHeader* saturn_movie_header;
extern u16 saturn_movie_x_offset;
extern u16 saturn_movie_width;
extern u16 saturn_movie_height;
extern volatile u8 saturn_movie_timer_flag;
extern u8 saturn_movie_top;

#ifdef VERSION_SATURN_PROTO
#include "saturn/player_resources.h"
#define MOVIE_WORK saturn_work_area.movie.work
#define MOVIE_RING saturn_work_area.movie.ring
#define MOVIE_DECODE saturn_work_area.movie.decode
#else
extern u32 saturn_movie_work[MOVIE_WORK_BYTES / 4];
extern u32 saturn_movie_ring[MOVIE_RING_BYTES / 4];
extern u32 saturn_movie_decode[MOVIE_DECODE_BYTES / 4];
#define MOVIE_WORK saturn_movie_work
#define MOVIE_RING saturn_movie_ring
#define MOVIE_DECODE saturn_movie_decode
void saturn_sound_forget_stage_map(void);
#endif

const u16 saturn_movie_cycle_patterns[8] = {
    0xFFFF,
    0x4567,
    0x0123,
    0x4567,
    0xFFFF,
    0x4567,
    0x0123,
    0x4567,
};

struct MovieCycles {
    u16 words[8];
};

static const struct MovieCycles movie_cycles = {
    { 0x4444, 0x4444, 0xFFFF, 0xFFFF, 0x4444, 0x4444, 0xCCFF, 0xFFFF },
};

#ifdef VERSION_SATURN_PROTO
static u32* movie_save_area(void)
{
    return (u32*)((u8*)saturn_sound_effects - sizeof(saturn_work_area.movie));
}
#endif

static void movie_error(void* object, s32 code)
{
    for (;;) { }
}

static void movie_timer(void)
{
    saturn_movie_timer_flag = 1;
}

static void movie_line_scroll(u16 width)
{
    volatile u32* table = VDP2_LINE_SCROLL_TABLE;
    u16 count;
    u16 i;
    u32 cells;
    u32 position;
    s32 y;
    s32 next;
    s32 skip;
    for (count = saturn_movie_top * 2; count > 0; count--) {
        *table++ = 0;
    }
    if (saturn_movie_x_offset != 0) {
        saturn_movie_x_offset = (saturn_movie_x_offset >> 3) + (saturn_movie_x_offset % 8 != 0);
    }
    cells = width >> 3;
    for (i = 0; i < MOVIE_LINES; i++) {
        position = (u32)i * width;
        y = (position << 7) & 0x01FF0000;
        next = ((s16)(y / 0x10000) + 1) * 64;
        skip = saturn_movie_x_offset + next - (s32)(cells * i);
        if (next >= (s32)(cells * (i + 1))) {
            skip = 64;
        }
        *table++ = (position << 16) & 0x01FF0000;
        *table++ = y + ((64 - skip) << 10);
    }
    for (i = 0; i < 44; i++) {
        VDP2_CELL_SCROLL_TABLE[i * 2 + 1] = i * 0x400;
    }
}

static void movie_set_window(s16 x, s16 y)
{
    u16 right = saturn_movie_width + x;
    s32 bottom = saturn_movie_top + y + saturn_movie_height;
    SHADOW32(0x70) = 0;
    SHADOW16(0xD0) = 0;
    SHADOW16(0xC0) = 0;
    SHADOW16(0xC2) = saturn_movie_top;
    SHADOW16(0xC4) = 0;
    SHADOW16(0xC6) = 0;
    if (x != 0) {
        SHADOW32(0x70) = ((0x800 - x) & 0x7FF) << 16;
        right += x;
        SHADOW16(0xC0) = x * 2;
    }
    if (y != 0) {
        bottom += y;
#ifdef VERSION_SATURN_PROTO
        SHADOW16(0xC2) += saturn_movie_top + y + 1;
#else
        SHADOW16(0xC2) += y + 1;
#endif
    }
    SHADOW16(0xD0) = 3;
    SHADOW16(0xC4) = right * 2 - 1;
    SHADOW16(0xC6) = bottom - 1;
    saturn_movie_top += y;
    saturn_movie_x_offset = x;
    movie_line_scroll(saturn_movie_width);
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    INT_SetScuFunc(SCU_TIMER0, movie_timer);
    SCU_T0C = saturn_movie_top + 1;
    SCU_T1MD = SCU_T1MD_ENABLE_LINE;
    saturn_bios_change_scu_mask(~SCU_MASK_TIMER0, 0);
    _builtin_set_cr(_builtin_get_cr() & SR_IMASK_CLEAR);
}

static void movie_video_setup(void)
{
    struct MovieCycles cycles;
    cycles = movie_cycles;
    saturn_vdp2_set_screen_mode(0, 1, 0);
    SHADOW16(0x0E) = (SHADOW16(0x0E) & 0x0FFF) | 0x1000;
    SHADOW32(0xAC) = 0x12F37FFF;
    VDP2_BACK_COLOR = 0;
    saturn_vdp2_ram_control_config[0] = 0;
    saturn_vdp2_ram_control_config[2] = 0;
    saturn_vdp2_ram_control_config[3] = 0;
    saturn_vdp2_ram_control_config[1] = 1;
    saturn_vdp2_ram_control_config[4] = 0;
    saturn_vdp2_ram_control_config[5] = 0;
    saturn_vdp2_set_ram_control_stage(saturn_vdp2_ram_control_config);
    saturn_vdp2_set_char_control(4, 4, 1, 0);
    SHADOW16(0x3C) = 0;
    SHADOW16(0x9A) = 7;
    SHADOW32(0xA0) = 0x12F30000;
    SHADOW32(0x9C) = 0x12F38000;
    saturn_vdp2_set_cycles(cycles.words);
    SHADOW16(0xE0) |= 0x623;
    SHADOW16(0x20) |= 1;
    SHADOW16(0x110) = 0x7F;
}

static void movie_clear_vram(void)
{
    struct SaturnMovieDma dma;
    u32 zero = 0;
    dma.read = (u32)&zero;
    dma.write = VDP2_VRAM;
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
}

static void movie_restore_screen(void)
{
    s32 i;
    CPK_DestroyGfsMovie(saturn_movie_handle);
    GFS_Close((GfsHn)saturn_cd_handle);
    saturn_movie_active = 0;
    SHADOW16(0x00) &= ~TVMD_DISPLAY_ON;
    SHADOW16(0x9A) = 0;
    SHADOW16(0xD0) = 0;
    CPK_Finish();
    _builtin_set_cr((_builtin_get_cr() & SR_IMASK_CLEAR) | SR_IMASK_ALL);
    INT_SetScuFunc(SCU_TIMER0, NULL);
    saturn_bios_change_scu_mask(SCU_MASK_ALL, SCU_MASK_TIMER0);
    _builtin_set_cr(_builtin_get_cr() & SR_IMASK_CLEAR);
    saturn_thread_sleep(1);
    saturn_vdp2_ram_control_config[0] = 1;
    saturn_vdp2_ram_control_config[2] = 0;
    saturn_vdp2_ram_control_config[3] = 0;
    saturn_vdp2_ram_control_config[1] = 1;
    saturn_vdp2_ram_control_config[4] = 0;
    saturn_vdp2_ram_control_config[5] = 0;
    saturn_vdp2_set_ram_control(saturn_vdp2_ram_control_config);
    SHADOW16(0x28) = 0x0101;
#ifdef VERSION_SATURN_PROTO
    SHADOW16(0x2A) = 0;
#else
    SHADOW16(0x2A) = 1;
#endif
    SHADOW16(0x30) = 0;
    SHADOW16(0x32) = 0;
    SHADOW16(0x34) = 0;
    SHADOW16(0x36) = 0;
#ifdef VERSION_SATURN_PROTO
    SHADOW16(0x3A) = 5;
#else
    SHADOW16(0x3A) = 0x15;
#endif
    SHADOW16(0x40) = 0x3030;
    SHADOW16(0x42) = 0x3030;
    SHADOW16(0x3C) |= 1;
    SHADOW16(0x44) = 0x3434;
    SHADOW16(0x46) = 0x3434;
    SHADOW16(0x3C) |= 0x10;
#ifdef VERSION_SATURN_PROTO
    SHADOW16(0x48) = 0x1E1E;
    SHADOW16(0x4A) = 0x1E1E;
#else
    SHADOW16(0x48) = 0x3838;
    SHADOW16(0x4A) = 0x3838;
    SHADOW16(0x3C) |= 0x100;
#endif
    SHADOW16(0x4C) = 0x1F1F;
    SHADOW16(0x4E) = 0x1F1F;
    SHADOW16(0x9A) = 0;
    SHADOW32(0xA0) = 0;
    for (i = 0; i < 8; i++)
        SHADOW16(0x10 + i * 2) = saturn_movie_cycle_patterns[i];
    movie_clear_vram();
    saturn_vram_clear_banks(VRAM_ALL_BANKS);
    saturn_text_layers_clear(TEXT_LAYERS_ALL);
    saturn_stage_commit_video();
}

void saturn_movie_play(const char* path, s32 mode)
{
#ifdef VERSION_SATURN_PROTO
    if (mode != 0) {
        DMA_CpuMemCopy4(movie_save_area(), &saturn_work_area, sizeof(saturn_work_area.movie) / 4);
        while (DMA_CpuResult() == DMA_BUSY) { }
    }
    saturn_movie_timer_flag = 0;
    saturn_sound_change_map(0);
#else
    s16 top = mode != 0 ? MOVIE_INGAME_TOP : 0;
    saturn_movie_timer_flag = 0;
    saturn_sound_enable_sequences();
    saturn_sound_change_map_quiet(0);
#endif
    saturn_movie_x_offset = 0;
    saturn_movie_top = MOVIE_TOP;
    CPK_SetCpu(CPK_CPU_DUAL);
    movie_clear_vram();
    movie_video_setup();
    while (CPK_Init() != 1) { }
    CPK_SetErrFunc(movie_error, NULL);
    saturn_cd_file_id = GFS_NameToId(path);
    do {
        saturn_cd_handle = (u32)GFS_Open(saturn_cd_file_id);
    } while (saturn_cd_handle == 0);
    saturn_movie_para.work_addr = MOVIE_WORK;
    saturn_movie_para.work_size = MOVIE_WORK_BYTES;
    saturn_movie_para.buf_addr = MOVIE_RING;
    saturn_movie_para.buf_size = MOVIE_RING_BYTES;
    saturn_movie_para.pcm_addr = (u16*)MOVIE_PCM_BUFFER;
    saturn_movie_para.pcm_size = MOVIE_PCM_SAMPLES;
    do {
        saturn_movie_handle = CPK_CreateGfsMovie(&saturn_movie_para, (GfsHn)saturn_cd_handle);
    } while (saturn_movie_handle == NULL);
    CPK_SetColor(saturn_movie_handle, CPK_COLOR_24BIT);
    CPK_SetTrModeCd(saturn_movie_handle, CPK_TRMODE_CPU);
    CPK_SetTrModePcm(saturn_movie_handle, CPK_TRMODE_CPU);
    CPK_SetLoadNum(saturn_movie_handle, MOVIE_LOAD_SECTORS);
    CPK_PreloadHeader(saturn_movie_handle);
    saturn_movie_header = CPK_GetHeader(saturn_movie_handle);
    saturn_movie_width = saturn_movie_header->width;
    saturn_movie_height = saturn_movie_header->height;
#ifdef VERSION_SATURN_PROTO
    movie_set_window(0, 0);
#else
    movie_set_window(0, top);
#endif
    CPK_SetDecodeAddr(saturn_movie_handle, MOVIE_DECODE, MOVIE_LINE_BYTES);
    CPK_SetStartTrgSize(saturn_movie_handle, MOVIE_START_TRIGGER_BYTES);
    SHADOW16(0x00) |= TVMD_DISPLAY_ON;
#ifndef VERSION_SATURN_PROTO
    SHADOW32(0x70) = 0;
    SHADOW32(0x74) = 0;
#endif
    CPK_SetVolume(saturn_movie_handle, MOVIE_VOLUME);
    CPK_SetSilenceRate(saturn_movie_handle, MOVIE_SILENCE_RATE);
    CPK_Start(saturn_movie_handle);
    saturn_movie_active = 1;
    saturn_thread_sleep(2);
    while (!(saturn_pad_held & PAD_START)) {
        CPK_Task(saturn_movie_handle);
        saturn_thread_sleep(1);
        if (CPK_IsDispTime(saturn_movie_handle) == 1) {
            saturn_movie_timer_flag = 0;
            while (saturn_movie_timer_flag == 0) { }
#ifdef VERSION_SATURN_PROTO
            DMA_ScuMemCopy((void*)VDP2_VRAM, MOVIE_DECODE, MOVIE_DECODE_BYTES);
#else
            DMA_ScuMemCopy((void*)VDP2_VRAM, MOVIE_DECODE, mode != 0 ? MOVIE_INGAME_DECODE_BYTES : MOVIE_DECODE_BYTES);
#endif
            while (DMA_CpuResult() == DMA_BUSY) { }
            CPK_CompleteDisp(saturn_movie_handle);
        }
        if (CPK_GetPlayStatus(saturn_movie_handle) == CPK_STAT_PLAY_END)
            break;
    }
#ifndef VERSION_SATURN_PROTO
    saturn_sound_forget_stage_map();
#endif
    movie_restore_screen();
#ifdef VERSION_SATURN_PROTO
    if (mode != 0) {
        DMA_CpuMemCopy4(&saturn_work_area, movie_save_area(), sizeof(saturn_work_area.movie) / 4);
        while (DMA_CpuResult() == DMA_BUSY) { }
    }
#endif
}
