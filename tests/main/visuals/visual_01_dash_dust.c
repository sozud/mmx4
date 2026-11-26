#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_01_dash_dust.h"

static struct PlayerObj dust_player, dust_entity;
#define dv state_room.visual
#define DUST(momentum, anim, setup) (dust_player = g_Player, dust_entity = g_Entity, state_reset(0, 0, 0), g_Player.x_pos.i.hi = 0x100, g_Player.y_pos.i.hi = 0x80, g_Player.dash_momentum = momentum, g_Player.unk17 = anim, g_Player.controlling_clone = 0, g_Player.unk2 = 0, g_Player.unk15 = 0, dv.active = 1, dv.state = 1, dv.animation_step.fields.relative_step = 1, setup, dash_dust_update(&dv), state_extra = dv.on_screen, g_Player = dust_player, g_Entity = dust_entity)
static void dust_dash_ends(void)
{
    DUST(1, 0x11, 0);
}
static void dust_brake(void) { DUST(0, 0x12, 0); }
static void dust_brake_ends(void) { DUST(0, 0, 0); }
static void dust_animation_ends(void) { DUST(1, 0x10, dv.animation_step.fields.relative_step = -1); }
static void dust_clone_right(void) { DUST(1, 0x10, (g_Player.controlling_clone = 1, g_Entity = g_Player, g_Entity.controlling_clone = 0, g_Entity.unk15 = PLAYER_FACING_RIGHT, g_Entity.x_pos.i.hi = 0x140)); }
static void (*const dust_cases[])(void) = {
    dust_dash_ends,
    dust_brake,
    dust_brake_ends,
    dust_animation_ends,
    dust_clone_right,
};
static const u32 dust_expected[] = {
    0x0u,
    0x0u,
    0x1200000u,
    0x8C0000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x1u,
    0x1u,
    0x1200000u,
    0x8C0000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x1200000u,
    0x8C0000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1200000u,
    0x8C0000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x0u,
    0x0u,
    0x1u,
    0x400001u,
    0x1200000u,
    0x8C0000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x1u,
    0x0u,
};
static u32 test_dust(u32 row)
{
    return object_run(dust_cases[row], row, &dust_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dash_dust_states", 0, 0, COUNT(dust_cases), test_dust },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dust_cases);
