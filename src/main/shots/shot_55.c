// ShotObj, shot_object_update_funcs[55]
// 800AC8C4..800ADF30
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AC8C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ACCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ACD04);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ACD84);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ACDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ACE90);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ACF60);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD00C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD080);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD12C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD1B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD224);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD338);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD404);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD440);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD47C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD4DC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD538);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD630);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD66C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD6DC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD820);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD868);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD92C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800AD9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADA0C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADA64);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADAD8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADBE0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADCE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADD40);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADDB4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADE04);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADE54);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_55", func_800ADED4);

void func_800ADEF4(struct ShotObj* arg0)
{
    D_80109EE8[arg0->base.state](arg0);
}

void (*D_80109EE8[])(struct ShotObj*) = {
    func_800AC8C4,
    func_800ADE54,
    func_800ADED4,
};
