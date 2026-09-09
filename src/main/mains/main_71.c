// MainObj, main_object_update_funcs[71]
// 80089AA4..8008ADFC
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089AA4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089B58);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089C0C);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089C7C);

void func_80089EBC(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089EC8);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089F58);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089F94);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089FAC);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089FD4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A024);

void func_8008A05C(void)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A064);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A180);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A2E0);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A3B0);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A4D8);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A60C);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A778);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A8E4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A9F4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AAF4);

void func_8008AC20(struct MainObj* arg0)
{
    func_80089F58(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AC40);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AD48);

void func_8008AD74(void)
{
}

void func_8008AD7C(void)
{
}

void func_8008AD84(struct MainObj* arg0)
{
    D_80104D28[arg0->unk5](arg0);
}

void func_8008ADC0(struct MainObj* arg0)
{
    D_80104D34[arg0->state](arg0);
}
