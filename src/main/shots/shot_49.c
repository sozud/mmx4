// ShotObj, shot_object_update_funcs[49]
// 800A9DF4..800AA2FC
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800A9DF4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800A9EC0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800A9F30);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800A9FD0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800AA000);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800AA030);

void func_800AA10C(struct ShotObj* arg0)
{
    D_80109BE0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800AA148);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_49", func_800AA20C);

void (*D_80109BE0[])(struct ShotObj*) = {
    func_800A9DF4,
    func_800AA030,
    func_800A9D98,
};
