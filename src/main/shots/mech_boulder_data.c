#include "common.h"

u8 mech_boulder_debris[8] = { 0x0F, 0x10, 0x11, 0x0F, 0x10, 0x11, 0, 0 };

void (*mech_boulder_state_funcs[])(struct ShotObj*) = {
    func_8009A5F4,
    mech_boulder_fall,
    mech_boulder_despawn,
    mech_boulder_shockwave_start,
    mech_boulder_shockwave,
    mech_boulder_shockwave_despawn,
};
