// MiscObj, misc_object_update_funcs[11]
// 800CA0C8..800CA228
#include "common.h"

void blink_marker_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    blink_marker_state_funcs[self->state](self);
}

void blink_marker_init(struct MiscObj* self)
{
    s8 variant;

    variant = self->unk2;
    switch (variant) {
    case 1:
    case 2:
        set_animation(self, variant + 1);
        break;
    case 3:
        is_on_screen(BASE_OBJECT(self));
        break;
    }
    self->ext.misc_11.active = 0;
    self->state = (u8)self->state + 1;
}

void blink_marker_main(struct MiscObj* self)
{
    if (self->ext.misc_11.active != 0) {
        self->state++;
    }
    if (self->unk2 == 0) {
        if (FLICKER_ENABLED) {
            self->on_screen ^= 1;
        }
        if (self->on_screen == 0) {
            return;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}

void blink_marker_despawn(struct MiscObj* self)
{
    self->ext.misc_11.active = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*blink_marker_state_funcs[])(struct MiscObj*) = {
    blink_marker_init,
    blink_marker_main,
    blink_marker_despawn,
};
