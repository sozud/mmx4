// VisualObj, visual_object_update_funcs[13]
// 800B1AF8..800B1C5C
#include "common.h"

u8 ride_chaser_jet_animations[16] = {
    0x15,
    0x16,
    0x17,
    0x18,
    0x15,
    0x15,
    0x15,
    0x16,
    0x16,
    0x16,
    0x17,
    0x17,
    0x17,
    0,
    0,
    0,
};

void ride_chaser_jet_update(struct VisualObj* arg0)
{
    ride_chaser_jet_state_funcs[arg0->state](arg0);
}

void ride_chaser_jet_init(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk54 = 0xFF;
    arg0->unk56 = 0xFF;
    arg0->unk16 = 6;
    set_animation(arg0, 0x15);
}

void ride_chaser_jet_main(struct VisualObj* arg0)
{
    struct PlayerObj* player;
    s32 animation;
    s16 previous_frame;
    u8 frame;
    u8 next_animation;

    player = arg0->unk50;
    if (player->state != 2) {
        frame = player->animation_step.fields.frame_index;
        previous_frame = arg0->unk56;
        next_animation = ride_chaser_jet_animations[frame];
        if (frame != previous_frame && (animation = next_animation & 0xFF) != arg0->unk54) {
            set_animation_frame(ANIMATED_OBJECT(arg0), animation,
                arg0->animation_step.fields.event);
            frame = player->animation_step.fields.frame_index;
            arg0->unk54 = next_animation;
            arg0->unk56 = frame;
        }
        arg0->x_pos.i.hi = player->x_pos.i.hi;
        arg0->y_pos.i.hi = player->y_pos.i.hi;
        animate_object(ANIMATED_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
}

void ride_chaser_jet_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*ride_chaser_jet_state_funcs[])(struct VisualObj*) = {
    ride_chaser_jet_init,
    ride_chaser_jet_main,
    ride_chaser_jet_despawn,
};
