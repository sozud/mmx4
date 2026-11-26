#include "test_runtime.h"

#include "support/state_cases.h"
s32 water_wake_player_idle(struct PlayerObj*);
s32 water_wake_player_moving(struct PlayerObj*);

static struct PlayerObj wake_player;
#define WAKE(kind, pose) (state_reset(0, 0, 0), memset(&wake_player, 0, sizeof(wake_player)), wake_player.unk2 = kind, wake_player.unk17 = pose, state_extra = water_wake_player_idle(&wake_player) | water_wake_player_moving(&wake_player) << 1)
static void ww_zero_still(void) { WAKE(1, 3); }

static void (*const water_wake_modes_cases[])(void) = {
    ww_zero_still,
};
static const u32 water_wake_modes_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u };

static u32 test_water_wake_modes(u32 row)
{
    return state_run(water_wake_modes_cases[row], row, &water_wake_modes_expected[row * 10]);
}

#include "main/visuals/visual_07_water_wake.h"
static struct PlayerObj wake_saved_player, wake_saved_entity;
static u32 wake_frames[0x100];
static u32 wake_pages[0x40];
#define wv state_room.visual
#define WW(st, step, kind, pose, attr, setup) (wake_saved_player = g_Player, wake_saved_entity = g_Entity, state_reset(step, 0, 0), state_terrain(attr), TEST_MENU_FRAMES = (u8*)wake_frames, D_801406A8 = wake_pages, memset(&engine_obj, 0, sizeof(engine_obj)), memset(&g_Player, 0, sizeof(g_Player)), g_Player.active = 1, g_Player.state = 1, g_Player.hp = 0x10, g_Player.unk17 = pose, g_Player.unk15 = PLAYER_FACING_RIGHT, g_Player.unk68 = &state_hit_box, g_Player.x_pos.i.hi = 0x40, g_Player.y_pos.i.hi = 0x20, g_Entity = g_Player, wv.active = 1, wv.state = st, wv.unk2 = kind, setup, water_wake_update(&wv), state_extra = wv.unk17 | (u32)wv.on_screen << 8, g_Player = wake_saved_player, g_Entity = wake_saved_entity)
static void wake_init(void) { WW(0, 0, 0, 2, 0x24, 0); }
static void wake_player_down(void) { WW(1, 0, 0, 2, 0x24, g_Player.hp = 0); }
static void wake_player_dying(void) { WW(1, 0, 0, 2, 0x24, g_Player.state = 3); }
static void wake_appears_idle(void) { WW(1, 0, 1, 2, 0x24, 0); }
static void wake_clone_appears_moving(void) { WW(1, 0, 2, 7, 0x24, 0); }
static void wake_stays_hidden_inactive(void) { WW(1, 0, 0, 0, 0x24, g_Player.active = 0); }
static void wake_idle_to_moving(void) { WW(1, 1, 0, 7, 0x24, wv.on_screen = 1); }
static void wake_idle_ends(void) { WW(1, 1, 0, 0, 0x24, wv.on_screen = 1); }
static void wake_moves(void) { WW(1, 2, 0, 7, 0x24, wv.on_screen = 1); }
static void wake_moving_to_idle(void) { WW(1, 2, 0, 2, 0x24, wv.on_screen = 1); }
static void wake_moving_ends(void) { WW(1, 2, 0, 0, 0x24, wv.on_screen = 1); }
static void wake_off_water(void) { WW(1, 1, 0, 2, 0, wv.on_screen = 1); }
static void (*const wake_cases[])(void) = {
    wake_init,
    wake_player_down,
    wake_player_dying,
    wake_appears_idle,
    wake_clone_appears_moving,
    wake_stays_hidden_inactive,
    wake_idle_to_moving,
    wake_idle_ends,
    wake_moves,
    wake_moving_to_idle,
    wake_moving_ends,
    wake_off_water,
};
static const u32 wake_expected[] = {
    0x1u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u | VISUAL_STAGE_PALETTE(14), 0x0u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x101u, 0xFF400101u, 0x480000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x113u, 0x0u,
    0x201u, 0xFF400201u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x114u, 0x0u,
    0x1u, 0x400001u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x201u, 0xFF400001u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x114u, 0x0u,
    0x1u, 0x400001u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x201u, 0x400001u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x101u, 0xFF400001u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x113u, 0x0u,
    0x1u, 0x400001u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x101u, 0x400001u, 0x380000u, 0x200000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
};
static u32 test_wake(u32 row)
{
    return object_run(wake_cases[row], row, &wake_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "water_wake_modes", 0, 0, COUNT(water_wake_modes_cases), test_water_wake_modes },
    { "water_wake_states", 0, 0, COUNT(wake_cases), test_wake },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(water_wake_modes_cases) + COUNT(wake_cases);
