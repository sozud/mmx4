// WeaponObj, weapon_object_update_funcs[60]
// 80098F4C..800992FC
#include "common.h"

void func_80098F4C(struct WeaponObj* arg0)
{
    D_80108C00[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_60", func_80098F88);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_60", func_80099118);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_60", func_800992C4);

void (*D_80108C00[])(struct WeaponObj*) = {
    func_80098F88,
    func_80099118,
    func_800992C4,
};
