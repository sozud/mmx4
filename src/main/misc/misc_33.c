// MiscObj, misc_object_update_funcs[33]
// 800CE340..800CE894
#include "common.h"

void func_800CE340(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010EDDC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE388);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE670);

void func_800CE6AC(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE6CC);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE754);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE7C8);

INCLUDE_ASM("main/nonmatchings/misc/misc_33", func_800CE81C);

#define STEP(value)       \
    {                     \
        .packed = (value) \
    }

union AnimationStep D_8010ECE0[24] = {
    STEP(0x00010003),
    STEP(0x01010003),
    STEP(0x03010003),
    STEP(0x05010003),
    STEP(0x07010003),
    STEP(0x09010003),
    STEP(0x0B010003),
    STEP(0x0D010003),
    STEP(0x0F010003),
    STEP(0x11010003),
    STEP(0x13010003),
    STEP(0x15010003),
    STEP(0x17010003),
    STEP(0x19010003),
    STEP(0x1B010003),
    STEP(0x1D010003),
    STEP(0x1F010003),
    STEP(0x21010003),
    STEP(0x23010003),
    STEP(0x25010003),
    STEP(0x27010003),
    STEP(0x29010003),
    STEP(0x2B010003),
    STEP(0x2D000003),
};

union AnimationStep D_8010ED40[24] = {
    STEP(0x00010003),
    STEP(0x02010003),
    STEP(0x04010003),
    STEP(0x06010003),
    STEP(0x08010003),
    STEP(0x0A010003),
    STEP(0x0C010003),
    STEP(0x0E010003),
    STEP(0x10010003),
    STEP(0x12010003),
    STEP(0x14010003),
    STEP(0x16010003),
    STEP(0x18010003),
    STEP(0x1A010003),
    STEP(0x1C010003),
    STEP(0x1E010003),
    STEP(0x20010003),
    STEP(0x22010003),
    STEP(0x24010003),
    STEP(0x26010003),
    STEP(0x28010003),
    STEP(0x2A010003),
    STEP(0x2C010003),
    STEP(0x2E000003),
};

union AnimationStep D_8010EDA0[1] = { STEP(0x2F000008) };
union AnimationStep D_8010EDA4[1] = { STEP(0x30000008) };
union AnimationStep D_8010EDA8[1] = { STEP(0x31000008) };

union AnimationStep* D_8010EDAC[5] = {
    D_8010ECE0,
    D_8010ED40,
    D_8010EDA0,
    D_8010EDA4,
    D_8010EDA8,
};

#undef STEP

struct Misc33Position {
    s16 x;
    s16 y;
};

struct Misc33Position D_8010EDC0[6] = {
    { 0x778, 0x60 },
    { 0x378, 0x360 },
    { 0x878, 0x260 },
    { 0x378, 0x360 },
    { 0xC78, 0x560 },
    { 0x378, 0x360 },
};

struct Misc33Position D_8010EDD8 = { 0xFF0, 0x290 };

void (*D_8010EDDC[3])(struct MiscObj*) = {
    func_800CE388,
    func_800CE670,
    func_800CE6AC,
};

void (*D_8010EDE8[2])(struct MiscObj*) = {
    func_800CE6CC,
    func_800CE754,
};

void (*D_8010EDF0[2])(struct MiscObj*) = {
    func_800CE7C8,
    func_800CE81C,
};
