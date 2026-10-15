#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 drone_pod_random_explosion_expected[] = { 1u };
static u32 test_drone_pod_random_explosion(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&visual_objects, 0, sizeof(visual_objects));
    main_bss_state.frame_counter = -1048575;
    drone_pod_random_explosion(&obj);
    observed_values[0] = (u32)obj.ext.main_70.unk85;
    return c_test_observe(0, row, observed_values, drone_pod_random_explosion_expected, 1);
}
#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "drone_pod_random_explosion", 0, 0, 1, test_drone_pod_random_explosion },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
