// VisualObj, visual_object_update_funcs[1]
// 800AED18..800AEED8
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_01", func_800AED18);

void func_800AEE5C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->base.unk15 = arg1->base.unk15;
    if (arg0->base.unk15 == 0) {
        arg0->base.x_pos.i.hi = arg1->base.x_pos.i.hi + D_8010A1B4[arg1->base.unk2].x;
    } else {
        arg0->base.x_pos.i.hi = arg1->base.x_pos.i.hi - D_8010A1B4[arg1->base.unk2].x;
    }
    arg0->base.y_pos.i.hi = arg1->base.y_pos.i.hi + D_8010A1B4[arg1->base.unk2].y;
}
