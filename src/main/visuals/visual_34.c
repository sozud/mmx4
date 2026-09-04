// VisualObj, visual_object_update_funcs[34]
// 800B5570..800B56F4
#include "common.h"

void func_800B5570(struct VisualObj* arg0)
{
    D_8010A790[arg0->base.state](arg0);
}

void func_800B55AC(struct VisualObj* arg0)
{
    if (arg0->unk50->base.state >= 2) {
        arg0->base.on_screen = 0;
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->base.unk2 == 0) {
        if (--arg0->unk5E == 0) {
            arg0->base.state = 1;
        } else {
            if (arg0->unk5C == 0) {
                arg0->base.x_pos.i.hi = arg0->base.x_pos.i.hi + 0x20;
            } else {
                arg0->base.x_pos.i.hi = arg0->base.x_pos.i.hi - 0x20;
            }
            arg0->base.y_pos.i.hi += 1;
            arg0->unk5C ^= 0x20;
            func_80015DC8(arg0);
        }
    } else {
        if (--arg0->unk5C == 0) {
            arg0->base.state = 1;
        }
        arg0->base.x_pos.val = arg0->unk50->base.x_pos.val;
        arg0->base.y_pos.val = arg0->unk50->base.y_pos.val;
        func_80015DC8(arg0);
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800B56D4(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A790[])(struct VisualObj*) = {
    func_800B55AC,
    func_800B56D4,
};
