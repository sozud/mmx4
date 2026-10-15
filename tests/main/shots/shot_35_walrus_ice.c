#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

#define ICICLE_CASE(name, owner_state, ticks)                                             \
    static u32 name(void)                                                                 \
    {                                                                                     \
        struct ShotObj obj;                                                               \
        struct MainObj owner;                                                             \
        RECT offsets = { 11, 22, 33, 44 };                                                \
        u32 actual;                                                                       \
        memset(&obj, 0, sizeof(obj));                                                     \
        memset(&owner, 0, sizeof(owner));                                                 \
        memset(background_objects, 0, sizeof(background_objects));                        \
        background_objects[0].unk1E = 100;                                                \
        owner.unk6 = owner_state;                                                         \
        owner.ext.main_57.rect = &offsets;                                                \
        obj.unk7C = &owner;                                                               \
        obj.unk2 = 2;                                                                     \
        obj.timer = ticks;                                                                \
        obj.x_pos.i.hi = -10;                                                             \
        walrus_ice_icicle_wait_drop(&obj);                                                \
        assert(obj.unk7C == &owner && owner.ext.main_57.rect == &offsets);                \
        assert(owner.unk6 == owner_state && offsets.w == 33);                             \
        actual = obj.x_pos.u.hi | ((u32)(u8)obj.timer << 16) | ((u32)(u8)obj.unk6 << 24); \
        return actual;                                                                    \
    }
ICICLE_CASE(waiting, 0, 2)
ICICLE_CASE(expired, 0, 1)
ICICLE_CASE(owner_trigger, 5, 2)

static const CTestCase icicle_wait_cases[] = {
    waiting,
    expired,
    owner_trigger,
};
static const u32 icicle_wait_cases_expected[] = { 0x1FFF6u, 0x10F0095u, 0x10F0095u };
#undef ICICLE_CASE

static const u32 walrus_ice_ball_main_expected[] = { 6u, 0x80000000u, 0u, 0u, 0u, 0u };
static u32 test_walrus_ice_ball_main(u32 row)
{
    u32 observed_values[6];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&misc_objects, 0, sizeof(misc_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.x_pos.val = -2147483648;
    obj.y_pos.val = 0;
    obj.unk6 = 0;
    child_0_present = 255;
    child_0.unk5 = 0;
    obj.unk42 = 0;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    walrus_ice_ball_main(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk18.val;
    observed_values[2] = (u32)obj.unk1C.val;
    observed_values[3] = (u32)obj.unk42;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, walrus_ice_ball_main_expected, 6);
}

#include "support/projectile_damage.h"
DAMAGE_CASE(2)
DAMAGE_CASE(3)
DAMAGE_CASE(4)
DAMAGE_CASE(5)
DAMAGE_CASE(6)
DAMAGE_CASE(7)
DAMAGE_CASE(8)
DAMAGE_CASE(9)
DAMAGE_CASE(10)
static const CTestCase walrus_ice_damage_cases[] = { DAMAGE_ENTRY(2) DAMAGE_ENTRY(3) DAMAGE_ENTRY(4) DAMAGE_ENTRY(5) DAMAGE_ENTRY(6) DAMAGE_ENTRY(7) DAMAGE_ENTRY(8) DAMAGE_ENTRY(9) DAMAGE_ENTRY(10) };

static const u32 walrus_ice_damage_cases_expected[] = { 0x12350A06u, 0x12350006u, 0x92350701u, 0x12350A06u, 0x12350006u, 0x92350701u, 0x12350506u, 0x12350006u, 0x92350201u };
const struct CTestGroup c_test_groups[] = {
    { "icicle_wait", icicle_wait_cases, icicle_wait_cases_expected, COUNT(icicle_wait_cases), 0 },
    { "walrus_ice_ball_main", 0, 0, 1, test_walrus_ice_ball_main },
    { "walrus_ice_damage", walrus_ice_damage_cases, walrus_ice_damage_cases_expected, COUNT(walrus_ice_damage_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(icicle_wait_cases) + 1 + COUNT(walrus_ice_damage_cases);
