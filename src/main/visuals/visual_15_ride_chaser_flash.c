// VisualObj, visual_object_update_funcs[15]
// 800B1D6C..800B1EA4
#include "common.h"

void ride_chaser_flash_update(struct VisualObj* arg0)
{
    ride_chaser_flash_state_funcs[arg0->state](arg0);
}

void ride_chaser_flash_init(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk54 = 3;
    arg0->unk16 = 2;
    set_animation(arg0, 0x19);
}

void ride_chaser_flash_main(struct VisualObj* arg0)
{
    struct BaseObj* temp_s1 = arg0->unk50;

    arg0->x_pos.i.hi = temp_s1->x_pos.i.hi;
    arg0->y_pos.i.hi = temp_s1->y_pos.i.hi;
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk54--;
    }
    animate_object(arg0);
    if (temp_s1->state == 2) {
        arg0->state = 2;
    } else {
        if (arg0->unk54 == 0) {
            arg0->state = 2;
        }
        update_on_screen(arg0, 0x10, 0x10);
    }
}

void ride_chaser_flash_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*ride_chaser_flash_state_funcs[])(struct VisualObj*) = {
    ride_chaser_flash_init,
    ride_chaser_flash_main,
    ride_chaser_flash_despawn,
};
