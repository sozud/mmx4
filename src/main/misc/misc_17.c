// MiscObj, misc_object_update_funcs[17]
// 800CADF8..800CB00C
#include "common.h"

void func_800CADF8(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800CAE38(arg0);
    } else {
        func_800CAF90(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_17", func_800CAE38);

INCLUDE_ASM("main/nonmatchings/misc/misc_17", func_800CAF90);

s8 D_8010E68C[4] = { 1, 3, 2, 3 };
