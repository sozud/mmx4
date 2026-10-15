#include "test_runtime.h"

#include "support/tile_effects.h"
TILE_LOOP(3)
TILE_LOOP(4)
TILE_LOOP(5)
static const CTestCase tile_loop_anim_tiles_cases[] = { TILE_LOOP_ENTRIES(3) TILE_LOOP_ENTRIES(4) TILE_LOOP_ENTRIES(5) };

static const u32 tile_loop_anim_tiles_cases_expected[] = { 0x10001u, 0xCAFEu, 0xBEEFu, 0x0u, 0x1010009u, 0xA121u, 0xA121u, 0x1u, 0x10009u, 0xA120u, 0xA120u, 0x0u };
const struct CTestGroup c_test_groups[] = {
    { "tile_loop_anim_tiles", tile_loop_anim_tiles_cases, tile_loop_anim_tiles_cases_expected, COUNT(tile_loop_anim_tiles_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tile_loop_anim_tiles_cases);
