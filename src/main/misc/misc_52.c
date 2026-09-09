// MiscObj, misc_object_update_funcs[52]
// 800D2190..800D2A74
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2190);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2420);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D24B4);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D254C);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D25AC);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D25FC);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D26F4);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2794);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2854);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D28BC);

void func_800D28E8(struct MiscObj* arg0)
{
    D_8010F528[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2924);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2970);

void func_800D29C0(struct PlayerObj* arg0)
{
    D_8010F530[arg0->unk6](arg0);
}

void func_800D29FC(struct BarObj* arg0)
{
    D_8010F538[arg0->unk5](arg0);
}

void func_800D2A38(struct MiscObj* arg0)
{
    D_8010F544[arg0->state](arg0);
}
