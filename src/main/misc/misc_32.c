// MiscObj, misc_object_update_funcs[32]
// 800CE114..800CE340
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_32", func_800CE114);

INCLUDE_ASM("main/nonmatchings/misc/misc_32", func_800CE1D4);

void func_800CE304(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    D_8010ECD8[arg0->state](arg0);
}

void (*D_8010ECD8[2])(struct MiscObj*) = {
    func_800CE114,
    func_800CE1D4,
};
