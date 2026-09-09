// ShotObj, shot_object_update_funcs[28]
// 8009F46C..8009F638
#include "common.h"

void func_8009F46C(struct ShotObj* arg0)
{
    struct BaseObj* unk7C = arg0->unk7C;
    arg0->x_pos.val = unk7C->x_pos.val;
    arg0->y_pos.val = unk7C->y_pos.val;
    D_801091C4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_28", func_8009F4C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_28", func_8009F594);

void func_8009F618(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801091C4[])(struct ShotObj*) = {
    func_8009F4C0,
    func_8009F594,
    func_8009F618,
};
