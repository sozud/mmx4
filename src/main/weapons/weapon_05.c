// WeaponObj, weapon_object_update_funcs[5]
// 800957B0..80095DC0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_800957B0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095854);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_8009596C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095A28);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095AAC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095B10);

void func_80095B94(struct WeaponObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 == 0) {
        func_80095DA8(arg0);
        return;
    }
    func_8002B318((struct BaseObj*)arg0, 0x2C, 0x20);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095BE8);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095C38);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095CC0);

void func_80095D18(struct WeaponObj* arg0)
{
    func_80015D60(arg0, 2);
    arg0->unk67 = 1;
    arg0->y_vel.val = -FIXED(6);
    arg0->x_vel.val = 0;
    arg0->unk5 = 2;
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_05", func_80095D60);

void func_80095DA8(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
}
