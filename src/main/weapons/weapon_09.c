// WeaponObj, weapon_object_update_funcs[9, 18]
// 80092648..800927EC
#include "common.h"

void func_80092648(struct WeaponObj* arg0)
{
    D_80108738[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_09", func_80092684);

void func_8009273C(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x14) == 0 && arg0->unk98 == 0) {
        func_80015DC8(arg0);
        func_8002B718(MOVING_OBJECT(arg0));
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x14);
        return;
    }
    func_80092600(arg0);
}

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
