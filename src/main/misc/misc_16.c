// MiscObj, misc_object_update_funcs[16]
// 800CAC18..800CADF8
#include "common.h"

void vent_puff_update(struct MiscObj* self)
{
    vent_puff_state_funcs[self->state](self);
}

void vent_puff_init(struct MiscObj* self)
{
    u16 timer = self->ext.misc_16.timer;

    if (timer != 0) {
        self->ext.misc_16.timer = timer - 1;
        return;
    }

    self->unk15 = 0;
    self->state = 1;
    self->unk6 = 0;
    self->bg_offset = 0;

    if (self->unk2 == 0) {
        self->y_vel.val = FIXED(-0.625);
        self->x_vel.val = FIXED(-0.25);
        set_animation(self, 0x19);
    } else {
        self->y_vel.val = FIXED(-1.25);
        self->x_vel.val = FIXED(-0.5);
        set_animation(self, 0x1A);
    }

    self->unk2C = 0;
    self->unk28 = 0;
}

// vent_puff_rise
INCLUDE_ASM("main/nonmatchings/misc/misc_16", func_800CACF0);

void vent_puff_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*vent_puff_state_funcs[3])(struct MiscObj*) = {
    vent_puff_init,
    func_800CACF0,
    vent_puff_despawn,
};
