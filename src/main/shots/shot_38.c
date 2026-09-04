// ShotObj, shot_object_update_funcs[38]
// 800A428C..800A47C4
#include "common.h"

void func_800A428C(struct ShotObj* arg0)
{
    D_801097E4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_38", func_800A42C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_38", func_800A4518);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_38", func_800A46D4);

void func_800A46F4(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_38", func_800A46FC);

void (*D_801097E4[])(struct ShotObj*) = {
    func_800A42C8,
    func_800A4518,
    func_800A46D4,
    func_800A46F4,
};
