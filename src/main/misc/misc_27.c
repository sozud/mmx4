// MiscObj, misc_object_update_funcs[27]
// 800CC908..800CCA34
#include "common.h"

void func_800CC908(struct MiscObj* arg0)
{
    D_8010E960[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_27", func_800CC944);

void func_800CCA14(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010E960[])(struct MiscObj*) = {
    func_800CC944,
    func_800CCA14,
};
