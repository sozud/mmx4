// ShotObj, shot_object_update_funcs[56]
// 800ADF30..800AE450
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800ADF30);

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800AE1BC);

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800AE2AC);

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800AE2FC);

void func_800AE31C(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800AE324);

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800AE3D4);

void func_800AE3F4(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
    arg0->on_screen = 0;
    D_80109F44[arg0->state](arg0);
}

void (*D_80109F44[])(struct ShotObj*) = {
    func_800ADF30,
    func_800AE324,
    func_800AE3D4,
};
