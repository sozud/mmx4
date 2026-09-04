// VisualObj, visual_object_update_funcs[24]
// 800B35B8..800B3D3C
#include "common.h"

void func_800B35B8(struct VisualObj* arg0)
{
    D_8010A64C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B35F4);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B36F0);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B372C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3768);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B37F8);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3848);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3884);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B392C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B397C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B39B8);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3A60);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3B58);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3B94);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3C34);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3C90);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_24", func_800B3CCC);

void (*D_8010A64C[])(struct VisualObj*) = {
    func_800B35F4,
    func_800B36F0,
};
