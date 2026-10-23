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

typedef void (*SaturnMovieScuMask)(s32 mask, s32 bits);
extern SaturnMovieScuMask saturn_bios_change_scu_mask;
extern u8 saturn_movie_active;
extern u8 saturn_vdp2_ram_control_config[6];
void INT_SetScuFunc(s32 vector, void* function);
void DMA_ScuSetPrm(struct SaturnMovieDma* parameters, u32 channel);
void DMA_ScuStart(u32 channel);
u32 DMA_ScuResult(void);

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

static void movie_restore_screen(void)
{
    struct SaturnMovieDma dma;
    u32 zero;
    s32 i;
    saturn_movie_active = 0;
    SHADOW16(0x00) &= ~TVMD_DISPLAY_ON;
    SHADOW16(0x9A) = 0;
    SHADOW16(0xD0) = 0;
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
    SHADOW16(0x2A) = 1;
    SHADOW16(0x30) = 0;
    SHADOW16(0x32) = 0;
    SHADOW16(0x34) = 0;
    SHADOW16(0x36) = 0;
    SHADOW16(0x3A) = 0x15;
    SHADOW16(0x40) = 0x3030;
    SHADOW16(0x42) = 0x3030;
    SHADOW16(0x3C) |= 1;
    SHADOW16(0x44) = 0x3434;
    SHADOW16(0x46) = 0x3434;
    SHADOW16(0x3C) |= 0x10;
    SHADOW16(0x48) = 0x3838;
    SHADOW16(0x4A) = 0x3838;
    SHADOW16(0x3C) |= 0x100;
    SHADOW16(0x4C) = 0x1F1F;
    SHADOW16(0x4E) = 0x1F1F;
    SHADOW16(0x9A) = 0;
    SHADOW32(0xA0) = 0;
    for (i = 0; i < 8; i++)
        SHADOW16(0x10 + i * 2) = saturn_movie_cycle_patterns[i];
    zero = 0;
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
    saturn_vram_clear_banks(VRAM_ALL_BANKS);
    saturn_text_layers_clear(TEXT_LAYERS_ALL);
    saturn_stage_commit_video();
}

void saturn_movie_play(const char* path, s32 mode)
{
    movie_restore_screen();
}
