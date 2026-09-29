// VisualObj, visual_object_update_funcs[34]
// 800B5570..800B56F4
#include "common.h"

void split_mushroom_fx_update(struct VisualObj* arg0)
{
    split_mushroom_fx_state_funcs[arg0->state](arg0);
}

void split_mushroom_fx_main(struct VisualObj* arg0)
{
    if (arg0->unk50->state >= 2) {
        arg0->on_screen = 0;
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->unk2 == 0) {
        if (--arg0->unk5C.fields.unk5E == 0) {
            arg0->state = 1;
        } else {
            if (arg0->unk5C.value == 0) {
                arg0->x_pos.i.hi = arg0->x_pos.i.hi + 0x20;
            } else {
                arg0->x_pos.i.hi = arg0->x_pos.i.hi - 0x20;
            }
            arg0->y_pos.i.hi += 1;
            arg0->unk5C.value ^= 0x20;
            animate_object(arg0);
        }
    } else {
        if (--arg0->unk5C.value == 0) {
            arg0->state = 1;
        }
        arg0->x_pos.val = arg0->unk50->x_pos.val;
        arg0->y_pos.val = arg0->unk50->y_pos.val;
        animate_object(arg0);
    }
    update_on_screen(arg0, 0x20, 0x20);
}

void split_mushroom_fx_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*split_mushroom_fx_state_funcs[])(struct VisualObj*) = {
    split_mushroom_fx_main,
    split_mushroom_fx_despawn,
};
