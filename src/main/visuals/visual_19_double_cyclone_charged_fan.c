// VisualObj, visual_object_update_funcs[19]
// 800B2698..800B28CC
#include "common.h"
#include "main/visuals/visual_19_double_cyclone_charged_fan.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "weapon_resources.h"
#include "main/mains/main_23_slope_skier.h"

extern union AnimationStep* D_8011C0F0[5];
extern struct VisualSpawnOffset double_cyclone_charged_fan_offsets[2];

// double_cyclone_charged_fan_update

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/visuals/visual_19_double_cyclone_charged_fan", func_800B2698);
#else
void func_800B2698(struct VisualObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;
    s16 dx;
    struct PlayerObj* player = &g_Player;
    s16 dy;
    s32 cancel;

    cancel = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0)
        cancel = 1;
    if (g_Player.weapon != 7)
        cancel = 1;
    if (g_Player.actions_reset != 0)
        cancel = 1;
    if (g_Player.hp == 0)
        cancel = 1;
    if (cancel)
        goto zero;
    if (arg0->state == 0) {
        arg0->on_screen = 1;
        player_gfx = SP_PLAYER_GFX;
        sprite_frames = SP_SPRITE_FRAMES;
        arg0->unk38 = (u8*)player_gfx + player_gfx[8];
        arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
        arg0->animation_table = D_8011C0F0;
        arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
        arg0->unk42 = WEAPON_PALETTE_1;
        arg0->unk16 = VISUAL_SATURN_LAYER(0);
        dx = double_cyclone_charged_fan_offsets[arg0->unk2].x;
        dy = double_cyclone_charged_fan_offsets[arg0->unk2].y;
        if (arg0->unk2 == 0)
            arg0->unk15 = 0;
        else
            arg0->unk15 = PLAYER_FACING_RIGHT;
        if (player->unk15 == 0) {
            arg0->x_pos.i.hi = player->x_pos.i.hi + dx;
        } else {
            arg0->x_pos.i.hi = player->x_pos.i.hi - dx;
            arg0->unk15 ^= PLAYER_FACING_RIGHT;
        }
        {
            s16 y = player->y_pos.i.hi + dy;
            arg0->unk5C.value = 0x10;
            arg0->unk49 = 0;
            arg0->y_pos.i.hi = y;
        }
        set_animation(arg0, 3);
        arg0->state++;
        double_cyclone_charged_fan_draw(arg0);
    } else {
        if (arg0->unk5C.value == 0) {
        zero:
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
        arg0->unk5C.value--;
        animate_object(ANIMATED_OBJECT(arg0));
        double_cyclone_charged_fan_draw(arg0);
    }
}
#endif

void double_cyclone_charged_fan_draw(struct VisualObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    }
    update_on_screen(arg0, 0x18, 0x30);
}
