// MiscObj, misc_object_update_funcs[11]
// 800CA0C8..800CA228
#include "common.h"

void func_800CA0C8(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010E580[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_11", func_800CA110);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_11", func_800CA188);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_11", func_800CA208);

void (*D_8010E580[])(struct MiscObj*) = {
    func_800CA110,
    func_800CA188,
    func_800CA208,
};
