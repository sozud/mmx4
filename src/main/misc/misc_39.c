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

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CF844);

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CF898);

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CF8F0);

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CF950);

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CFAC8);

INCLUDE_ASM("main/nonmatchings/misc/misc_39", func_800CFB20);

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
