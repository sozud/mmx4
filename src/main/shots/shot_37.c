// ShotObj, shot_object_update_funcs[37]
// 800A3C78..800A428C
#include "common.h"

s8 D_8010979C[4] = { -11, -11, 22, 22 };

u16 D_801097A0[11][2] = {
    { 0x43, 0x28 },
    { 0x80, 0x28 },
    { 0xBC, 0x28 },
    { 0xF8, 0x28 },
    { 0x52, 0x70 },
    { 0x9E, 0x70 },
    { 0xEA, 0x70 },
    { 0x43, 0xB0 },
    { 0x80, 0xB0 },
    { 0xBC, 0xB0 },
    { 0xF8, 0xB0 },
};

void func_800A3C78(struct ShotObj* arg0)
{
    D_801097CC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_37", func_800A3CB4);

INCLUDE_ASM("main/nonmatchings/shots/shot_37", func_800A3FEC);

INCLUDE_ASM("main/nonmatchings/shots/shot_37", func_800A4230);

void func_800A4284(struct ShotObj* arg0)
{
}

void (*D_801097CC[])(struct ShotObj*) = {
    func_800A3CB4,
    func_800A3FEC,
    func_800A4230,
    func_800A4284,
};
