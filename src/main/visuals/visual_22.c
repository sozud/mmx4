// VisualObj, visual_object_update_funcs[22]
// 800B3074..800B322C
#include "common.h"

void func_800B3074(struct VisualObj* arg0)
{
    D_8010A5D4[arg0->state](arg0);
}

void func_800B30B0(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    if (arg0->unk2 != 0x10) {
        arg0->unk15 = 0;
        func_800B3100(arg0);
    } else {
        arg0->unk16 = 2;
        func_80015D60(arg0, 0x25);
    }
}

void func_800B3100(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0;

    if (arg0->unk2 != 0x10) {
        if (arg0->unk2 < 7) {
            if (arg0->unk2 == 0) {
                func_80015D60(arg0, 0x21);
            } else {
                func_80015D60(arg0, ((arg0->unk2 - 1) >> 1) + 0x21);
            }
            arg0->unk2++;
            is_on_screen(arg0);
        } else {
            arg0->on_screen = 0;
            arg0->state = 2;
        }
    } else {
        temp_a0 = arg0->unk50;
        if (((u8)temp_a0->unk94[0] == 2) && (temp_a0->active != 0) && (temp_a0->unk97 & 0x40)) {
            arg0->unk15 = temp_a0->unk15;
            arg0->x_pos.i.hi = temp_a0->x_pos.i.hi;
            arg0->y_pos.i.hi = temp_a0->y_pos.i.hi;
            func_80015DC8(arg0);
            is_on_screen(arg0);
            return;
        }
        arg0->on_screen = 0;
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

u32 D_8010A5E0 = 0x33CD;
