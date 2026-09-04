// VisualObj, visual_object_update_funcs[8]
// 800B0890..800B1354
#include "common.h"

void func_800B0890(struct VisualObj* arg0)
{
    D_8010A430[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_08", func_800B08CC);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_08", func_800B0B48);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_08", func_800B0C78);

void func_800B0C98(struct VisualObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_08", func_800B0CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_08", func_800B10E4);

void (*D_8010A430[])(struct VisualObj*) = {
    func_800B08CC,
    func_800B0B48,
    func_800B0C78,
    func_800B0C98,
};
