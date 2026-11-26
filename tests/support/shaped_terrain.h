#ifndef MMX4_TESTS_SHAPED_TERRAIN_H
#define MMX4_TESTS_SHAPED_TERRAIN_H

#define SHAPED_OPEN 0
#define SHAPED_COLUMNS_BELOW(n) (0x100 | (n))
#define SHAPED_COLUMNS_FROM(n) (0x200 | (n))
#define SHAPED_ROWS_BELOW(n) (0x300 | (n))
#define SHAPED_ROWS_FROM(n) (0x400 | (n))
static u8 shaped_map[256];
static u16 shaped_tiles[2][16][16];
static u32 shaped_attributes[2];

static void shaped_terrain(u32 attribute, u32 shape)
{
    u32 column, row, n = shape & 0xFF, solid;
    memset(shaped_map, 1, sizeof(shaped_map));
    memset(shaped_tiles, 0, sizeof(shaped_tiles));
    for (row = 0; row < 16; row++)
        for (column = 0; column < 16; column++) {
            switch (shape >> 8) {
            case 1:
                solid = column < n;
                break;
            case 2:
                solid = column >= n;
                break;
            case 3:
                solid = row < n;
                break;
            case 4:
                solid = row >= n;
                break;
            default:
                solid = 0;
                break;
            }
            shaped_tiles[1][row][column] = solid;
        }
    shaped_attributes[0] = 0;
    shaped_attributes[1] = C_TEST_PSX_WORD(attribute);
    SP_BG_TILEMAP = shaped_map;
    TEST_BG_TILE_PIXELS = (u8*)shaped_tiles;
    TEST_BG_TILE_ATTRS = (u8*)shaped_attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
}

#endif
