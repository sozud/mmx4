// MiscObj, misc_object_update_funcs[49]
// 800D1990..800D1B44
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_49", func_800D1990);

INCLUDE_ASM("main/nonmatchings/misc/misc_49", func_800D1A48);

void func_800D1AE8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800D1B08(struct MiscObj* arg0)
{
    D_8010F1E0[arg0->state](arg0);
}
