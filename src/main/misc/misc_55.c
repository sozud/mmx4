// MiscObj, misc_object_update_funcs[55]
// 800D3084..800D3388
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_55", func_800D3084);

INCLUDE_ASM("main/nonmatchings/misc/misc_55", func_800D31F8);

void func_800D323C(struct MiscObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
    func_80015DC8(arg0);
    is_on_screen(arg0);
    if (func_8002B160(arg0) != 0) {
        arg0->state = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_55", func_800D3288);

void func_800D330C(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800D332C(struct MiscObj* arg0)
{
    if (arg0->ext.misc_55.owner->unk94 != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
    D_8010F58C[arg0->state](arg0);
}
