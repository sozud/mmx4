// WeaponObj, weapon_object_update_funcs[7]
// 80096E10..80097384
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80096E10);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80096EA4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097048);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_800970EC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097144);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_800971D4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097214);

void func_80097278(struct WeaponObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 == 0) {
        func_800972C8(arg0);
    } else {
        func_80097328(arg0);
    }
}

void func_800972C8(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_800972DC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097328);
