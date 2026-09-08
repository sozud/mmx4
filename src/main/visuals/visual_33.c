// VisualObj, visual_object_update_funcs[33]
// 800B2AD0..800B2D48
#ifdef VERSION_JP
#define PLAYER_UNKA6_ADDRESS 0x80141A4E
#else
#define PLAYER_UNKA6_ADDRESS 0x8014196E
#endif
#include "common.h"

void func_800B2AD0(struct VisualObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s8 var_s1;

    if (arg0->state == 0) {
        arg0->on_screen = 1;
        arg0->unk2 = -1;
        arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x30 / 4];
        arg0->animation_table = &D_8011BF40;
        arg0->unk42 = 0x7802;
        arg0->unk40 = 0;
        arg0->unk16 = 3;
        arg0->unk5C = 0;
        arg0->state++;
    }

    var_s1 = -((player->animation_step.fields.frame_index == 0xE5 || player->animation_step.fields.frame_index == 0xE6) ^ 1);
    if (player->animation_step.fields.frame_index == 0xDD || player->animation_step.fields.frame_index == 0xDE) {
        var_s1 = 1;
    }
    if (player->animation_step.fields.frame_index == 0xDF || player->animation_step.fields.frame_index == 0xE0) {
        var_s1 = 2;
    }
    if (player->animation_step.fields.frame_index == 0xE1 || player->animation_step.fields.frame_index == 0xE2) {
        var_s1 = 3;
    }
    if (player->animation_step.fields.frame_index == 0xE3 || player->animation_step.fields.frame_index == 0xE4) {
        var_s1 = 4;
    }

    if (var_s1 == -1) {
        ZeroObjectState(arg0);
        return;
    }
    if (var_s1 != arg0->unk2) {
        func_80015D60(arg0, var_s1 + 0x20);
        arg0->unk2 = var_s1;
    } else {
        func_80015DC8(arg0, var_s1);
    }

    arg0->unk15 = player->unk15;
    arg0->x_pos.val = player->x_pos.val;
    arg0->y_pos.val = player->y_pos.val;
    if (arg0->unk5C == 0) {
        arg0->unk5C = 8;
        func_8001540C(0, 0x1F, arg0);
    } else {
        arg0->unk5C--;
    }
    func_8002B318(arg0, 0x28, 0x28);
}

void func_800B2C8C(struct MiscObj* arg0)
{
    u8 playerUnkA6;

    if (arg0->state == 0) {
        arg0->bg_offset = -1;
        arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x30 / 4];
        arg0->unk42 = 0x780A;
        arg0->unk16 = 0x10;
        arg0->x_pos.i.hi = 0x20;
        arg0->unk40 = 0;
        arg0->y_pos.i.hi = 0x34;
        arg0->state++;
    } else {
        arg0->on_screen = 0;
        if (engine_obj.unk1F != 0 && g_Player.unkA6 != 0) {
            arg0->on_screen = 1;
            playerUnkA6 = *(u8*)PLAYER_UNKA6_ADDRESS;
            arg0->x_pos.i.hi = 0x20;
            arg0->y_pos.i.hi = 0x34;
            arg0->animation_step.fields.frame_index = 0x1F - playerUnkA6;
        }
    }
}
