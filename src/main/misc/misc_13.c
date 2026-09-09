// MiscObj, misc_object_update_funcs[13]
// 800CA52C..800CA754
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_13", func_800CA52C);

INCLUDE_ASM("main/nonmatchings/misc/misc_13", func_800CA60C);

void func_800CA6F8(struct MiscObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800CA718(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    D_8010E640[arg0->state](arg0);
}
