// WeaponObj, weapon_object_update_funcs[6]
// 800961B0..800969D8
#include "common.h"
#include "scratchpad.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_06", func_800961B0);

void func_8009633C(struct WeaponObj* arg0, struct PlayerObj* arg1)
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
    arg0->ext.weapon_6.direction = 8;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    func_80015D60(arg0, 1);
    arg0->state++;
    func_80096584(arg0, arg1);
}

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

s32 func_8009663C(struct WeaponObj* arg0, struct PlayerObj* player, struct MainObj* target)
{
    s32 slot;
    s8 active;

    if (target == player->weapon_06_slots[0]) {
        return 0;
    }
    if (target == player->weapon_06_slots[1]) {
        return 0;
    }
    if (target == player->weapon_06_slots[2]) {
        return 0;
    }
    active = target->active;
    if (active == 0) {
        return 0;
    }
    if (active & 4) {
        return 0;
    }
    if (target->unk7A != 0) {
        return 0;
    }
    if (target->unk54 == NULL) {
        return 0;
    }
    if (target->unk5C == 0) {
        return 0;
    }
    slot = -1;
    if (player->weapon_06_slots[2] == NULL) {
        slot = 2;
    }
    if (player->weapon_06_slots[1] == NULL) {
        slot = 1;
    }
    if (player->weapon_06_slots[0] == NULL) {
        slot = 0;
    }
    if (slot != -1 && func_8002BB80(MAIN_OBJECT(arg0), target) != 0) {
        if (func_80036DA0(1, 6, slot, PLAYER_OBJECT(target)) != NULL) {
            player->weapon_06_slots[slot] = target;
            player->unk99++;
            func_8001540C(0, 0x1C, arg0);
        }
        arg0->unk50 = NULL;
        func_8002B318(BASE_OBJECT(arg0), 0x18, 0x18);
        return 1;
    }
    return 0;
}

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

void func_80096834(struct WeaponObj* self, struct PlayerObj* player,
    struct PlayerObj* owner)
{
    struct QuadObj* quad;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x18, 0x18);
    if ((player->unk8F != 0) && (player->unk96 == 6)) {
        self->unk50 = &D_80108994;
        self->ext.weapon_6.lifetime = 0x3C;
        self->unk64 = 1;
        self->ext.weapon_6.timer = 6;
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 9;
            quad->unk2 = (u8)self->unk2;
            quad->unk5C = owner;
        }
        self->state = (u8)self->state + 1;
    }
}

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
