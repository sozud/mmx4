// LayerObj, layer_object_update_funcs[7]
// 800DA878..800DAE8C
#include "common.h"

void func_800DA878(struct LayerObj* arg0)
{
    D_8010FFD0[arg0->base.state](arg0);
}

void func_800DA8B4(struct LayerObj* arg0)
{
    arg0->base.state++;
    background_objects[1].unk4D = 1;
    background_objects[1].unk4E = 6;
    *(s32*)&arg0->base.bg_offset = 0x8000;
    arg0->base.unk5 = 0;
    arg0->base.unk6 = 0;
    arg0->base.unk7 = 0;
    func_800DA90C(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_07", func_800DA90C);

void func_800DA964(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_07", func_800DA984);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_07", func_800DAB40);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_07", func_800DAB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_07", func_800DABE4);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_07", func_800DADA0);

void func_800DAE84(void)
{
}

void (*D_8010FFD0[])(struct LayerObj*) = {
    func_800DA8B4,
    func_800DA90C,
    func_800DA964,
};
