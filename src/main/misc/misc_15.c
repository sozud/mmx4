// MiscObj, misc_object_update_funcs[15]
// 800CA86C..800CAC18
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_15", func_800CA86C);

void func_800CA954(struct MiscObj* self)
{
    u8 value;

    self->on_screen = 0;
    if (self->unk2 == 0) {
        value = self->unk6;
        self->unk6 = value + 1;
        if (!(value & 1)) {
            return;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void func_800CA9B0(struct MiscObj* arg0)
{
    D_8010E678[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_15", func_800CA9EC);

INCLUDE_ASM("main/nonmatchings/misc/misc_15", func_800CAB10);

union AnimationStep D_8010E654[4] = {
    { .packed = 0x00010006 },
    { .packed = 0x01010006 },
    { .packed = 0x02010005 },
    { .packed = 0x02FD0001 },
};

union AnimationStep D_8010E664[3] = {
    { .packed = 0x03000001 },
    { .packed = 0x05000001 },
    { .packed = 0x04000001 },
};

union AnimationStep* D_8010E670[2] = { D_8010E654, D_8010E664 };

void (*D_8010E678[2])(struct MiscObj*) = {
    func_800CA86C,
    func_800CA954,
};
