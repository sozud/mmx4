// ShotObj, shot_object_update_funcs[2, 3, 4, 5]
// 80099D10..8009A984
#include "common.h"

u8 D_80108D04[28] = {
    0xF9,
    0xF7,
    0x0F,
    0x10,
    0xE3,
    0xF0,
    0x15,
    0x0C,
    0xAF,
    0xE3,
    0x2D,
    0x16,
    0xC2,
    0xEA,
    0x22,
    0x0F,
    0xDF,
    0xF4,
    0x19,
    0x07,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
u8 D_80108D20[8] = { 0x0F, 0x10, 0x11, 0x0F, 0x10, 0x11, 0, 0 };

void func_80099D10(struct ShotObj* arg0)
{
}

void func_80099D18(struct ShotObj* arg0)
{
    D_80108CC4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_80099D54);

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_80099E34);

void func_80099F28(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_80099F48);

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A10C);

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A264);

void func_8009A338(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009A358(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    CollisionRelated(arg0);
    D_80108CE4[arg0->state](arg0);
}

void func_8009A3B4(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk15 == 0) {
        arg0->x_pos.val = arg0->unk7C->x_pos.val + FIXED(-75);
    } else {
        arg0->x_pos.val = arg0->unk7C->x_pos.val + FIXED(75);
    }
    arg0->y_pos.val = arg0->unk7C->y_pos.val + FIXED(2);
    arg0->unk42 = arg0->unk7C->unk42;
    arg0->on_screen = 0;
    D_80108CF8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A448);

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A4F4);

void func_8009A598(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009A5B8(struct ShotObj* arg0)
{
    D_80108D28[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A5F4);

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A6B4);

void func_8009A7D8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A7F8);

INCLUDE_ASM("main/nonmatchings/shots/shot_02", func_8009A87C);

void func_8009A964(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108D28[])(struct ShotObj*) = {
    func_8009A5F4,
    func_8009A6B4,
    func_8009A7D8,
    func_8009A7F8,
    func_8009A87C,
    func_8009A964,
};
