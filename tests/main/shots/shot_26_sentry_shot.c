#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_26_sentry_shot.h"

void sentry_shot_fly(struct ShotObj*);
void sentry_shot_idle(struct ShotObj*);
extern u8 sentry_shot_hit_boxes[8];
static struct WeaponObj sentry_owner;
#define ss state_room.shot
#define SENTRY(st) (state_reset(0, 0, 0), memset(&sentry_owner, 0, sizeof(sentry_owner)), memset(weapon_objects, 0, sizeof(weapon_objects)), sentry_owner.animation_table = (void*)state_table, sentry_owner.unk42 = 0x8123, ss.active = 1, ss.state = st, ss.unk7C = &sentry_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, ss.x_vel.val = 0x10000, ss.y_vel.val = -0x8000, g_Player.x_pos.i.hi = 0x400, g_Player.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1))

static const u8 sentry_init_kinds[] = { 2, 5, 6, 10, 13, 14, 8, 18, 21, 22, 26, 29, 30, 24, 0, 0 };
static u32 sentry_init_row;
static void sentry_init(void)
{
    static u32 collision_state;
    SENTRY(0);
    ss.unk2 = sentry_init_kinds[sentry_init_row];
    sentry_owner.unk15 = sentry_init_row == 14 ? PLAYER_FACING_RIGHT : 0;
    if (sentry_init_row == 15)
        ss.unk84.collision_state = &collision_state;
    sentry_shot_update(&ss);
}
static const u32 sentry_init_expected[] = {
    0x1u, 0xFF000201u, 0x8A0000u, 0x540000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000501u, 0x8A0000u, 0x540000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000601u, 0x8A0000u, 0x540000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000A01u, 0x760000u, 0x540000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000D01u, 0x760000u, 0x540000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000E01u, 0x760000u, 0x540000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000801u, 0x800000u, 0x500000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF001201u, 0x760000u, 0x6C0000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF001501u, 0x760000u, 0x6C0000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF001601u, 0x760000u, 0x6C0000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF001A01u, 0x8A0000u, 0x6C0000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF001D01u, 0x8A0000u, 0x6C0000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF001E01u, 0x8A0000u, 0x6C0000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF001801u, 0x800000u, 0x700000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF400001u, 0x8D0000u, 0x600000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
    0x1u, 0xFF000001u, 0x730000u, 0x600000u, 0x20000u, 0xFFFF0000u, 0x0u, 0x50123u, 0x0u, 0x0u,
};
static u32 test_sentry_init(u32 row)
{
    sentry_init_row = row;
    return object_run(sentry_init, row, &sentry_init_expected[row * 10]);
}

#define PLAYER_HERE() (g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, ((struct MainObj*)&g_Player)->hurt_box = &state_hit_box, g_Player.hp = 0x10, SPIKE_IMMUNE_SET(g_Player, 0))
#define FLY(setup) (SENTRY(1), ss.unk50.data = sentry_shot_hit_boxes, setup, sentry_shot_fly(&ss))
static void sentry_destroyed(void) { FLY((((struct MainObj*)&ss)->hp = 1, state_hit((struct MainObj*)&ss, 0, 0, 1))); }
static void sentry_hits_player(void) { FLY(PLAYER_HERE()); }
static void sentry_hits_wall(void) { FLY(ss.unk70 = 4); }
static void sentry_flies_on(void) { FLY(0); }
static void sentry_off_screen(void) { FLY(ss.x_pos.i.hi = 0x200); }
static void sentry_despawn(void) { SENTRY(2), sentry_shot_update(&ss); }
static void sentry_idle(void) { SENTRY(3), sentry_shot_idle(&ss); }
static void (*const sentry_fly_cases[])(void) = {
    sentry_destroyed,
    sentry_hits_player,
    sentry_hits_wall,
    sentry_flies_on,
    sentry_off_screen,
    sentry_despawn,
    sentry_idle,
};
static const u32 sentry_fly_expected[] = {
    0x2u, 0x1u, 0x810000u, 0x608000u, 0x10000u, 0xFFFF8000u, 0x0u, 0x48000u, 0x0u, 0x2100u,
    0x2u, 0x1u, 0x810000u, 0x608000u, 0x10000u, 0xFFFF8000u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x810000u, 0x608000u, 0x10000u, 0xFFFF8000u, 0x0u, 0x40000u, 0x0u, 0x2100u,
    0x1u, 0x1u, 0x810000u, 0x608000u, 0x10000u, 0xFFFF8000u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x2010000u, 0x608000u, 0x10000u, 0xFFFF8000u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x10000u, 0xFFFF8000u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x3u, 0x1u, 0x800000u, 0x600000u, 0x10000u, 0xFFFF8000u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_sentry_fly(u32 row)
{
    return object_run(sentry_fly_cases[row], row, &sentry_fly_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "sentry_shot_init", 0, 0, COUNT(sentry_init_kinds), test_sentry_init },
    { "sentry_shot_fly", 0, 0, COUNT(sentry_fly_cases), test_sentry_fly },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sentry_init_kinds) + COUNT(sentry_fly_cases);
