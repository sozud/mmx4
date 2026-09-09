// MiscObj, misc_object_update_funcs[2]
// 800C7EDC..800C85D0
#include "common.h"

void func_800C7EDC(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800C7F1C();
    } else {
        func_800C80D8();
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C7F1C);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C80D8);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C813C);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C8214);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C833C);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C842C);
