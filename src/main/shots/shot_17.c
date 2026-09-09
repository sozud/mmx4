// ShotObj, shot_object_update_funcs[17]
// 8009C5F0..8009CAC0
#include "common.h"

void func_8009C5F0(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_80108F6C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C638);

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C784);

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C860);

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C96C);

void func_8009C9C8(struct ShotObj* arg0)
{
}

void func_8009C9D0(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C9F0);

void func_8009CAA0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108F6C[])(struct ShotObj*) = {
    func_8009C638,
    func_8009C9F0,
    func_8009CAA0,
};
