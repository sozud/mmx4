// VisualObj, visual_object_update_funcs[11]
// 800B17CC..800B19BC
#include "common.h"

void func_800B17CC(struct VisualObj* arg0)
{
    D_8010A4E0[arg0->base.state](arg0);
}

void func_800B1808(struct VisualObj* arg0)
{
    arg0->base.unk15 = arg0->unk50->base.unk15;
    func_80015D60(arg0, arg0->base.unk2);
    arg0->base.on_screen = 1;
    arg0->base.state++;
    func_8002B318(arg0, 0x50, 0x50);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_11", func_800B1864);

void func_800B199C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A4E0[])(struct VisualObj*) = {
    func_800B1808,
    func_800B1864,
    func_800B199C,
};
