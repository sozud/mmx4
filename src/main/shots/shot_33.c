// ShotObj, shot_object_update_funcs[33]
// 800A03B8..800A16FC
#include "common.h"

void func_800A03B8(struct ShotObj* arg0)
{
    D_801094EC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A03F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A068C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A0A18);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A0A38);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A0C4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A0FC8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A0FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A12EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_33", func_800A16DC);

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
