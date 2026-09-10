// WeaponObj, weapon_object_update_funcs[61, 62]
// 800992FC..800994A0
#include "common.h"

void func_800992FC(struct WeaponObj* arg0)
{
    D_80108C38[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_61", func_80099338);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_61", func_80099388);

void func_80099480(struct WeaponObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80108C0C[7][4] = {
    { 0xFC, 0xFD, 6, 5 },
    { 0xC0, 0xF9, 0x38, 0x1A },
    { 0xB9, 0xCD, 0x31, 0x40 },
    { 0xB1, 0xBF, 0x4A, 0x60 },
    { 0xB9, 0xD4, 0x3E, 0x3F },
    { 0xB1, 0xBF, 0x4A, 0x60 },
    { 0x96, 0xF1, 0x72, 0x29 },
};

u8 D_80108C28[8] = { 8, 9, 0x0A, 0x0B, 0x0F, 0, 0, 0 };

u8 D_80108C30[8] = { 3, 9, 3, 6, 0x0D, 0, 0, 0 };

void (*D_80108C38[])(struct WeaponObj*) = {
    func_80099338,
    func_80099388,
    func_80099480,
};
