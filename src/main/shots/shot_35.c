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

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2C70);

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

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A3010);

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
