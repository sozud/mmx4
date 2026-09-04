// ShotObj, shot_object_update_funcs[22]
// 8009D74C..8009DD40
#include "common.h"

void func_8009D74C(struct ShotObj* arg0)
{
    D_80109008[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009D788);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009D85C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009D8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009DA08);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009DA28);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009DA7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009DB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009DB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_22", func_8009DCF4);

void (*D_80109008[])(struct ShotObj*) = {
    func_8009D788,
    func_8009DB9C,
    func_8009DCF4,
};
