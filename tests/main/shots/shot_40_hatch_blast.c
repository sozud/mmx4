#include "test_runtime.h"

#include "support/tile_fixture.h"
#include "support/state_cases.h"
#include "main/shots/shot_40_hatch_blast.h"

void hatch_blast_despawn(struct ShotObj*);
static struct WeaponObj hatch_owner;
#define hs state_room.shot
#define HATCH(st, step) (state_reset(step, 0, 0), memset(&hatch_owner, 0, sizeof(hatch_owner)), memset(&engine_obj, 0, sizeof(engine_obj)), memset(misc_objects, 0, sizeof(misc_objects)), hatch_owner.active = 1, hatch_owner.id = 0x3F, hatch_owner.unk7 = 1, hs.active = 1, hs.state = st, hs.unk7C = &hatch_owner, hs.x_pos.i.hi = 0x80, hs.y_pos.i.hi = 0x60, hs.timer = 5, tile_fixture_begin_layout(0x10, 2), WEAPON_FRAME_COUNTER = 4)
#define DONE() (state_extra = (u8)hs.unk8A | (u8)hs.timer << 8 | (u32)(u8)hatch_owner.unk7 << 16 | (hs.unk50.data != NULL) << 24 | (u32)(u8)misc_objects[1].active << 28, hs.x_vel.val = tile_fixture_end())
static void hatch_opening(void)
{
    HATCH(1, 0), hs.animation_step.fields.relative_step = 1, hatch_blast_update(&hs), DONE();
}
static void hatch_opened(void) { HATCH(1, 0), hs.animation_step.fields.relative_step = 0, hatch_blast_update(&hs), DONE(); }
static void hatch_fire_ends(void) { HATCH(1, 1), hs.timer = 0, hatch_blast_update(&hs), DONE(); }
static void hatch_fire_elsewhere(void) { HATCH(1, 1), hs.unk70 = 1, hatch_blast_update(&hs), DONE(); }
static void hatch_fire_cracks_wall(void) { HATCH(1, 1), engine_obj.stage = 7, hs.unk70 = 1, hatch_blast_update(&hs), DONE(); }
static void hatch_fire_in_air(void) { HATCH(1, 1), engine_obj.stage = 7, hatch_blast_update(&hs), DONE(); }
static void hatch_fire_cracked(void) { HATCH(1, 1), engine_obj.stage = 7, hs.unk70 = 8, hs.unk7 = 1, hatch_blast_update(&hs), DONE(); }
static void hatch_crack_between(void) { HATCH(1, 2), hs.animation_step.fields.relative_step = 1, hs.unk8A = 5, WEAPON_FRAME_COUNTER = 5, hatch_blast_update(&hs), DONE(); }
static void hatch_wall_breaks(void) { HATCH(1, 2), hs.unk8A = 1, WEAPON_FRAME_COUNTER = 5, hatch_blast_update(&hs), DONE(); }
static void hatch_despawn(void) { HATCH(2, 0), hatch_blast_update(&hs), DONE(); }
static void (*const hatch_cases[])(void) = {
    hatch_opening,
    hatch_opened,
    hatch_fire_ends,
    hatch_fire_elsewhere,
    hatch_fire_cracks_wall,
    hatch_fire_in_air,
    hatch_fire_cracked,
    hatch_crack_between,
    hatch_wall_breaks,
    hatch_despawn,
};
static const u32 hatch_expected[] = {
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10500u,
    0x0u,
    0x101u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x101F000u,
    0x0u,
    0x201u,
    0xFF000001u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x10000u,
    0x0u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10400u,
    0x0u,
    0x1000101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10010413u,
    0x41002100u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10400u,
    0x0u,
    0x1000101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10400u,
    0x0u,
    0x201u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x10504u,
    0x0u,
    0x2u,
    0x1u,
    0x800000u,
    0x600000u,
    0x5E00100u,
    0x0u,
    0x0u,
    0x50000u,
    0x10010500u,
    0x41000000u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x500u,
    0x0u,
};
static u32 test_hatch(u32 row)
{
    return object_run(hatch_cases[row], row, &hatch_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "hatch_blast_states", 0, 0, COUNT(hatch_cases), test_hatch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hatch_cases);
