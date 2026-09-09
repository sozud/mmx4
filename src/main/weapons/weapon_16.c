// WeaponObj, weapon_object_update_funcs[16]
// 80097384..80097860
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097384);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097430);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_800975DC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097670);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_800976DC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097740);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097780);

void func_800977D4(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_16", func_80097804);
