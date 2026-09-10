// ShotObj, shot_object_update_funcs[9]
// 8009B07C..8009B3E8
#include "common.h"

u8 D_80108D94[4] = { 0xCB, 0xD0, 0x2C, 0x3A };
u8 D_80108D98[4] = { 0xFB, 0xFC, 0x0D, 0x06 };
s8 D_80108D9C[6][2] = {
    { 0, 0x18 },
    { -0x14, 0x14 },
    { -0x20, 0 },
    { -9, -5 },
    { -0x0E, 0x0C },
    { 0, 0 },
};

void func_8009B07C(struct ShotObj* arg0)
{
    D_80108DA8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_09", func_8009B0B8);

INCLUDE_ASM("main/nonmatchings/shots/shot_09", func_8009B12C);

void func_8009B1C8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_09", func_8009B1E8);

INCLUDE_ASM("main/nonmatchings/shots/shot_09", func_8009B2F4);

void func_8009B3C8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108DA8[])(struct ShotObj*) = {
    func_8009B0B8,
    func_8009B12C,
    func_8009B1C8,
    func_8009B1E8,
    func_8009B2F4,
    func_8009B3C8,
};
