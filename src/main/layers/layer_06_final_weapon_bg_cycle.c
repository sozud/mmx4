// LayerObj, layer_object_update_funcs[6]
// 800DA7C0..800DA878
#include "common.h"

void final_weapon_bg_cycle_update(struct LayerObj* arg0)
{
    final_weapon_bg_cycle_state_funcs[arg0->state](arg0);
}

void final_weapon_bg_cycle_init(struct LayerObj* arg0)
{
    arg0->bg_offset = 0;
    arg0->unk15 = 0;
    arg0->unk16 = 0;
    arg0->state++;
}

void final_weapon_bg_cycle_main(struct LayerObj* arg0)
{
    struct BackgroundObj* background;
    u8 temp_v0;
    s16 temp_v0_3;

    temp_v0 = arg0->bg_offset + 1;
    arg0->bg_offset = temp_v0;
    if (temp_v0 == 8) {
        arg0->bg_offset = 0;
        arg0->unk15 += 1;
        if (arg0->unk15 == 4) {
            arg0->unk15 = 0;
        }
        temp_v0_3 = arg0->unk15;
        background = &background_objects[1];
        background->x_pos.i.hi = temp_v0_3 << 9;
        background->unk4C = 1;
    }
}

void (*final_weapon_bg_cycle_state_funcs[])(struct LayerObj*) = {
    final_weapon_bg_cycle_init,
    final_weapon_bg_cycle_main,
};
