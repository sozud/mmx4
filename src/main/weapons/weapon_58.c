// WeaponObj, weapon_object_update_funcs[58]
// 80098990..80098ABC
#include "common.h"

void func_80098990(struct WeaponObj* arg0)
{
    D_80108BC0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_58", func_800989CC);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_58", func_80098A78);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_58", func_80098A9C);

void (*D_80108BC0[])(struct WeaponObj*) = {
    func_800989CC,
    func_80098A78,
    func_80098A9C,
};
