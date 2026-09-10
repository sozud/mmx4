// ShotObj, shot_object_update_funcs[31]
// 8009FF10..800A0170
#include "common.h"

u8 D_8010923C[2][4] = {
    { 0xF8, 0xEE, 0x0F, 0x23 },
    { 0xF7, 0xF1, 0x14, 0x1B },
};
s8 D_80109244[4] = { -72, -6, -60, -51 };

void func_8009FF10(struct ShotObj* arg0)
{
    D_80109248[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_31", func_8009FF4C);

INCLUDE_ASM("main/nonmatchings/shots/shot_31", func_800A00C4);

void func_800A0150(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80109248[])(struct ShotObj*) = {
    func_8009FF4C,
    func_800A00C4,
    func_800A0150,
};
