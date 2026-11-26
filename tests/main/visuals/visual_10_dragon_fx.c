#include "test_runtime.h"
#include "main/visuals/visual_10_dragon_fx.h"

#include "support/state_cases.h"
void func_800B158C(struct VisualObj* arg0);

static const struct {
    u8 owner_active, owner_state, subtype, flag, event, toggle;
    u32 expected[3];
} flash_cases[] = {
    { 1, 2, 0, 0, 0, 0, { 0u, 0x00100010u, 0x1111u } },
    { 1, 1, 1, 1, 1, 0, { 0x00010141u, 0x00C801A8u, 0x2222u } },
    { 1, 1, 0, 1, 1, 0, { 0x01000041u, 0x00C80258u, 0x2222u } },
    { 0, 1, 0, 0, 0, 0, { 0u, 0x00100010u, 0x1111u } },
    { 1, 1, 0, 0, 0, 0, { 0x41u, 0x00C80258u, 0x1111u } },
    { 1, 1, 1, 1, 0, 1, { 0x00010141u, 0x00C801A8u, 0x2222u } },
    { 1, 1, 1, 1, 1, 1, { 0x00000141u, 0x00C801A8u, 0x2222u } },
};
static u32 flash(u32 row)
{
    static struct MainObj owner;
    struct VisualObj* fx = &state_room.visual;
    u32 observed[3];
    state_reset(flash_cases[row].toggle, 0, 0);
    memset(&owner, 0, sizeof(owner));
    owner.active = flash_cases[row].owner_active;
    owner.state = flash_cases[row].owner_state;
    owner.x_pos.i.hi = 0x200;
    owner.y_pos.i.hi = 0x100;
    owner.unk42 = 0x2222;
    ((u8*)&owner.ext)[0] = flash_cases[row].flag;
    fx->active = 0x41;
    fx->id = 10;
    fx->state = 1;
    fx->unk2 = flash_cases[row].subtype;
    fx->unk16 = VISUAL_SATURN_LAYER(0x10);
    fx->x_pos.i.hi = 0x10;
    fx->y_pos.i.hi = 0x10;
    fx->unk42 = 0x1111;
    fx->unk50 = (struct PlayerObj*)&owner;
    fx->animation_step.fields.event = flash_cases[row].event;
    func_800B158C(fx);
    observed[0] = (u8)fx->active | (u32)(u8)fx->unk2 << 8 | (u32)(u8)fx->unk5 << 16 | (u32)(u8)fx->animation_step.fields.event << 24;
    observed[1] = (u16)fx->x_pos.i.hi | (u32)(u16)fx->y_pos.i.hi << 16;
    observed[2] = fx->unk42;
    return c_test_observe(0, row, observed, flash_cases[row].expected, 3);
}


#define sv state_room.visual
#define DFX(st, kind, setup) (state_reset(0, 0, 0), sv.active = 0x41, sv.state = st, sv.unk2 = kind, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, setup, dragon_fx_update(&sv), state_extra = sv.unk17)
static void dfx_flash_left(void) { DFX(0, 0, 0); }
static void dfx_flash_right(void) { DFX(0, 1, 0); }
static void dfx_trail(void) { DFX(3, 0, sv.animation_step.fields.relative_step = 1); }
static void dfx_trail_end(void) { DFX(3, 0, sv.animation_step.fields.relative_step = -1); }

static void (*const dfx_cases[])(void) = {
    dfx_flash_left,
    dfx_flash_right,
    dfx_trail,
    dfx_trail_end,
};
static const u32 dfx_expected[] = {
    1u, 0xFF000041u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 5u, 0u,
    1u, 0xFF400141u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 5u, 0u,
    3u, 0x41u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
    4u, 0x41u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
};
static u32 test_dfx(u32 row)
{
    return object_run(dfx_cases[row], row, &dfx_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dragon_fx_states", 0, 0, COUNT(dfx_cases), test_dfx },
    { "flash_follows_owner_palette_and_sounds", NULL, NULL, COUNT(flash_cases), flash },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(flash_cases) + COUNT(dfx_cases);
