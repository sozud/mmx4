// MainObj, main_object_update_funcs[76]
// 800919C4..800922D8
#include "common.h"

void func_800919C4(struct MainObj* arg0)
{
    D_80105FB4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091A00);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091AC4);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091B1C);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091C64);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091D1C);

void func_80091E18(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091E38);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091EC4);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091FC8);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_8009216C);

INCLUDE_RODATA("main/nonmatchings/mains/main_76", D_80010D7C);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_800921E8);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_8009227C);

void (*D_80105FB4[])(struct MainObj*) = {
    func_80091A00,
    func_80091D1C,
    func_80091E18,
};
