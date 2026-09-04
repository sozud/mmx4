// VisualObj, visual_object_update_funcs[17]
// 800B2090..800B2544
#include "common.h"

void func_800B2090(struct VisualObj* arg0)
{
    D_8010A570[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_17", func_800B20CC);

void func_800B2200(struct VisualObj* arg0)
{
    struct PlayerObj* temp_s0;

    if (arg0->base.unk2 == 0) {
        temp_s0 = arg0->unk50;
        arg0->base.x_pos.val = temp_s0->base.x_pos.val;
        arg0->base.y_pos.val = temp_s0->base.y_pos.val;
        func_80015DC8();
        if (temp_s0->unk8A == 0) {
            ZeroObjectState(arg0);
        } else {
            func_8002B318(arg0, 0x10, 0x10);
        }
    } else {
        D_8010A57C[arg0->base.unk5](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_17", func_800B22B4);

void func_800B23DC(struct VisualObj* arg0)
{
    if (arg0->unk50->base.state >= 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        arg0->base.unk6 = 0;
    } else {
        func_80015DC8(arg0);
    }
    func_8002B318(arg0, 0x10, 0x10);
}

void func_800B2444(struct VisualObj* arg0)
{
    switch (arg0->base.unk5) {
    case 0:
        arg0->unk24 = -0x8000;
        arg0->unk54 = 0x78;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->base.unk5 = 1;
        func_80015DC8(arg0);
        func_8002B318(arg0, 0x10, 0x10);
        break;
    case 1:
        if (--arg0->unk54 == 0) {
            arg0->base.unk5 = 2;
        }
        if (!(arg0->unk54 & 7)) {
            func_800AF878(arg0, 0, 0xF, 0xF);
        }
        func_8002B694(arg0);
        func_80015DC8(arg0);
        func_8002B318(arg0, 0x10, 0x10);
        break;
    case 2:
        ZeroObjectState(arg0);
        break;
    }
}

void (*D_8010A570[])(struct VisualObj*) = {
    func_800B20CC,
    func_800B2200,
    func_800B2444,
};

void (*D_8010A57C[])(struct VisualObj*) = {
    func_800B22B4,
    func_800B23DC,
};
