#include "test_runtime.h"

struct func_800CDF4C_case {
    u32 timer, unk2, pressed, unk0, selection;
    u32 expected[2];
};
static const struct func_800CDF4C_case func_800CDF4C_cases[] = {
    { 255, 3, 0, 0, 255, { 3u, 0x7800u } },
    { 0, 0, 2048, 10, 0, { 0xFFFFFFFFu, 0u } },
    { 0, 0, 2048, 8, 0, { 0xFFFFFFFFu, 0u } },
    { 0, 0, 2048, 0, 0, { 0u, 0x7803u } },
};
static u32 test_func_800CDF4C(u32 row)
{
    const struct func_800CDF4C_case* c = &func_800CDF4C_cases[row];
    u32 observed_values[2];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800F1D90, 0, sizeof(D_800F1D90));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&game_info, 0, sizeof(game_info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.ext.misc_31.timer = c->timer;
    obj.unk2 = c->unk2;
    controller_input.pressed = c->pressed;
    game_info.unk0 = c->unk0;
    main_bss_state.transition.selection = c->selection;
    func_800CDF4C(&obj);
    observed_values[0] = (u32)obj.unk2;
    observed_values[1] = (u32)obj.unk42;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}
#undef controller_input
#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "func_800CDF4C", 0, 0, 4, test_func_800CDF4C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4;
