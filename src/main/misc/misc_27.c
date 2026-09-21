// MiscObj, misc_object_update_funcs[27]
// 800CC908..800CCA34
#include "common.h"

void func_800CC908(struct MiscObj* arg0)
{
    D_8010E960[arg0->state](arg0);
}

void func_800CC944(struct MiscObj* self)
{
    s8 timer;
    s8 owner_state;

    self->x_pos.val = self->ext.misc_5.owner->x_pos.val;
    self->y_pos.val = self->ext.misc_5.owner->y_pos.val;
    self->unk15 = self->ext.misc_5.owner->unk15;
    self->unk42 = self->ext.misc_5.owner->unk42;
    func_80015DC8(ANIMATED_OBJECT(self));
    owner_state = self->ext.misc_5.owner->state;
    if (owner_state == 2 || owner_state == 5 || owner_state == 8) {
        self->state = 1;
        return;
    }
    if (self->unk6 == 0) {
        timer = (u8)self->unk7 + 1;
        self->unk7 = timer;
        if (timer & 1) {
            self->on_screen = 0;
            return;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void func_800CCA14(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010E960[])(struct MiscObj*) = {
    func_800CC944,
    func_800CCA14,
};
