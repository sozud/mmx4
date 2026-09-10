#include "common.h"

struct MenuRuntimeData {
    u8 byte_0;
    u8 byte_1;
    u16 halfword_2;
    u8 buffer[33];
    u8 padding[3];
    u8 button_lookup[24];
    u16 low_button_masks[8];
    u16 high_button_masks[3];
    u16 sign_bit_mask;
};

struct MenuRuntimeData D_800F1D94 = {
    0,
    0,
    0,
    { 0 },
    { 0 },
    {
        1,
        0,
        2,
        0x20,
        5,
        0,
        0x40,
        6,
        5,
        8,
        3,
        4,
        0x10,
        4,
        3,
        4,
        2,
        1,
        0x80,
        7,
        7,
        2,
        1,
        6,
    },
    {
        0x0001,
        0x0002,
        0x0004,
        0x0008,
        0x0010,
        0x0020,
        0x0040,
        0x0080,
    },
    { 0x1000, 0x2000, 0x4000 },
    0x8000,
};
