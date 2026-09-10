#include "common.h"

#ifdef VERSION_JP
#define JP_VALUE(us, jp) jp
#else
#define JP_VALUE(us, jp) us
#endif

struct MovieHudQuad {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    s16 index;
};

struct MoviePlaybackData {
    u32 file_id;
    u16 arg2;
    u16 arg8;
    u16 arg9;
    u16 skip_button;
};

struct MovieHudQuad D_800F1C18[13] = {
    { 60, 27, 156, 27, 56, 32, 152, 32, 0 },
    { 188, 27, 284, 27, 184, 32, 280, 32, 1 },
    { 60, 51, 156, 51, 56, 56, 152, 56, 2 },
    { 188, 51, 284, 51, 184, 56, 280, 56, 3 },
    { 60, 75, 156, 75, 56, 80, 152, 80, 4 },
    { 188, 75, 284, 75, 184, 80, 280, 80, 5 },
    { 60, 99, 156, 99, 56, 104, 152, 104, 6 },
    { 188, 99, 284, 99, 184, 104, 280, 104, 7 },
    { 60, 123, 156, 123, 56, 128, 152, 128, 8 },
    { 188, 123, 284, 123, 184, 128, 280, 128, 9 },
    { 110, 196, 142, 196, 107, 200, 139, 200, 10 },
    { 157, 196, 190, 196, 155, 200, 187, 200, 11 },
    { 206, 196, 238, 196, 203, 200, 235, 200, 12 },
};

struct MoviePlaybackData D_800F1D04[11] = {
    { JP_VALUE(0x8A, 0x89), 0x0092, 0x001D, 1, 0x0800 },
    { JP_VALUE(0x8B, 0x8A), 0x0542, 0x0019, 1, 0x08F0 },
    { JP_VALUE(0x8C, 0x8B), 0x0412, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x8D, 0x8C), 0x04F3, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x8E, 0x8D), 0x0422, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x8F, 0x8E), 0x0536, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x90, 0x8F), 0x03B0, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x91, 0x90), 0x04C0, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x92, 0x91), 0x03E4, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x93, 0x92), 0x0C64, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
    { JP_VALUE(0x94, 0x93), 0x03CB, 0x0019, 1, JP_VALUE(0x0840, 0x0820) },
};

u32 D_800F1D88 = 1;
u32 D_800F1D8C = 0x80;
