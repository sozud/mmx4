#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_34_split_mushroom_fx.h"

static struct PlayerObj fx_owner;
#define fv state_room.visual
#define SFX(st, kind, setup) (state_reset(0, 0, 0), memset(&fx_owner, 0, sizeof(fx_owner)), fx_owner.state = 1, fx_owner.x_pos.i.hi = 0x90, fx_owner.y_pos.i.hi = 0x70, fv.active = 1, fv.state = st, fv.unk2 = kind, fv.unk50 = &fx_owner, fv.x_pos.i.hi = 0x80, fv.y_pos.i.hi = 0x60, setup, split_mushroom_fx_update(&fv), state_extra = (u8)fv.unk5C.value | (u32)(u16)fv.unk5C.fields.unk5E << 16)
static void sfx_owner_split(void) { SFX(0, 0, fx_owner.state = 2); }
static void sfx_shuffle_done(void) { SFX(0, 0, fv.unk5C.fields.unk5E = 1); }
static void sfx_shuffle_right(void) { SFX(0, 0, fv.unk5C.fields.unk5E = 5); }
static void sfx_shuffle_left(void) { SFX(0, 0, (fv.unk5C.fields.unk5E = 5, fv.unk5C.value = 0x20)); }
static void sfx_follow_done(void) { SFX(0, 1, fv.unk5C.value = 1); }
static void sfx_follows(void) { SFX(0, 1, fv.unk5C.value = 5); }
static void sfx_despawn(void) { SFX(1, 1, 0); }
static void (*const sfx_cases[])(void) = {
    sfx_owner_split,
    sfx_shuffle_done,
    sfx_shuffle_right,
    sfx_shuffle_left,
    sfx_follow_done,
    sfx_follows,
    sfx_despawn,
};
static const u32 sfx_expected[] = {
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x1u, 0xA00000u, 0x610000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x40020u, 0x0u,
    0x0u, 0x1u, 0x600000u, 0x610000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x40000u, 0x0u,
    0x1u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x0u, 0x101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x4u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_sfx(u32 row)
{
    return object_run(sfx_cases[row], row, &sfx_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "split_mushroom_fx_states", 0, 0, COUNT(sfx_cases), test_sfx },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sfx_cases);
