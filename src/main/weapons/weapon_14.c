// WeaponObj, weapon_object_update_funcs[14]
// 80095DC0..800961B0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_14", func_80095DC0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_14", func_80095E3C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_14", func_80095F9C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_14", func_80096018);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_14", func_80096060);

void func_80096170(struct WeaponObj* arg0)
{
    if (arg0->unk98 != 0) {
        func_80095DA8(arg0);
        return;
    }

    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x18);
}
