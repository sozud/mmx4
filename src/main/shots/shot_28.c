// ShotObj, shot_object_update_funcs[28]
// 8009F46C..8009F638
#include "common.h"

void func_8009F46C(struct ShotObj* arg0)
{
    struct BaseObj* unk7C = arg0->unk7C;
    arg0->base.x_pos.val = unk7C->x_pos.val;
    arg0->base.y_pos.val = unk7C->y_pos.val;
    D_801091C4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_28", func_8009F4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_28", func_8009F594);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_28", func_8009F618);

void (*D_801091C4[])(struct ShotObj*) = {
    func_8009F4C0,
    func_8009F594,
    func_8009F618,
};
