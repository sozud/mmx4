#include "test_runtime.h"
#include "main/effects/effect_01_tile_animator.h"
#include "main/CB184.h"
#include "main/tile_effects.h"

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

static const u32 tile_effect_apply_cases_expected[] = { 0xA120u, 0xBEEFu, 0xA120u, 0xA120u, 0xCAFEu, 0xBEEFu, 0xCAFEu, 0xBEEFu };
const struct CTestGroup c_test_groups[] = {
    { "tile_effect_apply", tile_effect_apply_cases, tile_effect_apply_cases_expected, COUNT(tile_effect_apply_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(tile_effect_apply_cases);
