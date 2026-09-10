// MiscObj, misc_object_update_funcs[24]
// 800CBECC..800CC460
#include "common.h"

void func_800CBECC(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010E90C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_24", func_800CBF14);

void func_800CC040(struct MiscObj* arg0)
{
    D_8010E918[arg0->unk5](arg0);
    if (func_8002B160(arg0) == 0) {
        is_on_screen(arg0);
    } else {
        arg0->state = 2;
    }
}

void func_800CC0AC(struct MiscObj* arg0)
{
    D_8010E924[arg0->unk6](arg0);
}

void func_800CC0E8(struct MiscObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_24", func_800CC114);

void func_800CC1F8(struct MiscObj* arg0)
{
    D_8010E92C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_24", func_800CC234);

INCLUDE_ASM("main/nonmatchings/misc/misc_24", func_800CC304);

void func_800CC350(struct MiscObj* arg0)
{
    D_8010E934[arg0->unk6](arg0);
}

void func_800CC38C(struct MiscObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 3);
    arg0->ext.misc_24.child_active = 0;
    arg0->ext.misc_24.child->ext.misc_11.active = 1;
}

void func_800CC3D4(struct MiscObj* arg0)
{
    func_80015DC8();
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800CC418(struct MiscObj* arg0)
{
    if (arg0->ext.misc_24.child_active != 0) {
        ZeroObjectState(OBJECT_HEADER(arg0->ext.misc_24.child));
    }
    func_8002B0C8(OBJECT_HEADER(arg0));
}

union AnimationStep D_8010E83C[16] = {
    { .packed = 0x00010002 },
    { .packed = 0x01010002 },
    { .packed = 0x02010002 },
    { .packed = 0x03010002 },
    { .packed = 0x04010001 },
    { .packed = 0x05010005 },
    { .packed = 0x04010001 },
    { .packed = 0x06010005 },
    { .packed = 0x04010001 },
    { .packed = 0x07010004 },
    { .packed = 0x04010001 },
    { .packed = 0x08010004 },
    { .packed = 0x09010006 },
    { .packed = 0x0A010004 },
    { .packed = 0x0B010004 },
    { .packed = 0x0C000003 },
};

union AnimationStep D_8010E87C[8] = {
    { .packed = 0x0D010003 },
    { .packed = 0x0E010003 },
    { .packed = 0x0F010003 },
    { .packed = 0x10010003 },
    { .packed = 0x11010003 },
    { .packed = 0x12010003 },
    { .packed = 0x13010003 },
    { .packed = 0x14F90003 },
};

union AnimationStep D_8010E89C[8] = {
    { .packed = 0x15010003 },
    { .packed = 0x16010003 },
    { .packed = 0x17010003 },
    { .packed = 0x18010003 },
    { .packed = 0x19010003 },
    { .packed = 0x1A010003 },
    { .packed = 0x1B010003 },
    { .packed = 0x1CF90003 },
};

union AnimationStep D_8010E8BC[16] = {
    { .packed = 0x0C010003 },
    { .packed = 0x0B010004 },
    { .packed = 0x0A010004 },
    { .packed = 0x09010006 },
    { .packed = 0x08010004 },
    { .packed = 0x04010001 },
    { .packed = 0x07010004 },
    { .packed = 0x04010001 },
    { .packed = 0x06010005 },
    { .packed = 0x04010001 },
    { .packed = 0x05010005 },
    { .packed = 0x04010001 },
    { .packed = 0x03010002 },
    { .packed = 0x02010002 },
    { .packed = 0x01010001 },
    { .packed = 0x00000001 },
};

union AnimationStep* D_8010E8FC[4] = {
    D_8010E83C,
    D_8010E87C,
    D_8010E89C,
    D_8010E8BC,
};

void (*D_8010E90C[])(struct MiscObj*) = {
    func_800CBF14,
    func_800CC040,
    func_800CC418,
};

void (*D_8010E918[])(struct MiscObj*) = {
    func_800CC0AC,
    func_800CC1F8,
    func_800CC350,
};

void (*D_8010E924[])(struct MiscObj*) = {
    func_800CC0E8,
    func_800CC114,
};

void (*D_8010E92C[])(struct MiscObj*) = {
    func_800CC234,
    func_800CC304,
};

void (*D_8010E934[])(struct MiscObj*) = {
    func_800CC38C,
    func_800CC3D4,
};
