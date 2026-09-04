// VisualObj, visual_object_update_funcs[28]
// 800B3E7C..800B41CC
#include "common.h"

void func_800B3E7C(struct VisualObj* arg0)
{
    D_8010A6A0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_28", func_800B3EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_28", func_800B3FD4);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_28", func_800B41AC);

void (*D_8010A6A0[])(struct VisualObj*) = {
    func_800B3EB8,
    func_800B3FD4,
    func_800B41AC,
};
