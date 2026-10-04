// EffectObj, effect_object_update_funcs[31]
// 800BC4D8..800BC518
#include "common.h"

void floor_trap_explode(struct EffectObj* self);
void floor_trap_wait(struct EffectObj* self);

void floor_trap_update(struct EffectObj* self)
{
    if (self->state == 0) {
        floor_trap_wait(self);
    } else {
        floor_trap_explode(self);
    }
}
