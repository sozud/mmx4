// MiscObj, misc_object_update_funcs[40]
// 800CFB70..800CFE98
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFB70);

INCLUDE_ASM("main/nonmatchings/misc/misc_40", func_800CFC6C);

void func_800CFD38(struct MiscObj* self)
{
    s8 subtype;

    subtype = self->unk2;
    if (self->y_vel.val < D_8010EFA4[subtype]) {
        self->unk2C = -D_8010EF94[subtype];
        func_80015D60(self, 2);
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->unk5 = 0;
    self->ext.misc_24.timer = D_8010EFB4[self->unk2] + (get_random() & 0x3F);
}

void func_800CFE00(struct MiscObj* arg0)
{
    D_8010EFBC[arg0->unk5](arg0);
}

void func_800CFE3C(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800CFE5C(struct MiscObj* arg0)
{
    D_8010EFC4[arg0->state](arg0);
}

union AnimationStep D_8010EF40[4] = {
    { .packed = 0x0001000E },
    { .packed = 0x0101000E },
    { .packed = 0x0201000E },
    { .packed = 0x01FD000E },
};

union AnimationStep D_8010EF50[3] = {
    { .packed = 0x0001000E },
    { .packed = 0x0101000E },
    { .packed = 0x0200000E },
};

union AnimationStep D_8010EF5C[3] = {
    { .packed = 0x0201000E },
    { .packed = 0x0101000E },
    { .packed = 0x0000000E },
};

union AnimationStep* D_8010EF68[3] = {
    D_8010EF40,
    D_8010EF50,
    D_8010EF5C,
};

u16 D_8010EF74[8] = {
    0x90,
    0x70,
    0xB0,
    0xD0,
    0x80,
    0xA0,
    0xC0,
    0xE0,
};

s32 D_8010EF84[4] = {
    -0x18000,
    -0x28000,
    -0x38000,
    -0x48000,
};

s32 D_8010EF94[4] = {
    0x1000,
    0x1000,
    0x1000,
    0x1000,
};

s32 D_8010EFA4[4] = {
    -0x18000,
    -0x10000,
    -0x8000,
    -0x4000,
};

u16 D_8010EFB4[4] = { 0xB4, 0x12C, 0x168, 0 };

void (*D_8010EFBC[2])(struct MiscObj*) = {
    func_800CFC6C,
    func_800CFD38,
};

void (*D_8010EFC4[3])(struct MiscObj*) = {
    func_800CFB70,
    func_800CFE00,
    func_800CFE3C,
};
