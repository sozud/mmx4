#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/effects/effect_31_floor_trap.h"

static struct RideArmorObj trap_qux;
#define fte state_room.effect
#define TRAP(st, step, setup) (trap_qux = qux_object, state_reset(step, 0, 0), memset(&qux_object, 0, sizeof(qux_object)), fte.active = 1, fte.state = st, fte.x_pos.i.hi = 0x80, fte.y_pos.i.hi = 0x60, setup, floor_trap_update(&fte), qux_object = trap_qux)
static void trap_waits(void)
{
    TRAP(0, 0, 0);
}
static void trap_counts(void) { TRAP(1, 2, 0); }
static void (*const trap_cases[])(void) = {
    trap_waits,
    trap_counts,
};
static const u32 trap_expected[] = {
    0x0u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
};
static u32 test_trap(u32 row)
{
    return object_run(trap_cases[row], row, &trap_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "floor_trap_states", 0, 0, COUNT(trap_cases), test_trap },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(trap_cases);
