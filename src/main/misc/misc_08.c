// MiscObj, misc_object_update_funcs[8]
// 800C9510..800C9D64
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C9510);

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C969C);

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C9914);

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C993C);

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C99CC);

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C9C64);

INCLUDE_ASM("main/nonmatchings/misc/misc_08", func_800C9CB0);

void func_800C9D08(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C9D28(struct MiscObj* arg0)
{
    D_8010E0F4[arg0->state](arg0);
}
