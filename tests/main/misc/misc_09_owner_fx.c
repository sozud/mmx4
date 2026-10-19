#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_09_owner_fx.h"

static struct ItemObj fx_owner;
#define sm state_room.misc
#define FX(st, onscreen) (state_reset(0, 0, 0), memset(&fx_owner, 0, sizeof(fx_owner)), fx_owner.animation_table = (void*)state_table, fx_owner.unk42 = 0x8123, fx_owner.bg_offset = 2, sm.active = 1, sm.state = st, sm.unk2 = 3, sm.on_screen = onscreen, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.ext.misc_9.owner = &fx_owner)
static void ofx_init(void)
{
    FX(0, 0);
    owner_fx_update(&sm);
    state_extra = sm.on_screen | sm.unk16 << 8 | (u8)sm.bg_offset << 16;
}
static void ofx_hidden(void)
{
    FX(1, 1);
    owner_fx_update(&sm);
    state_extra = sm.on_screen;
}
static void ofx_shown(void)
{
    FX(1, 0);
    owner_fx_update(&sm);
    state_extra = sm.on_screen;
}
static void ofx_event(void)
{
    FX(1, 0);
    sm.animation_step.fields.event = 1;
    owner_fx_update(&sm);
}
static void ofx_owner_gone(void)
{
    FX(1, 0);
    fx_owner.ext.packed = 1;
    owner_fx_update(&sm);
}

static void (*const owner_fx_states_cases[])(void) = {
    ofx_init,
    ofx_hidden,
    ofx_shown,
    ofx_event,
    ofx_owner_gone,
};
static const u32 owner_fx_states_expected[] = { 1u, 0xFF000301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50123u, 0x20501u, 0u, 1u, 0x301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0x301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_owner_fx_states(u32 row)
{
    return object_run(owner_fx_states_cases[row], row, &owner_fx_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "owner_fx_states", 0, 0, COUNT(owner_fx_states_cases), test_owner_fx_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(owner_fx_states_cases);
