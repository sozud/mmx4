// ShotObj, shot_object_update_funcs[40]
// 800A5348..800A56E4
#include "common.h"

void func_800A5348(struct ShotObj* arg0)
{
    D_801098B8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5384);

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5404);

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5460);

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5500);

INCLUDE_ASM("main/nonmatchings/shots/shot_40", func_800A5540);

void func_800A56C0(struct ShotObj* arg0)
{
    arg0->unk7C->unk7 = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801098B8[])(struct ShotObj*) = {
    func_800A5384,
    func_800A5540,
    func_800A56C0,
};
