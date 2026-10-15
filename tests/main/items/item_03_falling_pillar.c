#include "test_runtime.h"
extern struct TileEffectRecord** tile_effect_tables[26];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u8 tilemap[256];
static u16 pixels[258];
static u32 falling_pillar_context_pillar_case(u32 mode, u32 observation)
{
    struct ItemObj obj, before;
    struct Item03StageEntry entries_before[22];
    struct EngineObj engine_before;
    struct BackgroundObj bg_before[3];
    struct TileEffectRecord record_before;
    struct TileEffectRecord* record;
    u16 tiles_before[40];
    u8 id[7] = { 0, 4, 9, 10, 14, 20, 10 };
    s16 x;
    u32 i, j, k, actual, tile_count, tile_x, tile_y, end_y, changed = 0;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 0;
    engine_obj.substage = 1;
    obj.active = 0x41;
    obj.id = 3;
    obj.unk2 = id[mode];
    obj.state = 2;
    obj.unk5 = 0x35;
    obj.unk6 = 0x27;
    obj.bg_offset = 0;
    x = falling_pillar_entries[obj.unk2].trigger_x;
    if (mode == 0 || mode == 4)
        x++;
    if (mode == 2 || mode == 3)
        x--;
    if (mode == 1)
        x = falling_pillar_entries[obj.unk2].right;
    if (mode == 5)
        x = falling_pillar_entries[obj.unk2].right + 1;
    obj.x_pos.val = x * 65536 + 0x2468;
    obj.y_pos.val = 0x200 * 65536 + 0x1357;
    obj.x_vel.val = 0x1234;
    obj.y_vel.val = -0x1000;
    obj.ext.packed = mode == 1 || mode == 6;
    obj.unk7C.timer = mode == 0 || mode == 4 ? 1 : 2;
    record = tile_effect_tables[1][obj.unk2 + 0xB];
    assert(record != NULL && record->layer == 0 && record->has_next == 0);
    assert((record->packed_count & 1) == 0);
    tile_count = record->packed_count >> 1;
    assert(tile_count > 0 && tile_count <= COUNT(tiles_before));
    record_before = *record;
    for (i = 0; i < tile_count; i++)
        tiles_before[i] = record->tiles[i];
    tile_x = record->x / 16;
    tile_y = record->y / 16;
    end_y = tile_y + tile_count - 1;
    assert((tile_x >> 4) < 16 && (end_y >> 4) < 16);
    background_objects[0].x_pos.i.hi = record->x;
    background_objects[0].y_pos.i.hi = record->y;
    before = obj;
    engine_before = engine_obj;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    memcpy(entries_before, falling_pillar_entries, sizeof(entries_before));
    SP_BG_TILEMAP = tilemap;
    TEST_BG_TILE_PIXELS = (u8*)&pixels[1];
    memset(tilemap, 0, sizeof(tilemap));
    layout_width = 16;
    layout_size = 256;
    for (i = 0; i < COUNT(pixels); i++)
        pixels[i] = 0xBEEF;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                D_801441C8[i][j][k] = 0xCAFE;
    func_800C05FC(&obj);
    before.state = obj.state;
    before.on_screen = obj.on_screen;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.ext.packed = obj.ext.packed;
    before.unk7C.timer = obj.unk7C.timer;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    bg_before[0].unk36 = background_objects[0].unk36;
    bg_before[0].unk45 = background_objects[0].unk45;
    bg_before[0].unk3E.bytes[0] = background_objects[0].unk3E.bytes[0];
    bg_before[0].unk3C = background_objects[0].unk3C;
    bg_before[0].unk3A = background_objects[0].unk3A;
    bg_before[0].unk34 = background_objects[0].unk34;
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    for (i = 0; i < sizeof(engine_before) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(entries_before); i++)
        assert(((u8*)falling_pillar_entries)[i] == ((u8*)entries_before)[i]);
    for (i = 0; i < sizeof(record_before); i++)
        assert(((u8*)record)[i] == ((u8*)&record_before)[i]);
    for (i = 0; i < tile_count; i++)
        assert(record->tiles[i] == tiles_before[i]);
    for (i = 0; i < COUNT(tilemap); i++)
        assert(tilemap[i] == 0);
    assert(pixels[0] == 0xBEEF && pixels[257] == 0xBEEF);
    for (i = 0; i < 256; i++) {
        if ((i & 15) != (tile_x & 15))
            assert(pixels[1 + i] == 0xBEEF);
        else if (pixels[1 + i] != 0xBEEF)
            changed |= 1u << (i >> 4);
    }
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                if (i != 0 || k != (tile_x & 31))
                    assert(D_801441C8[i][j][k] == 0xCAFE);
    switch (observation) {
    case 0:
        actual = obj.x_pos.val;
        break;
    case 1:
        actual = obj.y_pos.val;
        break;
    case 2:
        actual = ((u32*)&obj)[1];
        break;
    case 3:
        actual = obj.ext.packed;
        break;
    case 4:
        actual = obj.unk7C.timer;
        break;
    case 5:
        actual = pixels[1 + (tile_y & 15) * 16 + (tile_x & 15)];
        break;
    case 6:
        actual = pixels[1 + (end_y & 15) * 16 + (tile_x & 15)];
        break;
    case 7:
        actual = D_801441C8[0][tile_y & 31][tile_x & 31] | ((u32)D_801441C8[0][end_y & 31][tile_x & 31] << 16);
        break;
    case 8:
        actual = changed;
        break;
    case 9:
        actual = (u8)background_objects[0].unk36 | ((u32)(u8)background_objects[0].unk45 << 8) | ((u32)background_objects[0].unk3E.bytes[0] << 16);
        break;
    default:
        actual = (u8)background_objects[0].unk3C | ((u32)(u8)background_objects[0].unk3A << 8) | ((u32)(u16)background_objects[0].unk34 << 16);
        break;
    }
    return actual;
}
#define PILLAR_CASE(m, n)                                    \
    static u32 falling_pillar_context_pillar_##m##_##n(void) \
    {                                                        \
        return falling_pillar_context_pillar_case(m, n);     \
    }
#define PILLAR_MODE(m) PILLAR_CASE(m, 0) PILLAR_CASE(m, 1) PILLAR_CASE(m, 2) PILLAR_CASE(m, 3) PILLAR_CASE(m, 4) PILLAR_CASE(m, 5) PILLAR_CASE(m, 6) PILLAR_CASE(m, 7) PILLAR_CASE(m, 8) PILLAR_CASE(m, 9) PILLAR_CASE(m, 10)
PILLAR_MODE(0)
PILLAR_MODE(1)
PILLAR_MODE(2)
PILLAR_MODE(3)
PILLAR_MODE(4)
PILLAR_MODE(5)
PILLAR_MODE(6)
#define PILLAR_ENTRY(m, n) falling_pillar_context_pillar_##m##_##n,
#define PILLAR_ENTRIES(m) PILLAR_ENTRY(m, 0) PILLAR_ENTRY(m, 1) PILLAR_ENTRY(m, 2) PILLAR_ENTRY(m, 3) PILLAR_ENTRY(m, 4) PILLAR_ENTRY(m, 5) PILLAR_ENTRY(m, 6) PILLAR_ENTRY(m, 7) PILLAR_ENTRY(m, 8) PILLAR_ENTRY(m, 9) PILLAR_ENTRY(m, 10)
static const CTestCase falling_pillar_context_cases[]
    = { PILLAR_ENTRIES(0) PILLAR_ENTRIES(1) PILLAR_ENTRIES(2) PILLAR_ENTRIES(3) PILLAR_ENTRIES(4) PILLAR_ENTRIES(5) PILLAR_ENTRIES(6) };
static const u32 falling_pillar_context_cases_expected[] = { 0xDF9369Cu, 0x2002357u, 0x273502u, 0x1u, 0x28u, 0x3Eu, 0x4Eu, 0xCAFE00A1u, 0xFFFFu, 0x30320u, 0x100101u, 0xE50369Cu, 0x2002357u, 0x273503u, 0x1u, 0x1u, 0xBEEFu, 0xBEEFu, 0xCAFECAFEu, 0x0u, 0x0u, 0x0u, 0xE4F369Cu, 0x2002357u, 0x273502u, 0x0u, 0x1u, 0xBEEFu, 0xBEEFu, 0xCAFECAFEu, 0x0u, 0x0u, 0x0u, 0xEF0369Cu, 0x2002357u, 0x273503u, 0x1u, 0x1u, 0x124u, 0x124u, 0x1DC01DCu, 0xFFFFu, 0x0u, 0x0u, 0xF09369Cu, 0x2002357u, 0x273502u, 0x0u, 0x0u, 0xBEEFu, 0xBEEFu, 0xCAFECAFEu, 0x0u, 0x0u, 0x0u, 0xE50369Cu, 0x2002357u, 0x273503u, 0x1u, 0x1u, 0x3Eu, 0x4Eu, 0xCAFE00A1u, 0xFFFFu, 0x0u, 0x0u, 0xEF0369Cu, 0x2002357u, 0x273503u, 0x1u, 0x1u, 0xBEEFu, 0xBEEFu, 0xCAFECAFEu, 0x0u, 0x0u, 0x0u };
#undef PILLAR_CASE
#undef PILLAR_MODE
#undef PILLAR_ENTRY
#undef PILLAR_ENTRIES

static u32 falling_pillar_threshold_context_pillar_case(u32 mode)
{
    struct ItemObj obj, before;
    struct PlayerObj player_before;
    struct BackgroundObj backgrounds_before[3];
    u32 i, actual, index = mode == 2 ? 0 : 1;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    D_8013E198[5] = -1;
    obj.active = 0x41;
    obj.id = 3;
    obj.state = 1;
    obj.unk2 = index;
    obj.bg_offset = 0;
    obj.on_screen = 7;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.unk7C.timer = 0x7777;
    g_Player.y_pos.i.hi = mode == 0 ? falling_pillar_entries[index].velocity - 1 : falling_pillar_entries[index].velocity;
    before = obj;
    player_before = g_Player;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    falling_pillar_wait_player(&obj);
    before.on_screen = 1;
    if (mode != 0) {
        before.state = 2;
        before.unk7C.timer = 10;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(D_8013E198[5] == -1);
    actual = (u8)obj.state | ((u32)(u16)obj.unk7C.timer << 8);
    return actual;
}
#define CASE(m)                                                  \
    static u32 falling_pillar_threshold_context_pillar_##m(void) \
    {                                                            \
        return falling_pillar_threshold_context_pillar_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
#define ENTRY(m) falling_pillar_threshold_context_pillar_##m,
static const CTestCase falling_pillar_threshold_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) };
static const u32 falling_pillar_threshold_context_cases_expected[] = { 0x777701u, 0xA02u, 0xA02u };
#undef CASE
#undef ENTRY

struct falling_pillar_finish_case {
    u32 unk2;
    u32 expected[2];
};
static const struct falling_pillar_finish_case falling_pillar_finish_cases[] = {
    { -1, { 0u, 0u } },
    { 0, { 0u, 0u } },
};
static u32 test_falling_pillar_finish(u32 row)
{
    const struct falling_pillar_finish_case* c = &falling_pillar_finish_cases[row];
    u32 observed_values[2];
    struct ItemObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk2 = c->unk2;
    falling_pillar_finish(&obj);
    observed_values[0] = (u32)obj.ext.timer;
    observed_values[1] = (u32)obj.unk7C.timer;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "falling_pillar_context", falling_pillar_context_cases, falling_pillar_context_cases_expected, COUNT(falling_pillar_context_cases), 0 },
    { "falling_pillar_threshold_context", falling_pillar_threshold_context_cases, falling_pillar_threshold_context_cases_expected, COUNT(falling_pillar_threshold_context_cases), 0 },
    { "falling_pillar_finish", 0, 0, 2, test_falling_pillar_finish },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(falling_pillar_context_cases) + COUNT(falling_pillar_threshold_context_cases) + 2;
