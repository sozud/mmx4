#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_00_wall_slide_dust.h"

static struct PlayerObj slide_player, slide_entity;
#define wd state_room.visual
#define SLIDE(st, mode, step, setup) (slide_player = g_Player, slide_entity = g_Entity, state_reset(0, 0, 0), g_Player.controlling_clone = 0, g_Player.unk2 = 0, g_Player.unk15 = 0, g_Player.x_pos.i.hi = 0x100, g_Player.y_pos.i.hi = 0x80, g_Player.unk5 = mode, g_Player.unk6 = step, wd.active = 1, wd.state = st, wd.animation_step.fields.relative_step = 1, setup, wall_slide_dust_update(&wd), state_extra = wd.unk17 | (u32)wd.on_screen << 8, g_Player = slide_player, g_Entity = slide_entity)
static void slide_turning(void) { SLIDE(1, 0x0B, 1, 0); }
static void slide_kick(void) { SLIDE(1, 0x34, 0, 0); }
static void slide_clone_right(void) { SLIDE(1, 0x0B, 0, (g_Player.controlling_clone = 1, g_Entity = g_Player, g_Entity.controlling_clone = 0, g_Entity.unk15 = PLAYER_FACING_RIGHT)); }
static void slide_fades(void) { SLIDE(2, 0, 0, 0); }
static void slide_gone(void) { SLIDE(2, 0, 0, wd.animation_step.fields.relative_step = -1); }
static void (*const slide_cases[])(void) = {
    slide_turning,
    slide_kick,
    slide_clone_right,
    slide_fades,
    slide_gone,
};
static const u32 slide_expected[] = {
    0x2u, 0xFF000001u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x104u, 0x0u,
    0x1u, 0x1u, 0x10A0000u, 0x910000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x1u, 0x400001u, 0xF60000u, 0x910000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x2u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
};
static u32 test_slide(u32 row)
{
    return object_run(slide_cases[row], row, &slide_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "wall_slide_dust_states", 0, 0, COUNT(slide_cases), test_slide },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(slide_cases);
