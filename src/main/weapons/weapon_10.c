// WeaponObj, weapon_object_update_funcs[10]
// 80093564..80093CBC
#include "common.h"

void func_80093564(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.unkC3 != 0;
    if (g_Player.unkC4 != 0) {
        disabled = 1;
    }
    if (g_Player.unk93 != 1) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    if (arg0->unk2 == 0) {
        D_80108804[arg0->state](arg0);
    } else {
        D_80108818[arg0->state](arg0);
    }
}

void func_80093610(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;
    struct Weapon10Ext* ext;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    player_gfx = SP_PLAYER_GFX;
    arg0->unk50 = (const u8*)D_801087C8;
    gfx_offset = player_gfx[2];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[10];
    arg0->animation_table = D_8011C070;
    arg0->unk40 = 0x530;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    arg0->unk15 = player->unk15;
    ext = &arg0->ext.weapon_10;
    func_80092E2C((struct VisualObj*)arg0, player, arg0->id);
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(8);
    } else {
        arg0->x_vel.val = FIXED(-8);
    }
    arg0->unk49 = 1;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    ext->timer = 0x10;
    ext->unk8F = 0;
    func_80015D60(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_80093C54(arg0);
}

void func_8009372C(struct WeaponObj* arg0)
{
    D_8010882C[arg0->unk5](arg0);
    func_80093C54(arg0);
}

void func_8009377C(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_10.timer == 0) {
        func_80015D60(arg0, 6);
        arg0->unk15 = 0;
        arg0->unk5++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->ext.weapon_10.timer--;
}

void func_800937EC(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 7);
        arg0->unk50 = (const u8*)D_801087CC;
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x3C;
        arg0->ext.weapon_10.unk90 = 0;
        arg0->unk5++;
    }
}

void func_80093858(struct WeaponObj* arg0)
{
    u8 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800933A0(arg0, arg0->ext.raw);
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        temp_v0 = 0x98;
        arg0->ext.weapon_10.timer = temp_v0;
        arg0->ext.weapon_10.unk8F = 1;
        arg0->unk5++;
    } else {
        arg0->ext.weapon_10.timer = temp_v0 - 1;
    }
}

void func_800938C0(struct WeaponObj* arg0)
{
    u8* timer_ptr;

    timer_ptr = &arg0->ext.weapon_10.timer;
    if (arg0->ext.weapon_10.timer == 0) {
        func_80015D60(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer--;
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_800933A0(arg0, timer_ptr);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_10", func_80093930);

void func_800939F4(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;
    u8 state;
    s32 y;

    owner = arg0->owner;
    if ((u8)owner->unk8F != 0) {
        arg0->on_screen = 1;
        state = (u8)arg0->state + 1;
        arg0->x_pos.val = owner->x_pos.val;
        y = owner->y_pos.val;
        arg0->ext.weapon_10.timer = 0x10;
        arg0->state = state;
        arg0->unk5 = 0;
        arg0->y_pos.val = y;
        func_80093C54(arg0);
    }
}

void func_80093A5C(struct WeaponObj* arg0)
{
    D_8010883C[arg0->unk5](arg0);
    func_80093C54(arg0);
}

void func_80093AAC(struct WeaponObj* arg0)
{
    u8* timer;
    u8 temp_v0;

    timer = &arg0->ext.weapon_10.timer;
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 7);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }

    temp_v0 = *timer;
    if (temp_v0 == 0) {
        arg0->unk50 = (const u8*)D_801087D0;
        arg0->unk64 = 1;
        *timer = 0x78;
        arg0->unk5++;
        return;
    }

    *timer = temp_v0 - 1;
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80093B4C(struct WeaponObj* arg0)
{
    u8 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x10;
        arg0->unk5++;
        return;
    }
    arg0->ext.weapon_10.timer = temp_v0 - 1;
}

void func_80093BA8(struct WeaponObj* arg0)
{
    u8 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->ext.weapon_10.timer;
    if (timer == 0) {
        func_80015D60(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer = timer - 1;
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

void func_80093C08(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->on_screen = 0;
        arg0->state = 3;
    } else {
        func_80093C54(arg0);
    }
}

void func_80093C54(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
    if (arg0->unk2 == 1) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x40);
    }
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
}
