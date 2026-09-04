// ShotObj, shot_object_update_funcs[10]
// 8009B3E8..8009B67C
#include "common.h"

void func_8009B3E8(struct ShotObj* arg0)
{
    D_80108E48[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_10", func_8009B424);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_10", func_8009B594);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_10", func_8009B654);

void func_8009B674(struct ShotObj* arg)
{
}

void (*D_80108E48[])(struct ShotObj*) = {
    func_8009B424,
    func_8009B594,
    func_8009B654,
    func_8009B674,
};
