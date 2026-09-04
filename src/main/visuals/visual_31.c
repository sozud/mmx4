// VisualObj, visual_object_update_funcs[31]
// 800B4B64..800B4E34
#include "common.h"

void func_800B4B64(struct VisualObj* arg0)
{
    D_8010A704[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_31", func_800B4BA0);

void func_800B4CC8(struct VisualObj* arg0)
{
    if (arg0->unk56 == 0) {
        arg0->base.state++;
    } else {
        arg0->unk56--;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_31", func_800B4D00);

void func_800B4E14(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A704[])(struct VisualObj*) = {
    func_800B4BA0,
    func_800B4CC8,
    func_800B4D00,
    func_800B4E14,
};
