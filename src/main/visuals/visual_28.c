// VisualObj, visual_object_update_funcs[28]
// 800B3E7C..800B41CC
#include "common.h"

void func_800B3E7C(struct VisualObj* arg0)
{
    D_8010A6A0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_28", func_800B3EB8);

INCLUDE_ASM("main/nonmatchings/visuals/visual_28", func_800B3FD4);

void func_800B41AC(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010A6A0[])(struct VisualObj*) = {
    func_800B3EB8,
    func_800B3FD4,
    func_800B41AC,
};
