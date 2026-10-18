#include "test_runtime.h"

#include "support/state_cases.h"
void fortress_collapse_despawn(struct EffectObj*);

static void fcol_despawn(void)
{
    state_reset(0, 0, 0);
    state_room.effect.active = 1;
    state_room.effect.state = 3;
    fortress_collapse_despawn(&state_room.effect);
}

static void (*const fortress_collapse_misc_cases[])(void) = {
    fcol_despawn,
};
static const u32 fortress_collapse_misc_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_fortress_collapse_misc(u32 row)
{
    return object_run(fortress_collapse_misc_cases[row], row, &fortress_collapse_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "fortress_collapse_misc", 0, 0, COUNT(fortress_collapse_misc_cases), test_fortress_collapse_misc },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(fortress_collapse_misc_cases);
