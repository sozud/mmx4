// MainObj, main_object_update_funcs[72]
// 8008ADFC..8008BA38
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008ADFC);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008AE94);

void func_8008AEC4(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

void func_8008AED0(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008AEE8);

void func_8008AF10(struct MainObj* arg0)
{
    s32 value;

    value = arg0->ext.main_72.unk84 << 8;
    if (arg0->unk15 == 0) {
        value = -value;
    }
    arg0->unk20 = value;
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008AF30);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B020);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B188);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B270);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B33C);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B42C);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B4B8);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B5C0);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B69C);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B7D4);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B898);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B8B8);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B984);

void func_8008B9B0(void)
{
}

void func_8008B9B8(void)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B9C0);

void func_8008B9FC(struct MainObj* arg0)
{
    D_80104F48[arg0->state](arg0);
}
