// ShotObj, shot_object_update_funcs[51]
// 800AA5E0..800AAAD4
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_51", func_800AA5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_51", func_800AA68C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_51", func_800AA730);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_51", func_800AA7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_51", func_800AA85C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_51", func_800AA954);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_51", func_800AA994);

void func_800AAA98(struct ShotObj* arg0)
{
    D_80109C20[arg0->base.state](arg0);
}

void (*D_80109C20[])(struct ShotObj*) = {
    func_800AA148,
    func_800AA994,
    func_800A9D98,
};
