#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_35_cyclone_trail.h"

static struct BaseObj trail_source;
#define tm state_room.misc
#define TRAIL(st, kind) (state_reset(0, 0, 0), memset(&trail_source, 0, sizeof(trail_source)), trail_source.x_pos.i.hi = 0x90, trail_source.y_pos.i.hi = 0x70, trail_source.unk15 = PLAYER_FACING_RIGHT, tm.active = 1, tm.state = st, tm.unk2 = kind, tm.ext.pointer.unk50 = (void*)&trail_source, cyclone_trail_update(&tm), state_extra = tm.unk17 | (u32)tm.on_screen << 8)
static void trail_init_0(void)
{
    TRAIL(0, 0);
}
static void trail_init_1(void) { TRAIL(0, 1); }
static void trail_init_2(void) { TRAIL(0, 2); }
static void trail_init_3(void) { TRAIL(0, 3); }
static void trail_init_4(void) { TRAIL(0, 4); }
static void trail_init_other(void) { TRAIL(0, 5); }
static void trail_fades(void) { state_reset(0, 0, 0), tm.active = 1, tm.state = 1, tm.animation_step.fields.relative_step = 1, tm.x_pos.i.hi = 0x80, tm.y_pos.i.hi = 0x60, cyclone_trail_update(&tm), state_extra = tm.on_screen; }
static void trail_gone(void) { state_reset(0, 0, 0), tm.active = 1, tm.state = 1, cyclone_trail_update(&tm), state_extra = tm.on_screen; }
static void (*const trail_cases[])(void) = {
    trail_init_0,
    trail_init_1,
    trail_init_2,
    trail_init_3,
    trail_init_4,
    trail_init_other,
    trail_fades,
    trail_gone,
};
static const u32 trail_expected[] = {
    0x1u,
    0xFF400001u,
    0x900000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x114u,
    0x0u,
    0x1u,
    0xFF400101u,
    0x900000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x115u,
    0x0u,
    0x1u,
    0xFF400201u,
    0x900000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x116u,
    0x0u,
    0x1u,
    0xFF400301u,
    0x900000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x117u,
    0x0u,
    0x1u,
    0xFF400401u,
    0x900000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x118u,
    0x0u,
    0x1u,
    0x400501u,
    0x900000u,
    0x700000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x100u,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
};
static u32 test_trail(u32 row)
{
    return object_run(trail_cases[row], row, &trail_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "cyclone_trail_states", 0, 0, COUNT(trail_cases), test_trail },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(trail_cases);
