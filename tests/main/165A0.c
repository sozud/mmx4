#include "test_runtime.h"
#include "main/165A0.h"

static u32 tile_case(u32 mode)
{
    struct BackgroundObj before[3];
    u32 i;
    memset(background_objects, 0, sizeof(background_objects));
    if (mode == 2)
        for (i = 0; i < 3; i++)
            background_objects[i].y_pos.i.hi = -512;
    if (mode == 1)
        for (i = 0; i < 3; i++)
            background_objects[i].x_pos.i.hi = -512;
    memcpy(before, background_objects, sizeof(before));
    for (i = 0; i < sizeof(D_801441C8) / 4; i++)
        ((u32*)D_801441C8)[i] = 0x42424242;
    func_800261B4(mode == 0 ? -32 : 0);
    for (i = 0; i < sizeof(before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)before)[i]);
    for (i = 0; i < sizeof(D_801441C8) / 4; i++)
        assert(((u32*)D_801441C8)[i] == 0x42424242);
    return D_801441C8[0][0][0] | ((u32)D_801441C8[2][31][31] << 16);
}
static const u32 background_negative_tile_guards_cases_expected[] = { 0x42424242u, 0x42424242u, 0x42424242u };

void func_800267D4(s32 input);
extern void func_80026CEC(s32 arg0);

void func_800270F8(s32 x, s32 y, s32 tile_x, s32 tile_y);
void func_800265B4(void);

#define PACKETS 96
#define MAP_WIDTH 40
#define MAP_ROWS 34

static SPRT_16 packets[PACKETS], expected_packets[PACKETS];
static DR_TPAGE expected_pages[2][6][8];
static struct DrawInfo draw, expected_draw;
static struct BackgroundObj expected_backgrounds[3];
static u32 descriptors[7][256];
#define DESCRIPTOR(b, t)                                              \
    (((0x7900u + (b)*17 + (t) / 16) << 16) | (((t) ^ ((b)*19)) & 255) \
        | (((((t) % 16 + 2 * ((t) / 16) + (b)) & 7) == 0)             \
                ? (0x15 + (((t) / 16 + (b)) & 7)) << 8                \
                : 0))
#define DESCRIPTOR_ROW(b, y)                                    \
    DESCRIPTOR(b, (y)*16), DESCRIPTOR(b, (y)*16 + 1),           \
        DESCRIPTOR(b, (y)*16 + 2), DESCRIPTOR(b, (y)*16 + 3),   \
        DESCRIPTOR(b, (y)*16 + 4), DESCRIPTOR(b, (y)*16 + 5),   \
        DESCRIPTOR(b, (y)*16 + 6), DESCRIPTOR(b, (y)*16 + 7),   \
        DESCRIPTOR(b, (y)*16 + 8), DESCRIPTOR(b, (y)*16 + 9),   \
        DESCRIPTOR(b, (y)*16 + 10), DESCRIPTOR(b, (y)*16 + 11), \
        DESCRIPTOR(b, (y)*16 + 12), DESCRIPTOR(b, (y)*16 + 13), \
        DESCRIPTOR(b, (y)*16 + 14), DESCRIPTOR(b, (y)*16 + 15)
#define DESCRIPTOR_BLOCK(b)                                                                            \
    {                                                                                                  \
        DESCRIPTOR_ROW(b, 0), DESCRIPTOR_ROW(b, 1), DESCRIPTOR_ROW(b, 2), DESCRIPTOR_ROW(b, 3),        \
            DESCRIPTOR_ROW(b, 4), DESCRIPTOR_ROW(b, 5), DESCRIPTOR_ROW(b, 6), DESCRIPTOR_ROW(b, 7),    \
            DESCRIPTOR_ROW(b, 8), DESCRIPTOR_ROW(b, 9), DESCRIPTOR_ROW(b, 10), DESCRIPTOR_ROW(b, 11),  \
            DESCRIPTOR_ROW(b, 12), DESCRIPTOR_ROW(b, 13), DESCRIPTOR_ROW(b, 14), DESCRIPTOR_ROW(b, 15) \
    }
static const u32 expected_descriptors[7][256] = {
    DESCRIPTOR_BLOCK(0),
    DESCRIPTOR_BLOCK(1),
    DESCRIPTOR_BLOCK(2),
    DESCRIPTOR_BLOCK(3),
    DESCRIPTOR_BLOCK(4),
    DESCRIPTOR_BLOCK(5),
    DESCRIPTOR_BLOCK(6),
};
#undef DESCRIPTOR_BLOCK
#undef DESCRIPTOR_ROW
#undef DESCRIPTOR
static u8 tilemap[3][MAP_ROWS][MAP_WIDTH];
static u8 expected_tilemap[3][MAP_ROWS][MAP_WIDTH];
static s32 heads[8], tails[8];
static u32 emitted, buffer_index, layer_index;

struct ExpectedTile {
    s16 x, y;
    u32 attributes;
};
static struct ExpectedTile chunks[6][48];
static u32 chunk_counts[6];

static void prepare(u32 buffer, u32 layer)
{
    u32 b, i, j;
    buffer_index = buffer;
    layer_index = layer;
    emitted = 0;
    memset(packets, 0x5A, sizeof(packets));
    for (i = 0; i < PACKETS; i++) {
        setSprt16(&packets[i]);
        setShadeTex(&packets[i], 1);
        setSemiTrans(&packets[i], i & 1);
        setaddr(&packets[i], 0x00654321);
    }
    memcpy(expected_packets, packets, sizeof(packets));
    memset(&draw, 0x53, sizeof(draw));
    setaddr(&draw.ordering_table.unk3, 0x00543210);
    setaddr(&draw.ordering_table.unk5[2], 0x00432100);
    expected_draw = draw;
    cur_draw_info = &draw;
    memset(D_80171EB0, 0x64, sizeof(D_80171EB0));
    for (b = 0; b < 2; b++)
        for (i = 0; i < 6; i++)
            for (j = 0; j < 8; j++) {
                setDrawTPage(&D_80171EB0[b][i][j], 0, 0, 0x15 + j);
                setaddr(&D_80171EB0[b][i][j], 0x00321000);
            }
    memcpy(expected_pages, D_80171EB0, sizeof(expected_pages));
    memset(background_objects, 0x27, sizeof(background_objects));
    background_objects[layer].unk4A = 3;
    background_objects[layer].unk4B = 7;
    memcpy(expected_backgrounds, background_objects, sizeof(expected_backgrounds));
    memset(tilemap, 0, sizeof(tilemap));
    memcpy(descriptors, expected_descriptors, sizeof(descriptors));
    for (i = 0; i < 8; i++)
        heads[i] = tails[i] = -1;
    memset(chunk_counts, 0, sizeof(chunk_counts));
    SP_DRAW_BUFFER = buffer;
    SP_CUR_BG_INDEX = layer;
    SP_BG_BLOCK = 1;
    SP_BG_PRIM_CURSOR = &packets[1];
    SP_BG_SPRITE_COUNT = 41;
    SP_BG_TILEMAP = (u8*)tilemap;
    TEST_BG_TILE_ATTRS = (u8*)descriptors;
    layout_width = MAP_WIDTH;
    layout_size = MAP_WIDTH * MAP_ROWS;
    func_800267D4(layer);
}

static void expect_tile(s32 x, s32 y, u32 attributes)
{
    u32 index, bucket;
    if (((attributes >> 8) & 255) == 0)
        return;
    index = ++emitted;
    assert(index < PACKETS - 1);
    bucket = ((attributes >> 8) & 255) - 0x15;
    assert(bucket < 8);
    expected_packets[index].x0 = x;
    expected_packets[index].y0 = y;
    expected_packets[index].u0 = (attributes & 15) * 16;
    expected_packets[index].v0 = attributes & 0xF0;
    expected_packets[index].clut = attributes >> 16;
    if (heads[bucket] < 0)
        heads[bucket] = index;
    else
        setaddr(&expected_packets[tails[bucket]], &packets[index]);
    tails[bucket] = index;
}

static void expect_rectangle(s32 x, s32 y, u32 tx, u32 ty,
    u32 width, u32 height, u32 block)
{
    u32 r, c;
    for (r = 0; r < height; r++)
        for (c = 0; c < width; c++)
            expect_tile(x + c * 16, y + r * 16,
                expected_descriptors[block][(ty + r) * 16 + tx + c]);
}

static u32 finish(s32 emit_lists)
{
    u32 bucket;
    assert(SP_BG_PRIM_CURSOR == &packets[emitted + 1]);
    assert(SP_BG_SPRITE_COUNT == 41);
    assert(SP_DRAW_BUFFER == buffer_index && SP_CUR_BG_INDEX == layer_index);
    assert(cur_draw_info == &draw);
    assert(SP_BG_TILEMAP == (u8*)tilemap);
    assert(TEST_BG_TILE_ATTRS == (u8*)descriptors);
    for (bucket = 0; bucket < 8; bucket++)
        if (heads[bucket] >= 0) {
            setaddr(&expected_pages[buffer_index][layer_index][bucket], &packets[heads[bucket]]);
            setaddr(&expected_packets[tails[bucket]], getaddr(&expected_draw.ordering_table.unk3));
            setaddr(&expected_draw.ordering_table.unk3, &D_80171EB0[buffer_index][layer_index][bucket]);
        }
    if (emit_lists)
        func_80026894(layer_index);
#define CHECK_WORDS(actual, expected) \
    assert(c_test_word_difference((const u32*)(actual), (const u32*)(expected), sizeof(*(actual)) / 4) == 0)
    CHECK_WORDS(&packets, &expected_packets);
    CHECK_WORDS(&D_80171EB0, &expected_pages);
    CHECK_WORDS(&draw, &expected_draw);
    CHECK_WORDS(&background_objects, &expected_backgrounds);
    CHECK_WORDS(&descriptors, &expected_descriptors);
    CHECK_WORDS(&tilemap, &expected_tilemap);
#undef CHECK_WORDS
    return 1;
}

static const struct Rectangle {
    u8 width, height, tx, ty, repeats;
} rectangles[] = {
    { 0, 0, 0, 0, 1 },
    { 0, 3, 2, 4, 1 },
    { 5, 0, 1, 6, 1 },
    { 1, 1, 0, 0, 1 },
    { 1, 1, 15, 15, 1 },
    { 1, 1, 7, 0, 1 },
    { 8, 4, 4, 11, 1 },
    { 16, 16, 0, 0, 1 },
    { 16, 8, 0, 0, 2 },
};

static u32 test_rectangle(u32 row)
{
    const struct Rectangle* rect = &rectangles[row / 6];
    u32 repeat;
    prepare(row % 2, row / 2 % 3);
    memcpy(expected_tilemap, tilemap, sizeof(tilemap));
    SP_BG_BLOCK_WIDTH = rect->width;
    SP_BG_BLOCK_HEIGHT = rect->height;
    for (repeat = 0; repeat < rect->repeats; repeat++) {
        SP_BG_BLOCK = repeat + 1;
        expect_rectangle(-13 + repeat * 32, -7 + repeat * 16,
            rect->tx, rect->ty, rect->width, rect->height, repeat + 1);
        func_800270F8(-13 + repeat * 32, -7 + repeat * 16, rect->tx, rect->ty);
    }
    assert(SP_BG_BLOCK_WIDTH == rect->width && SP_BG_BLOCK_HEIGHT == rect->height);
    return finish(1);
}

static void expect_viewport(s32 x, s32 y)
{
    u32 r, c, tx, ty, bx, by, block, chunk, count, i;
    struct ExpectedTile* tile;
    for (r = 0; r < 16; r++)
        for (c = 0; c < 21; c++) {
            tx = ((x >> 4) & 15) + c;
            ty = ((y >> 4) & 15) + r;
            bx = ((x >> 8) & 31) + tx / 16;
            by = ((y >> 8) & 31) + ty / 16;
            block = tilemap[layer_index][by][bx];
            if (block == 0)
                continue;
            chunk = (ty / 16) * 3 + tx / 16;
            count = chunk_counts[chunk]++;
            assert(count < COUNT(chunks[chunk]));
            tile = &chunks[chunk][count];
            tile->x = c * 16 - (x & 15);
            tile->y = r * 16 - (y & 15);
            tile->attributes = expected_descriptors[block][(ty & 15) * 16 + (tx & 15)];
            if (((tile->attributes >> 8) & 255) == 0)
                chunk_counts[chunk]--;
        }
    for (i = 0; i < 6; i++)
        for (c = 0; c < chunk_counts[i]; c++)
            expect_tile(chunks[i][c].x, chunks[i][c].y, chunks[i][c].attributes);
}

static void map_blocks(s32 x, s32 y, u32 mask)
{
    u32 i, bx = (x >> 8) & 31, by = (y >> 8) & 31;
    for (i = 0; i < 6; i++)
        if (mask & (1 << i))
            tilemap[layer_index][by + i / 3][bx + i % 3] = i + 1;
    memcpy(expected_tilemap, tilemap, sizeof(tilemap));
    background_objects[layer_index].x_pos.val = x * 65536 + 0x1234;
    background_objects[layer_index].y_pos.val = y * 65536 + 0x5678;
    memcpy(expected_backgrounds, background_objects, sizeof(expected_backgrounds));
}

static u32 test_viewport(u32 row)
{
    static const u8 offsets[] = { 0, 11, 12, 15 };
    static const u8 vertical[] = { 0, 1, 8, 15 };
    s32 x = 5 * 256 + offsets[row % 4] * 16 + row % 16;
    s32 y = 7 * 256 + vertical[row / 4] * 16 + (row * 3 & 15);
    if (row == 15)
        x = y = -1;
    prepare(row % 2, row / 2 % 3);
    map_blocks(x, y, 63);
    expect_viewport(x, y);
    SP_BG_BLOCK_HEIGHT = 16 - ((y >> 4) & 15);
    func_80026CEC(layer_index);
    return finish(1);
}

static u32 test_empty_blocks(u32 row)
{
    u32 choice = row / 6;
    u32 mask = choice == 0 ? 0 : choice == 1 ? 63
                                             : 63 ^ (1 << (choice - 2));
    prepare(row % 2, row / 2 % 3);
    map_blocks(5 * 256 + 255, 7 * 256 + 135, mask);
    expect_viewport(5 * 256 + 255, 7 * 256 + 135);
    SP_BG_BLOCK_HEIGHT = 8;
    func_80026CEC(layer_index);
    return finish(1);
}

static u32 test_inherited_height(u32 row)
{
    prepare(row % 2, row / 2 % 3);
    map_blocks(5 * 256 + 240, 7 * 256 + 240, (1 << 1) | (1 << 4));
    SP_BG_BLOCK_HEIGHT = 1;
    expect_rectangle(16, 0, 0, 15, 16, 1, 2);
    expect_rectangle(16, 16, 0, 0, 16, 1, 5);
    func_80026CEC(layer_index);
    assert(SP_BG_BLOCK_HEIGHT == 1);
    return finish(1);
}

static u32 test_frame(u32 row)
{
    SPRT_16 expected[2][4];
    struct DrawInfo initial_draw;
    u32 b, i, layer, count = 0, mask = row / 2;
    u32 attributes = expected_descriptors[3][255];
    u32 bucket = ((attributes >> 8) & 255) - 0x15;
    prepare(row % 2, 0);
    initial_draw = draw;
    for (b = 0; b < 2; b++)
        for (i = 0; i < 4; i++) {
            memset(&D_8015D9D0[b].sprites[i], 0x5A, sizeof(SPRT_16));
            setSprt16(&D_8015D9D0[b].sprites[i]);
            setShadeTex(&D_8015D9D0[b].sprites[i], 1);
            setaddr(&D_8015D9D0[b].sprites[i], 0x00654321);
            expected[b][i] = D_8015D9D0[b].sprites[i];
        }
    for (layer = 0; layer < 3; layer++) {
        background_objects[layer].unk3 = (mask >> layer) & 1;
        background_objects[layer].unk4A = 3;
        background_objects[layer].unk4B = 7;
        background_objects[layer].x_pos.i.hi = 240;
        background_objects[layer].y_pos.i.hi = 240;
        tilemap[layer][0][0] = 3;
        if (mask & (1 << layer)) {
            SPRT_16* sprite = &expected[buffer_index][count];
            sprite->x0 = sprite->y0 = 0;
            sprite->u0 = (attributes & 15) * 16;
            sprite->v0 = attributes & 0xF0;
            sprite->clut = attributes >> 16;
            setaddr(sprite, getaddr(&expected_draw.ordering_table.unk3));
            setaddr(&expected_pages[buffer_index][layer][bucket], &D_8015D9D0[buffer_index].sprites[count]);
            setaddr(&expected_draw.ordering_table.unk3, &D_80171EB0[buffer_index][layer][bucket]);
            count++;
        }
    }
    memcpy(expected_backgrounds, background_objects, sizeof(expected_backgrounds));
    memcpy(expected_tilemap, tilemap, sizeof(expected_tilemap));
    func_800265B4();
    assert(SP_BG_PRIM_CURSOR == &D_8015D9D0[buffer_index].sprites[count]);
    assert(SP_CUR_BG_INDEX == (mask & 4 ? 2 : mask & 2 ? 1
                                                       : 0));
    draw = initial_draw;
    func_800265B4();
    assert(SP_BG_PRIM_CURSOR == &D_8015D9D0[buffer_index].sprites[count]);
    for (b = 0; b < 2; b++)
        assert(c_test_word_difference((const u32*)D_8015D9D0[b].sprites,
                   (const u32*)expected[b], sizeof(expected[b]) / 4)
            == 0);
    SP_BG_PRIM_CURSOR = &packets[1];
    layer_index = SP_CUR_BG_INDEX;
    return finish(0);
}

const struct CTestGroup c_test_groups[] = {
    { "background_negative_tile_guards", NULL, background_negative_tile_guards_cases_expected, COUNT(background_negative_tile_guards_cases_expected), tile_case },
    { "packed_block_rectangle", 0, 0, COUNT(rectangles) * 6, test_rectangle },
    { "viewport_block_seams", 0, 0, 16, test_viewport },
    { "viewport_empty_blocks", 0, 0, 2, test_empty_blocks },
    { "viewport_inherited_height", 0, 0, 6, test_inherited_height },
    { "background_frame_layer_masks", 0, 0, 16, test_frame },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(background_negative_tile_guards_cases_expected) + COUNT(rectangles) * 6 + 16 + 2 + 6 + 16;
