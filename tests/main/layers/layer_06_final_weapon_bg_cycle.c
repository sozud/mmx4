#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/layers/layer_06_final_weapon_bg_cycle.h"

#define lc state_room.unk
#ifdef MMX4_SATURN
#define CYCLE_PANEL_X(panel) (((panel)&1) << 9)
#else
#define CYCLE_PANEL_X(panel) ((panel) << 9)
#endif
#define CYCLE(st, frames, panel) (state_reset(0, 0, 0), ((struct LayerObj*)&lc)->active = 1, ((struct LayerObj*)&lc)->state = st, ((struct LayerObj*)&lc)->bg_offset = frames, ((struct LayerObj*)&lc)->unk15 = panel, final_weapon_bg_cycle_update((struct LayerObj*)&lc), state_extra = (u8)((struct LayerObj*)&lc)->bg_offset | (u32)(u8)((struct LayerObj*)&lc)->unk15 << 8 | (u32)(u16)background_objects[1].x_pos.i.hi << 16 | (u32)background_objects[1].unk4C << 30)
static void cycle_init(void) { CYCLE(0, 3, 2); }
static void cycle_counts(void) { CYCLE(1, 3, 1); }
static void cycle_next_panel(void) { CYCLE(1, 7, 1); }
static void cycle_wraps(void) { CYCLE(1, 7, 3); }
static void (*const cycle_cases[])(void) = {
    cycle_init,
    cycle_counts,
    cycle_next_panel,
    cycle_wraps,
};
static const u32 cycle_expected[] = {
    0x1u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x10001u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x104u,
    0x0u,
    0x1u,
    0x20001u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x40000200u | (u32)CYCLE_PANEL_X(2) << 16,
    0x0u,
    0x1u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x40000000u,
    0x0u,
};
static u32 test_cycle(u32 row)
{
    return object_run(cycle_cases[row], row, &cycle_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "final_weapon_bg_cycle_states", 0, 0, COUNT(cycle_cases), test_cycle },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(cycle_cases);
