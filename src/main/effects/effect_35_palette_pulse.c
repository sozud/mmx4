// EffectObj, effect_object_update_funcs[35]
// 800BD1A4..800BD1E4
#include "common.h"

u16 palette_pulse_palette[16] = {
    0,
    0xFFFF,
    0xAB3F,
    0x829F,
    0x81FF,
    0x815F,
    0x80DD,
    0x84D8,
    0x84B4,
    0x8470,
    0xAB3F,
    0x829F,
    0x81FF,
    0x815F,
    0x80DD,
    0x84D4,
};


void palette_pulse_update(struct EffectObj* self)
{
    if (self->state == 0) {
        palette_pulse_init(self);
    } else {
        func_800BD080(self);
    }
}
