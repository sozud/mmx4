// ShotObj, shot_object_update_funcs[9]
// 8009B07C..8009B3E8
#include "common.h"

void func_8009B07C(struct ShotObj* arg0)
{
    D_80108DA8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_09", func_8009B0B8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_09", func_8009B12C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_09", func_8009B1C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_09", func_8009B1E8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_09", func_8009B2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_09", func_8009B3C8);

void (*D_80108DA8[])(struct ShotObj*) = {
    func_8009B0B8,
    func_8009B12C,
    func_8009B1C8,
    func_8009B1E8,
    func_8009B2F4,
    func_8009B3C8,
};
