#include "common.h"

void (*option_toggle_state_funcs[3])(struct MiscObj*) = {
    func_800CDE44,
    func_800CDF4C,
    option_toggle_refresh,
};
