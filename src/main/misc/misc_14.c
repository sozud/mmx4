// MiscObj, misc_object_update_funcs[14]
// 800CA754..800CA86C
#include "common.h"

void func_800CA754(register struct MiscObj* self)
{
    struct MiscObj* source;
    u8 state;
    u8 bg_offset;

    source = self->ext.pointer.unk50;
    state = self->state + 1;
    self->unk40 = source->unk40;
    self->unk42 = source->unk42 & 0x7FFF;
    self->animation_table = source->animation_table;
    self->unk3C = source->unk3C;
    bg_offset = source->bg_offset;
    self->unk15 = 0;
    self->unk16 = 7;
    self->state = state;
    self->bg_offset = bg_offset;
    func_80015D90(ANIMATED_OBJECT(self), 2, self->unk2);
    self->unk7 = 0xA;
    is_on_screen(BASE_OBJECT(self));
}

void func_800CA7E4(struct MiscObj* self)
{
    if (--self->unk7 == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}

void func_800CA830(struct MiscObj* arg0)
{
    D_8010E64C[arg0->state](arg0);
}

void (*D_8010E64C[2])(struct MiscObj*) = {
    func_800CA754,
    func_800CA7E4,
};
