// WeaponObj, weapon_object_update_funcs[8]
// 80097860..80097B28
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_80097860);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_800978DC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_80097A24);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_80097AC8);

void func_80097B14(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}
