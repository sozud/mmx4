// MiscObj, misc_object_update_funcs[33]
// 800CE340..800CE894
#include "common.h"

void func_800CE340(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010EDDC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE388);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE670);

void func_800CE6AC(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE6CC);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE754);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE7C8);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE81C);
