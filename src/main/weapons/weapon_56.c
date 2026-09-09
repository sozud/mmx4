// WeaponObj, weapon_object_update_funcs[56]
// 800985F4..80098838
#include "common.h"

void func_800985F4(struct WeaponObj* arg0)
{
    D_80108B88[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_56", func_80098630);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_56", func_80098728);

void func_800987A8(struct WeaponObj* arg0)
{
    struct PlayerObj* temp_v1;

    temp_v1 = arg0->owner;
    temp_v1->unk98--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_56", func_800987DC);

void (*D_80108B88[])(struct WeaponObj*) = {
    func_80098630,
    func_80098728,
    func_800987A8,
};
