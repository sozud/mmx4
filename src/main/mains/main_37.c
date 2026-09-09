// MainObj, main_object_update_funcs[37]
// 8005FDBC..80060A88
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_8005FDBC);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_8005FE1C);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_80060144);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_80060228);

void func_8006025C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_37.saved_unk5;
}

void func_80060268(struct MainObj* arg0)
{
    D_800FE704[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800602A4);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_80060354);

void func_800603A0(struct MainObj* arg0)
{
    D_800FE70C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800603DC);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800604A0);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800604EC);

void func_80060538(struct MainObj* arg0)
{
    D_800FE718[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_80060574);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800606D8);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_80060870);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800608CC);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_8006097C);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800609C4);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_80060A10);

void func_80060A58(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
