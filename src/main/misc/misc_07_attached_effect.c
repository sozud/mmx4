// MiscObj, misc_object_update_funcs[7]
// 800C938C..800C9510
#include "common.h"

void attached_effect_update(struct MiscObj* self)
{
    attached_effect_state_funcs[self->state](self);
}

void attached_effect_init(struct MiscObj* self)
{
    s16 x;

    set_animation(self, 0xA);
    self->x_pos.val = ((struct FixedPointPosition*)self->ext.misc_7.position)->x;
    self->y_pos.val = ((struct FixedPointPosition*)self->ext.misc_7.position)->y;
    if (self->unk2 != 0) {
        if (self->unk15 != 0) {
            x = self->x_pos.u.hi + 3;
        } else {
            x = self->x_pos.u.hi - 3;
        }
        self->x_pos.i.hi = x;
    }
    self->state = 1;
}

void attached_effect_animate(struct MiscObj* self)
{
    s16 x_pos;
    animate_object(ANIMATED_OBJECT(self));
    self->x_pos.val = ((struct FixedPointPosition*)self->ext.misc_7.position)->x;
    self->y_pos.val = ((struct FixedPointPosition*)self->ext.misc_7.position)->y;
    if (self->unk2 != 0) {
        if (self->unk15 != 0) {
            x_pos = (u16)self->x_pos.i.hi + 3;
        } else {
            x_pos = (u16)self->x_pos.i.hi - 3;
        }
        self->x_pos.i.hi = x_pos;
    }
    if (self->animation_step.fields.event != 0) {
        self->state = 2;
    }
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void attached_effect_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*attached_effect_state_funcs[3])(struct MiscObj*) = {
    attached_effect_init,
    attached_effect_animate,
    attached_effect_despawn,
};
