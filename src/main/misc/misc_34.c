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

void func_800CEA40(struct MiscObj* self)
{
    D_8010EEE4[self->unk5](self);
    func_800CEFC0(self);
    func_800CF0B0(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state++;
    }
}

void func_800CEAC8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEAE8);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEB44);

INCLUDE_ASM("main/nonmatchings/misc/misc_34", func_800CEBC0);

void func_800CEE30(struct MiscObj* arg0)
{
    D_8010EEF4[arg0->unk6](arg0);
}

void func_800CEE6C(struct MiscObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 4);
    self->y_vel.val = FIXED(1);
    self->ext.misc_34.enabled = 0;
    self->x_vel.val = 0;
    self->ext.misc_34.timer = 0x1E;
    self->unk6++;
}

void func_800CEEC4(struct MiscObj* self)
{
    u8 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    timer = self->ext.misc_34.timer - 1;
    self->ext.misc_34.timer = timer;
    if (timer == 0) {
        self->ext.misc_34.timer = 0x1E;
        self->x_vel.val = FIXED(3);
        self->y_vel.val = 0;
        self->unk28 = FIXED(-0.0625);
        self->unk6++;
    }
}

void func_800CEF34(struct MiscObj* self)
{
    u8 timer;
    struct Misc34Related* related;

    func_8002B694(ANIMATED_OBJECT(self));
    timer = self->ext.misc_34.timer - 1;
    self->ext.misc_34.timer = timer;
    if (timer == 0) {
        related = self->ext.misc_34.related;
        related->active = 1;
        if (!(ENGINE_CHECKPOINT & 1)) {
            related->variant = self->ext.misc_34.variant;
        } else {
            related->variant = 3;
        }
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
    }
}

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

void (*D_8010EEF4[3])(struct MiscObj*) = {
    func_800CEE6C,
    func_800CEEC4,
    func_800CEF34,
};
