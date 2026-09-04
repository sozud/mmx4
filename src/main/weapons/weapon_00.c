// WeaponObj, weapon_object_update_funcs[0, 12, 23, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]
// 800922D8..80092648
#include "common.h"

void func_800922D8(struct WeaponObj* arg0)
{
    D_80108728[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_00", func_80092314);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_00", func_80092408);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_00", func_80092490);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_00", func_800924F8);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_00", func_80092598);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_00", func_80092600);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_00", func_80092614);

void (*D_80108728[])(struct WeaponObj*) = {
    func_80092314,
    func_80092408,
    func_80092598,
    func_80092614,
};
