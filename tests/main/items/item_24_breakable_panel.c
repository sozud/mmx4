#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/items/item_24_breakable_panel.h"

void breakable_panel_main(struct ItemObj*);
void breakable_panel_destroyed(struct ItemObj*);
#define bp state_room.item
#define BP(st, setup)                                                                                                                     \
    (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 7, engine_obj.substage = 1,                     \
        memset(weapon_objects, 0, sizeof(weapon_objects)), g_Player.unk68 = NULL, bp.active = 0x41, bp.id = 0x18,                         \
        bp.state = st, bp.x_pos.i.hi = 0x498, bp.y_pos.i.hi = 0x3A8, bp.unk42 = 0x8001, setup,                                            \
        breakable_panel_update(&bp), state_extra = (u8)bp.unk7C.timer | (u32)(u8)((struct MainObj*)&bp)->hp << 8 | (u32)cur_random << 16, \
        engine_obj.stage = engine_obj.substage = 0)
#define BP_HIT(life) (((struct MainObj*)&bp)->hp = life, state_hit((struct MainObj*)&bp, 0, 0, 1))
static void bp_idle(void)
{
    BP(1, 0);
}
static void bp_hit(void) { BP(1, BP_HIT(0x10)); }
static void bp_broken(void) { BP(1, BP_HIT(1)); }
static void bp_end_burst(void) { BP(2, (bp.unk7C.timer = 2, WEAPON_FRAME_COUNTER = 0x10, cur_random = 0x1234)); }
static void bp_end_quiet(void) { BP(2, (bp.unk7C.timer = 2, WEAPON_FRAME_COUNTER = 9, cur_random = 0x1234)); }
static void bp_end(void) { BP(2, (bp.unk7C.timer = 1, cur_random = 0x1234)); }

static void (*const breakable_panel_states_cases[])(void) = {
    bp_idle,
    bp_hit,
    bp_broken,
    bp_end_burst,
    bp_end_quiet,
    bp_end,
};
static const u32 breakable_panel_states_expected[] = {
    0x1u,
    0x41u,
    0x4980000u,
    0x3A80000u,
    0x0u,
    0x0u,
    0x0u,
    0x50001u,
    0x0u,
    0x0u,
    0x1u,
    0x41u,
    0x4980000u,
    0x3A80000u,
    0x0u,
    0x0u,
    0x0u,
    0x58001u,
    0xF00u,
    0x2100u,
    0x2u,
    0x41u,
    0x4980000u,
    0x3A80000u,
    0x0u,
    0x0u,
    0x0u,
    0x58001u,
    0x1Eu,
    0x41002100u,
    0x2u,
    0x41u,
    0x4980000u,
    0x3A80000u,
    0x0u,
    0x0u,
    0x0u,
    0x58001u,
    0x39EC0001u,
    0x2100u,
    0x2u,
    0x41u,
    0x4980000u,
    0x3A80000u,
    0x0u,
    0x0u,
    0x0u,
    0x58001u,
    0x12340001u,
    0x0u,
    0x0u,
    0x0u,
    0x4980000u,
    0x3A80000u,
    0x0u,
    0x0u,
    0x0u,
    0x58001u,
    0x12340000u,
    0x0u,
};

static u32 test_breakable_panel_states(u32 row)
{
    return object_run(breakable_panel_states_cases[row], row, &breakable_panel_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "breakable_panel_states", 0, 0, COUNT(breakable_panel_states_cases), test_breakable_panel_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(breakable_panel_states_cases);
