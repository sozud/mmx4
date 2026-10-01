// MiscObj, misc_object_update_funcs[9]
// 800C9D64..800C9EAC
#include "common.h"

void owner_fx_update(struct MiscObj* self)
{
    if (self->state == 0) {
        owner_fx_init(self);
    } else {
        owner_fx_animate(self);
    }
}

void owner_fx_init(struct MiscObj* self)
{
    self->on_screen = 1;
    self->unk3C = (void*)self->ext.misc_9.owner->sprite_frames;
    self->animation_table = (u32**)self->ext.misc_9.owner->animation_table;
    self->unk40 = self->ext.misc_9.owner->unk40;
    self->unk42 = self->ext.misc_9.owner->unk42 & 0x7FFF;
    self->unk16 = 5;
    self->bg_offset = (s8)(u8)self->ext.misc_9.owner->bg_offset;
    set_animation(self, self->unk2);
    self->state = (u8)self->state + 1;
    is_on_screen(BASE_OBJECT(self));
}

void owner_fx_animate(struct MiscObj* self)
{
    u8 on_screen;

    if (self->ext.misc_9.owner->ext.packed == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (FLICKER_ENABLED) {
            self->on_screen ^= 1;
        }
        if (self->on_screen != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
        if (self->animation_step.fields.event != 1) {
            return;
        }
    }
    ZeroObjectState(OBJECT_HEADER(self));
}
