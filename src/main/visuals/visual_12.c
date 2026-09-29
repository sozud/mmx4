// VisualObj, visual_object_update_funcs[12]
// 800B19BC..800B1AF8
#include "common.h"

void ride_dust_update(struct VisualObj* arg0)
{
    ride_dust_state_funcs[arg0->state](arg0);
}

void ride_dust_init(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = ride_dust_layers[arg0->unk2];
    set_animation(arg0, ride_dust_animations[arg0->unk2]);
}

void ride_dust_main(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0 = arg0->unk50;
    if (temp_a0->state != 2) {
        if (arg0->animation_step.fields.relative_step >= 0) {
            arg0->x_pos.i.hi = temp_a0->x_pos.i.hi;
            arg0->y_pos.i.hi = temp_a0->y_pos.i.hi;
            animate_object(arg0);
        } else {
            arg0->state = 2;
        }
        update_on_screen(arg0, 0x10, 0x10);
    } else {
        arg0->state = 2;
    }
}

void ride_dust_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*ride_dust_state_funcs[])(struct VisualObj*) = {
    ride_dust_init,
    ride_dust_main,
    ride_dust_despawn,
};

u8 ride_dust_animations[12] = {
    0x13,
    0x12,
    0x11,
    0x14,
    0x13,
    0x16,
    0x17,
    0x14,
    0x15,
    0,
    0,
    0,
};
u8 ride_dust_layers[12] = { 0, 0, 0, 0, 0, 4, 4, 4, 2, 0, 0, 0 };
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
