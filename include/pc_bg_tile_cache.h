#ifndef MMX4_PC_BG_TILE_CACHE_H
#define MMX4_PC_BG_TILE_CACHE_H

#include <stdint.h>

#define PC_TILEMAP_SIZE (0x300 + 0x300)

void mmx4_pc_write_bg_tile_cache(int32_t layer, int32_t row, int32_t column, uint16_t tile);
uint8_t mmx4_pc_read_bg_tilemap(const uint8_t* tilemap, int32_t offset);

#endif
