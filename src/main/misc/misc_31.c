// MiscObj, misc_object_update_funcs[31]
// 800CDE44..800CE114
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_31", func_800CDE44);

INCLUDE_ASM("main/nonmatchings/misc/misc_31", func_800CDF4C);

void func_800CE080(struct MiscObj* self)
{
    if (D_80171EA9 != self->ext.misc_31.animation) {
        self->animation_step.fields.frame_index = D_80171EA9 == 0 ? 0x57 : 0x56;
        self->ext.misc_31.animation = D_80171EA9;
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_800CE0D8(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    D_8010EC38[arg0->state](arg0);
}

void (*D_8010EC38[3])(struct MiscObj*) = {
    func_800CDE44,
    func_800CDF4C,
    func_800CE080,
};

union AnimationStep D_8010EC44[36] = {
    { .packed = 0x3101000F },
    { .packed = 0x3201000D },
    { .packed = 0x3301000A },
    { .packed = 0x31010008 },
    { .packed = 0x32010007 },
    { .packed = 0x33010006 },
    { .packed = 0x31010006 },
    { .packed = 0x32010005 },
    { .packed = 0x33010005 },
    { .packed = 0x31010004 },
    { .packed = 0x32010005 },
    { .packed = 0x33010005 },
    { .packed = 0x31010006 },
    { .packed = 0x32010006 },
    { .packed = 0x33010007 },
    { .packed = 0x31010008 },
    { .packed = 0x3201000A },
    { .packed = 0x3301000D },
    { .packed = 0x3101000F },
    { .packed = 0x3301000D },
    { .packed = 0x3201000A },
    { .packed = 0x31010008 },
    { .packed = 0x33010007 },
    { .packed = 0x32010006 },
    { .packed = 0x31010006 },
    { .packed = 0x33010005 },
    { .packed = 0x32010005 },
    { .packed = 0x31010004 },
    { .packed = 0x33010005 },
    { .packed = 0x32010005 },
    { .packed = 0x31010006 },
    { .packed = 0x33010006 },
    { .packed = 0x32010007 },
    { .packed = 0x31010008 },
    { .packed = 0x3301000A },
    { .packed = 0x32DD000D },
};

u32* D_8010ECD4[1] = { (u32*)D_8010EC44 };
