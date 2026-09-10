// EffectObj, effect_object_update_funcs[32]
// 800BC518..800BC748
#include "common.h"

void func_800BC518(struct EffectObj* arg0)
{
    D_8010BF90[arg0->state](arg0);
}

void func_800BC554(struct EffectObj* arg0)
{
    arg0->ext.effect_32.unk15 = 0;
    arg0->state++;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_32", func_800BC568);

INCLUDE_ASM("main/nonmatchings/effects/effect_32", func_800BC5D4);

INCLUDE_ASM("main/nonmatchings/effects/effect_32", func_800BC63C);

void func_800BC6FC(struct EffectObj* arg0, s32 arg1)
{
    arg0->ext.effect_32.palette_source = D_8010BF88[arg1 & 0xFF];
    arg0->ext.effect_32.palette[0] = arg0->ext.effect_32.palette_source[0];
    arg0->ext.effect_32.palette[1] = arg0->ext.effect_32.palette_source[1];
    arg0->ext.effect_32.palette[2] = arg0->ext.effect_32.palette_source[2];
    arg0->ext.effect_32.palette[3] = arg0->ext.effect_32.palette_source[3];
}

void (*D_8010BF90[])(struct EffectObj*) = {
    func_800BC554,
    func_800BC568,
};
