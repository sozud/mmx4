// ShotObj, shot_object_update_funcs[13]
// 8009BD28..8009BF14
#include "common.h"

void func_8009BD28(struct ShotObj* arg0)
{
    D_80108EBC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_13", func_8009BD64);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_13", func_8009BE14);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_13", func_8009BEF4);

void (*D_80108EBC[])(struct ShotObj*) = {
    func_8009BD64,
    func_8009BE14,
    func_8009BEF4,
};
