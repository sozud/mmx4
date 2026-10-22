// VisualObj, visual_object_update_funcs[19]
// 800B2698..800B28CC
#include "common.h"
#include "main/visuals/visual_19_double_cyclone_charged_fan.h"
#include "main/55C4.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/mains/main_23_slope_skier.h"
#endif

// double_cyclone_charged_fan_update
#ifdef MMX4_PC
void func_800B2698(struct VisualObj* arg0);
extern u32* D_8011C0F0[5];
extern struct VisualSpawnOffset double_cyclone_charged_fan_offsets[2];
void double_cyclone_charged_fan_draw(struct VisualObj* arg0);
#endif

#ifdef MMX4_PC
void func_800B2698(struct VisualObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;
    struct VisualSpawnOffset offset;

    if (g_Player.input_locked != 0 || g_Player.capsule_state != 0 || g_Player.weapon != 7 || g_Player.actions_reset != 0 || g_Player.hp == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state != 0) {
        if (arg0->unk5C.value == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
        arg0->unk5C.value--;
        animate_object(ANIMATED_OBJECT(arg0));
        double_cyclone_charged_fan_draw(arg0);
        return;
    }
    arg0->on_screen = 1;
    player_gfx = SP_PLAYER_GFX;
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->animation_table = D_8011C0F0;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    offset = double_cyclone_charged_fan_offsets[arg0->unk2];
    arg0->unk15 = arg0->unk2 != 0 ? 0x40 : 0;
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + offset.x;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - offset.x;
        arg0->unk15 ^= 0x40;
    }
    arg0->unk5C.value = 0x10;
    arg0->unk49 = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + offset.y;
    set_animation(arg0, 3);
    arg0->state++;
    double_cyclone_charged_fan_draw(arg0);
}
#else
INCLUDE_ASM("main/nonmatchings/visuals/visual_19_double_cyclone_charged_fan", func_800B2698);
#endif

void double_cyclone_charged_fan_draw(struct VisualObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    }
    update_on_screen(arg0, 0x18, 0x30);
}
