// MiscObj, misc_object_update_funcs[17]
// 800CADF8..800CB00C
#include "common.h"

void death_orb_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800CAE38(self);
    } else {
        death_orb_fly(self);
    }
}

// death_orb_init
INCLUDE_ASM("main/nonmatchings/misc/misc_17", func_800CAE38);

void death_orb_fly(struct MiscObj* self)
{
    if ((self->unk2 & 0x80) && (func_8002B1E8(BASE_OBJECT(self), 0x80000, 0x80000) == 1)) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x80000, 0x80000);
}

s8 death_orb_frames[4] = { 1, 3, 2, 3 };
