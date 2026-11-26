#include "test_runtime.h"
#include "main/quads/quad_09_aiming_laser_beam.h"
#include "main/visuals/visual_18_aiming_laser_scope.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"

#include "support/aiming_cancellation.h"
AIMING_CANCEL_MODE(3, 0)
static const CTestCase aiming_laser_scope_cancellation_cases[] = { AIMING_CANCEL_ENTRIES(3, 0) };

static const u32 aiming_laser_scope_cancellation_cases_expected[] = { 0x0u, 0x641234u, 0xC82468u, 0x6u };
#include "support/state_cases.h"
#include "support/player_gfx_archive.h"
static u32 scope_sprites[32];
static struct PlayerObj scope_player;
#define lv state_room.visual
#define SCOPE(st, setup) (scope_player = g_Player, state_reset(0, 0, 0), gfx_archive_fill(), TEST_PLAYER_GFX = (u8*)&gfx_archive, TEST_SPRITE_FRAMES = (u8*)scope_sprites, GFX_QUEUE_RESET(), memset(&engine_obj, 0, sizeof(engine_obj)), g_Player.weapon = 6, g_Player.hp = 0x10, g_Player.unk15 = PLAYER_FACING_RIGHT, g_Player.x_pos.i.hi = 0x100, g_Player.y_pos.i.hi = 0x80, lv.active = 1, lv.state = st, setup, aiming_laser_scope_update(&lv), state_extra = lv.unk17 | (u32)lv.on_screen << 8 | GFX_QUEUED() << 16, g_Player = scope_player)
static void scope_boss_intro(void)
{
    SCOPE(1, engine_obj.unkF = 1);
}
static void scope_other_weapon(void) { SCOPE(1, g_Player.weapon = 5); }
static void scope_init(void) { SCOPE(0, 0); }
static void scope_follows(void) { SCOPE(1, lv.animation_table = (void*)state_table); }
static void (*const scope_cases[])(void) = {
    scope_boss_intro,
    scope_other_weapon,
    scope_init,
    scope_follows,
};
static const u32 scope_expected[] = {
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x400001u | GFX_DECODED_FRAME(0x12) << 24,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x20000u | WEAPON_PALETTE_1,
    0x100u | GFX_ONE_UPLOAD,
    0x0u,
    0x1u,
    0x400001u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x100u,
    0x0u,
};
static u32 test_scope(u32 row)
{
    return object_run(scope_cases[row], row, &scope_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "aiming_laser_scope_cancellation", aiming_laser_scope_cancellation_cases, aiming_laser_scope_cancellation_cases_expected, COUNT(aiming_laser_scope_cancellation_cases), 0 },
    { "aiming_laser_scope_states", 0, 0, COUNT(scope_cases), test_scope },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(aiming_laser_scope_cancellation_cases) + COUNT(scope_cases);
