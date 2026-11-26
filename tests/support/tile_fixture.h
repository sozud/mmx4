#ifndef MMX4_TESTS_TILE_FIXTURE_H
#define MMX4_TESTS_TILE_FIXTURE_H

#include "main/effects/effect_01_tile_animator.h"
#include "main/CB184.h"
#include "main/tile_effects.h"
#include "support/tile_effects.h"

static struct TileEffectRecord** tile_fixture_saved_table;
static u8* tile_fixture_saved_map;
static u16* tile_fixture_saved_pixels;
#ifdef MMX4_SATURN
static u32* tile_fixture_saved_cells;
#endif
static u8 tile_fixture_saved_width, tile_fixture_saved_height;
static u16 tile_fixture_saved_size;

static u8 tile_fixture_map[0x20];

static void tile_fixture_begin_layout(u8 width, u8 height)
{
    u32 i, j, k;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(records, 0, sizeof(records));
    tile_fixture_saved_table = tile_effect_tables[0];
    tile_fixture_saved_map = SP_BG_TILEMAP;
    tile_fixture_saved_pixels = SP_BG_TILE_PIXELS;
    tile_fixture_saved_width = layout_width;
    tile_fixture_saved_height = layout_height;
    tile_fixture_saved_size = layout_size;
    tile_effect_tables[0] = table;
    TEST_BG_TILE_PIXELS = (u8*)&pixels[1];
    memset(tile_fixture_map, 0, sizeof(tile_fixture_map));
    SP_BG_TILEMAP = tile_fixture_map;
#ifdef MMX4_SATURN
    tile_fixture_saved_cells = SP_BG_TILE_ATTRS;
    SP_BG_TILE_ATTRS = cells;
#endif
    layout_width = width;
    layout_height = height;
    layout_size = width * height;
    for (i = 0; i < 6; i++) {
        tiles[i] = 0xA120 + i;
        records[i].packed_count = 3;
        records[i].tiles = &tiles[i];
        table[i] = &records[i];
    }
    for (i = 0; i < COUNT(pixels); i++)
        pixels[i] = 0xBEEF;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                D_801441C8[i][j][k] = 0xCAFE;
}

static u32 tile_fixture_end(void)
{
    u32 i, j, k, cache = 0, screen = 0, last = 0;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                if (D_801441C8[i][j][k] != 0xCAFE) {
                    cache++;
                    last = (D_801441C8[i][j][k] - 0xA120) << 16 | (k & 15) << 20 | (j & 15) << 24;
                }
    for (i = 1; i < COUNT(pixels); i++)
        if (pixels[i] != 0xBEEF) {
            screen++;
            last = (u32)(pixels[i] - 0xA120) << 16 | (i - 1) % 16 << 20 | (i - 1) / 16 << 24;
        }
    tile_effect_tables[0] = tile_fixture_saved_table;
    SP_BG_TILEMAP = tile_fixture_saved_map;
    TEST_BG_TILE_PIXELS = (u8*)tile_fixture_saved_pixels;
#ifdef MMX4_SATURN
    SP_BG_TILE_ATTRS = tile_fixture_saved_cells;
#endif
    layout_width = tile_fixture_saved_width;
    layout_height = tile_fixture_saved_height;
    layout_size = tile_fixture_saved_size;
    return (cache & 0xFF) | (screen & 0xFF) << 8 | last;
}
static void tile_fixture_begin(void)
{
    tile_fixture_begin_layout(1, 1);
}
#define TILE_FIXTURE_WRITES(mode, count) ((TILE_CACHE_WRITTEN(mode) ? (count) : 0) | (TILE_SCREEN_WRITTEN(mode) ? (count) : 0) << 8)

#endif
