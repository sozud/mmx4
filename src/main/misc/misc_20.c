// MiscObj, misc_object_update_funcs[20]
// 800CB8F8..800CBA80
#include "common.h"

void func_800CB8F8(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010E830[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_20", func_800CB940);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_20", func_800CB9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_20", func_800CBA5C);

void (*D_8010E830[])(struct MiscObj*) = {
    func_800CB940,
    func_800CB9C4,
    func_800CBA5C,
};
