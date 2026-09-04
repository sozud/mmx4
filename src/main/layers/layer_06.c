// LayerObj, layer_object_update_funcs[6]
// 800DA7C0..800DA878
#include "common.h"

void func_800DA7C0(struct LayerObj* arg0)
{
    D_8010FFC8[arg0->base.state](arg0);
}

void func_800DA7FC(struct LayerObj* arg0)
{
    arg0->base.bg_offset = 0;
    arg0->base.unk15 = 0;
    arg0->base.unk16 = 0;
    arg0->base.state++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_06", func_800DA818);

void (*D_8010FFC8[])(struct LayerObj*) = {
    func_800DA7FC,
    func_800DA818,
};
