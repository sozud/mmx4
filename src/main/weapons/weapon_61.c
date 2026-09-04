// WeaponObj, weapon_object_update_funcs[61, 62]
// 800992FC..800994A0
#include "common.h"

void func_800992FC(struct WeaponObj* arg0)
{
    D_80108C38[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_61", func_80099338);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_61", func_80099388);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_61", func_80099480);

void (*D_80108C38[])(struct WeaponObj*) = {
    func_80099338,
    func_80099388,
    func_80099480,
};
