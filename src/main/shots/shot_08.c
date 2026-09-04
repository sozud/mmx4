// ShotObj, shot_object_update_funcs[8]
// 8009AEE4..8009B07C
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_08", func_8009AEE4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_08", func_8009AF98);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_08", func_8009B020);

void func_8009B040(struct ShotObj* arg0)
{
    D_80108D88[arg0->base.state](arg0);
}

void (*D_80108D88[])(struct ShotObj*) = {
    func_8009AEE4,
    func_8009AF98,
    func_8009B020,
};
