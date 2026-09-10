// MiscObj, misc_object_update_funcs[51]
// 800D1DC4..800D2190
#include "common.h"

void func_800D1DC4(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010F4BC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D1E0C);

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D1E9C);

void func_800D1F04(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D1F24);

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D1F74);

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D1FB8);

void func_800D2010(struct MiscObj* arg0)
{
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D2030);

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D2094);

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D212C);

void (*D_8010F4BC[3])(struct MiscObj*) = {
    func_800D1E0C,
    func_800D1E9C,
    func_800D1F04,
};

void (*D_8010F4C8[4])(struct MiscObj*) = {
    func_800D1F24,
    func_800D2030,
    func_800D2094,
    func_800D212C,
};

void (*D_8010F4D8[3])(struct MiscObj*) = {
    func_800D1F74,
    func_800D1FB8,
    func_800D2010,
};
