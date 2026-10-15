#include "test_runtime.h"

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

static const u32 gunship_exhaust_main_expected[] = { 1u, 0xFFFFFFFFu, 0u, 0u };
static u32 test_gunship_exhaust_main(u32 row)
{
    u32 observed_values[4];
    struct VisualObj obj;
    struct PlayerObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0_present = 255;
    obj.unk2 = -1;
    obj.unk50 = child_0_present ? &child_0 : NULL;
    gunship_exhaust_main(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk54;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    observed_values[3] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, gunship_exhaust_main_expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "gunship_exhaust_raw_subtype", gunship_exhaust_raw_subtype_cases, gunship_exhaust_raw_subtype_cases_expected, COUNT(gunship_exhaust_raw_subtype_cases), 0 },
    { "gunship_exhaust_main", 0, 0, 1, test_gunship_exhaust_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gunship_exhaust_raw_subtype_cases) + 1;
