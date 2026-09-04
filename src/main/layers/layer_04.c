// LayerObj, layer_object_update_funcs[4]
// 800DA05C..800DA298
#include "common.h"

void func_800DA05C(struct LayerObj* arg0)
{
    D_8010FF88[arg0->base.state](arg0);
}

void func_800DA098(struct LayerObj* arg0)
{
    arg0->base.unk5 = 1;
    arg0->base.bg_offset = 2;
    arg0->base.state++;
    background_objects[0].unk2E = 0xA0;
    background_objects[0].unk2C = 0x50;
    func_800DA0EC(arg0);
}

void func_800DA0EC(struct LayerObj* arg0)
{
    arg0->base.unk15 = arg0->base.bg_offset;
    func_800DA230(arg0);
    D_8010FF94[arg0->base.unk5](arg0);
}

void func_800DA140(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

void func_800DA160(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA1A0(arg0);
    } else {
        func_800DA1B4(arg0);
    }
}

void func_800DA1A0(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA1B4(struct LayerObj* arg0)
{
    arg0->base.unk5 = 2;
    arg0->base.unk6 = 0;
}

void func_800DA1C4(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA204(arg0);
    } else {
        func_800DA218(arg0);
    }
}

void func_800DA204(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA218(struct LayerObj* arg0)
{
    arg0->base.unk5 = 2;
    arg0->base.unk6 = 0;
}

void func_800DA228(struct LayerObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_04", func_800DA230);

void (*D_8010FF88[])(struct LayerObj*) = {
    func_800DA098,
    func_800DA0EC,
    func_800DA140,
};

void (*D_8010FF94[])(struct LayerObj*) = {
    func_800DA160,
    func_800DA1C4,
    func_800DA228,
};
