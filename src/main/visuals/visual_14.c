// VisualObj, visual_object_update_funcs[14]
// 800B1C5C..800B1D6C
#include "common.h"

void lift_effect_update(struct VisualObj* arg0)
{
    lift_effect_state_funcs[arg0->state](arg0);
}

void lift_effect_init(struct VisualObj* arg0)
{
    arg0->unk15 = arg0->unk50->unk15;
    set_animation(arg0, arg0->unk2);
    arg0->on_screen = 1;
    arg0->state++;
    update_on_screen(arg0, 0x50, 0x50);
}

void lift_effect_main(struct VisualObj* arg0)
{
    struct PlayerObj* temp_s1 = arg0->unk50;
    animate_object(arg0);
    arg0->x_pos.i.hi = temp_s1->x_pos.i.hi;
    arg0->y_pos.i.hi = temp_s1->y_pos.i.hi;
    update_on_screen(arg0, 0x30, 0x30);
}

void lift_effect_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*lift_effect_state_funcs[])(struct VisualObj*) = {
    lift_effect_init,
    lift_effect_main,
    lift_effect_despawn,
};
