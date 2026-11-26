#include "test_runtime.h"
#include "main/misc/misc_30_spore_rain_fx.h"

struct spore_rain_fx_animate_case {
    u32 state, unk2, unk54, x_pos;
    u32 expected[8];
};
static const struct spore_rain_fx_animate_case spore_rain_fx_animate_cases[] = {
    { 2, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, -1, 1, 33554946, { 0u, 0u, 0u, 1u, 0x200u, 0x2000202u, 0u, 0u } },
    { 0, -1, 0, 0, { 0xFFFFFFFFu, 0u, 1u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_spore_rain_fx_animate(u32 row)
{
    const struct spore_rain_fx_animate_case* c = &spore_rain_fx_animate_cases[row];
    u32 observed_values[8];
    struct MiscObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0.state = c->state;
    obj.unk2 = c->unk2;
    obj.ext.misc_30.unk54 = c->unk54;
    child_0.x_pos.val = c->x_pos;
    obj.ext.misc_30.owner = &child_0;
    spore_rain_fx_animate(&obj);
    observed_values[0] = (u32)obj.ext.misc_30.unk54;
    observed_values[1] = (u32)obj.ext.misc_30.unk56;
    observed_values[2] = (u32)obj.on_screen;
    observed_values[3] = (u32)obj.state;
    observed_values[4] = (u32)obj.x_pos.i.hi;
    observed_values[5] = (u32)obj.x_pos.val;
    observed_values[6] = (u32)obj.y_pos.i.hi;
    observed_values[7] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

#include "support/state_cases.h"
static struct MainObj spore_owner;
#define sm state_room.misc
#define SPORE(count, side) (state_reset(0, 0, 0), memset(&spore_owner, 0, sizeof(spore_owner)), spore_owner.state = 1, sm.active = 1, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.ext.misc_30.owner = &spore_owner, sm.ext.misc_30.unk56 = count, sm.ext.misc_30.unk54 = side, spore_rain_fx_update(&sm), state_extra = (u8)sm.ext.misc_30.unk54 | (u32)(u16)sm.ext.misc_30.unk56 << 16)
static void sp_landed(void)
{
    SPORE(1, 0);
}
static void sp_zig(void) { SPORE(5, 0); }
static void sp_zag(void) { SPORE(5, 0x20); }

static void (*const sp_cases[])(void) = {
    sp_landed,
    sp_zig,
    sp_zag,
};
static const u32 sp_expected[] = {
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0u,
    0x1u,
    0xA00000u,
    0x610000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x40020u,
    0u,
    0u,
    0x1u,
    0x600000u,
    0x610000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x40000u,
    0u,
};
static u32 test_sp(u32 row)
{
    return object_run(sp_cases[row], row, &sp_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "spore_rain_steps", 0, 0, COUNT(sp_cases), test_sp },
    { "spore_rain_fx_animate", 0, 0, 3, test_spore_rain_fx_animate },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + COUNT(sp_cases);
