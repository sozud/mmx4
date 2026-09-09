// ShotObj, shot_object_update_funcs[46]
// 800A8628..800A9964
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8628);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8A58);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8AE4);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8B88);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8C88);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8D1C);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8D68);

void func_800A8DB8(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8DC0);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8E50);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A8FBC);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9054);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A90C8);

void func_800A916C(struct ShotObj* arg0)
{
    D_80109B2C[arg0->unk5](arg0);
    is_on_screen((struct BaseObj*)arg0);
    if (arg0->unk7C->state == 2) {
        arg0->state = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A91D8);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9210);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A92C8);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9334);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A93FC);

void func_800A94A4(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A94D4);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9544);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9654);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A96F8);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A97C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A9818);

INCLUDE_ASM("main/nonmatchings/shots/shot_46", func_800A98AC);

void func_800A9928(struct ShotObj* arg0)
{
    D_80109B7C[arg0->state](arg0);
}

void (*D_80109B7C[])(struct ShotObj*) = {
    func_800A8628,
    func_800A9818,
    func_800A98AC,
};
