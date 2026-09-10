// WeaponObj, weapon_object_update_funcs[2]
// 80093CBC..800941D4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093CBC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093D78);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093EB4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093FC4);

void func_8009403C(struct WeaponObj* arg0)
{
    if (!(arg0->unk70 & 8)) {
        arg0->unk67 = -1;
        arg0->unk2C = 0x4200;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk5 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80094078);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80094104);

void func_80094154(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_8009416C);
