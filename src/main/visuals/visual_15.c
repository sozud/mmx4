// VisualObj, visual_object_update_funcs[15]
// 800B1D6C..800B1EA4
#include "common.h"

void func_800B1D6C(struct VisualObj* arg0)
{
    D_8010A538[arg0->base.state](arg0);
}

void func_800B1DA8(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    arg0->unk54 = 3;
    arg0->base.unk16 = 2;
    func_80015D60(arg0, 0x19);
}

void func_800B1DE4(struct VisualObj* arg0)
{
    struct BaseObj* temp_s1 = arg0->unk50;

    arg0->base.x_pos.i.hi = temp_s1->x_pos.i.hi;
    arg0->base.y_pos.i.hi = temp_s1->y_pos.i.hi;
    if (arg0->unk46 < 0) {
        arg0->unk54--;
    }
    func_80015DC8(arg0);
    if (temp_s1->state == 2) {
        arg0->base.state = 2;
    } else {
        if (arg0->unk54 == 0) {
            arg0->base.state = 2;
        }
        func_8002B318(arg0, 0x10, 0x10);
    }
}

void func_800B1E84(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A538[])(struct VisualObj*) = {
    func_800B1DA8,
    func_800B1DE4,
    func_800B1E84,
};
