// WeaponObj, weapon_object_update_funcs[4]
// 800951C0..800954BC
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_04", func_800951C0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_04", func_80095254);

void func_800953D0(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x28) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B718(MOVING_OBJECT(arg0));
        func_8009547C(arg0);
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 3;
}

void func_80095430(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.unk98--;
    g_Player.unk99--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void func_8009547C(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x28);
}
