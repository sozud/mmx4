// WeaponObj, weapon_object_update_funcs[9, 18]
// 80092648..800927EC
#include "common.h"

void func_80092648(struct WeaponObj* arg0)
{
    D_80108738[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_09", func_80092684);

INCLUDE_ASM("asm/us/main/nonmatchings/weapons/weapon_09", func_8009273C);

void func_800927B4(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.unk98--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108738[])(struct WeaponObj*) = {
    func_80092684,
    func_8009273C,
    func_800927B4,
    func_800927B4,
};
