// WeaponObj, weapon_object_update_funcs[6]
// 800961B0..800969D8
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800961B0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_8009633C);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800963E8);

void func_80096584(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    u8* temp_a0;

    arg0->unk15 = arg1->unk15;
    temp_a0 = arg0->ext.raw;
    if (arg0->unk15 != 0) {
        arg0->ext.raw[1] = arg0->ext.raw[0];
    } else {
        arg0->ext.raw[1] = 0x20 - arg0->ext.raw[0];
    }
    func_8002B93C(MOVING_OBJECT(arg0), (temp_a0[1] - 8) & 0x1F);
    arg0->x_pos.val = arg1->x_pos.val + arg0->x_vel.val * 0x60;
    arg0->y_pos.val = arg1->y_pos.val + arg0->y_vel.val * 0x60;
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x18);
}

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

void func_800968F8(struct WeaponObj* arg0)
{
    u8* temp_s1 = arg0->ext.raw;
    u8 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.raw[2] == 0) {
        arg0->unk50 = 0;
        arg0->on_screen = 0;
        arg0->state = 3;
        return;
    }
    temp_v0 = arg0->ext.raw[3];
    if (temp_v0 == 0) {
        arg0->ext.raw[3] = 6;
        arg0->unk64++;
    } else {
        arg0->ext.raw[3] = temp_v0 - 1;
    }
    temp_s1[2] -= 1;
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x18);
}

void func_80096994(struct WeaponObj* arg0, struct PlayerObj* arg1)
{
    arg1->weapon_06_slots[arg0->unk2] = NULL;
    arg0->unk50 = 0;
    arg1->unk99--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}
