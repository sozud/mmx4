// ShotObj, shot_object_update_funcs[34]
// 800A16FC..800A22D4
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A16FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A18A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A18F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A19A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A1B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A1BEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A1C90);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A1CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A1E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A1F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A2098);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_34", func_800A220C);

void func_800A2278(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010958C[arg0->base.state](arg0);
    CollisionRelated(arg0);
}

void (*D_8010958C[])(struct ShotObj*) = {
    func_800A16FC,
    func_800A2098,
    func_800A220C,
};
