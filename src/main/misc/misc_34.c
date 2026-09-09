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
