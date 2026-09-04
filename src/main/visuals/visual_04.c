// VisualObj, visual_object_update_funcs[4]
// 800AFB50..800AFC9C
#include "common.h"

void func_800AFB50(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800AFB90(arg0);
    } else {
        func_800AFC4C(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_04", func_800AFB90);

void func_800AFC4C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 < 0) {
        ZeroObjectState(arg0);
    } else {
        is_on_screen(arg0);
    }
}
