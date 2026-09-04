// ShotObj, shot_object_update_funcs[16]
// 8009C364..8009C5F0
#include "common.h"

void func_8009C364(struct ShotObj* arg0)
{
    D_80108F54[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_16", func_8009C3A0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_16", func_8009C45C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_16", func_8009C588);

void (*D_80108F54[])(struct ShotObj*) = {
    func_8009C3A0,
    func_8009C45C,
    func_8009C588,
};
