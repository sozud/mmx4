// MiscObj, misc_object_update_funcs[30]
// 800CDCC0..800CDE44
#include "common.h"

void spore_rain_fx_update(struct MiscObj* self)
{
    spore_rain_fx_state_funcs[self->state](self);
}

void spore_rain_fx_animate(struct MiscObj* self)
{
    struct MainObj* owner = self->ext.misc_30.owner;

    if (owner->state >= 2) {
        self->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (self->unk2 == 0) {
        if (--self->ext.misc_30.unk56 == 0) {
            self->state = 1;
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
            return;
        }
        if (self->ext.misc_30.unk54 == 0) {
            self->x_pos.i.hi += 0x20;
        } else {
            self->x_pos.i.hi -= 0x20;
        }
        self->y_pos.i.hi++;
        self->ext.misc_30.unk54 ^= 0x20;
        animate_object(ANIMATED_OBJECT(self));
    } else {
        if (--self->ext.misc_30.unk54 == 0) {
            self->state = 1;
        }
        self->x_pos.val = self->ext.misc_30.owner->x_pos.val;
        self->y_pos.val = self->ext.misc_30.owner->y_pos.val;
        animate_object(ANIMATED_OBJECT(self));
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void spore_rain_fx_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*spore_rain_fx_state_funcs[2])(struct MiscObj*) = {
    spore_rain_fx_animate,
    spore_rain_fx_despawn,
};
