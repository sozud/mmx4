// ShotObj, shot_object_update_funcs[54]
// 800ABE08..800AC8C4
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800ABE08);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC114);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC180);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC204);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC31C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC364);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC3BC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC440);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC4A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC4F8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC550);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC5BC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC610);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC66C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC6A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC6E8);

void func_800AC708(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC710);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC7CC);

void func_800AC7EC(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    }
    arg0->base.on_screen = 0;
    D_80109DF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_54", func_800AC848);

void (*D_80109DF8[])(struct ShotObj*) = {
    func_800ABE08,
    func_800AC710,
    func_800AC7CC,
};
