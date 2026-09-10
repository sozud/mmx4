// ShotObj, shot_object_update_funcs[21]
// 8009D200..8009D74C
#include "common.h"

u8 D_80108FDC[4] = { 0xF7, 0xF8, 0x11, 0x11 };
u8 D_80108FE0[4] = { 0xF3, 0xFC, 0x18, 0x0B };
u8 D_80108FE4[4] = { 0xFC, 0xF4, 0x08, 0x18 };
u8 D_80108FE8[4] = { 0, 0, 5, 5 };
u8 D_80108FEC[4] = { 0, 2, 0x0A, 4 };
u8 D_80108FF0[4] = { 0, 0, 4, 0x0A };

void func_8009D200(struct ShotObj* arg0)
{
    D_80108FF4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_21", func_8009D23C);

INCLUDE_ASM("main/nonmatchings/shots/shot_21", func_8009D3F4);

void func_8009D560(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009D580(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_21", func_8009D588);

void (*D_80108FF4[])(struct ShotObj*) = {
    func_8009D23C,
    func_8009D3F4,
    func_8009D560,
    func_8009D580,
};
