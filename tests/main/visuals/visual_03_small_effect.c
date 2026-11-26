#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_03_small_effect.h"

static struct PlayerObj small_player;
#define sv state_room.visual
#define SMALL(st, kind, setup) (small_player = g_Player, state_reset(0, 0, 0), g_Player.unkDF = 1, sv.active = 1, sv.state = st, sv.unk2 = kind, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, sv.animation_step.fields.relative_step = 1, setup, small_effect_update(&sv), state_extra = sv.unk17 | (u32)sv.on_screen << 8 | (u32)(u8)g_Player.unkDF << 16 | (u32)(u8)sv.animation_step.fields.event << 24, g_Player = small_player)
static void small_init(void)
{
    SMALL(0, 3, 0);
}
static void small_kind_9_event(void) { SMALL(1, 9, sv.animation_step.fields.event = 1); }
static void small_kind_9(void) { SMALL(1, 9, 0); }
static void small_ends(void) { SMALL(1, 3, sv.animation_step.fields.relative_step = -1); }
static void small_off_screen(void) { SMALL(1, 3, sv.x_pos.i.hi = 0x200); }
static void small_despawn(void) { SMALL(2, 3, 0); }
static void small_other_state(void) { SMALL(3, 3, 0); }
static void (*const small_cases[])(void) = {
    small_init,
    small_kind_9_event,
    small_kind_9,
    small_ends,
    small_off_screen,
    small_despawn,
    small_other_state,
};
static const u32 small_expected[] = {
    0x1u,
    0xFF000301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1010Au,
    0x0u,
    0x1u,
    0x901u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
    0x1u,
    0x901u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x2u,
    0x301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10100u,
    0x0u,
    0x2u,
    0x301u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10000u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10000u,
    0x0u,
    0x3u,
    0x301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10000u,
    0x0u,
};
static u32 test_small(u32 row)
{
    return object_run(small_cases[row], row, &small_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "small_effect_states", 0, 0, COUNT(small_cases), test_small },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(small_cases);
