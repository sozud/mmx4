// MiscObj, misc_object_update_funcs[50]
// 800D1B44..800D1DC4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_50", func_800D1B44);

INCLUDE_ASM("main/nonmatchings/misc/misc_50", func_800D1CF8);

void func_800D1D38(struct MiscObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_50", func_800D1D58);

void func_800D1D88(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    D_8010F4AC[arg0->state](arg0);
}
