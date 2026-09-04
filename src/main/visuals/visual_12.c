// VisualObj, visual_object_update_funcs[12]
// 800B19BC..800B1AF8
#include "common.h"

void func_800B19BC(struct VisualObj* arg0)
{
    D_8010A4EC[arg0->base.state](arg0);
}

void func_800B19F8(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    arg0->base.unk16 = D_8010A504[arg0->base.unk2];
    func_80015D60(arg0, D_8010A4F8[arg0->base.unk2]);
}

void func_800B1A48(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0 = arg0->unk50;
    if (temp_a0->base.state != 2) {
        if (arg0->unk46 >= 0) {
            arg0->base.x_pos.i.hi = temp_a0->base.x_pos.i.hi;
            arg0->base.y_pos.i.hi = temp_a0->base.y_pos.i.hi;
            func_80015DC8(arg0);
        } else {
            arg0->base.state = 2;
        }
        func_8002B318(arg0, 0x10, 0x10);
    } else {
        arg0->base.state = 2;
    }
}

void func_800B1AD8(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A4EC[])(struct VisualObj*) = {
    func_800B19F8,
    func_800B1A48,
    func_800B1AD8,
};

u8 D_8010A4F8[12] = {
    0x13,
    0x12,
    0x11,
    0x14,
    0x13,
    0x16,
    0x17,
    0x14,
    0x15,
    0,
    0,
    0,
};
u8 D_8010A504[12] = { 0, 0, 0, 0, 0, 4, 4, 4, 2, 0, 0, 0 };
u8 D_8010A510[16] = {
    0x15,
    0x16,
    0x17,
    0x18,
    0x15,
    0x15,
    0x15,
    0x16,
    0x16,
    0x16,
    0x17,
    0x17,
    0x17,
    0,
    0,
    0,
};
