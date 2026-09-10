// WeaponObj, weapon_object_update_funcs[13]
// 800954BC..800957B0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_13", func_800954BC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_13", func_80095538);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_13", func_8009564C);

void func_80095770(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x38, 0x38);
}
