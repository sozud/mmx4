// LayerObj, layer_object_update_funcs[6]
// 800DA7C0..800DA878
#include "common.h"
#include "main/layers/layer_06_final_weapon_bg_cycle.h"

// final_weapon_bg_cycle_state_funcs
extern void (*final_weapon_bg_cycle_state_funcs[])(struct LayerObj*);
void final_weapon_bg_cycle_init(struct LayerObj*);
void final_weapon_bg_cycle_main(struct LayerObj*);

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

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/layers/layer_06_final_weapon_bg_cycle", final_weapon_bg_cycle_main);
#else
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
#ifdef MMX4_SATURN
        background = &background_objects[1];
        background->x_pos.i.hi = (arg0->unk15 & 1) << 9;
        background->y_pos.i.hi = (arg0->unk15 & 2) << 7;
#else
        temp_v0_3 = arg0->unk15;
        background = &background_objects[1];
        background->x_pos.i.hi = temp_v0_3 << 9;
#endif
        background->unk4C = 1;
    }
}
#endif

void (*final_weapon_bg_cycle_state_funcs[])(struct LayerObj*) = {
    final_weapon_bg_cycle_init,
    final_weapon_bg_cycle_main,
};
