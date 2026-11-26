#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_25_grenade.h"

void grenade_fly(struct ShotObj*);
void grenade_idle(struct ShotObj*);
extern u8 grenade_hit_box[4], grenade_terrain_box[4];
#define gs state_room.shot
#define GRENADE(st, kind, face) (state_reset(0, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), gs.active = 1, gs.state = st, gs.unk2 = kind, gs.unk15 = face, gs.x_pos.i.hi = 0x80, gs.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x400, g_Player.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1))
static void grenade_init_lob_right(void) { GRENADE(0, 0x81, PLAYER_FACING_RIGHT), grenade_update(&gs), state_extra = gs.unk17 | (u32)gs.unk60 << 8; }
static void grenade_init_lob_left(void) { GRENADE(0, 0x81, 0), grenade_update(&gs), state_extra = gs.unk17 | (u32)gs.unk60 << 8; }
static void grenade_init_low_right(void) { GRENADE(0, 0x80, PLAYER_FACING_RIGHT), grenade_update(&gs), state_extra = gs.unk17 | (u32)gs.unk60 << 8; }
static void grenade_init_high_left(void) { GRENADE(0, 0x82, 0), grenade_update(&gs), state_extra = gs.unk17 | (u32)gs.unk60 << 8; }
static void grenade_init_thrown_right(void) { GRENADE(0, 0, PLAYER_FACING_RIGHT), grenade_update(&gs), state_extra = gs.unk17 | (u32)gs.unk60 << 8; }
static void grenade_init_thrown_left(void) { GRENADE(0, 0, 0), grenade_update(&gs), state_extra = gs.unk17 | (u32)gs.unk60 << 8; }
#define PLAYER_HERE() (g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, ((struct MainObj*)&g_Player)->hurt_box = &state_hit_box, g_Player.hp = 0x10, SPIKE_IMMUNE_SET(g_Player, 0))
#define FLY(kind, setup) (GRENADE(1, kind, 0), gs.unk50.data = grenade_hit_box, setup, grenade_fly(&gs))
static void grenade_hits_player_bursts(void) { FLY(0x40, PLAYER_HERE()); }
static void grenade_hits_player(void) { FLY(0, PLAYER_HERE()); }
static void grenade_flies_on(void) { FLY(0, 0); }
static void grenade_off_screen(void) { FLY(0x40, gs.x_pos.i.hi = 0x200); }
static void grenade_hits_wall(void)
{
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    FLY(0x40, (state_terrain(0x38), gs.unk68 = (struct Unk_unk68*)grenade_terrain_box, SP_CUR_MAIN_OBJ = (struct MainObj*)&gs));
    SP_CUR_MAIN_OBJ = current;
}
static void grenade_despawn(void) { GRENADE(2, 0, 0), grenade_update(&gs), state_extra = gs.unk17 | (u32)gs.unk60 << 8; }
static void grenade_rests(void) { GRENADE(3, 0, 0), grenade_idle(&gs); }
static void (*const grenade_cases[])(void) = {
    grenade_init_lob_right,
    grenade_init_lob_left,
    grenade_init_low_right,
    grenade_init_high_left,
    grenade_init_thrown_right,
    grenade_init_thrown_left,
    grenade_hits_player_bursts,
    grenade_hits_player,
    grenade_flies_on,
    grenade_off_screen,
    grenade_hits_wall,
    grenade_despawn,
    grenade_rests,
};
static const u32 grenade_expected[] = {
    0x1u, 0xFF408101u, 0xB00000u, 0x4B0000u, 0x30000u, 0x0u, 0x0u, 0x50000u, 0x210u, 0x0u,
    0x1u, 0xFF008101u, 0x500000u, 0x4B0000u, 0xFFFD0000u, 0x0u, 0x0u, 0x50000u, 0x210u, 0x0u,
    0x1u, 0xFF408001u, 0xA10000u, 0x360000u, 0x30000u, 0x18000u, 0x0u, 0x50000u, 0x210u, 0x0u,
    0x1u, 0xFF008201u, 0x580000u, 0x670000u, 0xFFFE8000u, 0xFFFE8000u, 0x0u, 0x50000u, 0x210u, 0x0u,
    0x1u, 0xFF400001u, 0xA10000u, 0x360000u, 0x30000u, 0x18000u, 0x400000u, 0x50000u, 0x516u, 0x0u,
    0x1u, 0xFF000001u, 0x5F0000u, 0x360000u, 0xFFFD0000u, 0x18000u, 0x400000u, 0x50000u, 0x516u, 0x0u,
    0x2u, 0x4001u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x2100u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x4001u, 0x2000000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x4001u, 0x7C0000u, 0x5C0000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x2100u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x3u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_grenade(u32 row)
{
    return object_run(grenade_cases[row], row, &grenade_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "grenade_states", 0, 0, COUNT(grenade_cases), test_grenade },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(grenade_cases);
