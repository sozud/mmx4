// MiscObj, misc_object_update_funcs[20]
// 800CB8F8..800CBA80
#include "common.h"

void func_800CB8F8(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010E830[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_20", func_800CB940);

INCLUDE_ASM("main/nonmatchings/misc/misc_20", func_800CB9C4);

void func_800CBA5C(struct MiscObj* arg0)
{
    arg0->ext.misc_20.owner->private_state.misc_20_active = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010E830[])(struct MiscObj*) = {
    func_800CB940,
    func_800CB9C4,
    func_800CBA5C,
};
