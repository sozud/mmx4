#ifndef MMX4_TESTS_PLAYER_GFX_ARCHIVE_H
#define MMX4_TESTS_PLAYER_GFX_ARCHIVE_H

static struct {
    u32 root[8];
    u32 bank[256];
    u16 stream[24];
} gfx_archive;

static void gfx_archive_fill(void)
{
    u32 i;
    memset(&gfx_archive, 0, sizeof(gfx_archive));
    gfx_archive.root[7] = 0x20;
    for (i = 0; i < 256; i++)
        gfx_archive.bank[i] = 1 << 20 | (u32)((u8*)gfx_archive.stream - (u8*)gfx_archive.bank);
    for (i = 1; i <= 16; i++)
        gfx_archive.stream[i] = 0x1100;
    gfx_archive.stream[17] = 0x7000;
    gfx_archive.stream[18] = 0x1100;
    gfx_archive.stream[19] = 0x1001;
    gfx_archive.stream[21] = 2;
}

#ifdef MMX4_SATURN
#define GFX_QUEUE_RESET() 0
#define GFX_QUEUED() 0u
#define GFX_ONE_UPLOAD 0u
#define GFX_DECODED_FRAME(frame) 0xFFu
#else
#define GFX_QUEUE_RESET() (vram_rect_ptr = vram_rect_ptrs)
#define GFX_QUEUED() (u32)(vram_rect_ptr - vram_rect_ptrs)
#define GFX_ONE_UPLOAD 0x10000u
#define GFX_DECODED_FRAME(frame) (u32)(frame)
#endif

#endif
