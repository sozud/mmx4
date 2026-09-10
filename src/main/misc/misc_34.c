// MiscObj, misc_object_update_funcs[34]
// 800CE894..800CF144
#include "common.h"

void func_800CE894(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010EED8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CE8DC);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEA40);

void func_800CEAC8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEAE8);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEB44);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEBC0);

void func_800CEE30(struct PlayerObj* arg0)
{
    D_8010EEF4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEE6C);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEEC4);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEF34);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEFC0);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CF0B0);

#define STEP(value)       \
    {                     \
        .packed = (value) \
    }

union AnimationStep D_8010EDF8[6] = {
    STEP(0x1B010006),
    STEP(0x1C010006),
    STEP(0x1D010006),
    STEP(0x00010006),
    STEP(0x01010006),
    STEP(0x02000006),
};

union AnimationStep D_8010EE10[24] = {
    STEP(0x03010006),
    STEP(0x04010006),
    STEP(0x05010006),
    STEP(0x06010003),
    STEP(0x07010003),
    STEP(0x08010003),
    STEP(0x09010003),
    STEP(0x0A010003),
    STEP(0x0B010003),
    STEP(0x0C010006),
    STEP(0x0D010006),
    STEP(0x0E010006),
    STEP(0x0F010006),
    STEP(0x10010006),
    STEP(0x11010006),
    STEP(0x18010006),
    STEP(0x19010006),
    STEP(0x1A010006),
    STEP(0x12010003),
    STEP(0x13010003),
    STEP(0x14010003),
    STEP(0x15010003),
    STEP(0x16010003),
    STEP(0x17E90003),
};

union AnimationStep D_8010EE70[6] = {
    STEP(0x1E010003),
    STEP(0x1F010003),
    STEP(0x20010003),
    STEP(0x21010003),
    STEP(0x22010003),
    STEP(0x23FB0003),
};

union AnimationStep D_8010EE88[6] = {
    STEP(0x24010003),
    STEP(0x25010003),
    STEP(0x26010003),
    STEP(0x27010003),
    STEP(0x28010003),
    STEP(0x29FB0003),
};

union AnimationStep D_8010EEA0[6] = {
    STEP(0x02010006),
    STEP(0x01010006),
    STEP(0x00010006),
    STEP(0x1D010006),
    STEP(0x1C010006),
    STEP(0x1B000006),
};

union AnimationStep* D_8010EEB8[5] = {
    D_8010EDF8,
    D_8010EE10,
    D_8010EE70,
    D_8010EE88,
    D_8010EEA0,
};

#undef STEP

u8 D_8010EECC[12] = {
    0x0F,
    0x0F,
    0,
    0,
    0x12,
    0x11,
    0,
    0,
    0x23,
    0x2C,
    0,
    0,
};

void (*D_8010EED8[3])(struct MiscObj*) = {
    func_800CE8DC,
    func_800CEA40,
    func_800CEAC8,
};

void (*D_8010EEE4[4])(struct MiscObj*) = {
    func_800CEAE8,
    func_800CEB44,
    func_800CEBC0,
    func_800CEE30,
};

void (*D_8010EEF4[3])(struct PlayerObj*) = {
    func_800CEE6C,
    func_800CEEC4,
    func_800CEF34,
};
