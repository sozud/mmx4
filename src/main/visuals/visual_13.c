// VisualObj, visual_object_update_funcs[13]
// 800B1AF8..800B1C5C
#include "common.h"

void func_800B1AF8(struct VisualObj* arg0)
{
    D_8010A520[arg0->state](arg0);
}

void func_800B1B34(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk54 = 0xFF;
    arg0->unk56 = 0xFF;
    arg0->unk16 = 6;
    func_80015D60(arg0, 0x15);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_13", func_800B1B74);

void func_800B1C3C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A520[])(struct VisualObj*) = {
    func_800B1B34,
    func_800B1B74,
    func_800B1C3C,
};
