// ShotObj, shot_object_update_funcs[27]
// 8009F240..8009F46C
#include "common.h"

void func_8009F240(struct ShotObj* arg0)
{
    D_801091B4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_27", func_8009F27C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_27", func_8009F3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_27", func_8009F44C);

void (*D_801091B4[])(struct ShotObj*) = {
    func_8009F27C,
    func_8009F3A8,
    func_8009F44C,
};
