// MiscObj, misc_object_update_funcs[53]
// 800D2A74..800D3084
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2A74);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2B9C);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2C04);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2CA4);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2D7C);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2DCC);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2E1C);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2E64);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2EDC);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2F34);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2FC4);

void func_800D301C(struct MiscObj* arg0)
{
    engine_obj.unkF = 1;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_800D3048(struct MiscObj* arg0)
{
    D_8010F580[arg0->state](arg0);
}
