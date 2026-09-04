// ShotObj, shot_object_update_funcs[39]
// 800A47C4..800A5348
#include "common.h"

void func_800A47C4(struct ShotObj* arg0)
{
    D_8010984C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4800);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4968);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4A50);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4ADC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4D00);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4D20);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4E48);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4F04);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4F24);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A4FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A5070);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A50EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A5144);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A5194);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_39", func_800A5318);

void (*D_8010984C[])(struct ShotObj*) = {
    func_800A4800,
    func_800A4968,
    func_800A4A50,
    func_800A4ABC,
    func_800A4ADC,
    func_800A4B6C,
    func_800A4D00,
    func_800A4D20,
    func_800A4E48,
    func_800A4F04,
};
