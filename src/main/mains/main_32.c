// MainObj, main_object_update_funcs[32]
// 8005C824..8005D1F4
#include "common.h"

void func_8005C824(struct MainObj* arg0)
{
    D_800FDD2C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005C860);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005C960);

void func_8005CADC(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005CAFC(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_32.saved_unk5;
}

void func_8005CB08(struct MainObj* arg0)
{
    func_8005D118(arg0);
    D_800FDD5C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CB54);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CB90);

void func_8005CC6C(struct MainObj* arg0)
{
    D_800FDD64[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CCA8);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CCFC);

void func_8005CD5C(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->ext.main_32.unk80 == 0) {
        func_80015D60(arg0, 3);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}

void func_8005CDB0(struct MainObj* arg0)
{
    D_800FDD6C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CDEC);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CE50);

void func_8005CE80(struct MainObj* arg0)
{
    D_800FDD74[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CEBC);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CF30);

void func_8005CF60(struct MainObj* arg0)
{
    D_800FDD7C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CF9C);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005D0A0);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005D0D8);

void func_8005D118(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005D148);
