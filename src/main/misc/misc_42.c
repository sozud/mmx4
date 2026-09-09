// MiscObj, misc_object_update_funcs[42]
// 800CFE98..800D0374
#include "common.h"

void func_800CFE98(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010EFD0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_42", func_800CFEE0);

INCLUDE_ASM("main/nonmatchings/misc/misc_42", func_800D0118);
