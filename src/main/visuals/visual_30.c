// VisualObj, visual_object_update_funcs[30]
// 800B4610..800B4B64
#include "common.h"

void func_800B4610(struct VisualObj* arg0)
{
    D_8010A6C8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B464C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B46C8);

void func_800B46E8(struct VisualObj* arg0)
{
    D_8010A6D4[arg0->base.unk5](arg0);
    if (arg0->unk50->base.state == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        arg0->base.unk6 = 0;
    }
}

void func_800B4754(struct VisualObj* arg0)
{
    D_8010A6E4[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B4790);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B4808);

void func_800B4858(struct VisualObj* arg0)
{
    D_8010A6EC[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B4894);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B490C);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B4960);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_30", func_800B499C);

void func_800B4A18(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    is_on_screen(arg0);
    if (--arg0->unk54 == 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    }
}

void func_800B4A6C(struct VisualObj* arg0)
{
    D_8010A6FC[arg0->base.unk6](arg0);
}

void func_800B4AA8(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    arg0->base.unk16 = 4;
    arg0->base.x_pos.val = entity->base.x_pos.val;
    arg0->base.y_pos.val = entity->base.y_pos.val + FIXED(32);
    func_80015D60(arg0, 0x15);
    arg0->unk54 = 0x20;
    arg0->base.unk6++;
}

void func_800B4B0C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (--arg0->unk54 == 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    } else {
        is_on_screen(arg0);
    }
}

void (*D_8010A6C8[])(struct VisualObj*) = {
    func_800B464C,
    func_800B46E8,
    func_800B46C8,
};

void (*D_8010A6D4[])(struct VisualObj*) = {
    func_800B4754,
    func_800B4858,
    func_800B4960,
    func_800B4A6C,
};

void (*D_8010A6E4[])(struct VisualObj*) = {
    func_800B4790,
    func_800B4808,
};

void (*D_8010A6EC[])(struct VisualObj*) = {
    func_800B4894,
    func_800B490C,
};
