// ShotObj, shot_object_update_funcs[24]
// 8009E0B8..8009EB6C
#include "common.h"

void func_8009E0B8(struct ShotObj* arg0)
{
    D_8010910C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E0F4);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E188);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E34C);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E3A8);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E490);

void func_8009E5A4(struct ShotObj* arg0)
{
    arg0->unk5 = arg0->unk84.bytes[1];
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E5B0);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E608);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E690);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E718);

void func_8009E7B4(struct ShotObj* arg0)
{
    s8 temp_v0;

    temp_v0 = (u8)arg0->unk7 - 1;
    arg0->unk7 = temp_v0;
    if (temp_v0 == 0) {
        arg0->unk7 = 0x37;
        arg0->x_vel.val = -FIXED(4);
        arg0->unk5 = 7;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E7EC);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E8E0);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E9EC);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009EAA4);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009EAF0);

u8 D_801090C4[4] = { 0xFD, 0xFD, 0x05, 0x05 };

u8 D_801090C8[4] = { 0x43, 0xF7, 0x28, 0x11 };

u8 D_801090CC[2][4] = {
    { 0x45, 0xFD, 0x25, 0x04 },
    { 0xFE, 0xF8, 0x03, 0x02 },
};

s16 D_801090D4[3][2] = {
    { -0x72, -0x3A },
    { -0x6E, -0x18 },
    { -0x6D, 9 },
};

s16 D_801090E0[4] = { -0x53, -0x4F, -0x4E, 0 };

u16 D_801090E8[3][2] = {
    { 0x1A8B, 0x0143 },
    { 0x1A8E, 0x0168 },
    { 0x1A8F, 0x018A },
};

u8 D_801090F4[4] = { 1, 2, 4, 0 };

u8 D_801090F8[4] = { 0x10, 0x20, 0x40, 0 };

u8 D_801090FC[4] = { 0xFE, 0xFD, 0xFB, 0 };

u8 D_80109100[4] = { 0xEF, 0xDF, 0xBF, 0 };

u8 D_80109104[8] = { 6, 7, 8, 6, 7, 8, 0, 0 };

void (*D_8010910C[])(struct ShotObj*) = {
    func_8009E0F4,
    func_8009E188,
    func_8009E34C,
    func_8009E3A8,
    func_8009E490,
    func_8009EAF0,
};
