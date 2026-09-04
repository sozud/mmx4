// LayerObj, layer_object_update_funcs[1]
// 800D8ED4..800D9218
#include "common.h"

void func_800D8ED4(struct LayerObj* arg0)
{
    D_8010FF40[arg0->base.state](arg0);
}

void func_800D8F10(struct LayerObj* arg0)
{
    arg0->base.unk5 = 2;
    arg0->base.bg_offset = 3;
    arg0->base.state++;
    func_800D8F48(arg0);
}

void func_800D8F48(struct LayerObj* arg0)
{
    arg0->base.unk15 = arg0->base.bg_offset;
    func_800D91A8(arg0);
    D_8010FF48[arg0->base.unk5](arg0);
}

void func_800D8F9C(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D8FDC(arg0);
    } else {
        func_800D9008(arg0);
    }
}

void func_800D8FDC(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 5;
    background_objects[1].unk40 = 0x28;
    arg0->base.unk6++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_01", func_800D9008);

void func_800D9050(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D9090(arg0);
    } else {
        func_800D90BC(arg0);
    }
}

void func_800D9090(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 2;
    background_objects[1].unk40 = 0x200;
    arg0->base.unk6++;
}

void func_800D90BC(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

void func_800D90CC(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D910C(arg0);
    } else {
        func_800D9138(arg0);
    }
}

void func_800D910C(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 5;
    background_objects[1].unk40 = 0xB60;
    arg0->base.unk6++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_01", func_800D9138);

void func_800D91A0(struct LayerObj* arg0)
{
}

void func_800D91A8(struct LayerObj* arg0)
{
    u32 var_v1;

    if (g_Player.base.y_pos.i.hi < 0x201) {
        var_v1 = (u32) ~(g_Player.base.x_pos.i.hi - 0x450) >> 0x1F;
    } else {
        var_v1 = 2;
        if (g_Player.base.x_pos.i.hi - 0xA00 < 0) {
            var_v1 = 1;
        }
    }
    arg0->base.bg_offset = var_v1;
    if (var_v1 != arg0->base.unk15) {
        arg0->base.unk5 = var_v1;
        arg0->base.unk6 = 0;
    }
}

void (*D_8010FF40[])(struct LayerObj*) = {
    func_800D8F10,
    func_800D8F48,
};

void (*D_8010FF48[])(struct LayerObj*) = {
    func_800D8F9C,
    func_800D9050,
    func_800D90CC,
};
