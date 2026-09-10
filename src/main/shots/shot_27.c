// ShotObj, shot_object_update_funcs[27]
// 8009F240..8009F46C
#include "common.h"

u8 D_8010919C[4] = { 0xFD, 0xFD, 5, 5 };
s8 D_801091A0[20] = {
    2,
    -0x16,
    -0x0D,
    -0x19,
    -0x12,
    -0x11,
    -0x12,
    -5,
    -0x0C,
    5,
    2,
    -0x1D,
    -9,
    -0x1E,
    -0x12,
    -0x17,
    -0x15,
    -0x0B,
    -0x0C,
    -3,
};

void func_8009F240(struct ShotObj* arg0)
{
    D_801091B4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_27", func_8009F27C);

INCLUDE_ASM("main/nonmatchings/shots/shot_27", func_8009F3A8);

void func_8009F44C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801091B4[])(struct ShotObj*) = {
    func_8009F27C,
    func_8009F3A8,
    func_8009F44C,
};
