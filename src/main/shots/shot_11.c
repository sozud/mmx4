// ShotObj, shot_object_update_funcs[11]
// 8009B67C..8009B7F8
#include "common.h"

void func_8009B67C(struct ShotObj* arg0)
{
    D_80108E5C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_11", func_8009B6B8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_11", func_8009B734);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_11", func_8009B7D8);

void (*D_80108E5C[])(struct ShotObj*) = {
    func_8009B6B8,
    func_8009B734,
    func_8009B7D8,
};
