// VisualObj, visual_object_update_funcs[14]
// 800B1C5C..800B1D6C
#include "common.h"

void func_800B1C5C(struct VisualObj* arg0)
{
    D_8010A52C[arg0->base.state](arg0);
}

void func_800B1C98(struct VisualObj* arg0)
{
    arg0->base.unk15 = arg0->unk50->base.unk15;
    func_80015D60(arg0, arg0->base.unk2);
    arg0->base.on_screen = 1;
    arg0->base.state++;
    func_8002B318(arg0, 0x50, 0x50);
}

void func_800B1CF4(struct VisualObj* arg0)
{
    struct PlayerObj* temp_s1 = arg0->unk50;
    func_80015DC8(arg0);
    arg0->base.x_pos.i.hi = temp_s1->base.x_pos.i.hi;
    arg0->base.y_pos.i.hi = temp_s1->base.y_pos.i.hi;
    func_8002B318(arg0, 0x30, 0x30);
}

void func_800B1D4C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A52C[])(struct VisualObj*) = {
    func_800B1C98,
    func_800B1CF4,
    func_800B1D4C,
};
