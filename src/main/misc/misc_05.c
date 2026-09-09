// MiscObj, misc_object_update_funcs[5]
// 800C8FA8..800C91B0
#include "common.h"

void func_800C8FA8(struct MiscObj* arg0)
{
    D_8010DC3C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_05", func_800C8FE4);

INCLUDE_ASM("main/nonmatchings/misc/misc_05", func_800C903C);

void func_800C90A0(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_05", func_800C90C0);

INCLUDE_ASM("main/nonmatchings/misc/misc_05", func_800C90F8);

void func_800C9190(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
