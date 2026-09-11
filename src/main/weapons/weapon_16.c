// WeaponObj, weapon_object_update_funcs[16]
// 80097384..80097860
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097384);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097430);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_800975DC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097670);

void func_800976DC(struct WeaponObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->ext.weapon_16.unk91 == 0) {
        arg0->ext.weapon_16.unk91 = 4;
        arg0->unk64++;
    } else {
        arg0->ext.weapon_16.unk91--;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x30);
}

void func_80097740(struct WeaponObj* arg0)
{
    if (func_80097780(arg0) == 0) {
        func_80015DC8(arg0);
        func_800977D4(arg0);
    }
}

s32 func_80097780(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_16.timer == 0) {
        func_800972C8(arg0);
        func_800977D4(arg0);
        return 1;
    }
    arg0->ext.weapon_16.timer--;
    return 0;
}

void func_800977D4(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
}

void func_80097804(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    if (arg0->unk2 == 0) {
        g_Player.unk98--;
        g_Player.unk99--;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}
