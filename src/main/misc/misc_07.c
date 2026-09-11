// MiscObj, misc_object_update_funcs[7]
// 800C938C..800C9510
#include "common.h"

void func_800C938C(struct MiscObj* arg0)
{
    D_8010DC70[arg0->state](arg0);
}

void func_800C93C8(struct MiscObj* arg0)
{
    s16 x;

    func_80015D60(arg0, 0xA);
    arg0->x_pos.val = arg0->ext.misc_7.position[0].val;
    arg0->y_pos.val = arg0->ext.misc_7.position[1].val;
    if (arg0->unk2 != 0) {
        if (arg0->unk15 != 0) {
            x = arg0->x_pos.u.hi + 3;
        } else {
            x = arg0->x_pos.u.hi - 3;
        }
        arg0->x_pos.i.hi = x;
    }
    arg0->state = 1;
}

INCLUDE_ASM("main/nonmatchings/misc/misc_07", func_800C9450);

void func_800C94F0(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
