// ShotObj, shot_object_update_funcs[7]
// 8009AD30..8009AEE4
#include "common.h"

void func_8009AD30(struct ShotObj* arg0)
{
    D_80108D74[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_07", func_8009AD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_07", func_8009ADF8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_07", func_8009AEBC);

void func_8009AEDC(struct ShotObj* arg0)
{
}

void (*D_80108D74[])(struct ShotObj*) = {
    func_8009AD6C,
    func_8009ADF8,
    func_8009AEBC,
    func_8009AEDC,
};
