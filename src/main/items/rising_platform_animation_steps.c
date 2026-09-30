#include "common.h"

struct Item06AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item06AnimationStep rising_platform_anim_steps[5] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
};
