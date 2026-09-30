// MiscObj, misc_object_update_funcs[27]
// 800CC908..800CCA34
#include "common.h"

void owner_aura_update(struct MiscObj* self)
{
    owner_aura_state_funcs[self->state](self);
}

void owner_aura_follow(struct MiscObj* self)
{
    s8 timer;
    s8 owner_state;

    self->x_pos.val = self->ext.misc_5.owner->x_pos.val;
    self->y_pos.val = self->ext.misc_5.owner->y_pos.val;
    self->unk15 = self->ext.misc_5.owner->unk15;
    self->unk42 = self->ext.misc_5.owner->unk42;
    animate_object(ANIMATED_OBJECT(self));
    owner_state = self->ext.misc_5.owner->state;
    if (owner_state == 2 || owner_state == 5 || owner_state == 8) {
        self->state = 1;
        return;
    }
    if (self->unk6 == 0) {
        timer = ++self->unk7;
        if (timer & 1) {
            self->on_screen = 0;
            return;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void owner_aura_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*owner_aura_state_funcs[])(struct MiscObj*) = {
    owner_aura_follow,
    owner_aura_despawn,
};
