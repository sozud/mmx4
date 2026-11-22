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
#ifdef VERSION_DEMO
    { -31, 15, 0x16, 0x11 },
    { -78, 5, 0x38, 0x1B },
    { -92, 5, 0x38, 0x1C },
    { -111, 10, 0x37, 0x1C },
    { -116, 16, 0x18, 0x19 },
    { -122, 32, 0x09, 0x09 },
#else
    { -29, -16, 0x15, 0x0C },
    { -81, -29, 0x2D, 0x16 },
    { -62, -22, 0x22, 0x0F },
    { -33, -12, 0x19, 0x07 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
#endif
};
