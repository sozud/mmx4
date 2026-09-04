// VisualObj, visual_object_update_funcs[16]
// 800B1EA4..800B2090
#include "common.h"

void func_800B1EA4(struct VisualObj* arg0)
{
    D_8010A544[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_16", func_800B1EE0);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_16", func_800B1F78);

void func_800B2070(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A544[])(struct VisualObj*) = {
    func_800B1EE0,
    func_800B1F78,
    func_800B2070,
};
