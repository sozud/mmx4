// WeaponObj, weapon_object_update_funcs[57]
// 80098838..80098990
#include "common.h"

void func_80098838(struct WeaponObj* arg0)
{
    D_80108BA8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_57", func_80098874);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_57", func_800988C4);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_57", func_80098970);

void (*D_80108BA8[])(struct WeaponObj*) = {
    func_80098874,
    func_800988C4,
    func_80098970,
};
