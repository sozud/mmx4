// ShotObj, shot_object_update_funcs[1]
// 80099B30..80099D10
#include "common.h"

u8 D_80108C8C[4] = { 0xF8, 0xFC, 0x0D, 0x09 };
s8 D_80108C90[2][2] = { { 0x12, 0x09 }, { -0x12, 0x09 } };
u8 D_80108C94[5][4] = {
    { 3, 0, 1, 0x3B },
    { 3, 0, 1, 0x3C },
    { 3, 0, 1, 0x3D },
    { 3, 0, 1, 0x3E },
    { 3, 0, 0xFC, 0x3F },
};
u8* D_80108CA8 = D_80108C94[0];

void func_80099B30(struct ShotObj* arg0)
{
    D_80108CAC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_01", func_80099B6C);

INCLUDE_ASM("main/nonmatchings/shots/shot_01", func_80099C68);

void func_80099CF0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108CAC[])(struct ShotObj*) = {
    func_80099B6C,
    func_80099C68,
    func_80099CF0,
};
