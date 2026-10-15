#include "test_runtime.h"

static const u32 func_80027BE4_expected[] = { 0xFFFFFF80u, 0u, 6u, 0xFFFFFFFFu };
static u32 test_func_80027BE4(u32 row)
{
    u32 observed_values[4];
    struct BackgroundObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk1C = 6;
    obj.x_pos.i.hi = 8;
    engine_obj.stage = 5;
    g_Player.ride_state = -1;
    obj.unk20 = -1;
    g_Player.y_pos.i.hi = 13944;
    func_80027BE4(&obj);
    observed_values[0] = (u32)g_Player.hp;
    observed_values[1] = (u32)g_Player.x_pos.i.hi;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    observed_values[3] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_80027BE4_expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "func_80027BE4", 0, 0, 1, test_func_80027BE4 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
