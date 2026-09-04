// VisualObj, visual_object_update_funcs[23]
// 800B322C..800B35B8
#include "common.h"

void func_800B322C(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    switch (arg0->base.unk2) {
    case 0:
        arg0->unk5C = 0;
        arg0->base.x_pos.i.hi -= arg0->base.unk15 ? -0x33 : 0x33;
        arg0->base.y_pos.i.hi -= 4;
        func_80015D60(arg0, 0x13);
        break;
    case 1:
        func_80015D60(arg0, 0x1E);
        break;
    case 2:
        // see func_800AF28C & func_8003D4C8 for a similar pattern
        arg0->unk42 = (((func_8002938C(0x84) * 4 + 0x18) % 16) | ((((func_8002938C(0x84) + 6) / 4) + 0x1E0) << 6));
        func_80015D60(arg0, 0x2B);
        break;
    }
    arg0->unk42 &= ~0x8000;
}

void func_800B3358(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    switch (arg0->base.unk5) {
    case 0:
        if (arg0->unk46 == 0) {
            arg0->base.unk5++;
            func_80015D60(arg0, 0x14);
        }
        break;
    case 1:
        if ((u8)entity->unk88 != 0) {
            arg0->base.unk5++;
            func_80015D60(arg0, 0x15);
        }
        break;
    case 2:
        if (arg0->unk46 == 0) {
            arg0->base.state = 2;
        }
        break;
    }
    if (entity->base.state >= 2) {
        arg0->base.state = 2;
    }
}

void func_800B3444(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    switch (arg0->base.unk5) {
    case 0:
        if (arg0->unk46 == 0) {
            arg0->base.unk5++;
            func_80015D60(arg0, 0x20);
        }
        break;
    case 1:
        if (arg0->unk46 == 0) {
            arg0->base.state = 2;
        }
        break;
    }

    if (entity->base.state == 2) {
        arg0->base.state = 2;
    }
    func_8002B718(arg0);
}

void func_800B34EC(struct VisualObj* arg0)
{
    if (arg0->unk46 == 0) {
        arg0->base.state = 2;
    }
}

void func_800B3508(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    D_8010A5E4[arg0->base.unk2](arg0);
    is_on_screen(arg0);
}

void func_800B355C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B357C(struct VisualObj* arg0)
{
    D_8010A5F0[arg0->base.state](arg0);
}

void (*D_8010A5E4[])(struct VisualObj*) = {
    func_800B3358,
    func_800B3444,
    func_800B34EC,
};

void (*D_8010A5F0[])(struct VisualObj*) = {
    func_800B322C,
    func_800B3508,
    func_800B355C,
};
