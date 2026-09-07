// MiscObj, misc_object_update_funcs[3]
// 800C85D0..800C8774
#include "common.h"

void func_800C8610(struct MiscObj* arg0);
void func_800C8708(struct MiscObj* arg0);

void func_800C85D0(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800C8610(arg0);
    } else {
        func_800C8708(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_03", func_800C8610);

INCLUDE_ASM("main/nonmatchings/misc/misc_03", func_800C8708);
