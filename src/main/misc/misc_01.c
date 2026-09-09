// MiscObj, misc_object_update_funcs[1]
// 800C7BF4..800C7EDC
#include "common.h"

void func_800C7BF4(struct MiscObj* arg0)
{
    D_8010DABC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_01", func_800C7C30);

INCLUDE_ASM("main/nonmatchings/misc/misc_01", func_800C7D40);

void func_800C7D84(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_01", func_800C7DA4);
