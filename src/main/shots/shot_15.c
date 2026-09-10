// ShotObj, shot_object_update_funcs[15]
// 8009C0F0..8009C364
#include "common.h"

u8 D_80108ED8[4] = { 0xFD, 0xFD, 0x06, 0x06 };

void func_8009C0F0(struct ShotObj* arg0)
{
    D_80108EDC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_15", func_8009C12C);

void func_8009C238(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_8009C258(struct ShotObj* arg)
{
}

void func_8009C260(struct ShotObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
    func_80015DC8(arg0);
    func_8002D9BC(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_15", func_8009C298);

void func_8009C344(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108EDC[])(struct ShotObj*) = {
    func_8009C12C,
    func_8009C298,
    func_8009C344,
};

void (*D_80108EE8[3])(struct ShotObj*) = {
    func_8009C238,
    func_8009C258,
    func_8009C260,
};

u8 D_80108EF4[11][4] = {
    { 0xF3, 0xFD, 0x0A, 0x05 },
    { 0xE4, 0xFD, 0x1A, 0x05 },
    { 0xCC, 0xFD, 0x31, 0x05 },
    { 0xAB, 0xFD, 0x5D, 0x05 },
    { 0xFD, 0xF4, 0x05, 0x0B },
    { 0xFD, 0xE8, 0x05, 0x17 },
    { 0xFD, 0xCD, 0x05, 0x31 },
    { 0xFD, 0xAE, 0x05, 0x42 },
    { 0xFD, 0xFE, 0x05, 0x0D },
    { 0xFD, 0xFE, 0x05, 0x16 },
    { 0xFD, 0xFE, 0x05, 0x34 },
};

u8 D_80108F20[4] = { 0xFD, 0xFE, 0x05, 0x50 };

u8* D_80108F24[12] = {
    D_80108EF4[0],
    D_80108EF4[1],
    D_80108EF4[2],
    D_80108EF4[3],
    D_80108EF4[4],
    D_80108EF4[5],
    D_80108EF4[6],
    D_80108EF4[7],
    D_80108EF4[8],
    D_80108EF4[9],
    D_80108EF4[10],
    D_80108F20,
};
