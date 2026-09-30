#include "common.h"

struct Item06AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

extern struct Item06AnimationStep rising_platform_anim_steps[5];

struct Item06AnimationStep* rising_platform_animations[5] = {
    &rising_platform_anim_steps[0],
    &rising_platform_anim_steps[1],
    &rising_platform_anim_steps[2],
    &rising_platform_anim_steps[3],
    &rising_platform_anim_steps[4],
};

u8 rising_platform_debris[2][4] = {
    { 1, 4, 3, 2 },
    { 3, 1, 2, 4 },
};

void (*rising_platform_state_funcs[])(struct ItemObj*) = {
    func_800C16F0,
    rising_platform_rise,
    rising_platform_despawn,
};
