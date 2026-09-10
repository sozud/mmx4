// ShotObj, shot_object_update_funcs[34]
// 800A16FC..800A22D4
#include "common.h"

s8 D_80109510[10][4] = {
    { -6, -10, 10, 18 },
    { -17, -10, 33, 18 },
    { 0, -1, 11, 3 },
    { -6, -5, 10, 11 },
    { -7, -15, 13, 30 },
    { 0, 0, 7, 8 },
    { 10, 10, 10, 11 },
    { 40, 40, 40, 42 },
    { 41, 41, 41, 42 },
    { 18, 9, -18, 9 },
};

s32 D_80109538[4] = { 7, 6, 11, 15 };

s32 D_80109548[4] = { 4, 5, 3, 2 };

void (*D_80109558[])(struct ShotObj*) = {
    func_800A19A8,
    func_800A1B1C,
    func_800A1BEC,
};

u8 D_80109564[4][4] = {
    { 8, 8, 13, 17 },
    { 7, 7, 12, 16 },
    { 9, 9, 14, 18 },
    { 6, 6, 11, 15 },
};

void (*D_80109574[])(struct ShotObj*) = {
    NULL,
    func_800A18F4,
    func_800A1F7C,
    func_800A1CCC,
    func_800A1E3C,
    func_800A1C90,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A16FC);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A18A8);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A18F4);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A19A8);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1B1C);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1BEC);

void func_800A1C90(struct ShotObj* arg0)
{
    D_80109558[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1CCC);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1E3C);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A1F7C);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A2098);

INCLUDE_ASM("main/nonmatchings/shots/shot_34", func_800A220C);

void func_800A2278(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010958C[arg0->state](arg0);
    CollisionRelated(arg0);
}

void (*D_8010958C[])(struct ShotObj*) = {
    func_800A16FC,
    func_800A2098,
    func_800A220C,
};
