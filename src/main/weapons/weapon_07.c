// WeaponObj, weapon_object_update_funcs[7]
// 80096E10..80097384
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80096E10);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80096EA4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097048);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_800970EC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097144);

void func_800971D4(struct WeaponObj* arg0)
{
    if (func_80097214(arg0) == 0) {
        func_80015DC8(arg0);
        func_80097328(arg0);
    }
}

s32 func_80097214(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_7.timer == 0) {
        func_80015D60(arg0, 2);
        arg0->unk50 = 0;
        arg0->unk5 = 3;
        func_80097328(arg0);
        return 1;
    }

    arg0->ext.weapon_7.timer--;
    return 0;
}

void func_80097278(struct WeaponObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 == 0) {
        func_800972C8(arg0);
    } else {
        func_80097328(arg0);
    }
}

void func_800972C8(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

void func_800972DC(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.unk98--;
    g_Player.unk99--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void func_80097328(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    } else {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}
