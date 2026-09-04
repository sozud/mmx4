// ShotObj, shot_object_update_funcs[15]
// 8009C0F0..8009C364
#include "common.h"

void func_8009C0F0(struct ShotObj* arg0)
{
    D_80108EDC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_15", func_8009C12C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_15", func_8009C238);

void func_8009C258(struct ShotObj* arg)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_15", func_8009C260);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_15", func_8009C298);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_15", func_8009C344);

void (*D_80108EDC[])(struct ShotObj*) = {
    func_8009C12C,
    func_8009C298,
    func_8009C344,
};
