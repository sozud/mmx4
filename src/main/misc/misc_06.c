// MiscObj, misc_object_update_funcs[6]
// 800C91B0..800C938C
#include "common.h"

void func_800C91B0(struct MiscObj* arg0)
{
    D_8010DC60[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_06", func_800C91EC);

INCLUDE_ASM("main/nonmatchings/misc/misc_06", func_800C92B8);

INCLUDE_ASM("main/nonmatchings/misc/misc_06", func_800C92E0);

void func_800C9368(struct MiscObj* arg0)
{
    arg0->ext.misc_6.saved_position.packed = 0;
    arg0->ext.misc_6.timer = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}
