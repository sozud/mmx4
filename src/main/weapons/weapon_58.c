// WeaponObj, weapon_object_update_funcs[58]
// 80098990..80098ABC
#include "common.h"

void func_80098990(struct WeaponObj* arg0)
{
    D_80108BC0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_58", func_800989CC);

void func_80098A78(struct WeaponObj* arg0)
{
    if ((u8)arg0->unk5-- == 0) {
        arg0->state = 2;
    }
}

void func_80098A9C(struct WeaponObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80108BB4[4] = { 0xF4, 0xB1, 0x16, 0x88 };

u8 D_80108BB8[4] = { 0xF4, 0xB1, 0x16, 0x4C };

u8 D_80108BBC[4] = { 0xF4, 0, 0x16, 0x39 };

void (*D_80108BC0[])(struct WeaponObj*) = {
    func_800989CC,
    func_80098A78,
    func_80098A9C,
};
