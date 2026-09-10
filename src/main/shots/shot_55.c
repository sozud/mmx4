// ShotObj, shot_object_update_funcs[55]
// 800AC8C4..800ADF30
#include "common.h"

s8 D_80109E04[3][4] = {
    { 0, -2, 32, 16 },
    { 15, -13, 32, 24 },
    { -36, -16, 43, 33 },
};

u8 D_80109E10[8] = { 40, 41, 42, 43, 44, 45, 0, 0 };

s8 D_80109E18[3][4] = {
    { -19, -3, 36, 4 },
    { -10, -9, 18, 16 },
    { -99, 53, -60, 38 },
};

s16 D_80109E24[4] = { 0x208, 0x238, 0x268, 0x290 };

u8 D_80109E2C[4] = { 2, 3, 0, 1 };

void (*D_80109E30[])(struct ShotObj*) = {
    func_800ACD84,
    func_800ACDE4,
    func_800ACE90,
    func_800ACF60,
    func_800AD00C,
    func_800AD080,
    func_800AD12C,
    func_800AD1B0,
    func_800AD224,
    func_800AD338,
    func_800AD404,
};

void (*D_80109E5C[])(struct ShotObj*) = {
    func_800AD47C,
    func_800AD4DC,
    func_800AD538,
    func_800ACF60,
    func_800AD00C,
    func_800AD080,
    func_800AD12C,
    func_800AD1B0,
    func_800AD224,
};

void (*D_80109E80[])(struct ShotObj*) = {
    func_800AD338,
    func_800AD404,
    func_800AD630,
    func_800AD440,
};

s8 D_80109E90[4] = { -63, -40, 13, -40 };

void (*D_80109E94[])(struct ShotObj*) = {
    func_800AD6DC,
    func_800AD820,
};

void (*D_80109E9C[])(struct ShotObj*) = {
    func_800AD8C0,
    func_800AD92C,
    func_800AD9C4,
};

void (*D_80109EA8[])(struct ShotObj*) = {
    func_800ADBE0,
    func_800ADCE8,
    func_800ADD40,
    func_800ADDB4,
};

void (*D_80109EB8[])(struct ShotObj*) = {
    func_800ACD04,
    func_800ACCAC,
    func_800AD66C,
    func_800AD66C,
    func_800AD868,
    func_800AD868,
    func_800ADA0C,
    func_800ADA0C,
    func_800ADA64,
    func_800ADAD8,
    func_800ADE04,
    func_800ADE04,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AC8C4);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACCAC);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACD04);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACD84);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACDE4);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACE90);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACF60);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD00C);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD080);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD12C);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD1B0);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD224);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD338);

void func_800AD404(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->timer = 0x80;
    }
}

void func_800AD440(struct ShotObj* arg0)
{
    D_80109E30[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD47C);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD4DC);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD538);

void func_800AD630(struct ShotObj* arg0)
{
    D_80109E5C[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD66C);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD6DC);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD820);

void func_800AD868(struct ShotObj* arg0)
{
    D_80109E94[arg0->unk5](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD8C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD92C);

void func_800AD9C4(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state++;
    }
}

void func_800ADA0C(struct ShotObj* arg0)
{
    D_80109E9C[arg0->unk5](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ADA64);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ADAD8);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ADBE0);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ADCE8);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ADD40);

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ADDB4);

void func_800ADE04(struct ShotObj* arg0)
{
    D_80109EA8[arg0->unk5](arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ADE54);

void func_800ADED4(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800ADEF4(struct ShotObj* arg0)
{
    D_80109EE8[arg0->state](arg0);
}

void (*D_80109EE8[])(struct ShotObj*) = {
    func_800AC8C4,
    func_800ADE54,
    func_800ADED4,
};
