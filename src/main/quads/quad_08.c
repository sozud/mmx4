// QuadObj, quad_object_update_funcs[8]
// 800D67A0..800D67DC
#include "common.h"

// QuadObj #8
void flash_band_update(struct QuadObj* arg0)
{
    flash_band_state_funcs[arg0->state](arg0);
}

void (*flash_band_state_funcs[])(struct QuadObj*) = {
    flash_band_init,
    flash_band_widen,
    flash_band_despawn,
};
