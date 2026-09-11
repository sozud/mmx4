// MiscObj, misc_object_update_funcs[39]
// 800CF790..800CFB70
#include "common.h"

void func_800CF790(struct MiscObj* arg0)
{
    D_8010EF20[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CF7CC);

void func_800CF824(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800CF844(struct MiscObj* self)
{
    self->unk15 = 0x40;
    self->y_vel.val = FIXED(0.5);
    self->unk16 = 0;
    self->x_vel.val = 0;
    self->ext.misc_39.timer = 0xD6;
    func_80015D60(self, 0xB);
    self->unk5 = 1;
}

void func_800CF898(struct MiscObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    timer = self->ext.misc_39.timer - 1;
    self->ext.misc_39.timer = timer;
    if (timer == 0) {
        self->ext.misc_39.timer = 0x78;
        self->unk5 = 2;
    }
}

void func_800CF8F0(struct MiscObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->ext.misc_39.timer - 1;
    self->ext.misc_39.timer = timer;
    if (timer == 0) {
        func_80015D60(self, 0xC);
        func_80015D60(self->ext.misc_39.related, 0x21);
        self->unk5 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CF950);

void func_800CFAC8(struct MiscObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->ext.misc_39.timer - 1;
    self->ext.misc_39.timer = timer;
    if (timer == 0) {
        self->ext.misc_39.timer = 0x76;
        self->y_vel.val = FIXED(-1);
        self->unk5 = 5;
    }
}

void func_800CFB20(struct MiscObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    timer = arg0->ext.misc_39.timer - 1;
    arg0->ext.misc_39.timer = timer;
    if (timer == 0) {
        arg0->state = 1;
    }
}

void (*D_8010EF20[2])(struct MiscObj*) = {
    func_800CF7CC,
    func_800CF824,
};

void (*D_8010EF28[6])(struct MiscObj*) = {
    func_800CF844,
    func_800CF898,
    func_800CF8F0,
    func_800CF950,
    func_800CFAC8,
    func_800CFB20,
};
