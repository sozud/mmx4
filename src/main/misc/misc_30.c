// MiscObj, misc_object_update_funcs[30]
// 800CDCC0..800CDE44
#include "common.h"

void func_800CDCC0(struct MiscObj* arg0)
{
    D_8010EC30[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_30", func_800CDCFC);

void func_800CDE24(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
