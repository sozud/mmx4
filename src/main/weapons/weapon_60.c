// WeaponObj, weapon_object_update_funcs[60]
// 80098F4C..800992FC
#include "common.h"

void func_80098F4C(struct WeaponObj* arg0)
{
    D_80108C00[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_60", func_80098F88);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_60", func_80099118);

void func_800992C4(struct WeaponObj* arg0)
{
    struct PlayerObj* temp_a2;

    temp_a2 = arg0->owner;
    temp_a2->input.bytes.previous_high ^= 1 << arg0->unk2;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108C00[])(struct WeaponObj*) = {
    func_80098F88,
    func_80099118,
    func_800992C4,
};
