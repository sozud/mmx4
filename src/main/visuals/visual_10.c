// VisualObj, visual_object_update_funcs[10]
// 800B14E8..800B17CC
#include "common.h"

void func_800B14E8(struct VisualObj* arg0)
{
    D_8010A4CC[arg0->base.state](arg0);
}

void func_800B1524(struct VisualObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        arg0->base.unk15 = 0;
    } else {
        arg0->base.unk15 = 0x40;
    }
    func_80015D60(arg0, 5);
    arg0->base.state++;
    func_8002B318(arg0, 0xA0, 0xA0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_10", func_800B158C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_10", func_800B16B0);

void func_800B1758(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 < 0) {
        arg0->base.state++;
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800B17AC(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A4CC[])(struct VisualObj*) = {
    func_800B1524,
    func_800B158C,
    func_800B16B0,
    func_800B1758,
    func_800B17AC,
};
