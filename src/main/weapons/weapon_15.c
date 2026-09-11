// WeaponObj, weapon_object_update_funcs[15]
// 800969D8..80096E10
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_15", func_800969D8);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_15", func_80096A84);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_15", func_80096B54);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_15", func_80096C8C);

void func_80096DC0(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    func_80015930(0, 0x1D);
    g_Player.unk99--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}
