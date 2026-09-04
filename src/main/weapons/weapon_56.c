// WeaponObj, weapon_object_update_funcs[56]
// 800985F4..80098838
#include "common.h"

void func_800985F4(struct WeaponObj* arg0)
{
    D_80108B88[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_56", func_80098630);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_56", func_80098728);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_56", func_800987A8);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_56", func_800987DC);

void (*D_80108B88[])(struct WeaponObj*) = {
    func_80098630,
    func_80098728,
    func_800987A8,
};
