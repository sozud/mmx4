// ShotObj, shot_object_update_funcs[38]
// 800A428C..800A47C4
#include "common.h"

u8 D_801097DC[4] = { 0xFC, 0xFC, 0x08, 0x08 };
u8 D_801097E0[4] = { 0xF0, 0x92, 0x1F, 0xD4 };

void func_800A428C(struct ShotObj* arg0)
{
    D_801097E4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_38", func_800A42C8);

INCLUDE_ASM("main/nonmatchings/shots/shot_38", func_800A4518);

void func_800A46D4(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A46F4(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_38", func_800A46FC);

void (*D_801097E4[])(struct ShotObj*) = {
    func_800A42C8,
    func_800A4518,
    func_800A46D4,
    func_800A46F4,
};
