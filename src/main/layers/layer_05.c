// LayerObj, layer_object_update_funcs[5]
// 800DA298..800DA7C0
#include "common.h"

void func_800DA298(struct LayerObj* arg0)
{
    D_8010FFA0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_05", func_800DA2D4);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_05", func_800DA358);

void func_800DA478(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

void func_800DA498(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA4D8(arg0);
    } else {
        func_800DA4EC(arg0);
    }
}

void func_800DA4D8(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA4EC(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

void func_800DA4FC(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA53C(arg0);
    } else {
        func_800DA550(arg0);
    }
}

void func_800DA53C(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA550(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

void func_800DA560(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA5A0(arg0);
    } else {
        func_800DA5B4(arg0);
    }
}

void func_800DA5A0(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA5B4(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_05", func_800DA5C4);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_05", func_800DA600);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_05", func_800DA6A4);

void func_800DA748(struct LayerObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_05", func_800DA750);

void (*D_8010FFA0[])(struct LayerObj*) = {
    func_800DA2D4,
    func_800DA358,
    func_800DA478,
};
