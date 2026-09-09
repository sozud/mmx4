// MainObj, main_object_update_funcs[11]
// 8004A718..8004B8C0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A718);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A78C);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A9F4);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AB6C);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004ACDC);

void func_8004ACF0(struct MainObj* arg0)
{
    arg0->state = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AD18);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004ADE8);

void func_8004AE00(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AE20);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B040);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B0A0);

void func_8004B280(struct MainObj* arg0)
{
    D_800FB550[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B2BC);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B418);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B514);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B668);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B748);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B808);
