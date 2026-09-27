#include "common.h"

void (*double_afterimage_state_funcs[])(struct MiscObj*) = {
    func_800D1990,
    func_800D1A48,
    double_afterimage_despawn,
};
