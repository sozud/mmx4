// ShotObj, shot_object_update_funcs[40]
// 800A5348..800A56E4
#include "common.h"

void func_800A5348(struct ShotObj* arg0)
{
    D_801098B8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_40", func_800A5384);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_40", func_800A5404);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_40", func_800A5460);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_40", func_800A5500);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_40", func_800A5540);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_40", func_800A56C0);

void (*D_801098B8[])(struct ShotObj*) = {
    func_800A5384,
    func_800A5540,
    func_800A56C0,
};
