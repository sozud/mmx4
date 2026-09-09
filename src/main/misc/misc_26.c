// MiscObj, misc_object_update_funcs[26]
// 800CC7BC..800CC908
#include "common.h"

void func_800CC7BC(struct MiscObj* arg0)
{
    D_8010E958[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_26", func_800CC7F8);

void func_800CC8E8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010E958[])(struct MiscObj*) = {
    func_800CC7F8,
    func_800CC8E8,
};
