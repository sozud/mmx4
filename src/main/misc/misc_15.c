// MiscObj, misc_object_update_funcs[15]
// 800CA86C..800CAC18
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_15", func_800CA86C);

INCLUDE_ASM("main/nonmatchings/misc/misc_15", func_800CA954);

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
