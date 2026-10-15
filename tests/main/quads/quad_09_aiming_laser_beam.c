#include "test_runtime.h"
void func_800D69A8(struct QuadObj*, struct PlayerObj*, struct PlayerObj*);

static const u32 func_800D69A8_expected[] = { 0u, 0u, 0xFFFFFFF7u, 6u, 3u, 6u, 3u, 0xFFFFFFFAu, 3u, 0u };
static u32 test_func_800D69A8(u32 row)
{
    u32 observed_values[10];
    struct QuadObj obj;
    struct PlayerObj argument_obj_1;
    struct PlayerObj argument_obj_2;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&argument_obj_2, 0, sizeof(argument_obj_2));
    func_800D69A8(&obj, &argument_obj_1, &argument_obj_2);
    observed_values[0] = (u32)obj.vertices[0].x.val;
    observed_values[1] = (u32)obj.vertices[0].y.val;
    observed_values[2] = (u32)obj.vertices[1].x.i.hi;
    observed_values[3] = (u32)obj.vertices[1].y.i.hi;
    observed_values[4] = (u32)obj.vertices[2].x.i.hi;
    observed_values[5] = (u32)obj.vertices[2].y.i.hi;
    observed_values[6] = (u32)obj.vertices[3].x.i.hi;
    observed_values[7] = (u32)obj.vertices[3].y.i.hi;
    observed_values[8] = (u32)obj.x_pos.i.hi;
    observed_values[9] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_800D69A8_expected, 10);
}

#include "support/aiming_cancellation.h"
AIMING_CANCEL_SIX(2)
AIMING_CANCEL_MODE(2, 6)
static const CTestCase aiming_laser_beam_cancellation_cases[] = { AIMING_CANCEL_SIX_ENTRIES(2) AIMING_CANCEL_ENTRIES(2, 6) };

static const u32 aiming_laser_beam_cancellation_cases_expected[] = { 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u, 0x0u, 0x641234u, 0xC82468u, 0x6u };
const struct CTestGroup c_test_groups[] = {
    { "func_800D69A8", 0, 0, 1, test_func_800D69A8 },
    { "aiming_laser_beam_cancellation", aiming_laser_beam_cancellation_cases, aiming_laser_beam_cancellation_cases_expected, COUNT(aiming_laser_beam_cancellation_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(aiming_laser_beam_cancellation_cases);
