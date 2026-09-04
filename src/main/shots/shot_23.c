// ShotObj, shot_object_update_funcs[23]
// 8009DD40..8009E0B8
#include "common.h"

void func_8009DD40(struct ShotObj* arg0)
{
    D_801090AC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_23", func_8009DD7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_23", func_8009DE04);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_23", func_8009DF40);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_23", func_8009DF60);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_23", func_8009DFA0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_23", func_8009E098);

void (*D_801090AC[])(struct ShotObj*) = {
    func_8009DD7C,
    func_8009DE04,
    func_8009E098,
};
