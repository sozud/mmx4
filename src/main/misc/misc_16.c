// MiscObj, misc_object_update_funcs[16]
// 800CAC18..800CADF8
#include "common.h"

void func_800CAC18(struct MiscObj* arg0)
{
    D_8010E680[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_16", func_800CAC54);

INCLUDE_ASM("main/nonmatchings/misc/misc_16", func_800CACF0);

void func_800CADD8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
