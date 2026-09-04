// ShotObj, shot_object_update_funcs[52]
// 800AAAD4..800AAC98
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_52", func_800AAAD4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_52", func_800AAB74);

void func_800AAC5C(struct ShotObj* arg0)
{
    D_80109C2C[arg0->base.state](arg0);
}

void (*D_80109C2C[])(struct ShotObj*) = {
    func_800AAAD4,
    func_800AAB74,
    func_800A9D98,
};
