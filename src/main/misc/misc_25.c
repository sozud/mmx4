// MiscObj, misc_object_update_funcs[25]
// 800CC460..800CC7BC
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_25", func_800CC460);

INCLUDE_ASM("main/nonmatchings/misc/misc_25", func_800CC4E0);

INCLUDE_ASM("main/nonmatchings/misc/misc_25", func_800CC738);

void func_800CC79C(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

struct Misc25Velocity {
    s8 x;
    s8 y;
};

struct Misc25Velocity D_8010E93C[8] = {
    { -13, 0 },
    { 13, 0 },
    { -10, -12 },
    { 10, -12 },
    { 0, -16 },
    { 0, 16 },
    { -10, 12 },
    { 10, 12 },
};

void (*D_8010E94C[3])(struct MiscObj*) = {
    func_800CC4E0,
    func_800CC738,
    func_800CC79C,
};
