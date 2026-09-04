// ShotObj, shot_object_update_funcs[32]
// 800A0170..800A03B8
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_32", func_800A0170);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_32", func_800A02FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_32", func_800A035C);

void func_800A037C(struct ShotObj* arg0)
{
    D_8010925C[arg0->base.state](arg0);
}

void (*D_8010925C[])(struct ShotObj*) = {
    func_800A0170,
    func_800A02FC,
    func_800A035C,
};
