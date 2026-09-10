// MiscObj, misc_object_update_funcs[36]
// 800CF2B8..800CF4B8
#include "common.h"

void func_800CF2B8(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010EF00[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_36", func_800CF300);

INCLUDE_ASM("main/nonmatchings/misc/misc_36", func_800CF428);

void func_800CF498(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010EF00[3])(struct MiscObj*) = {
    func_800CF300,
    func_800CF428,
    func_800CF498,
};
