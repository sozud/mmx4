// VisualObj, visual_object_update_funcs[33]
// 800B2AD0..800B2D48
#if defined(MMX4_PC)
#define PLAYER_UNKA6_ADDRESS (&g_Player.stock_charge)
#elif defined(VERSION_JP)
#define PLAYER_UNKA6_ADDRESS 0x80141A4E
#else
#define PLAYER_UNKA6_ADDRESS 0x8014196E
#endif
#include "common.h"
#include "main/visuals/visual_33_hover_jet.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "main/sprite_animations.h"
#include "weapon_resources.h"
#ifdef MMX4_SATURN
extern void saturn_queue_object(void*);
#endif

void hover_jet_update(struct VisualObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s8 var_s1;

    if (arg0->state == 0) {
        arg0->on_screen = 1;
        arg0->unk2 = -1;
        arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x30 / 4];
        arg0->animation_table = &D_8011BF40;
        arg0->unk40 = WEAPON_TEXTURE_BASE;
        arg0->unk42 = WEAPON_PALETTE_2;
        arg0->unk16 = VISUAL_SATURN_LAYER(3);
        arg0->unk5C.value = 0;
        arg0->state++;
    }

    var_s1 = -1;
    if (player->animation_step.fields.frame_index == 0xE5 || player->animation_step.fields.frame_index == 0xE6) {
        var_s1 = 0;
    }
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
        set_animation(arg0, var_s1 + 0x20);
        arg0->unk2 = var_s1;
    } else {
        animate_object(arg0);
    }

    arg0->unk15 = player->unk15;
    arg0->x_pos.val = player->x_pos.val;
    arg0->y_pos.val = player->y_pos.val;
    if (arg0->unk5C.value == 0) {
        arg0->unk5C.value = 8;
        func_8001540C(0, VISUAL_SOUND_HOVER, arg0);
    } else {
        arg0->unk5C.value--;
    }
    update_on_screen(arg0, 0x28, 0x28);
}

void stock_charge_meter_update(struct MiscObj* arg0)
{
    u8 playerUnkA6;
    struct PlayerObj* player = &g_Player;

    if (arg0->state == 0) {
        arg0->bg_offset = -1;
        arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x30 / 4];
        arg0->unk40 = WEAPON_TEXTURE_BASE;
        arg0->unk42 = WEAPON_PALETTE_10;
        arg0->unk16 = VISUAL_SATURN_LAYER(0x10);
        arg0->x_pos.i.hi = 0x20;
        arg0->y_pos.i.hi = 0x34;
        arg0->state++;
    } else {
        arg0->on_screen = 0;
        if (engine_obj.unk1F != 0 && player->stock_charge != 0) {
            arg0->on_screen = 1;
            playerUnkA6 = g_Player.stock_charge;
            arg0->x_pos.i.hi = 0x20;
            arg0->y_pos.i.hi = 0x34;
            arg0->animation_step.fields.frame_index = 0x1F - playerUnkA6;
        }
#ifdef MMX4_SATURN
        if (arg0->on_screen)
            saturn_queue_object(arg0);
#endif
    }
}
