#include "common.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/misc/option_toggle_funcs.h"

void (*option_toggle_state_funcs[3])(struct MiscObj*) = {
    func_800CDE44,
    func_800CDF4C,
    option_toggle_refresh,
};
