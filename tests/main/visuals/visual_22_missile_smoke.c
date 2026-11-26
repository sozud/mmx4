#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_22_missile_smoke.h"

static struct PlayerObj smoke_owner;
#define mv state_room.visual
#define SMOKE(st, kind, setup) (state_reset(0, 0, 0), memset(&smoke_owner, 0, sizeof(smoke_owner)), smoke_owner.active = 1, smoke_owner.shot_types[0] = 2, smoke_owner.last_shot_type = 0x40, smoke_owner.unk15 = PLAYER_FACING_RIGHT, smoke_owner.x_pos.i.hi = 0x90, smoke_owner.y_pos.i.hi = 0x70, mv.active = 1, mv.state = st, mv.unk2 = kind, mv.unk15 = PLAYER_FACING_RIGHT, mv.unk50 = &smoke_owner, mv.x_pos.i.hi = 0x80, mv.y_pos.i.hi = 0x60, setup, missile_smoke_update(&mv), state_extra = mv.unk17 | (u32)mv.on_screen << 8)
static void smoke_init_trail(void) { SMOKE(0, 0x10, 0); }
static void smoke_init_puff(void) { SMOKE(0, 0, 0); }
static void smoke_grows(void) { SMOKE(1, 3, 0); }
static void smoke_done(void) { SMOKE(1, 7, 0); }
static void smoke_trails(void) { SMOKE(1, 0x10, 0); }
static void smoke_other_shot(void) { SMOKE(1, 0x10, smoke_owner.shot_types[0] = 1); }
static void smoke_owner_gone(void) { SMOKE(1, 0x10, smoke_owner.active = 0); }
static void smoke_shot_ended(void) { SMOKE(1, 0x10, smoke_owner.last_shot_type = 0); }
static void smoke_despawn(void) { SMOKE(2, 7, 0); }
static void (*const smoke_cases[])(void) = {
    smoke_init_trail,
    smoke_init_puff,
    smoke_grows,
    smoke_done,
    smoke_trails,
    smoke_other_shot,
    smoke_owner_gone,
    smoke_shot_ended,
    smoke_despawn,
};
static const u32 smoke_expected[] = {
    0x1u, 0xFF401001u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x125u, 0x0u,
    0x1u, 0xFF000101u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x121u, 0x0u,
    0x1u, 0xFF400401u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x122u, 0x0u,
    0x2u, 0x400701u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0x401001u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x100u, 0x0u,
    0x0u, 0x400000u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x400000u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x400000u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x400000u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_smoke(u32 row)
{
    return object_run(smoke_cases[row], row, &smoke_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "missile_smoke_states", 0, 0, COUNT(smoke_cases), test_smoke },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(smoke_cases);
