// WeaponObj, weapon_object_update_funcs[1]
// 80092F08..80093564
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_80092F08);

void func_80093014(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;
    struct Weapon1Ext* ext;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    player_gfx = SP_PLAYER_GFX;
    arg0->unk50 = (const u8*)D_801087E8;
    gfx_offset = player_gfx[2];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[10];
    arg0->animation_table = D_8011C070;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    arg0->unk15 = player->unk15;
    ext = &arg0->ext.weapon_1;
    func_80092E2C((struct VisualObj*)arg0, player, arg0->id);
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(8);
    } else {
        arg0->x_vel.val = FIXED(-8);
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk49 = 0;
    ext->lifetime = 0x69;
    ext->timer = 0x10;
    func_80015D60(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_80093524(arg0);
}

void func_80093130(struct WeaponObj* arg0)
{
    u8 temp_v0;

    temp_v0 = arg0->ext.weapon_1.timer - 1;
    arg0->ext.weapon_1.timer = temp_v0;
    if (temp_v0 == 0) {
        func_80015D60(arg0, 1);
        arg0->unk16 = 3;
        arg0->state++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B718(MOVING_OBJECT(arg0));
    }
    func_80093524(arg0);
}

void func_800931A8(struct WeaponObj* arg0)
{
    s32 expired;
    u8 timer;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x28) == 0) {
        timer = arg0->ext.weapon_1.lifetime - 1;
        expired = (timer & 0xFF) == 0;
        arg0->ext.weapon_1.lifetime = timer;
        if ((u8)arg0->unk72 & 0xC) {
            expired = 1;
        }
        if (expired != 0) {
            func_80093260(arg0);
        } else {
            D_801087EC[arg0->unk5](arg0);
        }
        func_80093524(arg0);
    } else {
        arg0->on_screen = 0;
        arg0->state = 3;
        arg0->unk50 = 0;
        arg0->unk75 = 0;
    }
}

void func_80093260(struct WeaponObj* arg0)
{
    func_80015D60(arg0, 3);
    arg0->unk50 = 0;
    arg0->unk75 = 0;
    arg0->state = 4;
    arg0->unk5 = 0;
}

void func_800932A0(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 2);
        arg0->unk50 = (const u8*)D_801087FC;
        arg0->unk68 = D_80108800;
        arg0->ext.weapon_1.unk90 = 0;
        arg0->unk75 = 1;
        arg0->unk5++;
    }
}

void func_80093310(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800933A0(arg0, &arg0->ext.weapon_1.lifetime);
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
    func_80015DC8(ANIMATED_OBJECT(arg0));
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
