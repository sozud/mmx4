#include "test_runtime.h"

#include "support/tile_effects.h"
TILE_ANIMATOR(0)
TILE_ANIMATOR(1)
TILE_ANIMATOR(2)
static const CTestCase tile_animator_tiles_cases[] = { TILE_ANIMATOR_ENTRIES(0) TILE_ANIMATOR_ENTRIES(1) TILE_ANIMATOR_ENTRIES(2) };

static const u32 tile_animator_tiles_cases_expected[] = { 0x201u, 0xA122u, 0x300u, 0xA123u, 0x0u, 0xA120u };
const struct CTestGroup c_test_groups[] = {
    { "tile_animator_tiles", tile_animator_tiles_cases, tile_animator_tiles_cases_expected, COUNT(tile_animator_tiles_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tile_animator_tiles_cases);
