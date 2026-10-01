// MiscObj, misc_object_update_funcs[14]
// 800CA754..800CA86C
#include "common.h"

void frame_ghost_init(register struct MiscObj* self)
{
    struct MiscObj* source;
    u8 state;

    source = self->ext.pointer.unk50;
    state = self->state + 1;
    self->unk40 = source->unk40;
    self->unk42 = source->unk42 & 0x7FFF;
    self->animation_table = source->animation_table;
    self->unk3C = source->unk3C;
    self->bg_offset = source->bg_offset;
    self->unk15 = 0;
    self->unk16 = 7;
    self->state = state;
    set_animation_frame(ANIMATED_OBJECT(self), 2, self->unk2);
    self->unk7 = 0xA;
    is_on_screen(BASE_OBJECT(self));
}

void frame_ghost_fade(struct MiscObj* self)
{
    if (--self->unk7 == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}

void frame_ghost_update(struct MiscObj* self)
{
    frame_ghost_state_funcs[self->state](self);
}

void (*frame_ghost_state_funcs[2])(struct MiscObj*) = {
    frame_ghost_init,
    frame_ghost_fade,
};
