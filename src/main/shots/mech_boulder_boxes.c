#include "common.h"

struct Shot2Hitbox {
    s8 x;
    s8 y;
    u8 width;
    u8 height;
};

struct Shot2Hitbox mech_boulder_shockwave_boxes[1] = {
    { -7, -9, 0x0F, 0x10 },
};

struct Shot2Hitbox mech_boulder_shockwave_boxes_tail[6] = {
    { -29, -16, 0x15, 0x0C },
    { -81, -29, 0x2D, 0x16 },
    { -62, -22, 0x22, 0x0F },
    { -33, -12, 0x19, 0x07 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
};
