// MiscObj, misc_object_update_funcs[7]
// 800C938C..800C9510
#include "common.h"

void func_800C938C(struct MiscObj* arg0)
{
    D_8010DC70[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_07", func_800C93C8);

INCLUDE_ASM("main/nonmatchings/misc/misc_07", func_800C9450);

void func_800C94F0(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
