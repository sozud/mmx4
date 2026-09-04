// VisualObj, visual_object_update_funcs[22]
// 800B3074..800B322C
#include "common.h"

void func_800B3074(struct VisualObj* arg0)
{
    D_8010A5D4[arg0->base.state](arg0);
}

void func_800B30B0(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    if (arg0->base.unk2 != 0x10) {
        arg0->base.unk15 = 0;
        func_800B3100(arg0);
    } else {
        arg0->base.unk16 = 2;
        func_80015D60(arg0, 0x25);
    }
}

void func_800B3100(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0;

    if (arg0->base.unk2 != 0x10) {
        if (arg0->base.unk2 < 7) {
            if (arg0->base.unk2 == 0) {
                func_80015D60(arg0, 0x21);
            } else {
                func_80015D60(arg0, ((arg0->base.unk2 - 1) >> 1) + 0x21);
            }
            arg0->base.unk2++;
            is_on_screen(arg0);
        } else {
            arg0->base.on_screen = 0;
            arg0->base.state = 2;
        }
    } else {
        temp_a0 = arg0->unk50;
        if (((u8)temp_a0->unk94[0] == 2) && (temp_a0->base.active != 0) && (temp_a0->unk97 & 0x40)) {
            arg0->base.unk15 = temp_a0->base.unk15;
            arg0->base.x_pos.i.hi = temp_a0->base.x_pos.i.hi;
            arg0->base.y_pos.i.hi = temp_a0->base.y_pos.i.hi;
            func_80015DC8(arg0);
            is_on_screen(arg0);
            return;
        }
        arg0->base.on_screen = 0;
        ZeroObjectState(arg0);
    }
}

void func_800B320C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A5D4[])(struct VisualObj*) = {
    func_800B30B0,
    func_800B3100,
    func_800B320C,
};
