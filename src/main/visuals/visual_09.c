// VisualObj, visual_object_update_funcs[9]
// 800B1354..800B14E8
#include "common.h"

void func_800B1354(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800B1394(arg0);
    } else {
        func_800B1450(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_09", func_800B1394);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_09", func_800B1450);
