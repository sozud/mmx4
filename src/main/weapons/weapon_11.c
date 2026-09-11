// WeaponObj, weapon_object_update_funcs[11]
// 800941D4..80094A78
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_800941D4);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_80094280);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_800942E8);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_8009443C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_800944B8);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_8009462C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_800946F0);

void func_80094794(struct MiscObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;

    func_800948D4(arg0);
    player_gfx = SP_PLAYER_GFX;
    gfx_offset = player_gfx[0xC / 4];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[0x2C / 4];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    func_80015D60(arg0, (get_random() & 3) + 2);
}

void func_8009481C(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_8009485C(arg0);
    } else {
        func_80094A04(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_8009485C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_800948D4);

void func_80094A04(struct MiscObj* arg0)
{
    s8 on_screen;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x14, 0x18) == 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));
        on_screen = arg0->on_screen ^ 1;
        arg0->on_screen = on_screen;
        if (on_screen != 0) {
            func_8002B318(BASE_OBJECT(arg0), 0x14, 0x18);
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}
