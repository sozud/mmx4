// WeaponObj, weapon_object_update_funcs[16]
// 80097384..80097860
#include "common.h"

void func_80097384(struct WeaponObj* arg0)
{
    s32 var_a1;

    var_a1 = g_Player.unkC3 != 0;
    if (g_Player.unkC4 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unk93 != 7) {
        var_a1 = 1;
    }
    if (g_Player.unkBF != 0) {
        var_a1 = 1;
    }
    if (g_Player.unk5C == 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        arg0->state = 3;
    }
    D_801089E8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097430);

void func_800975DC(struct WeaponObj* arg0)
{
    if (func_80097780(arg0) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x30) == 0) {
            if (arg0->unk5 == 0) {
                func_80097670(arg0);
            } else {
                func_800976DC(arg0);
            }
        } else {
            arg0->on_screen = 0;
            arg0->state = 2;
            arg0->unk50 = 0;
        }
        func_800977D4(arg0);
    }
}

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
