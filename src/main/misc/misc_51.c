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
