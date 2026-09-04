// ShotObj, shot_object_update_funcs[14]
// 8009BF14..8009C0F0
#include "common.h"

void func_8009BF14(struct ShotObj* arg0)
{
    D_80108ECC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_14", func_8009BF50);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_14", func_8009BFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_14", func_8009C0D0);

void (*D_80108ECC[])(struct ShotObj*) = {
    func_8009BF50,
    func_8009BFE0,
    func_8009C0D0,
};
