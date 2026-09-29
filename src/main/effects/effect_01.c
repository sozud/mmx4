// EffectObj, effect_object_update_funcs[1]
// 800B58A0..800B5960
#include "common.h"

void tile_animator_update(struct EffectObj* self)
{
    tile_animator_state_funcs[self->state](self);
}

void tile_animator_init(struct EffectObj* self)
{
    self->unk6 = 0;
    self->unk5 = 0;
    self->state++;
}

void tile_animator_step(struct EffectObj* self, s32 arg1, s32 arg2)
{
    if (++self->unk5 == 3) {
        self->unk5 = 0;
        if (++self->unk6 >= 5) {
            self->unk6 = 0;
        }
    }
    refresh_visible_tile_effect((u8)self->unk6, arg1, arg2);
}

void (*tile_animator_state_funcs[])(struct EffectObj*) = {
    tile_animator_init,
    tile_animator_step,
};
