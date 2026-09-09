// MainObj, main_object_update_funcs[26]
// 80058158..800586F0
#include "common.h"

void func_80058158(struct MainObj* arg0)
{
    D_800FD1DC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_80058194);

void func_80058240(struct MainObj* arg0)
{
    arg0->unk5 = 2;
}

void func_8005824C(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_80058254);

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_800583B0);

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_800585F4);

void func_80058658(void)
{
}

void func_80058660(struct MainObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_80058680);
