#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/items/item_16_sliding_floor.h"

static struct Main45Ext floor_boss;
static u8 floor_parameter;
#define si state_room.item
#define FLOOR(st, x, ride, climb, held)                  \
    do {                                                 \
        u8 climbable = g_Player.wall_climbable;          \
        state_reset(0, 0, 0);                            \
        floor_parameter = 0;                             \
        floor_boss.unk83 = held;                         \
        si.active = 1;                                   \
        si.state = st;                                   \
        si.x_pos.i.hi = x;                               \
        si.y_pos.i.hi = 0x80;                            \
        si.x_vel.val = 0x10000;                          \
        si.unk76 = ride;                                 \
        si.unk7C.train_boss = &floor_boss;               \
        si.ext.train_layer_parameter = &floor_parameter; \
        g_Player.wall_climbable = climb;                 \
        sliding_floor_update(&si);                       \
        g_Player.wall_climbable = climbable;             \
        state_extra = floor_parameter;                   \
    } while (0)
static void sf_init(void)
{
    FLOOR(0, 0x1A00, 0, 0, 0);
}
static void sf_slide(void) { FLOOR(1, 0x1A00, 0, 0, 0); }
static void sf_slide_end(void) { FLOOR(1, 0x1AB0, 0, 0, 0); }
static void sf_climb(void) { FLOOR(1, 0x1A00, 0, 1, 0); }
static void sf_ridden(void) { FLOOR(1, 0x1A00, 1, 0, 0); }
static void sf_boss_hold(void) { FLOOR(1, 0x1A00, 1, 1, 1); }

static void (*const sliding_floor_states_cases[])(void) = {
    sf_init,
    sf_slide,
    sf_slide_end,
    sf_climb,
    sf_ridden,
    sf_boss_hold,
};
static const u32 sliding_floor_states_expected[] = { 1u, 1u, 0x1A000000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 1u, 0x1A010000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0x101u, 1u, 0x1AB00000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 1u, 0x1A010000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 1u, 0u, 1u, 1u, 0x1A010000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 1u, 0u, 1u, 1u, 0x1A010000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_sliding_floor_states(u32 row)
{
    return object_run(sliding_floor_states_cases[row], row, &sliding_floor_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "sliding_floor_states", 0, 0, COUNT(sliding_floor_states_cases), test_sliding_floor_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sliding_floor_states_cases);
