// WeaponObj, weapon_object_update_funcs[14]
// 80095DC0..800961B0
#include "common.h"

void func_80095DC0(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.unkC3 != 0;

    if (g_Player.unkC4 != 0) {
        should_reset = 1;
    }
    if (g_Player.unk93 != 5) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108974[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_14", func_80095E3C);

void func_80095F9C(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x2C, 0x18) == 0) {
        func_80015DC8(arg0);
        func_8002B718(MOVING_OBJECT(arg0));
        D_80108984[arg0->unk5](arg0);
        return;
    }

    func_80095DA8(arg0);
}

void func_80096018(struct WeaponObj* arg0)
{
    if (g_Player.input.buttons.held & 0xC) {
        arg0->ext.weapon_14.unk8D = 5;
        arg0->ext.weapon_14.unk8C = 0;
        arg0->unk5 = 1;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x18);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_14", func_80096060);

void func_80096170(struct WeaponObj* arg0)
{
    if (arg0->unk98 != 0) {
        func_80095DA8(arg0);
        return;
    }

    func_8002B318(BASE_OBJECT(arg0), 0x2C, 0x18);
}
