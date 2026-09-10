// ShotObj, shot_object_update_funcs[30]
// 8009FB60..8009FF10
#include "common.h"

void func_8009FB60(struct ShotObj* arg0)
{
    D_8010922C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_30", func_8009FB9C);

INCLUDE_ASM("main/nonmatchings/shots/shot_30", func_8009FD00);

void func_8009FE38(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009FE58(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_30", func_8009FE60);

void (*D_80109200[3])(struct ShotObj*) = {
    func_8009F89C,
    func_8009F94C,
    func_8009F9E0,
};

u8 D_8010920C[4][4] = {
    { 0xF3, 0xFA, 0x17, 0x0A },
    { 0xF5, 0xFD, 0x1B, 0x0A },
    { 0xFF, 0xFF, 0x0A, 0x04 },
    { 0x02, 0x02, 0x0D, 0x04 },
};

s32 D_8010921C[4] = { -0x22000, 0x22000, -0x10000, 0x10000 };

void (*D_8010922C[])(struct ShotObj*) = {
    func_8009FB9C,
    func_8009FD00,
    func_8009FE38,
    func_8009FE58,
};
