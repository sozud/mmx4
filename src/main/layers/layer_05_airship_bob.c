// LayerObj, layer_object_update_funcs[5]
// 800DA298..800DA7C0
#include "common.h"

void airship_bob_section_0_done(struct LayerObj* arg0);
void airship_bob_section_0_wait(struct LayerObj* arg0);
void airship_bob_section_1_done(struct LayerObj* arg0);
void airship_bob_section_1_wait(struct LayerObj* arg0);
void airship_bob_section_2_done(struct LayerObj* arg0);
void airship_bob_section_2_wait(struct LayerObj* arg0);

void airship_bob_update(struct LayerObj* arg0)
{
    airship_bob_state_funcs[arg0->state](arg0);
}

// airship_bob_init
INCLUDE_ASM("main/nonmatchings/layers/layer_05_airship_bob", func_800DA2D4);

// airship_bob_main
INCLUDE_ASM("main/nonmatchings/layers/layer_05_airship_bob", func_800DA358);

void airship_bob_despawn(struct LayerObj* arg0)
{
    despawn_object_permanently(arg0);
}

void airship_bob_section_0(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        airship_bob_section_0_wait(arg0);
    } else {
        airship_bob_section_0_done(arg0);
    }
}

void airship_bob_section_0_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void airship_bob_section_0_done(struct LayerObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void airship_bob_section_1(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        airship_bob_section_1_wait(arg0);
    } else {
        airship_bob_section_1_done(arg0);
    }
}

void airship_bob_section_1_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void airship_bob_section_1_done(struct LayerObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void airship_bob_section_2(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
        airship_bob_section_2_wait(arg0);
    } else {
        airship_bob_section_2_done(arg0);
    }
}

void airship_bob_section_2_wait(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void airship_bob_section_2_done(struct LayerObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void airship_bob_sway(struct LayerObj* arg0)
{
    airship_bob_sway_funcs[arg0->unk7](arg0);
}

void airship_bob_sway_up(struct LayerObj* arg0)
{
    if (arg0->unk18.val <= 0x5800) {
        if (arg0->unk18.val > 0) {
            if (arg0->private_state.value.val != 0) {
                arg0->private_state.value.val--;
                return;
            }
        }
        arg0->unk18.val += 0x400;
        background_objects[1].y_pos.val -= arg0->unk18.val / 2;
        background_objects[2].y_pos.val -= arg0->unk18.val;
        return;
    }
    arg0->private_state.value.val = 0x1E;
    arg0->unk7++;
}

void airship_bob_sway_down(struct LayerObj* arg0)
{
    if (arg0->unk18.val >= -0x5800) {
        if (arg0->unk18.val < 0) {
            if (arg0->private_state.value.val != 0) {
                arg0->private_state.value.val--;
                return;
            }
        }
        arg0->unk18.val -= 0x400;
        background_objects[1].y_pos.val -= arg0->unk18.val / 2;
        background_objects[2].y_pos.val -= arg0->unk18.val;
        return;
    }
    arg0->private_state.value.val = 0x1E;
    arg0->unk7--;
}

void airship_bob_idle(struct LayerObj* arg0)
{
}

void airship_bob_update_section(struct LayerObj* arg0)
{
    s8 offset = 0;
    s16 player_x = g_Player.x_pos.i.hi;

    while (1) {
        if (player_x - airship_bob_section_positions[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 2) {
            break;
        }
    }
    arg0->unk24 = offset;
    if (offset != arg0->unk25) {
        arg0->unk5 = offset;
        arg0->unk6 = 0;
    }
}

void (*airship_bob_state_funcs[])(struct LayerObj*) = {
    func_800DA2D4,
    func_800DA358,
    airship_bob_despawn,
};

s16 airship_bob_section_positions[2] = { 0x6A0, 0x810 };

void (*airship_bob_section_funcs[])(struct LayerObj*) = {
    airship_bob_section_0,
    airship_bob_section_1,
    airship_bob_section_2,
    airship_bob_idle,
};

void (*airship_bob_sway_funcs[])(struct LayerObj*) = {
    airship_bob_sway_up,
    airship_bob_sway_down,
};
