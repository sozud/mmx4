// MiscObj, misc_object_update_funcs[1]
// 800C7BF4..800C7EDC
#include "common.h"

void func_800C7BF4(struct MiscObj* arg0)
{
    D_8010DABC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_01", func_800C7C30);

INCLUDE_ASM("main/nonmatchings/misc/misc_01", func_800C7D40);

void func_800C7D84(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_01", func_800C7DA4);

struct Misc01AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Misc01AnimationStep D_8010D9F8[3] = {
    { 4, 0, 1, 0 },
    { 4, 0, 1, 1 },
    { 4, 0, 254, 2 },
};

struct Misc01AnimationStep D_8010DA04[7] = {
    { 4, 0, 1, 3 },
    { 4, 0, 1, 4 },
    { 4, 0, 1, 5 },
    { 4, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 4, 1, 0, 9 },
};

struct Misc01AnimationStep D_8010DA20[4] = {
    { 8, 0, 1, 10 },
    { 8, 0, 1, 11 },
    { 8, 0, 1, 12 },
    { 8, 0, 253, 11 },
};

struct Misc01AnimationStep D_8010DA30[4] = {
    { 6, 0, 1, 13 },
    { 6, 0, 1, 14 },
    { 6, 0, 1, 15 },
    { 6, 0, 253, 16 },
};

struct Misc01AnimationStep D_8010DA40[8] = {
    { 3, 0, 1, 17 },
    { 3, 0, 1, 18 },
    { 3, 0, 1, 19 },
    { 3, 0, 1, 20 },
    { 3, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 0, 1, 23 },
    { 3, 1, 249, 24 },
};

struct Misc01AnimationStep D_8010DA60[9] = {
    { 3, 0, 1, 25 },
    { 3, 0, 1, 26 },
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, 1, 29 },
    { 3, 0, 1, 30 },
    { 3, 0, 1, 31 },
    { 3, 0, 1, 32 },
    { 3, 0, 248, 33 },
};

struct Misc01AnimationStep D_8010DA84[6] = {
    { 3, 0, 1, 34 },
    { 3, 0, 1, 35 },
    { 3, 0, 1, 36 },
    { 3, 0, 1, 37 },
    { 3, 0, 252, 38 },
    { 1, 0, 0, 40 },
};

struct Misc01AnimationStep* D_8010DA9C[8] = {
    D_8010D9F8,
    D_8010DA04,
    D_8010DA20,
    D_8010DA30,
    D_8010DA40,
    D_8010DA60,
    D_8010DA84,
    D_8010DA84,
};

void (*D_8010DABC[])(struct MiscObj*) = { func_800C7C30, func_800C7D40, func_800C7D84 };
