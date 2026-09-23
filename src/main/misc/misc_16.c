// MiscObj, misc_object_update_funcs[16]
// 800CAC18..800CADF8
#include "common.h"

void func_800CAC18(struct MiscObj* arg0)
{
    D_8010E680[arg0->state](arg0);
}

void func_800CAC54(struct MiscObj* self)
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
        func_80015D60(self, 0x19);
    } else {
        self->y_vel.val = FIXED(-1.25);
        self->x_vel.val = FIXED(-0.5);
        func_80015D60(self, 0x1A);
    }

    self->unk2C = 0;
    self->unk28 = 0;
}

INCLUDE_ASM("main/nonmatchings/misc/misc_16", func_800CACF0);

void func_800CADD8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010E680[3])(struct MiscObj*) = {
    func_800CAC54,
    func_800CACF0,
    func_800CADD8,
};
