// WeaponObj, weapon_object_update_funcs[19]
// 800927EC..800929A0
#include "common.h"

void func_800927EC(struct WeaponObj* arg0)
{
    D_80108748[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_19", func_80092828);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_19", func_80092918);

void (*D_80108748[])(struct WeaponObj*) = {
    func_80092828,
    func_80092918,
    func_80092614,
    func_80092614,
};
