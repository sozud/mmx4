// MiscObj, misc_object_update_funcs[21]
// 800CB884..800CB8F8
#include "common.h"

void center_sprite_update(struct MiscObj* self)
{
    if (self->state == 0) {
        self->on_screen = 1;
        self->bg_offset = -1;
        self->animation_step.fields.frame_index = 0;
        self->unk38 = 0;
        self->unk3C = SP_SPRITE_FRAMES;
        self->animation_table = 0;
        self->unk40 = 0x600;
        self->unk42 = 0x7804;
        self->unk15 = 0;
        self->unk16 = 0;
        self->x_pos.i.hi = 0xA0;
        self->y_pos.i.hi = 0x78;
        self->state++;
    }
}
