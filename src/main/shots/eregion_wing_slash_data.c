#include "common.h"

u8 eregion_wing_slash_hit_box[4] = { 0x8C, 0xB8, 0x96, 0x87 };

void (*eregion_wing_slash_state_funcs[])(struct ShotObj*) = {
    func_8009A448,
    eregion_wing_slash_active,
    eregion_wing_slash_despawn,
};
