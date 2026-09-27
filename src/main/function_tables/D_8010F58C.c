#include "common.h"

void (*sigma_final_fx_state_funcs[])(struct MiscObj*) = {
    func_800D3084,
    sigma_final_fx_charge,
    sigma_final_fx_despawn,
    sigma_final_fx_gust,
    sigma_final_fx_follow,
};
