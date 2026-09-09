// VisualObj, visual_object_update_funcs[5]
// 800AFC9C..800AFF78
#include "common.h"

INCLUDE_ASM("main/nonmatchings/visuals/visual_05", func_800AFC9C);

INCLUDE_ASM("main/nonmatchings/visuals/visual_05", func_800AFD20);

void func_800AFD6C(struct BarObj* arg0)
{
    D_8010A2AC[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_05", func_800AFDA8);

INCLUDE_ASM("main/nonmatchings/visuals/visual_05", func_800AFE20);

INCLUDE_ASM("main/nonmatchings/visuals/visual_05", func_800AFEA4);

void func_800AFF08(struct VisualObj* arg0)
{
    struct PlayerObj* parent;

    parent = arg0->unk50;
    arg0->x_pos.val = parent->unk18;
    arg0->y_pos.val = parent->unk1C;
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_05", func_800AFF28);
