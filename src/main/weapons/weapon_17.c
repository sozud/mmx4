// WeaponObj, weapon_object_update_funcs[17]
// 80097B28..80097EEC
#include "common.h"

void func_80097B28(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.unkC3 != 0;

    if (g_Player.unkC4 != 0) {
        should_reset = 1;
    }
    if (g_Player.unk93 != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108A34[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_17", func_80097BA4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_17", func_80097CF4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_17", func_80097DD8);
