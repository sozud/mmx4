// ShotObj, shot_object_update_funcs[56]
// 800ADF30..800AE450
#include "common.h"

s8 D_80109EF4[8][4] = {
    { -13, -12, 28, 23 },
    { -6, -6, 15, 12 },
    { -8, -15, 22, 29 },
    { -19, -22, 40, 44 },
    { -7, -13, 15, 18 },
    { -8, -14, 18, 20 },
    { -8, -11, 16, 19 },
    { -12, -13, 24, 23 },
};

s8* D_80109F14[8] = {
    D_80109EF4[0],
    D_80109EF4[1],
    D_80109EF4[2],
    D_80109EF4[3],
    D_80109EF4[4],
    D_80109EF4[5],
    D_80109EF4[6],
    D_80109EF4[7],
};

void (*D_80109F34[])(struct ShotObj*) = {
    func_800AE2FC,
    func_800AE31C,
    func_800AE1BC,
    func_800AE2AC,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800ADF30);

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800AE1BC);

void func_800AE2AC(struct ShotObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
    if (arg0->on_screen == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_800AE2FC(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_800AE31C(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_56", func_800AE324);

void func_800AE3D4(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

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
