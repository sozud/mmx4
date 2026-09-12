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

void func_80093310(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800933A0(arg0, arg0->ext.raw);
    if ((arg0->unk76 != 0) && ((arg0->unk72 & 3) != 0)) {
        func_80015D60(arg0, 4);
        if (arg0->unk72 & 1) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
        arg0->unk5++;
    }
}

void func_800933A0(struct WeaponObj* arg0, u8* arg1)
{
    if (arg1[4] == 0) {
        arg1[4] = 0xA;
        func_8001540C(0, 0x19, arg0);
        return;
    }
    arg1[4]--;
}

void func_800933EC(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk76 == 0) {
        func_80015D60(arg0, 5);
        arg0->unk5++;
    }
}

void func_8009343C(struct WeaponObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80093260(arg0);
    }
}

void func_8009347C(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk75 = 0;
    if (arg0->unk2 == 0) {
        g_Player.unk98--;
        g_Player.unk99--;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800934D8(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->on_screen = 0;
        arg0->state = 3;
    } else {
        func_80093524(arg0);
    }
}

void func_80093524(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x28);
}
