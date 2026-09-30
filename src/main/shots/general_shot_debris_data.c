#include "common.h"

u8 general_shot_prop_debris[6] = { 40, 41, 42, 43, 44, 45 };

s8 general_shot_attack_boxes[][4] = {
    { -19, -3, 36, 4 },
#ifndef MMX4_WIN32
    { -10, -9, 18, 16 },
    { -99, 53, -60, 38 },
#endif
};
