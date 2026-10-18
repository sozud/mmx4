#include "test_runtime.h"
#include "main/visuals/visual_31_gunship_exhaust.h"
#include "main/55C4.h"
#include "main/mains/main_67_gunship.h"

static u32 exhaust_case(void)
{
    struct VisualObj obj, before;
    struct PlayerObj owner, owner_before;
    struct BackgroundObj backgrounds_before[3];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(background_objects, 0, sizeof(background_objects));
    owner.active = 0x41;
    owner.x_pos.i.hi = 300;
    owner.y_pos.i.hi = 200;
    obj.active = 0x41;
    obj.id = 31;
    obj.state = 2;
    obj.unk2 = 4;
    obj.unk54 = 2;
    obj.bg_offset = 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.on_screen = 7;
    obj.unk50 = &owner;
    obj.animation_table = (u32**)gunship_animations;
    set_animation(&obj, 0);
    before = obj;
    owner_before = owner;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    gunship_exhaust_main(&obj);
    before.unk54 = 1;
    before.on_screen = 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    actual = (u8)obj.state | ((u32)obj.unk54 << 8) | ((u32)(u8)obj.on_screen << 24);
    return actual;
}
static const CTestCase gunship_exhaust_raw_subtype_cases[] = { exhaust_case };
static const u32 gunship_exhaust_raw_subtype_cases_expected[] = { 0x1000102u };

#include "support/state_cases.h"

static struct MainObj exhaust_ship;
#define sv state_room.visual
#define JET(st, kind) (state_reset(0, 0, 0), memset(&exhaust_ship, 0, sizeof(exhaust_ship)), exhaust_ship.active = 1, exhaust_ship.x_pos.i.hi = 0x100, exhaust_ship.y_pos.i.hi = 0x80, exhaust_ship.unk15 = 0x40, sv.unk50 = (struct PlayerObj*)&exhaust_ship, sv.state = st, sv.unk2 = kind)
#define JET_SEEN() (state_extra = (u8)sv.unk54 | (u32)(u8)sv.unk56 << 8)
static void ge_init_a(void)
{
    JET(0, 0);
    cur_random = 1;
    gunship_exhaust_update(&sv);
    JET_SEEN();
}
static void ge_init_b(void)
{
    JET(0, 1);
    cur_random = 2;
    gunship_exhaust_update(&sv);
    JET_SEEN();
}
static void ge_init_c(void)
{
    JET(0, 2);
    cur_random = 3;
    gunship_exhaust_update(&sv);
    JET_SEEN();
}
static void ge_init_d(void)
{
    JET(0, 3);
    cur_random = 4;
    gunship_exhaust_update(&sv);
    JET_SEEN();
}
static void ge_delay(void)
{
    JET(1, 0);
    sv.unk56 = 2;
    gunship_exhaust_update(&sv);
    JET_SEEN();
}
static void ge_delay_done(void)
{
    JET(1, 0);
    gunship_exhaust_update(&sv);
}
static void ge_follow_a(void)
{
    JET(2, 0);
    sv.unk54 = 3;
    gunship_exhaust_update(&sv);
    JET_SEEN();
}
static void ge_follow_b(void)
{
    JET(2, 1);
    sv.unk54 = 3;
    gunship_exhaust_update(&sv);
}
static void ge_follow_c(void)
{
    JET(2, 2);
    sv.unk54 = 3;
    gunship_exhaust_update(&sv);
}
static void ge_follow_d(void)
{
    JET(2, 3);
    sv.unk54 = 3;
    gunship_exhaust_update(&sv);
}
static void ge_burn_out(void)
{
    JET(2, 0);
    sv.unk54 = 1;
    gunship_exhaust_update(&sv);
}
static void ge_ship_gone(void)
{
    JET(2, 0);
    sv.unk54 = 3;
    exhaust_ship.active = 0;
    gunship_exhaust_update(&sv);
}
static void ge_despawn(void)
{
    JET(3, 0);
    sv.active = 1;
    gunship_exhaust_update(&sv);
}

static void (*const gunship_exhaust_states_cases[])(void) = {
    ge_init_a,
    ge_init_b,
    ge_init_c,
    ge_init_d,
    ge_delay,
    ge_delay_done,
    ge_follow_a,
    ge_follow_b,
    ge_follow_c,
    ge_follow_d,
    ge_burn_out,
    ge_ship_gone,
    ge_despawn,
};
static const u32 gunship_exhaust_states_expected[] = { 1u, 0xFF400000u, 0xC40000u, 0x770000u, 0u, 0u, 0u, 0x50000u, 0x177u, 0u, 1u, 0xFF400100u, 0xEC0000u, 0x770000u, 0u, 0u, 0u, 0x50000u, 0x276u, 0u, 1u, 0xFF400200u, 0x1140000u, 0x770000u, 0u, 0u, 0u, 0x50000u, 0x375u, 0u, 1u, 0xFF400300u, 0x13C0000u, 0x770000u, 0u, 0u, 0u, 0x50000u, 0x474u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x100u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 2u, 0u, 0xC40000u, 0x770000u, 0u, 0u, 0u, 0x40000u, 2u, 0u, 2u, 0x100u, 0xEC0000u, 0x770000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 0x200u, 0x1140000u, 0x770000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 0x300u, 0x13C0000u, 0x770000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 3u, 0u, 0xC40000u, 0x770000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 3u, 0u, 0xC40000u, 0x770000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_gunship_exhaust_states(u32 row)
{
    return object_run(gunship_exhaust_states_cases[row], row, &gunship_exhaust_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "gunship_exhaust_states", 0, 0, COUNT(gunship_exhaust_states_cases), test_gunship_exhaust_states },
    { "gunship_exhaust_raw_subtype", gunship_exhaust_raw_subtype_cases, gunship_exhaust_raw_subtype_cases_expected, COUNT(gunship_exhaust_raw_subtype_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gunship_exhaust_states_cases) + COUNT(gunship_exhaust_raw_subtype_cases);
