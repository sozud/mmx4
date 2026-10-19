#include "test_runtime.h"
#include "main/shots/shot_38_owl_cyclone.h"
#include "support/state_cases.h"

#define ss state_room.shot

#include "support/pool_full.h"
static u32 pool_full_owl_cyclone_spawn_trail(void)
{
    u32 actual;
    pf_prepare();
    pf_shot.unk84.value = 0;
    pf_snapshot();
    owl_cyclone_spawn_trail(&pf_shot);
    pf_shot_expected.unk84.value = 5;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_owl_cyclone_spawn_trail,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
static struct MainObj cyclone_owner;
#define CYC(st, kind) (state_reset(0, 0, 0), memset(&cyclone_owner, 0, sizeof(cyclone_owner)), cyclone_owner.active = 1, cyclone_owner.x_pos.i.hi = 0x80, cyclone_owner.y_pos.i.hi = 0x60, ss.state = st, ss.unk2 = kind, ss.unk7C = (struct WeaponObj*)&cyclone_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define COLUMN(phase, t) (CYC(1, 5), ss.unk84.value = phase, ss.timer = t, owl_cyclone_update(&ss), state_extra = ss.unk84.value | ss.timer << 8)
static void oc_init_low(void)
{
    CYC(0, 0);
    owl_cyclone_update(&ss);
}
static void oc_init_mid(void)
{
    CYC(0, 1);
    cyclone_owner.unk15 = 0x40;
    owl_cyclone_update(&ss);
}
static void oc_init_level(void)
{
    CYC(0, 2);
    owl_cyclone_update(&ss);
}
static void oc_init_level_crouch(void)
{
    CYC(0, 2);
    cyclone_owner.unk17 = 4;
    owl_cyclone_update(&ss);
}
static void oc_init_rise(void)
{
    CYC(0, 3);
    owl_cyclone_update(&ss);
}
static void oc_init_high(void)
{
    CYC(0, 4);
    owl_cyclone_update(&ss);
}
static void oc_init_column(void)
{
    CYC(0, 5);
    owl_cyclone_update(&ss);
}
static void oc_fly(void)
{
    CYC(1, 0);
    ss.x_vel.val = 0x40000;
    owl_cyclone_update(&ss);
}
static void oc_fly_hit(void)
{
    CYC(1, 0);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    owl_cyclone_update(&ss);
}
static void oc_fly_orphan(void)
{
    CYC(1, 0);
    cyclone_owner.active = 0;
    owl_cyclone_update(&ss);
}
static void oc_fly_away(void)
{
    CYC(1, 0);
    ss.x_pos.i.hi = 0x1000;
    owl_cyclone_update(&ss);
}
static void oc_column_owner_gone(void)
{
    CYC(1, 5);
    cyclone_owner.state = 2;
    owl_cyclone_update(&ss);
}
static void oc_column_tick(void) { COLUMN(0, 3); }
static void oc_column_hover(void) { COLUMN(0, 1); }
static void oc_column_drop(void) { COLUMN(1, 1); }
static void oc_column_rest(void) { COLUMN(2, 1); }
static void oc_column_fall(void) { COLUMN(3, 1); }
static void oc_column_end(void) { COLUMN(4, 1); }

static void (*const owl_cyclone_states_cases[])(void) = {
    oc_init_low,
    oc_init_mid,
    oc_init_level,
    oc_init_level_crouch,
    oc_init_rise,
    oc_init_high,
    oc_init_column,
    oc_fly,
    oc_fly_hit,
    oc_fly_orphan,
    oc_fly_away,
    oc_column_owner_gone,
    oc_column_tick,
    oc_column_hover,
    oc_column_drop,
    oc_column_rest,
    oc_column_fall,
    oc_column_end,
};
static const u32 owl_cyclone_states_expected[] = { 1u, 0xFF000000u, 0x750000u, 0x4B0000u, 0xFFFBB000u, 0x45000u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000100u, 0x900000u, 0x4D0000u, 0x52800u, 0x2A000u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000200u, 0x6D0000u, 0x530000u, 0xFFFA0000u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000200u, 0x670000u, 0x5A0000u, 0xFFFA0000u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000300u, 0x670000u, 0x600000u, 0xFFFAD800u, 0xFFFD6000u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000400u, 0x6C0000u, 0x650000u, 0xFFFBB000u, 0xFFFBB000u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000500u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0u, 0x840000u, 0x600000u, 0x40000u, 0u, 0u, 0x40000u, 0u, 0x41000000u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x41002100u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x41000000u, 2u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x41000000u, 2u, 0x500u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0x500u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x200u, 0u, 1u, 0x500u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2D01u, 0u, 1u, 0x500u, 0x800000u, 0x600000u, 0u, 0x150000u, 0u, 0x40000u, 0xC02u, 0u, 1u, 0x500u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x3E03u, 0u, 1u, 0x500u, 0x800000u, 0x600000u, 0u, 0x150000u, 0u, 0x40000u, 0xC04u, 0u, 1u, 0x500u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 4u, 0u };

static u32 test_owl_cyclone_states(u32 row)
{
    return object_run(owl_cyclone_states_cases[row], row, &owl_cyclone_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "owl_cyclone_states", 0, 0, COUNT(owl_cyclone_states_cases), test_owl_cyclone_states },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(owl_cyclone_states_cases) + COUNT(pool_full_cases);
