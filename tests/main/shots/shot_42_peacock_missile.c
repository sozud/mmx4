#include "test_runtime.h"
s32 peacock_missile_hit_target(struct ShotObj*);

static u32 missile_case(u32 mode)
{
    struct ShotObj obj, before;
    struct WeaponObj target, target_before;
    struct Unk_unk68 box = { 0, 0, 8, 8 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&target, 0, sizeof(target));
    obj.active = 0x41;
    obj.id = 42;
    obj.unk5 = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk68 = &box;
    obj.unk7C = &target;
    target.active = 0x41;
    target.id = 0x17;
    target.unk68 = &box;
    target.x_pos.val = (mode == 0 ? 100 : 117) * 65536;
    target.y_pos.val = 200 * 65536;
    before = obj;
    target_before = target;
    actual = peacock_missile_hit_target(&obj);
    assert(actual == (mode == 0 ? 1 : 0));
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(target) / 4; i++)
        assert(((u32*)&target)[i] == ((u32*)&target_before)[i]);
    assert(box.unk0 == 0 && box.unk1 == 0 && box.unk2 == 8 && box.unk3 == 8);
    return actual;
}
#define CASE(m)                                            \
    static u32 peacock_missile_collision_missile_##m(void) \
    {                                                      \
        return missile_case(m);                            \
    }
CASE(0)
CASE(1)
#define ENTRY(m) peacock_missile_collision_missile_##m,
static const CTestCase peacock_missile_collision_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 peacock_missile_collision_cases_expected[] = { 0x1u, 0x0u };
#undef CASE
#undef ENTRY

static const u32 peacock_missile_hit_target_expected[] = { 0u, 1u };
static u32 test_peacock_missile_hit_target(u32 row)
{
    u32 observed_values[2];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    child_0.active = 1;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    return_value = peacock_missile_hit_target(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, peacock_missile_hit_target_expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "peacock_missile_collision", peacock_missile_collision_cases, peacock_missile_collision_cases_expected, COUNT(peacock_missile_collision_cases), 0 },
    { "peacock_missile_hit_target", 0, 0, 1, test_peacock_missile_hit_target },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(peacock_missile_collision_cases) + 1;
