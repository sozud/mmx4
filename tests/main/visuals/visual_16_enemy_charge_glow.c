#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_16_enemy_charge_glow.h"

static struct MainObj glow_owner;
#define gv state_room.visual
#define GLOW(st, kind, id_) (state_reset(0, 0, 0), memset(&glow_owner, 0, sizeof(glow_owner)), glow_owner.active = 1, glow_owner.id = id_, glow_owner.unk5 = 3, glow_owner.unk15 = PLAYER_FACING_RIGHT, glow_owner.x_pos.i.hi = 0x90, glow_owner.y_pos.i.hi = 0x70, gv.active = 1, gv.state = st, gv.unk2 = kind, gv.unk42 = 0x8123, gv.unk50 = (struct PlayerObj*)&glow_owner, gv.x_pos.i.hi = 0x80, gv.y_pos.i.hi = 0x60)
static void glow_init_charger(void) { GLOW(0, 0, 0x26), enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_init_other(void) { GLOW(0, 0, 0x27), enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_init_shot(void) { GLOW(0, 1, 0x27), enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_charger_full(void) { GLOW(1, 0, 0x26), glow_owner.ext.main_38.unk88 = 1, enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_other_full(void) { GLOW(1, 0, 0x27), glow_owner.ext.main_38.unk88 = 1, enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_charge_released(void) { GLOW(1, 0, 0x26), glow_owner.ext.main_38.unk88 = 2, enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_owner_moved_on(void) { GLOW(1, 0, 0x26), glow_owner.unk5 = 2, enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_shot_gone(void) { GLOW(1, 1, 0x27), glow_owner.active = 0, enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_shot_hit(void) { GLOW(1, 1, 0x27), ((struct ShotObj*)&glow_owner)->unk8C.word = 1, enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_shot_flies(void) { GLOW(1, 1, 0x27), enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void glow_despawn(void) { GLOW(2, 1, 0x27), enemy_charge_glow_update(&gv), state_extra = gv.unk17 | gv.on_screen << 8; }
static void (*const glow_cases[])(void) = {
    glow_init_charger,
    glow_init_other,
    glow_init_shot,
    glow_charger_full,
    glow_other_full,
    glow_charge_released,
    glow_owner_moved_on,
    glow_shot_gone,
    glow_shot_hit,
    glow_shot_flies,
    glow_despawn,
};
static const u32 glow_expected[] = {
    0x1u, 0xFF400001u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x114u, 0x0u,
    0x1u, 0xFF400001u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x108u, 0x0u,
    0x1u, 0xFF400101u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50123u, 0x10Du, 0x0u,
    0x1u, 0xFF000001u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x58123u, 0x113u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x100u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x100u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x100u, 0x0u,
    0x2u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x100u, 0x0u,
    0x2u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x100u, 0x0u,
    0x1u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x48123u, 0x100u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x58123u, 0x0u, 0x0u,
};
static u32 test_glow(u32 row)
{
    return object_run(glow_cases[row], row, &glow_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "enemy_charge_glow_states", 0, 0, COUNT(glow_cases), test_glow },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(glow_cases);
