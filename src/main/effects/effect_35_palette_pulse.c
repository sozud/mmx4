// EffectObj, effect_object_update_funcs[35]
// 800BD1A4..800BD1E4
#include "common.h"

void palette_pulse_update(struct EffectObj* self)
{
    if (self->state == 0) {
        palette_pulse_init(self);
    } else {
        func_800BD080(self);
    }
}
