// ItemObj, item_object_update_funcs[12]
// 800C3224..800C351C
#include "common.h"

void crusher_wall_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    crusher_wall_state_funcs[arg0->state](arg0);
    arg0->x_pos.val -= arg0->ext.packed;
    collide_with_players(arg0);
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0);
    } else {
        arg0->state = 3;
    }
}

void crusher_wall_init(struct ItemObj* self)
{
    self->active = 1;
    self->x_pos.i.hi = crusher_wall_x_positions[self->unk2];
    self->y_pos.i.hi = 0x1A8;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->bg_offset = g_Player.bg_offset;
    self->unk68 = (struct Unk_unk68*)crusher_wall_terrain_box;
    self->unk40 = 0x1500;
    self->animation_step.fields.frame_index = 0;
    self->unk16 = 6;
    self->unk15 = 0;
    self->sprite_frames = (u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 8);
    self->unk42 = 0x7901;
    self->unk7C.timer16 = 0x80;
    self->unk76 = 1;
    self->unk67 = 0;
    self->unk75 = 1;
    self->state = 1;
    self->ext.item_12.x_offset = 0x400;
}

void crusher_wall_rumble(struct ItemObj* arg0)
{

    crusher_wall_speed_funcs[arg0->unk5](arg0);
    if (--arg0->unk7C.timer16 != 0) {
        if (!(D_80141BD8.unk0 & 7)) {
            arg0->y_pos.u.hi += 0x10;
            func_800AF878(BASE_OBJECT(arg0), 1, 0x30, 0x20);
            func_800AF878(BASE_OBJECT(arg0), 1, 0x18, 0x10);
            arg0->y_pos.u.hi -= 0x10;
            start_screen_shake_y(8, 4, 1);
        }
    } else {
        arg0->state = 2;
    }
}

void crusher_wall_crush(struct ItemObj* arg0)
{
    if (crusher_wall_player_near(arg0) && (g_Player.unk70 & 8)) {
        g_Player.hp = -0x80;
    }
}

void crusher_wall_despawn(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void crusher_wall_accelerate(struct ItemObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->ext.item_12.x_offset += 0x100;
    } else {
        arg0->ext.item_12.x_offset += 0x200;
    }
}

void crusher_wall_hold(struct ItemObj* arg0)
{
    arg0->unk5++;
}

void crusher_wall_idle(struct ItemObj* arg0)
{
}

u8 crusher_wall_player_near(struct MainObj* arg0)
{
    s32 player_x;
    s32 object_x;
    object_x = arg0->x_pos.i.hi;
    player_x = g_Player.x_pos.i.hi;
    if (object_x - 0x30 < player_x && player_x < object_x + 0x30) {
        return 1;
    }
    return 0;
}

void (*crusher_wall_state_funcs[])(struct ItemObj*) = {
    crusher_wall_init,
    crusher_wall_rumble,
    crusher_wall_crush,
    crusher_wall_despawn,
};

void (*crusher_wall_speed_funcs[])(struct ItemObj*) = {
    crusher_wall_accelerate,
    crusher_wall_hold,
    crusher_wall_idle,
};

u8 crusher_wall_terrain_box[4] = { 0, 0, 0x30, 0x38 };
u16 crusher_wall_x_positions[4] = { 0x0900, 0x0D60, 0x13F0, 0x1A80 };
