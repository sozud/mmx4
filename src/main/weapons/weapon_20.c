// WeaponObj, weapon_object_update_funcs[20, 21]
// 800929A0..80092D64
#include "common.h"

void func_800929A0(struct WeaponObj* arg0)
{
    D_80108758[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_20", func_800929DC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_20", func_80092AE4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_20", func_80092B5C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_20", func_80092C2C);

void func_80092CEC(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    if (arg0->unk84.value == 0) {
        weapon = arg0->unk7C;
        if (weapon->ext.weapon_20.unk8E == 0) {
            arg0->unk84.value = 1;
        }
        if (weapon->unk15 != arg0->unk15) {
            arg0->unk84.value = 1;
        }
        if (arg0->unk84.value == 0) {
            func_80092E2C(arg0, weapon, arg0->id);
        }
    }
}

void (*D_80108758[])(struct WeaponObj*) = {
    func_800929DC,
    func_80092AE4,
    func_800927B4,
    func_800927B4,
};
