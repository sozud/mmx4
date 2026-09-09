// MainObj, main_object_update_funcs[14]
// 8004CF24..8004D930
#include "common.h"

void func_8004CF24(struct MainObj* arg0)
{
    D_800FB9FC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004CF60);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D044);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D160);

void func_8004D1C8(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_14.saved_unk5;
}

void func_8004D1D4(struct MainObj* arg0)
{
    D_800FBA20[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D210);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D290);

void func_8004D2E0(struct MainObj* arg0)
{
    D_800FBA28[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D31C);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D370);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D3C8);

void func_8004D408(struct MainObj* arg0)
{
    D_800FBA34[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D444);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D480);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D4D0);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D580);

void func_8004D5E0(struct MainObj* arg0)
{
    D_800FBA44[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D61C);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D69C);

void func_8004D6CC(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D6FC);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D784);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D84C);
