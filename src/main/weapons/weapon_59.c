// WeaponObj, weapon_object_update_funcs[59]
// 80098ABC..80098F4C
#include "common.h"

void func_80098ABC(struct WeaponObj* arg0)
{
    D_80108BD8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_59", func_80098AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_59", func_80098C08);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_59", func_80098C84);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_59", func_80098CC0);

void func_80098D64(struct ShotObj* arg0)
{
    D_80108BE4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_59", func_80098DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_59", func_80098EA8);

void (*D_80108BD8[])(struct WeaponObj*) = {
    func_80098AF8,
    func_80098C08,
    func_80098C84,
};

void (*D_80108BE4[])(struct WeaponObj*) = {
    func_80098AF8,
    func_80098CC0,
    func_80098C84,
};
