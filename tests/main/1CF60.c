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
    expected_attributes[probes[material].tile] = TEST_DISC32(probes[material].attribute);
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
#ifdef MMX4_SATURN
#define BARRIER_NO_HIT (direction == 2 ? (s32)code : 0)
#else
#define BARRIER_NO_HIT 0
#endif
    assert(result == (hit ? -1 : BARRIER_NO_HIT) && D_8013B7DC == expected_flags && D_8013B800 == expected_x && D_8013B804 == expected_y);
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

#include "support/shaped_terrain.h"
s32 func_8002D1F8(struct PlayerObj*, u8, s32);
s32 func_8002D41C(struct PlayerObj*, s32, s32);
s32 func_8002D6BC(struct PlayerObj*, u8);
void func_8002C99C(struct PlayerObj*);
static const struct {
    u8 check, code, flags;
    s8 result, displacement, climbable, spikes;
} codes[] = {
    { 0, 0x3A, 2, -1, 16 - 5, 0, 0 },
    { 1, 0x3A, 1, -1, ~5, 0, 0 },
    { 2, 0x3A, 4, -1, 16 - 7, 0, 0 },
    { 3, 0x22, 8, -1, -7, 0, 0 },
    { 3, 0x39, 8, -1, -7, 0, 0 },
    { 3, 0x3A, 8, -1, -7, 0, 0 },
    { 4, 0x3E, 0, -1, 0, 0, 1 },
    { 4, 0x3F, 0, -1, 0, 0, 1 },
    { 4, 0x3A, 0, -1, 0, 0, 0 },
    { 5, 0x3E, 0, -1, 0, 0, 1 },
    { 5, 0x3F, 0, -1, 0, 0, 1 },
    { 5, 0x21, 0, -1, 0, 0, 0 },
    { 5, 0x22, 0, -1, 0, 0, 0 },
    { 5, 0x3A, 0, -1, 0, 0, 0 },
    { 5, 0x40, 0, 0, 0, 0, 0 },
    { 6, 0x3A, 0, -1, 0, 1, 0 },
    { 6, 0x3E, 0, -1, 0, 0, 1 },
    { 6, 0x3F, 0, -1, 0, 0, 1 },
};
static u32 tile_code(u32 row)
{
    struct PlayerObj obj, expected;
    s32 result;
    memset(&obj, 0, sizeof(obj));
    obj.unk6C = 5;
    obj.unk6E = 7;
    obj.wall_climbable = 0x55;
    expected = obj;
    if (codes[row].check == 6)
        expected.wall_climbable = codes[row].climbable;
    expected.touching_spikes = codes[row].spikes;
    D_8013B7DC = 0x80;
    D_8013B800 = D_8013B804 = 0x1234;
    switch (codes[row].check) {
    case 0:
        result = func_8002CAF0(&obj, codes[row].code);
        break;
    case 1:
        result = func_8002CC34(&obj, codes[row].code);
        break;
    case 2:
        result = func_8002CD70(&obj, codes[row].code);
        break;
    case 3:
        result = func_8002D1F8(&obj, codes[row].code, 0);
        break;
    case 4:
    case 5:
        result = func_8002D41C(&obj, codes[row].code, codes[row].check - 4);
        break;
    default:
        result = func_8002D6BC(&obj, codes[row].code);
        break;
    }
    assert(result == codes[row].result && D_8013B7DC == (0x80 | codes[row].flags));
    assert(D_8013B800 == (codes[row].check < 2 ? codes[row].displacement : 0x1234));
    assert(D_8013B804 == (codes[row].check == 2 || codes[row].check == 3 ? codes[row].displacement : 0x1234));
    c_test_same_words(&obj, &expected, sizeof(obj));
    return 1;
}

static u32 terrain_probe(u32 row)
{
    struct PlayerObj obj, expected;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = 40;
    obj.y_pos.i.hi = 40;
    obj.unk6C = 3;
    obj.unk6E = 4;
    expected = obj;
    D_8013B7DC = 0;
    D_8013B800 = D_8013B804 = 0;
    D_8013B7E0 = 8;
    D_8013B7E4 = 16;
    D_8013B7E8 = D_8013B7EC = 0;
    D_8013B7F0 = D_8013B7F4 = D_8013B7FC = 40;
    D_8013B7F8 = 40;
    switch (row) {
    case 0:
        shaped_terrain(0x38, SHAPED_ROWS_FROM(2));
        assert(func_8002D5E4(&obj, 40) == -1);
        expected.wall_climbable = 1;
        break;
    case 1:
        shaped_terrain(0x38, SHAPED_COLUMNS_BELOW(3));
        D_8013B7E4 = 8;
        D_8013B804 = 5;
        D_8013B7F8 = 200;
        func_8002C99C(&obj);
        expected.y_pos.i.hi = 45;
        expected.wall_climbable = 1;
        break;
    case 2:
        shaped_terrain(9, SHAPED_COLUMNS_FROM(3));
        D_8013B7E0 = 16;
        func_8002CDD4(&obj);
        expected.y_pos.i.hi = 56;
        expected.unk6C = 40 & 15;
        expected.unk6E = 72 & 15;
        break;
    default:
        shaped_terrain(0x38, SHAPED_ROWS_FROM(0));
        assert(func_8002D7E4(&obj, 40, -16) == 0);
        break;
    }
    assert(D_8013B7DC == 0);
    c_test_same_words(&obj, &expected, sizeof(obj));
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "original_stage_tiles_one_way_and_spiked_barriers_four_directions_pixel_edges", NULL, NULL, 48, barrier },
    { "tile_codes", NULL, NULL, COUNT(codes), tile_code },
    { "terrain_probes", NULL, NULL, 4, terrain_probe },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 48 + COUNT(codes) + 4;
