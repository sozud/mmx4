// ShotObj, shot_object_update_funcs[35]
// 800A22D4..800A3924
#include "common.h"

void func_800A22D4(struct ShotObj* arg0)
{
    D_801096F4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2310);

void func_800A23B4(struct ShotObj* arg0)
{
    arg0->state = 7;
}

void func_800A23C0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A23E0(struct ShotObj* arg0)
{
    D_80109714[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A241C);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A24F0);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A25EC);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2748);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A27F4);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2870);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2928);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A29C8);

void func_800A2A58(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_80109734[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2AA0);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2B8C);

void func_800A2C70(struct ShotObj* arg0)
{
    s16 timer;
    s8 on_screen;

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x96, arg0);
        arg0->unk6++;
        return;
    }

    on_screen = arg0->on_screen ^ 1;
    arg0->on_screen = on_screen;
    if (on_screen != 0) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2CEC);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2D54);

void func_800A2E6C(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_80109748[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2EB4);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2F2C);

void func_800A3010(struct ShotObj* arg0)
{
    func_8002B93C(MOVING_OBJECT(arg0), arg0->unk2 + 0xC);
    arg0->x_vel.val *= 4;
    if (arg0->unk15 == 0x40) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->y_vel.val *= 4;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A3078);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A3170);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A31CC);

void func_800A325C(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_80109760[arg0->unk5](arg0);
    func_8002D9BC(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A32B8);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A33A0);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A348C);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A3520);

void func_800A3658(struct ShotObj* arg0)
{
    arg0->state = 6;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A366C);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A3758);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A382C);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A38B0);

RECT D_80109598[8] = {
    { 0x30, 0x90, 0xF0, 0x150 },
    { 0x30, 0x70, 0xB0, 0xF0 },
    { 0x70, 0xD0, 0x130, 0x190 },
    { 0x70, 0x90, 0xB0, 0xD0 },
    { 0xB0, 0x110, 0x170, 0x1B0 },
    { 0x110, 0x150, 0x190, 0x1B0 },
    { 0xD0, 0x110, 0x150, 0x190 },
    { 0x130, 0x150, 0x170, 0x190 },
};

RECT D_801095D8[8][2] = {
    { { 0x30, 0x70, 0xB0, 0xF0 }, { 0x130, 0x170, 0x190, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xB0 }, { 0xF0, 0x130, 0x170, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xD0 }, { 0xF0, 0x110, 0x170, 0x190 } },
    { { 0x30, 0x50, 0xB0, 0xD0 }, { 0xF0, 0x150, 0x170, 0x190 } },
    { { 0x30, 0x50, 0x70, 0x90 }, { 0x150, 0x170, 0x190, 0x1B0 } },
    { { 0x50, 0x70, 0x90, 0xF0 }, { 0x110, 0x170, 0x190, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xD0 }, { 0xF0, 0x150, 0x170, 0x190 } },
    { { 0x50, 0x70, 0xB0, 0xD0 }, { 0x110, 0x130, 0x170, 0x190 } },
};

RECT* D_80109658[8] = {
    &D_80109598[0],
    &D_80109598[1],
    &D_80109598[2],
    &D_80109598[3],
    &D_80109598[4],
    &D_80109598[5],
    &D_80109598[6],
    &D_80109598[7],
};

RECT* D_80109678[8] = {
    D_801095D8[0],
    D_801095D8[1],
    D_801095D8[2],
    D_801095D8[3],
    D_801095D8[4],
    D_801095D8[5],
    D_801095D8[6],
    D_801095D8[7],
};

RECT** D_80109698 = D_80109658;
RECT** D_8010969C = D_80109678;

s16 D_801096A0[2][2] = {
    { -19, -31 },
    { 36, -31 },
};

s8 D_801096A8[10][4] = {
    { -39, 21, 27, 30 },
    { 0, 10, 9, 3 },
    { 0, 0, 6, 6 },
    { 0, -4, 10, 7 },
    { -12, -32, 23, 63 },
    { -4, -20, 9, 30 },
    { -37, -56, 73, 118 },
    { -28, -48, 55, 88 },
    { -13, -12, 23, 23 },
    { -5, -8, 9, 15 },
};

s32 D_801096D0[3] = { 0x30000, 0x20000, 0x10000 };

u8 D_801096DC[12] = { 12, 13, 14, 15, 13, 15, 12, 14, 13, 15, 0, 0 };

u8 D_801096E8[12] = { 12, 13, 35, 15, 35, 15, 36, 14, 36, 15, 0, 0 };

void (*D_801096F4[])(struct ShotObj*) = {
    func_800A2310,
    func_800A23E0,
    func_800A2A58,
    func_800A325C,
    func_800A366C,
    func_800A2E6C,
    func_800A23B4,
    func_800A23C0,
};

void (*D_80109714[])(struct ShotObj*) = {
    func_800A241C,
    func_800A24F0,
};

void (*D_8010971C[])(struct ShotObj*) = {
    func_800A25EC,
    func_800A2748,
    func_800A27F4,
    func_800A2870,
    func_800A2928,
    func_800A29C8,
};

void (*D_80109734[])(struct ShotObj*) = {
    func_800A2AA0,
    func_800A2B8C,
};

void (*D_8010973C[])(struct ShotObj*) = {
    func_800A2C70,
    func_800A2CEC,
    func_800A2D54,
};

void (*D_80109748[])(struct ShotObj*) = {
    func_800A2EB4,
    func_800A2F2C,
};

void (*D_80109750[])(struct ShotObj*) = {
    func_800A3010,
    func_800A3078,
    func_800A3170,
    func_800A31CC,
};

void (*D_80109760[])(struct ShotObj*) = {
    func_800A32B8,
    func_800A33A0,
};

void (*D_80109768[])(struct ShotObj*) = {
    func_800A348C,
    func_800A3520,
    func_800A3658,
};

void (*D_80109774[])(struct ShotObj*) = {
    func_800A3758,
    func_800A382C,
};

s16 D_8010977C[4][2] = {
    { -0x1280, 0x2AFF },
    { -0x1280, 0x2AFF },
    { -0xA80, 0x19FF },
    { -0xA80, 0x19FF },
};
