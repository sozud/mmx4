#include "pc_bg_tile_cache.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern uint8_t D_801441BC[4];
extern uint8_t D_801441C0[8];
extern uint16_t D_801441C8[3][32][32];
extern uint8_t D_80141BE8[PC_TILEMAP_SIZE];
extern uint16_t g_FilterAmountG;
extern uint16_t D_80141F70[0x800];

uint8_t mmx4_pc_read_bg_tilemap(const uint8_t* tilemap, int32_t offset)
{
    if (tilemap == NULL)
        return 0;

    if (tilemap == D_80141BE8 && offset >= (0x80141F70 - 0x80141BE8) && offset < (0x80141F70 - 0x80141BE8) + (int32_t)sizeof(D_80141F70)) {
        int32_t palette_offset = offset - (0x80141F70 - 0x80141BE8);
        return (uint8_t)(D_80141F70[palette_offset / 2] >> ((palette_offset & 1) * 8));
    }
    if (offset >= 0 && (tilemap != D_80141BE8 || offset < PC_TILEMAP_SIZE))
        return tilemap[offset];

    if (tilemap == D_80141BE8 && offset >= -2 && offset < 0)
        return (uint8_t)(g_FilterAmountG >> ((offset + 2) * 8));
    fprintf(stderr, "MMX4 PC: unmapped original background tilemap read: %d\n", offset);
    abort();
}

void mmx4_pc_write_bg_tile_cache(int32_t layer, int32_t row, int32_t column, uint16_t tile)
{
    int32_t offset = ((layer * 32 + row) * 32 + column) * (int32_t)sizeof(tile);

    if (offset >= 0 && offset <= (int32_t)sizeof(D_801441C8) - (int32_t)sizeof(tile)) {
        memcpy((uint8_t*)D_801441C8 + offset, &tile, sizeof(tile));
    } else if (offset >= -(int32_t)sizeof(D_801441C0) && offset <= -2) {
        int32_t index = (int32_t)sizeof(D_801441C0) + offset;
        D_801441C0[index] = tile & 0xFF;
        D_801441C0[index + 1] = tile >> 8;
    } else if (offset >= -(int32_t)(sizeof(D_801441BC) + sizeof(D_801441C0)) && offset <= -10) {
        int32_t index = (int32_t)(sizeof(D_801441BC) + sizeof(D_801441C0)) + offset;
        D_801441BC[index] = tile & 0xFF;
        D_801441BC[index + 1] = tile >> 8;
    } else {
        fprintf(stderr, "MMX4 PC: unmapped original background tile-cache write: %d\n", offset);
        abort();
    }
}
