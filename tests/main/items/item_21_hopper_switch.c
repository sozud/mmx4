#include "test_runtime.h"
s32 hopper_switch_hopper_touching(struct ItemObj*);

static u32 live_hopper(void)
{
    struct ItemObj obj, before;
    struct MainObj pool_before[48];
    struct Unk_unk68 box = { 0, 0, 8, 8 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(main_objects, 0, sizeof(main_objects));
    obj.active = 0x41;
    obj.id = 21;
    obj.x_pos.val = 100 * 65536;
    obj.y_pos.val = 200 * 65536;
    obj.unk68 = &box;
    for (i = 0; i < 48; i++) {
        main_objects[i].active = 1;
        main_objects[i].id = 0x27;
    }
    main_objects[17].active = 0x41;
    main_objects[17].id = 0x29;
    main_objects[17].x_pos = obj.x_pos;
    main_objects[17].y_pos = obj.y_pos;
    main_objects[17].terrain_box = &box;
    before = obj;
    memcpy(pool_before, main_objects, sizeof(pool_before));
    actual = hopper_switch_hopper_touching(&obj);
    assert(actual == 1);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)main_objects)[i] == ((u32*)pool_before)[i]);
    assert(box.unk0 == 0 && box.unk1 == 0 && box.unk2 == 8 && box.unk3 == 8);
    return actual;
}
static const CTestCase hopper_switch_live_pool_cases[] = { live_hopper };
static const u32 hopper_switch_live_pool_cases_expected[] = { 0x1u };

static const u32 hopper_switch_hopper_touching_expected[] = { 0u };
static u32 test_hopper_switch_hopper_touching(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&main_objects, 0, sizeof(main_objects));
    main_objects[0].active = -1;
    main_objects[0].id = 0;
    return_value = hopper_switch_hopper_touching(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, hopper_switch_hopper_touching_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "hopper_switch_live_pool", hopper_switch_live_pool_cases, hopper_switch_live_pool_cases_expected, COUNT(hopper_switch_live_pool_cases), 0 },
    { "hopper_switch_hopper_touching", 0, 0, 1, test_hopper_switch_hopper_touching },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hopper_switch_live_pool_cases) + 1;
