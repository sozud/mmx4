#include "test_runtime.h"
#include "main/shots/shot_14_dash_gunner_shot.h"
#include "support/state_cases.h"

extern u8 dash_gunner_shot_hit_box[4];
static struct Unk_unk68 gunner_player_box = { 0, 0, 12, 24 };
#define ss state_room.shot
#define DGS(st, setup) (state_reset(0, 0, 0), memset(&g_Player, 0, sizeof(g_Player)), memset(&engine_obj, 0, sizeof(engine_obj)), g_Player.x_pos.i.hi = 0x400, ss.active = 0x41, ss.state = st, ss.unk2 = 2, ss.x_pos.i.hi = 0x780, ss.y_pos.i.hi = 0x60, ss.unk60 = 3, ss.unk50.data = dash_gunner_shot_hit_box, setup, dash_gunner_shot_update(&ss), state_extra = (u8)g_Player.hp | (u32)g_Player.hurt_type << 8)
#define PLAYER_AT(x) (engine_obj.stage = 3, background_objects[0].x_pos.i.hi = x - 0xA0, g_Player.x_pos.i.hi = x, g_Player.y_pos.i.hi = 0x60, g_Player.hp = 30, g_Player.unk54 = (const u32*)&gunner_player_box, ss.x_pos.i.hi = x)
static void dgs_start_left(void)
{
    DGS(0, 0);
}
static void dgs_start_right(void) { DGS(0, ss.unk15 = PLAYER_FACING_RIGHT); }
static void dgs_hits_early(void) { DGS(1, PLAYER_AT(0x7B6)); }
static void dgs_spares_late(void) { DGS(1, PLAYER_AT(0x7B7)); }
static void dgs_gone(void) { DGS(1, ss.x_pos.i.hi = 0x1000); }
static void (*const dash_gunner_shot_steps_cases[])(void) = {
    dgs_start_left,
    dgs_start_right,
    dgs_hits_early,
    dgs_spares_late,
    dgs_gone,
};
static const u32 dash_gunner_shot_steps_expected[] = {
    0x1u,
    0xFF000241u,
    0x77A0000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x1u,
    0xFF400241u,
    0x7860000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x1u,
    0x241u,
    0x7B60000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x19Bu,
    0u,
    0x1u,
    0x241u,
    0x7B70000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x1Eu,
    0u,
    0x2u,
    0x241u,
    0x10000000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
};
static u32 test_dash_gunner_shot_steps(u32 row)
{
    return object_run(dash_gunner_shot_steps_cases[row], row, &dash_gunner_shot_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dash_gunner_shot_steps", 0, 0, COUNT(dash_gunner_shot_steps_cases), test_dash_gunner_shot_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dash_gunner_shot_steps_cases);
