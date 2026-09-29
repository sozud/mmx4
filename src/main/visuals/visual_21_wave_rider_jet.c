// VisualObj, visual_object_update_funcs[21]
// 800B2E98..800B3074
#include "common.h"

void wave_rider_jet_init(struct VisualObj* arg0)
{
    struct VisualObj* temp_v1 = arg0->unk50;
    arg0->unk40 = temp_v1->unk40;
    arg0->unk42 = temp_v1->unk42 & ~0x8000;
    arg0->animation_table = temp_v1->animation_table;
    arg0->unk3C = temp_v1->unk3C;
    arg0->unk15 = temp_v1->unk15;
    arg0->bg_offset = temp_v1->bg_offset;
    arg0->x_pos.val = temp_v1->x_pos.val;
    arg0->y_pos.val = temp_v1->y_pos.val;
    arg0->unk16 = 6;
    arg0->unk2 = wave_rider_jet_animations[temp_v1->animation_step.fields.frame_index];
    set_animation(arg0, arg0->unk2);
    arg0->state++;
}

void wave_rider_jet_main(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0;

    temp_a0 = arg0->unk50;
    if (temp_a0->state == 0 || temp_a0->state == 2) {
        arg0->state = 2;
    } else {
        if (arg0->unk2 != wave_rider_jet_animations[temp_a0->animation_step.fields.frame_index]) {
            arg0->unk2 = wave_rider_jet_animations[temp_a0->animation_step.fields.frame_index];
            set_animation(arg0, arg0->unk2);
        } else {
            animate_object(arg0);
        }
        update_on_screen(arg0, 0x90, 0x90);
    }
}

void wave_rider_jet_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void wave_rider_jet_update(struct VisualObj* arg0)
{
    struct BaseObj* temp_v1 = arg0->unk50;

    arg0->x_pos.val = temp_v1->x_pos.val;
    arg0->y_pos.val = temp_v1->y_pos.val;
    wave_rider_jet_state_funcs[arg0->state](arg0);
}

u8 wave_rider_jet_animations[16] = {
    6,
    7,
    8,
    9,
    6,
    6,
    6,
    7,
    7,
    7,
    8,
    8,
    8,
    0,
    0,
    0,
};

void (*wave_rider_jet_state_funcs[])(struct VisualObj*) = {
    wave_rider_jet_init,
    wave_rider_jet_main,
    wave_rider_jet_despawn,
};
