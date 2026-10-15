#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 anchored_mine_main_expected[] = { 0u, 1u, 0x1606060u, 0u };
static u32 test_anchored_mine_main(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.x_pos.val = 23093344;
    obj.y_pos.val = 0;
    obj.unk5 = 1;
    obj.state = 0;
    anchored_mine_main(&obj);
    observed_values[0] = (u32)obj.ext.main_44.saved_unk5;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk18.val;
    observed_values[3] = (u32)obj.unk1C.val;
    return c_test_observe(0, row, observed_values, anchored_mine_main_expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "anchored_mine_main", 0, 0, 1, test_anchored_mine_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
