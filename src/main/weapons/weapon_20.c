// WeaponObj, weapon_object_update_funcs[20, 21]
// 800929A0..80092D64
#include "common.h"

void func_800929A0(struct WeaponObj* arg0)
{
    D_80108758[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_20", func_800929DC);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_20", func_80092AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_20", func_80092B5C);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_20", func_80092C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_20", func_80092CEC);

void (*D_80108758[])(struct WeaponObj*) = {
    func_800929DC,
    func_80092AE4,
    func_800927B4,
    func_800927B4,
};
