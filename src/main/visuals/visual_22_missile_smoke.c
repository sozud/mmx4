// VisualObj, visual_object_update_funcs[22]
// 800B3074..800B322C
#include "common.h"

void missile_smoke_update(struct VisualObj* arg0)
{
    missile_smoke_state_funcs[arg0->state](arg0);
}

void missile_smoke_init(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    if (arg0->unk2 != 0x10) {
        arg0->unk15 = 0;
        missile_smoke_main(arg0);
    } else {
        arg0->unk16 = 2;
        set_animation(arg0, 0x25);
    }
}

void missile_smoke_main(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0;

    if (arg0->unk2 != 0x10) {
        if (arg0->unk2 <= 6) {
            if (arg0->unk2 == 0) {
                set_animation(arg0, 0x21);
            } else {
                set_animation(arg0, ((arg0->unk2 - 1) >> 1) + 0x21);
            }
            arg0->unk2++;
            is_on_screen(arg0);
        } else {
            arg0->on_screen = 0;
            arg0->state = 2;
        }
    } else {
        temp_a0 = arg0->unk50;
        if (((u8)temp_a0->shot_types[0] == 2) && (temp_a0->active != 0) && (temp_a0->last_shot_type & 0x40)) {
            arg0->unk15 = temp_a0->unk15;
            arg0->x_pos.i.hi = temp_a0->x_pos.i.hi;
            arg0->y_pos.i.hi = temp_a0->y_pos.i.hi;
            animate_object(arg0);
            is_on_screen(arg0);
            return;
        }
        arg0->on_screen = 0;
        ZeroObjectState(arg0);
    }
}

void missile_smoke_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*missile_smoke_state_funcs[])(struct VisualObj*) = {
    missile_smoke_init,
    missile_smoke_main,
    missile_smoke_despawn,
};

u32 D_8010A5E0 = 0x33CD;
