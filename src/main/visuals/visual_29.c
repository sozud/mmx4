// VisualObj, visual_object_update_funcs[29]
// 800B41CC..800B4610
#include "common.h"

void func_800B41CC(struct VisualObj* arg0)
{
    D_8010A6AC[arg0->state](arg0);
}

void func_800B4208(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 2;
    arg0->unk54 = 0x3C;
    arg0->unk5 = 0;
    arg0->unk56 = 4;
    arg0->unk2C = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->x_vel.val = 0;
    func_80015D60(arg0, 0xA);
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_29", func_800B4274);

void func_800B4450(struct VisualObj* arg0)
{
    arg0->unk5++;
    arg0->unk50->input.buttons.held = 0;
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_29", func_800B4480);

void func_800B4558(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
}

void func_800B4578(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B4598(struct VisualObj* arg0)
{
    if (arg0->unk50->state != 1) {
        ZeroObjectState(arg0);
    } else {
        D_8010A6B8[arg0->unk5](arg0);
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
