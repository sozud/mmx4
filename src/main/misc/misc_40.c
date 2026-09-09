// MiscObj, misc_object_update_funcs[40]
// 800CFB70..800CFE98
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFB70);

INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFC6C);

INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFD38);

INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFE00);

void func_800CFE3C(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800CFE5C(struct MiscObj* arg0)
{
    D_8010EFC4[arg0->state](arg0);
}
