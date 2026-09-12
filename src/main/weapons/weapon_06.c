// WeaponObj, weapon_object_update_funcs[6]
// 800961B0..800969D8
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800961B0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_8009633C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800963E8);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_80096584);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_8009663C);

void func_80096794(struct WeaponObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;

    arg0->on_screen = 1;
    player_gfx = SP_PLAYER_GFX;
    gfx_offset = player_gfx[0x1C / 4];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[0x3C / 4];
    arg0->animation_table = D_8011C0E4;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0x12;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    func_80015D60(arg0, 2);
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x18);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_80096834);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800968F8);

void func_80096994(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    arg1->weapon_06_slots[arg0->unk2] = NULL;
    arg0->unk50 = 0;
    arg1->unk99--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}
