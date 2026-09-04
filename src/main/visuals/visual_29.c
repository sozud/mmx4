// VisualObj, visual_object_update_funcs[29]
// 800B41CC..800B4610
#include "common.h"

void func_800B41CC(struct VisualObj* arg0)
{
    D_8010A6AC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_29", func_800B4208);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_29", func_800B4274);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_29", func_800B4450);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_29", func_800B4480);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_29", func_800B4558);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_29", func_800B4578);

void func_800B4598(struct VisualObj* arg0)
{
    if (arg0->unk50->base.state != 1) {
        ZeroObjectState(arg0);
    } else {
        D_8010A6B8[arg0->base.unk5](arg0);
        is_on_screen(arg0);
    }
}

void (*D_8010A6AC[])(struct VisualObj*) = {
    func_800B4208,
    func_800B4598,
    func_800B4578,
};

void (*D_8010A6B8[])(struct VisualObj*) = {
    func_800B4274,
    func_800B4450,
    func_800B4480,
    func_800B4558,
};
