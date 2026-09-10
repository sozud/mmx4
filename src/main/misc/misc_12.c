// MiscObj, misc_object_update_funcs[12]
// 800CA228..800CA52C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA228);

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA3C0);

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA40C);

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA46C);

void func_800CA4B4(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    if (engine_obj.unk3 == arg0->unk2) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800CA4F0(struct MiscObj* arg0)
{
    D_8010E5F8[arg0->state](arg0);
}
