#include "test_runtime.h"
#include "main/1CF60.h"
u8 func_8002D7E4(struct PlayerObj*, s16, s16);
extern s32 func_8002CAF0(struct PlayerObj*, u8), func_8002CC34(struct PlayerObj*, u8), func_8002CD70(struct PlayerObj*, u8);
static const struct {
    u16 stage, width, height, block, map_y, map_x, tile_y, tile_x, tile;
    u32 attribute;
} probes[3] = {
    { 1, 28, 9, 33, 1, 22, 12, 6, 957, 0x03720021 },
    { 2, 25, 10, 24, 1, 7, 11, 13, 1060, 0x0406193E },
    { 3, 25, 10, 23, 4, 23, 15, 4, 1201, 0x049B253F },
};
static u8 map[768], expected_map[768];
static u16 tiles[34][16][16], expected_tiles[34][16][16];
static u32 attributes[1202], expected_attributes[1202];
static u32 barrier(u32 row)
{
    struct PlayerObj obj, expected, player_before = g_Player;
    struct EngineObj engine_before;
    u32 material = row % 3, direction = row / 3 % 4, edge = row / 12 % 2, seeded = row / 24, hit = material != 0 || direction == 3, i;
    s16 x = probes[material].map_x * 256 + probes[material].tile_x * 16 + (edge ? 15 : 0), y = probes[material].map_y * 256 + probes[material].tile_y * 16 + (edge ? 15 : 0), expected_x = 0x1357, expected_y = 0x2468;
    u8 code = probes[material].attribute, flags = seeded ? 0x80 : 0x10, expected_flags = flags;
    s32 result;
    engine_obj.stage = probes[material].stage;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    layout_width = probes[material].width;
    layout_height = probes[material].height;
    layout_size = layout_width * layout_height;
    memset(expected_map, 0, sizeof(expected_map));
    expected_map[probes[material].map_y * layout_width + probes[material].map_x] = probes[material].block;
    c_test_zero_words((u32*)expected_tiles, sizeof(expected_tiles) / 4);
    expected_tiles[probes[material].block][probes[material].tile_y][probes[material].tile_x] = probes[material].tile;
    c_test_zero_words(expected_attributes, COUNT(expected_attributes));
    expected_attributes[probes[material].tile] = probes[material].attribute;
    c_test_copy_words((u32*)map, (u32*)expected_map, sizeof(map) / 4);
    c_test_copy_words((u32*)tiles, (u32*)expected_tiles, sizeof(tiles) / 4);
    c_test_copy_words(attributes, expected_attributes, COUNT(attributes));
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.hp = 24;
    obj.x_pos.i.hi = x;
    obj.y_pos.i.hi = y;
    expected = obj;
    assert(func_8002D724(&obj, x, y) == code);
    c_test_same_words(&obj, &expected, sizeof(obj));
    assert(func_8002D7E4(&obj, x, y) == code);
    expected.unk6C = edge ? 15 : 0;
    expected.unk6E = edge ? 15 : 0;
    D_8013B7DC = flags;
    D_8013B800 = expected_x;
    D_8013B804 = expected_y;
    if (hit) {
        expected_flags |= direction == 0 ? 2 : direction == 1 ? 1
            : direction == 2                                  ? 4
                                                              : 8;
        if (direction == 0)
            expected_x = 16 - expected.unk6C;
        else if (direction == 1)
            expected_x = ~expected.unk6C;
        else if (direction == 2)
            expected_y = 16 - expected.unk6E;
        else
            expected_y = -expected.unk6E;
    }
    if (direction == 0)
        result = func_8002CAF0(&obj, code);
    else if (direction == 1)
        result = func_8002CC34(&obj, code);
    else if (direction == 2)
        result = func_8002CD70(&obj, code);
    else
        result = func_8002D1F8(&obj, code, 0);
    assert(result == (hit ? -1 : 0) && D_8013B7DC == expected_flags && D_8013B800 == expected_x && D_8013B804 == expected_y);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(map, expected_map, sizeof(map));
    c_test_same_words(tiles, expected_tiles, sizeof(tiles));
    c_test_same_words(attributes, expected_attributes, sizeof(attributes));
    assert(SP_BG_TILEMAP == map && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && layout_width == probes[material].width && layout_height == probes[material].height && layout_size == layout_width * layout_height);
    for (i = 0; i < 3; i++)
        assert(probes[i].attribute == (i == 0 ? 0x03720021 : i == 1 ? 0x0406193E
                                                                    : 0x049B253F));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "original_stage_tiles_one_way_and_spiked_barriers_four_directions_pixel_edges", NULL, NULL, 48, barrier } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 48;
