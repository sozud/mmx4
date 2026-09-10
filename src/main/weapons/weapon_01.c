// WeaponObj, weapon_object_update_funcs[1]
// 80092F08..80093564
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_80092F08);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_80093014);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_80093130);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_800931A8);

void func_80093260(struct WeaponObj* arg0)
{
    func_80015D60(arg0, 3);
    arg0->unk50 = 0;
    arg0->unk75 = 0;
    arg0->state = 4;
    arg0->unk5 = 0;
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_800932A0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_80093310);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_800933A0);

void func_800933EC(struct WeaponObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->unk76 == 0) {
        func_80015D60(arg0, 5);
        arg0->unk5++;
    }
}

void func_8009343C(struct WeaponObj* arg0)
{
    func_80015DC8();
    if (arg0->unk46 == 0) {
        func_80093260(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_8009347C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_800934D8);

void func_80093524(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x28);
}
