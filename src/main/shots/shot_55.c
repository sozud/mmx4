// ShotObj, shot_object_update_funcs[55]
// 800AC8C4..800ADF30
#include "common.h"

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
    func_80015DC8();
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
