// WeaponObj, weapon_object_update_funcs[6]
// 800961B0..800969D8
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800961B0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_8009633C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800963E8);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_80096584);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_8009663C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_80096794);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_80096834);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800968F8);

void func_80096994(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    arg1->weapon_06_slots[arg0->unk2] = NULL;
    arg0->unk50 = 0;
    arg1->unk99--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}
