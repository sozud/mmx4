// ShotObj, shot_object_update_funcs[33]
// 800A03B8..800A16FC
#include "common.h"

void func_800A03B8(struct ShotObj* arg0)
{
    D_801094EC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A03F4);

INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A068C);

void func_800A0A18(struct ShotObj* arg0)
{
    arg0->unk62 = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A0A38);

INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A0C4C);

void func_800A0FC8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A0FE8);

INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A12EC);

void func_800A16DC(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801094EC[])(struct ShotObj*) = {
    func_800A03F4,
    func_800A068C,
    func_800A0A18,
    func_800A0A38,
    func_800A0C4C,
    func_800A0FC8,
    func_800A0FE8,
    func_800A12EC,
    func_800A16DC,
};
