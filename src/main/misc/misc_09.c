// MiscObj, misc_object_update_funcs[9]
// 800C9D64..800C9EAC
#include "common.h"

void func_800C9D64(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800C9DA4(arg0);
    } else {
        func_800C9E34(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_09", func_800C9DA4);

INCLUDE_ASM("main/nonmatchings/misc/misc_09", func_800C9E34);
