#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/visuals/visual_30_colonel_fx.h"

static struct MainObj fx_owner;
#define sv state_room.visual
#define FX(st, mode, phase) (state_reset(mode, phase, 0), memset(&fx_owner, 0, sizeof(fx_owner)), fx_owner.x_pos.i.hi = 0x80, fx_owner.y_pos.i.hi = 0x100, fx_owner.unk42 = 0x8123, fx_owner.bg_offset = 1, fx_owner.animation_table = (void*)state_table, sv.unk50 = (struct PlayerObj*)&fx_owner, sv.state = st)
#define FX_SEEN() (state_extra = (u8)sv.unk54 | (u32)(u8)sv.unk16 << 8 | (u32)(u8)sv.bg_offset << 16 | (u32)(u8)sv.unk5C.value << 24)
static void cx_init(void)
{
    FX(0, 0, 0);
    sv.unk2 = 0x23;
    fx_owner.unk15 = 0x40;
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_beam_in_left(void)
{
    FX(1, 0, 0);
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_beam_in_right(void)
{
    FX(1, 0, 0);
    sv.unk15 = 0x40;
    colonel_fx_update(&sv);
}
static void cx_beam_in_done(void)
{
    FX(1, 0, 1);
    sv.unk5C.value = 1;
    colonel_fx_update(&sv);
}
static void cx_beam_in_wait(void)
{
    FX(1, 0, 1);
    colonel_fx_update(&sv);
}
static void cx_flash_left(void)
{
    FX(1, 1, 0);
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_flash_right(void)
{
    FX(1, 1, 0);
    sv.unk15 = 0x40;
    colonel_fx_update(&sv);
}
static void cx_flash_done(void)
{
    FX(1, 1, 1);
    sv.unk54 = 1;
    colonel_fx_update(&sv);
}
static void cx_flash_wait(void)
{
    FX(1, 1, 1);
    sv.unk54 = 2;
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_slash_left(void)
{
    FX(1, 2, 0);
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_slash_right(void)
{
    FX(1, 2, 0);
    sv.unk15 = 0x40;
    colonel_fx_update(&sv);
}
static void cx_slash_done(void)
{
    FX(1, 2, 1);
    sv.unk54 = 1;
    colonel_fx_update(&sv);
}
static void cx_slash_wait(void)
{
    FX(1, 2, 1);
    sv.unk54 = 2;
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_ground(void)
{
    FX(1, 3, 0);
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_ground_done(void)
{
    FX(1, 3, 1);
    sv.unk54 = 1;
    colonel_fx_update(&sv);
}
static void cx_ground_wait(void)
{
    FX(1, 3, 1);
    sv.unk54 = 2;
    colonel_fx_update(&sv);
    FX_SEEN();
}
static void cx_owner_gone(void)
{
    FX(1, 3, 1);
    sv.unk54 = 2;
    fx_owner.state = 2;
    colonel_fx_update(&sv);
}
static void cx_despawn(void)
{
    FX(2, 0, 0);
    sv.active = 1;
    colonel_fx_update(&sv);
}

static void (*const colonel_fx_states_cases[])(void) = {
    cx_init,
    cx_beam_in_left,
    cx_beam_in_right,
    cx_beam_in_done,
    cx_beam_in_wait,
    cx_flash_left,
    cx_flash_right,
    cx_flash_done,
    cx_flash_wait,
    cx_slash_left,
    cx_slash_right,
    cx_slash_done,
    cx_slash_wait,
    cx_ground,
    cx_ground_done,
    cx_ground_wait,
    cx_owner_gone,
    cx_despawn,
};
static const u32 colonel_fx_states_expected[] = { 0x201u, 0x400300u, 0u, 0u, 0u, 0u, 0u, 0x50123u, 0x10000u, 0u, 0x10001u, 0xFF000000u, 0x7B0000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0x400u, 0u, 0x10001u, 0xFF400000u, 0x850000u, 0x200000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10002u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10001u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10101u, 0xFF000000u, 0x850000u, 0xF00000u, 0u, 0u, 0u, 0x50000u, 0x400u, 0u, 0x10101u, 0xFF400000u, 0x7B0000u, 0xF00000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10002u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10101u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 0x10201u, 0xFF000000u, 0x790000u, 0xA30000u, 0u, 0u, 0u, 0x50000u, 0x430u, 0u, 0x10201u, 0xFF400000u, 0x870000u, 0xA30000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10002u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10201u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 0x10301u, 0xFF000000u, 0x800000u, 0x1200000u, 0u, 0u, 0u, 0x50000u, 0x420u, 0u, 0x10002u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10301u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_colonel_fx_states(u32 row)
{
    return object_run(colonel_fx_states_cases[row], row, &colonel_fx_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "colonel_fx_states", 0, 0, COUNT(colonel_fx_states_cases), test_colonel_fx_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(colonel_fx_states_cases);
