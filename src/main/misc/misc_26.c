// MiscObj, misc_object_update_funcs[26]
// 800CC7BC..800CC908
#include "common.h"

void func_800CC7BC(struct MiscObj* arg0)
{
    D_8010E958[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_26", func_800CC7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_26", func_800CC8E8);

void (*D_8010E958[])(struct MiscObj*) = {
    func_800CC7F8,
    func_800CC8E8,
};
