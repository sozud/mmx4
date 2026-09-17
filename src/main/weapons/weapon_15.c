// WeaponObj, weapon_object_update_funcs[15]
// 800969D8..80096E10
#include "common.h"

void func_800969D8(struct WeaponObj* arg0)
{
    s32 var_a1;

    var_a1 = g_Player.unkC3 != 0;
    if (g_Player.unkC4 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unk93 != 6) {
        var_a1 = 1;
    }
    if (g_Player.unk5C == 0) {
        var_a1 = 1;
    }
    if (g_Player.unkBF != 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        arg0->state = 3;
    }
    D_801089AC[arg0->state](arg0);
}

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
