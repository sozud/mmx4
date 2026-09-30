#include "common.h"

struct Item06AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

extern u8 gate_core_box_data[2][8];

u8* gate_core_terrain_boxes[2] = { gate_core_box_data[0], gate_core_box_data[1] };

u8* gate_core_hurt_boxes[2] = { &gate_core_box_data[0][4], &gate_core_box_data[1][4] };

struct Item06AnimationStep gate_core_anim_steps[6] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
};

struct Item06AnimationStep* gate_core_animations[5] = {
    &gate_core_anim_steps[1],
    &gate_core_anim_steps[2],
    &gate_core_anim_steps[3],
    &gate_core_anim_steps[4],
    &gate_core_anim_steps[5],
};

u8 gate_core_debris[3][4] = {
    { 0, 1, 4, 3 },
    { 4, 2, 3, 2 },
    { 2, 3, 4, 0 },
};

u8 gate_core_explosion_sounds[4][4] = { { 0 }, { 1 }, { 2 }, { 3 } };

s16 gate_core_exit_x[2] = { 0x18C0, 0x18E8 };
