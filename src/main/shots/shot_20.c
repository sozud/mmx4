// ShotObj, shot_object_update_funcs[20]
// 8009CF38..8009D200
#include "common.h"

u8 D_80108FBC[4] = { 0x80, 0xF1, 0xBE, 0x26 };
u8 D_80108FC0[4] = { 0x80, 0xF1, 0xFF, 0x26 };
u8 D_80108FC4[4] = { 0x80, 0xFA, 0xBD, 0x14 };
u8 D_80108FC8[4] = { 0x80, 0xFA, 0xFF, 0x14 };

void func_8009CF38(struct ShotObj* arg0)
{
    D_80108FCC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_20", func_8009CF74);

INCLUDE_ASM("main/nonmatchings/shots/shot_20", func_8009D048);

void func_8009D1D8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009D1F8(struct ShotObj* arg0)
{
}

void (*D_80108FCC[])(struct ShotObj*) = {
    func_8009CF74,
    func_8009D048,
    func_8009D1D8,
    func_8009D1F8,
};
