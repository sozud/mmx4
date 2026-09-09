// MiscObj, misc_object_update_funcs[31]
// 800CDE44..800CE114
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_31", func_800CDE44);

INCLUDE_ASM("main/nonmatchings/misc/misc_31", func_800CDF4C);

INCLUDE_ASM("main/nonmatchings/misc/misc_31", func_800CE080);

void func_800CE0D8(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    D_8010EC38[arg0->state](arg0);
}
