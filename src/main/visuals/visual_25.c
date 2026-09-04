// VisualObj, visual_object_update_funcs[25]
// 800B3D3C..800B3E7C
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_25", func_800B3D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_25", func_800B3DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_25", func_800B3E20);

void func_800B3E40(struct VisualObj* arg0)
{
    D_8010A694[arg0->base.state](arg0);
}

void (*D_8010A694[])(struct VisualObj*) = {
    func_800B3D3C,
    func_800B3DE8,
    func_800B3E20,
};
