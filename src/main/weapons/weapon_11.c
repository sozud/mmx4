// WeaponObj, weapon_object_update_funcs[11]
// 800941D4..80094A78
#include "common.h"

void func_800941D4(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.unkC3 != 0;
    if (g_Player.unkC4 != 0) {
        disabled = 1;
    }
    if (g_Player.unk93 != 2) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    if (arg0->unk2 == 0) {
        D_80108870[arg0->state](arg0);
    } else {
        D_80108880[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_80094280);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_800942E8);

void func_8009443C(s8 arg0)
{
    struct WeaponObj* weapon_obj;

    weapon_obj = find_free_weapon_obj();
    if (weapon_obj != NULL) {
        weapon_obj->active = 1;
        weapon_obj->id = 0xB;
        weapon_obj->unk2 = arg0;
        weapon_obj->bg_offset = g_Player.bg_offset;
        g_Player.unk98++;
        g_Player.unk99++;
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_800944B8);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_11", func_8009462C);

void func_800946F0(struct MiscObj* arg0)
{
    s32 var_a1;

    var_a1 = g_Player.unkC3 != 0;
    if (g_Player.unkC4 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unk93 != 2) {
        var_a1 = 1;
    }
    if (g_Player.unk96 == 0xB) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state == 0) {
        func_80094794(arg0);
        return;
    }
    func_80094A04(arg0);
}

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

void func_8009485C(struct MiscObj* arg0)
{
    s32* sprite_frames;
    s32 offset;

    func_800948D4(arg0);
    sprite_frames = SP_SPRITE_FRAMES;
    offset = sprite_frames[6];
    arg0->animation_table = D_8011C018;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7802;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + offset;
    func_80015D60(arg0, D_8010889C[get_random() & 7]);
}

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
