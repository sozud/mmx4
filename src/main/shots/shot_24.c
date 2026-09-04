// ShotObj, shot_object_update_funcs[24]
// 8009E0B8..8009EB6C
#include "common.h"

void func_8009E0B8(struct ShotObj* arg0)
{
    D_8010910C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E0F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E188);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E34C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E490);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E608);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E690);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E718);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E7EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009E9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009EAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_24", func_8009EAF0);

void (*D_8010910C[])(struct ShotObj*) = {
    func_8009E0F4,
    func_8009E188,
    func_8009E34C,
    func_8009E3A8,
    func_8009E490,
    func_8009EAF0,
};
