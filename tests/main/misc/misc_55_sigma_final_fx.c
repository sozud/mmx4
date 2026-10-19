#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_55_sigma_final_fx.h"
void sigma_final_fx_charge(struct MiscObj*);
void sigma_final_fx_follow(struct MiscObj*);

static struct MainObj final_fx_owner;
#define sm state_room.misc
#define SFX(kind) (state_reset(0, 0, 0), memset(&final_fx_owner, 0, sizeof(final_fx_owner)), final_fx_owner.animation_table = (void*)state_table, final_fx_owner.unk42 = 0x8010, final_fx_owner.x_pos.i.hi = 0x80, final_fx_owner.y_pos.i.hi = 0x60, sm.active = 1, sm.unk2 = kind, sm.ext.misc_55.owner = (void*)&final_fx_owner, background_objects[0].x_pos.i.hi = 0x400, background_objects[0].y_pos.i.hi = 0x200, cur_random = 0x1234)
static void sf_init_low(void)
{
    SFX(0);
    func_800D3084(&sm);
}
static void sf_init_high(void)
{
    SFX(1);
    func_800D3084(&sm);
}
static void sf_init_drift(void)
{
    SFX(2);
    func_800D3084(&sm);
}
static void sf_init_other(void)
{
    SFX(3);
    func_800D3084(&sm);
}
static void sf_follow(void)
{
    SFX(0);
    sigma_final_fx_follow(&sm);
}
static void sf_follow_owner_gone(void)
{
    SFX(0);
    final_fx_owner.state = 2;
    sigma_final_fx_follow(&sm);
}
static void sf_follow_away(void)
{
    SFX(0);
    final_fx_owner.x_pos.i.hi = 0x1000;
    sigma_final_fx_follow(&sm);
}
static void sf_charge(void)
{
    SFX(0);
    sm.animation_step.fields.relative_step = 1;
    sigma_final_fx_charge(&sm);
}
static void sf_charge_done(void)
{
    SFX(0);
    sigma_final_fx_charge(&sm);
}

static void (*const sigma_final_fx_states_cases[])(void) = {
    sf_init_low,
    sf_init_high,
    sf_init_drift,
    sf_init_other,
    sf_follow,
    sf_follow_owner_gone,
    sf_follow_away,
    sf_charge,
    sf_charge_done,
};
static const u32 sigma_final_fx_states_expected[] = { 1u, 0xFF000001u, 0x4FF0000u, 0x2790000u, 0u, 0u, 0u, 0x50010u, 0u, 0u, 1u, 0xFF000101u, 0x4FD0000u, 0x2590000u, 0u, 0u, 0u, 0x50010u, 0u, 0u, 3u, 0xFF000201u, 0x3E00000u, 0x26A0000u, 0x30000u, 0u, 0xFFFFF000u, 0x50013u, 0u, 0u, 4u, 0xFF000301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50010u, 0u, 0u, 2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_sigma_final_fx_states(u32 row)
{
    return object_run(sigma_final_fx_states_cases[row], row, &sigma_final_fx_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_final_fx_states", 0, 0, COUNT(sigma_final_fx_states_cases), test_sigma_final_fx_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_final_fx_states_cases);
