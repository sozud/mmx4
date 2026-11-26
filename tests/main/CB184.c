#include "test_runtime.h"
#include "main/effects/effect_01_tile_animator.h"
#include "main/CB184.h"
#include "main/tile_effects.h"
u8 tile_effect_is_visible(s16, s16, s16, s16);

#include "support/tile_effects.h"
TILE_OBSERVE(6, 1)
TILE_OBSERVE(6, 2)
TILE_OBSERVE(7, 1)
TILE_OBSERVE(7, 2)
TILE_OBSERVE(8, 1)
TILE_OBSERVE(8, 2)
TILE_OBSERVE(9, 1)
TILE_OBSERVE(9, 2)
static const CTestCase tile_effect_apply_cases[]
    = { TILE_ENTRY(6, 1) TILE_ENTRY(6, 2) TILE_ENTRY(7, 1) TILE_ENTRY(7, 2) TILE_ENTRY(8, 1) TILE_ENTRY(8, 2) TILE_ENTRY(9, 1) TILE_ENTRY(9, 2) };

#ifdef MMX4_SATURN
static const u32 tile_effect_apply_cases_expected[] = { 0xCAFEu, 0xA120u, 0xCAFEu, 0xA120u, 0xCAFEu, 0xBEEFu, 0xCAFEu, 0xBEEFu };
#else
static const u32 tile_effect_apply_cases_expected[] = { 0xA120u, 0xBEEFu, 0xA120u, 0xA120u, 0xCAFEu, 0xBEEFu, 0xCAFEu, 0xBEEFu };
#endif
static u32 test_tile_effect_above_view(u32 row)
{
    static const u32 expected = 0;
    u32 seen = tile_effect_is_visible(0, 0x100, 0x40, 0);
    return c_test_observe(0, row, &seen, &expected, 1);
}

#ifndef MMX4_SATURN
static u32 test_tile_effect_chain(u32 row)
{
    struct TileEffectRecord** saved_table = tile_effect_tables[0];
    u32 i, j, k;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(records, 0, sizeof(records));
    tile_effect_tables[0] = table;
    table[0] = &records[0];
    tiles[0] = 0xA120;
    tiles[1] = 0xA121;
    tiles[2] = 0xA122;
    records[0].packed_count = 3;
    records[0].x = records[0].y = 1;
    records[0].tiles = &tiles[0];
    records[0].has_next = 1;
    records[1].packed_count = 2;
    records[1].x = 0x31;
    records[1].y = 0x21;
    records[1].tiles = &tiles[1];
    records[2].packed_count = 2;
    records[2].x = 0x51;
    records[2].y = 0x51;
    records[2].tiles = &tiles[2];
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                D_801441C8[i][j][k] = 0xCAFE;
    refresh_visible_tile_effect(0, -1, -1);
    tile_effect_tables[0] = saved_table;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 32; j++)
            for (k = 0; k < 32; k++)
                assert(D_801441C8[i][j][k] == (i == 0 && j == 0 && k == 0 ? 0xA120 : i == 0 && j == 2 && k == 3 ? 0xA121 : 0xCAFE));
    return 1;
}
#define CHAIN_CASES 1
#else
#define test_tile_effect_chain NULL
#define CHAIN_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "tile_effect_apply", tile_effect_apply_cases, tile_effect_apply_cases_expected, COUNT(tile_effect_apply_cases), 0 },
    { "tile_effect_above_view", 0, 0, 1, test_tile_effect_above_view },
    { "tile_effect_chain", 0, 0, CHAIN_CASES, test_tile_effect_chain },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tile_effect_apply_cases) + 1 + CHAIN_CASES;
