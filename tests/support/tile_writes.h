#ifndef MMX4_TESTS_TILE_WRITES_H
#define MMX4_TESTS_TILE_WRITES_H

#include "main/tile_effects.h"

extern struct TileEffectRecord** tile_effect_tables[26];
static u8 tile_write_map[3 * 1024];
static u16 tile_write_pixels[256], tile_write_expected[256];
static u32 tile_write_count, tile_write_bad;
static u32 tile_write_cells[0x4000];
static u8* tile_write_saved_cells;
#ifndef MMX4_SATURN
static u16 tile_write_cache[3][32][32];
#endif
static u8 *tile_write_saved_map, *tile_write_saved_pixels;
static u8 tile_write_saved_width, tile_write_saved_height;
static u16 tile_write_saved_size;
static u8 tile_write_width = 32, tile_write_height = 32;

static void tile_writes_begin(void)
{
    memset(tile_write_map, 0, sizeof(tile_write_map));
    memset(tile_write_pixels, 0, sizeof(tile_write_pixels));
    memset(tile_write_expected, 0, sizeof(tile_write_expected));
    tile_write_count = tile_write_bad = 0;
    tile_write_saved_map = SP_BG_TILEMAP;
    tile_write_saved_pixels = TEST_BG_TILE_PIXELS;
    tile_write_saved_width = layout_width;
    tile_write_saved_height = layout_height;
    tile_write_saved_size = layout_size;
    SP_BG_TILEMAP = tile_write_map;
    TEST_BG_TILE_PIXELS = (u8*)tile_write_pixels;
    layout_width = tile_write_width;
    layout_height = tile_write_height;
    layout_size = 1024;
    tile_write_saved_cells = TEST_BG_TILE_ATTRS;
    TEST_BG_TILE_ATTRS = (u8*)tile_write_cells;
#ifndef MMX4_SATURN
    memset(D_801441C8, 0, sizeof(D_801441C8));
    memset(tile_write_cache, 0, sizeof(tile_write_cache));
#endif
}

static void tile_writes_begin_wide(void)
{
    tile_write_width = 64;
    tile_write_height = 16;
    tile_writes_begin();
}

static void tile_writes_expect(u32 id, s32 x_offset, s32 y_offset, u32 apply)
{
    struct TileEffectRecord* record = tile_effect_tables[engine_obj.stage * 2 + engine_obj.substage][id];
    while (1) {
        s16 x = (s16)(record->x + x_offset), y = (s16)(record->y + y_offset);
        s16 bx = background_objects[record->layer].x_pos.i.hi, by = background_objects[record->layer].y_pos.i.hi;
        u32 j;
        for (j = 0; j < (u32)(record->packed_count >> 1); j++) {
            u32 visible = bx - 0x20 <= x && bx + 0x160 > x && by - 0x20 <= y && by + 0x110 > y;
            u16 column = (u16)(x / 16), row = (u16)(y / 16);
            tile_write_bad |= !(x >= 0 && y >= 0 && column < tile_write_width * 16 && row < tile_write_height * 16 && record->layer < 3);
#ifdef MMX4_SATURN
            if (apply || visible)
                tile_write_expected[(row & 15) * 16 + (column & 15)] = record->tiles[j];
#else
            if (apply)
                tile_write_expected[(row & 15) * 16 + (column & 15)] = record->tiles[j];
            if (visible)
                tile_write_cache[record->layer][row & 31][column & 31] = record->tiles[j];
#endif
            tile_write_count += apply || visible;
            if (record->packed_count & 1)
                x += 0x10;
            else
                y += 0x10;
        }
        if (!record->has_next)
            break;
        record++;
    }
}

static u32 tile_writes_end(void)
{
    static const u32 zero_map[sizeof(tile_write_map) / 4];
    u32 i, hash = tile_write_count;
    assert(!tile_write_bad);
    c_test_same_words(tile_write_pixels, tile_write_expected, sizeof(tile_write_pixels));
    c_test_same_words(tile_write_map, zero_map, sizeof(tile_write_map));
    for (i = 0; i < COUNT(tile_write_pixels); i++)
        hash = hash * 33 + tile_write_pixels[i];
    TEST_BG_TILE_ATTRS = tile_write_saved_cells;
#ifndef MMX4_SATURN
    c_test_same_words(D_801441C8, tile_write_cache, sizeof(tile_write_cache));
#endif
    SP_BG_TILEMAP = tile_write_saved_map;
    TEST_BG_TILE_PIXELS = tile_write_saved_pixels;
    layout_width = tile_write_saved_width;
    layout_height = tile_write_saved_height;
    layout_size = tile_write_saved_size;
    tile_write_width = tile_write_height = 32;
    return hash;
}

#endif
