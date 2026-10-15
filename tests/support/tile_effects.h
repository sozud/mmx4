#ifndef MMX4_TESTS_TILE_EFFECTS_H
#define MMX4_TESTS_TILE_EFFECTS_H

void tile_loop_anim_step(struct EffectObj*);
extern struct TileEffectRecord** tile_effect_tables[26];

static struct TileEffectRecord records[6];
static struct TileEffectRecord* table[6];
static u16 tiles[6];
static u8 tilemap[1];
static u16 pixels[258];
static s32 script[6];

static u32 tile_case(u32 mode, u32 observation)
{
    struct EffectObj obj;
    struct TileEffectRecord** saved_table;
    u8* saved_map;
    u16* saved_pixels;
    u32 i, j, k, actual, cache, archive, cursor, tile_x, tile_y;
    u8 id, width;
    u16 size;

    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(records, 0, sizeof(records));
    assert(((unsigned long)pixels & 1) == 0);
    assert(((unsigned long)script & 3) == 0);
    assert(((unsigned long)records & 3) == 0);
    saved_table = tile_effect_tables[0];
    saved_map = SP_BG_TILEMAP;
    saved_pixels = SP_BG_TILE_PIXELS;
    width = layout_width;
    size = layout_size;
    tile_effect_tables[0] = table;
    SP_BG_TILEMAP = tilemap;
    TEST_BG_TILE_PIXELS = (u8*)&pixels[1];
    tilemap[0] = 0;
    layout_width = 1;
    layout_size = 1;
    for (i = 0; i < 6; i++) {
        tiles[i] = 0xA120 + i;
        records[i].packed_count = 3;
        records[i].tiles = &tiles[i];
        table[i] = &records[i];
        script[i] = (s32)(0x00010009u | (i << 24));
    }
    script[5] = (s32)0x05FB0009u;
    for (i = 0; i < COUNT(pixels); i++)
        pixels[i] = 0xBEEF;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                D_801441C8[i][j][k] = 0xCAFE;

    tile_x = mode >= 6 ? 0 : 2;
    tile_y = mode >= 6 ? 0 : 4;
    if (mode < 3) {
        obj.unk5 = mode == 0 ? 0 : 2;
        obj.unk6 = mode == 2 ? 4 : 2;
        tile_animator_step(&obj, 32, 64);
        id = mode == 0 ? 2 : mode == 1 ? 3
                                       : 0;
        actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8);
        cursor = 0;
    } else if (mode < 6) {
        obj.unk2 = mode == 5 ? 1 : 0;
        obj.x_pos.i.hi = (obj.unk2 ? 0x40 : 0x30) + 32;
        obj.y_pos.i.hi = (obj.unk2 ? 0x30 : 0x20) + 64;
        obj.ext.effect_40.palette_source.words = &script[mode == 5 ? 5 : 0];
        obj.ext.effect_40.palette.packed = script[mode == 5 ? 5 : 0];
        obj.ext.effect_40.palette.fields.timer = mode == 3 ? 2 : 1;
        tile_loop_anim_step(&obj);
        id = mode == 4 ? 1 : 0;
        actual = (u32)obj.ext.effect_40.palette.packed;
        assert(obj.ext.effect_40.palette_source.words == &script[mode == 4 ? 1 : 0]);
        cursor = obj.ext.effect_40.palette_source.words - script;
    } else {
        if (mode >= 8)
            records[0].packed_count = 0;
        if (mode == 6 || mode == 8)
            refresh_visible_tile_effect(0, -1, -1);
        else
            apply_tile_effect(0, -1, -1);
        id = 0;
        actual = cursor = 0;
    }
    cache = D_801441C8[0][tile_y][tile_x];
    archive = pixels[1 + tile_y * 16 + tile_x];
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                assert(D_801441C8[i][j][k] == (mode != 3 && mode < 8 && i == 0 && j == tile_y && k == tile_x ? tiles[id] : 0xCAFE));
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == ((mode == 4 || mode == 5 || mode == 7) && i == 1 + tile_y * 16 + tile_x ? tiles[id] : 0xBEEF));
    assert(engine_obj.stage == 0 && engine_obj.substage == 0 && tilemap[0] == 0);
    for (i = 0; i < 6; i++) {
        assert(tiles[i] == 0xA120 + i);
        assert(script[i] == (s32)(i == 5 ? 0x05FB0009u : 0x00010009u | (i << 24)));
    }
    tile_effect_tables[0] = saved_table;
    SP_BG_TILEMAP = saved_map;
    TEST_BG_TILE_PIXELS = (u8*)saved_pixels;
    layout_width = width;
    layout_size = size;
    if (observation == 1)
        return cache;
    if (observation == 2)
        return archive;
    if (observation == 3)
        return cursor;
    return actual;
}
#define TILE_OBSERVE(mode, field)          \
    static u32 tile_##mode##_##field(void) \
    {                                      \
        return tile_case(mode, field);     \
    }
#define TILE_ANIMATOR(mode) TILE_OBSERVE(mode, 0) TILE_OBSERVE(mode, 1)
#define TILE_LOOP(mode) TILE_ANIMATOR(mode) TILE_OBSERVE(mode, 2) TILE_OBSERVE(mode, 3)
#define TILE_ENTRY(mode, field) tile_##mode##_##field,
#define TILE_ANIMATOR_ENTRIES(mode) TILE_ENTRY(mode, 0) TILE_ENTRY(mode, 1)
#define TILE_LOOP_ENTRIES(mode) TILE_ANIMATOR_ENTRIES(mode) TILE_ENTRY(mode, 2) TILE_ENTRY(mode, 3)
#endif
