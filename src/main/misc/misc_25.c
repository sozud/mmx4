// MiscObj, misc_object_update_funcs[25]
// 800CC460..800CC7BC
#include "common.h"

void func_800CC460(struct MiscObj* arg0)
{
    struct ObjectHeader* owner;

    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    owner = OBJECT_HEADER(arg0->ext.unk.unk50);
    if (owner->active != 0x41) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else if (owner->id != 0x30) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else {
        D_8010E94C[arg0->state](arg0);
    }
}

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
