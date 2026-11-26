#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/effects/effect_06_checkpoint_trigger.h"

#define ce state_room.effect
#define CHECK(st, kind, px, py, setup) (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.checkpoint = 1, ce.active = 1, ce.state = st, ce.unk2 = kind, ce.x_pos.i.hi = 0x80, ce.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, setup, checkpoint_trigger_update(&ce), state_extra = engine_obj.checkpoint)
static void check_init_reached(void) { CHECK(0, 1, 0, 0, 0); }
static void check_init_ahead(void) { CHECK(0, 2, 0, 0, 0); }
static void check_off_screen(void) { CHECK(1, 2, 0, 0, ce.x_pos.i.hi = 0x200); }
static void check_passed(void) { CHECK(1, 2, 0x80, 0, 0); }
static void check_before(void) { CHECK(1, 2, 0x7F, 0, 0); }
static void check_dropped(void) { CHECK(1, 0x12, 0, 0x60, 0); }
static void check_above(void) { CHECK(1, 0x12, 0, 0x5F, 0); }
static void (*const check_cases[])(void) = {
    check_init_reached,
    check_init_ahead,
    check_off_screen,
    check_passed,
    check_before,
    check_dropped,
    check_above,
};
static const u32 check_expected[] = {
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
    0x1u,
    0x201u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2u,
    0x0u,
    0x1u,
    0x201u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x2u,
    0x0u,
    0x1u,
    0x1201u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
};
static u32 test_check(u32 row)
{
    return object_run(check_cases[row], row, &check_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "checkpoint_trigger_states", 0, 0, COUNT(check_cases), test_check },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(check_cases);
