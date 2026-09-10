// WeaponObj, weapon_object_update_funcs[13]
// 800954BC..800957B0
#include "common.h"

void func_800954BC(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.unkC3 != 0;

    if (g_Player.unkC4 != 0) {
        should_reset = 1;
    }
    if (g_Player.unk93 != 4) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108934[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_13", func_80095538);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_13", func_8009564C);

void func_80095770(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x38, 0x38);
}
