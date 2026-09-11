// MiscObj, misc_object_update_funcs[17]
// 800CADF8..800CB00C
#include "common.h"

void func_800CADF8(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800CAE38(arg0);
    } else {
        func_800CAF90(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_17", func_800CAE38);

void func_800CAF90(struct MiscObj* arg0)
{
    if ((arg0->unk2 & 0x80) && (func_8002B1E8(BASE_OBJECT(arg0), 0x80000, 0x80000) == 1)) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x80000, 0x80000);
}

s8 D_8010E68C[4] = { 1, 3, 2, 3 };
