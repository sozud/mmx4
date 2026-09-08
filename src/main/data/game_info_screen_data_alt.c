#include "common.h"

#ifdef VERSION_JP
#define GAME_INFO_ALT_X 0x50
#define GAME_INFO_ALT_Y 0x30
#else
#define GAME_INFO_ALT_X 0x40
#define GAME_INFO_ALT_Y 0x2E
#endif

u8 D_800F2328[16] = {
    GAME_INFO_ALT_X,
    GAME_INFO_ALT_Y,
    0x40,
    0x31,
    0x60,
    0x2A,
    0x80,
    0x2C,
    0xB0,
    0x2F,
    0x10,
    0x72,
    0xD0,
    0xFF,
    0x03,
    0x00,
};
