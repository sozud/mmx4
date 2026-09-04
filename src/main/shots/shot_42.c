// ShotObj, shot_object_update_funcs[42]
// 800A6374..800A6960
#include "common.h"

void func_800A6374(struct ShotObj* arg0)
{
    D_80109998[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A63B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A6510);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A6600);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A666C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A6794);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A67FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A6860);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_42", func_800A6940);

void (*D_80109998[])(struct ShotObj*) = {
    func_800A63B0,
    func_800A6860,
    func_800A6940,
};
