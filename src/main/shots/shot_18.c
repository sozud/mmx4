// ShotObj, shot_object_update_funcs[18]
// 8009CAC0..8009CC64
#include "common.h"

void func_8009CAC0(struct ShotObj* arg0)
{
    D_80108F90[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_18", func_8009CAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_18", func_8009CBA0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_18", func_8009CC44);

void (*D_80108F90[])(struct ShotObj*) = {
    func_8009CAFC,
    func_8009CBA0,
    func_8009CC44,
};
