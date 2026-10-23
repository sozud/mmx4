#include "common.h"
#include "saturn/platform.h"

#define CACHE_THROUGH 0x20000000
#define SLAVE_TRIGGER (*(volatile u16*)0x21000000)
#define SLAVE_TRIGGER_VALUE 0xFFFF
#define TEXTURE_FRAME_NEXT 71
#define TEXTURE_FRAME_LOADED 72
#define TEXTURE_FRAMES 56
#define TEXTURE_SLOT 64
#define TEXTURE_SIZE_MASK 0xFFF00000
#define TEXTURE_SIZE_SHIFT 13
#define TEXTURE_OFFSET_MASK 0xFFFFF
#define TEXTURE_VRAM 0x25C00000
#define TEXTURE_SLOT_SHIFT 3
#define TEXTURE_TRANSFER_ADD 0x100

typedef void (*SaturnGfxJob)(void);
extern SaturnGfxJob saturn_gfx_job;
extern u32 saturn_gfx_source;
extern u32 saturn_gfx_destination;
extern u32 saturn_gfx_staging_cursor;
extern u8 saturn_gfx_staging[];
void saturn_gfx_decompress_entry(void);
void saturn_transfer_enqueue(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile(u32 add_a, u32 add_b, u32 attribute_index);

void saturn_update_object_texture(u8* object)
{
    u8* frames;
    u32 descriptor;
    u32 size;
    u32 source;
    while (*(volatile SaturnGfxJob*)((u32)&saturn_gfx_job + CACHE_THROUGH) != 0) {
    }
    if ((s8)object[TEXTURE_FRAME_LOADED] == (s8)object[TEXTURE_FRAME_NEXT]) {
        return;
    }
    frames = *(u8**)(object + TEXTURE_FRAMES);
    descriptor = *(u32*)(frames + object[TEXTURE_FRAME_NEXT] * 4);
    size = (descriptor & TEXTURE_SIZE_MASK) >> TEXTURE_SIZE_SHIFT;
    source = (descriptor & TEXTURE_OFFSET_MASK) + (u32)frames;
    while (*(volatile SaturnGfxJob*)((u32)&saturn_gfx_job + CACHE_THROUGH) != 0) {
    }
    saturn_gfx_source = source;
    saturn_gfx_destination = saturn_gfx_staging_cursor + (u32)saturn_gfx_staging;
    saturn_gfx_job = saturn_gfx_decompress_entry;
    SLAVE_TRIGGER = SLAVE_TRIGGER_VALUE;
    saturn_transfer_profile(TEXTURE_TRANSFER_ADD, 1, 1);
    saturn_transfer_enqueue(saturn_gfx_staging_cursor + (u32)saturn_gfx_staging,
        TEXTURE_VRAM | ((u32) * (u16*)(object + TEXTURE_SLOT) << TEXTURE_SLOT_SHIFT), size);
    saturn_gfx_staging_cursor += size;
}
