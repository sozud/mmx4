// ShotObj, shot_object_update_funcs[39]
// 800A47C4..800A5348
#include "common.h"

void func_800A47C4(struct ShotObj* arg0)
{
    D_8010984C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4800);

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4968);

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4A50);

void func_800A4ABC(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4ADC);

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4B6C);

void func_800A4D00(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4D20);

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4E48);

void func_800A4F04(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A4F24);

void func_800A4FEC(struct ShotObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if ((arg0->unk84.bytes[0] == 0) && (arg0->y_vel.val < 0)) {
        func_80015D60(arg0, 3);
        arg0->unk84.bytes[0] = 1;
    }
    func_80015DC8(arg0);
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 0xA);
        arg0->unk5 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A5070);

void func_800A50EC(struct ShotObj* arg0)
{
    if (--arg0->timer == 0) {
        func_80015D60(arg0, 0x16);
        arg0->timer = 0x28;
        arg0->unk5 = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A5144);

INCLUDE_ASM("main/nonmatchings/shots/shot_39", func_800A5194);

void func_800A5318(struct ShotObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
    func_80015DC8(arg0);
}

u8 D_801097F4[4] = { 0xF1, 0xF1, 0x19, 0x1C };

u8 D_801097F8[4] = { 0xF9, 0xF9, 0x0D, 0x0D };

u8 D_801097FC[4] = { 0x3C, 0x3D, 0x3E, 0x3F };

u8 D_80109800[4] = { 0x2C, 0x2D, 0x2E, 0x2F };

u8 D_80109804[8] = { 0x0C, 0x0B, 0x06, 0x0F, 0xFC, 0x0F, 0xF5, 0x0D };

u8 D_8010980C[12] = { 0xFC, 0xED, 0xF4, 0xF0, 0x04, 0xF0, 0xF0, 0xF3, 0x08, 0xF3, 0, 0 };

s32 D_80109818[4] = { -0x22000, -0x10000, 0x10000, 0x22000 };

s32 D_80109828[4] = { -0xA00, -0x600, 0x600, 0xA00 };

s32 D_80109838[5] = { 0, 0x1000, -0x1000, 0x2000, -0x2000 };

void (*D_8010984C[])(struct ShotObj*) = {
    func_800A4800,
    func_800A4968,
    func_800A4A50,
    func_800A4ABC,
    func_800A4ADC,
    func_800A4B6C,
    func_800A4D00,
    func_800A4D20,
    func_800A4E48,
    func_800A4F04,
};

void (*D_80109874[7])(struct ShotObj*) = {
    func_800A4F24,
    func_800A4FEC,
    func_800A5070,
    func_800A50EC,
    func_800A5144,
    func_800A5194,
    func_800A5318,
};
