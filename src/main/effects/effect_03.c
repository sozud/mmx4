// EffectObj, effect_object_update_funcs[3]
// 800B5CC4..800B5EB0
#include "common.h"

void func_800B5CC4(struct EffectObj* arg0)
{
    if (arg0->state == 0) {
        func_800B5D04(arg0);
        return;
    }
    func_800B5E2C(arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_03", func_800B5D04);

void func_800B5E2C(struct EffectObj* arg0)
{
    if (arg0->ext.palette_animation.timer-- == 0) {
        arg0->ext.palette_animation.cursor += 2;
        if (arg0->ext.palette_animation.cursor[1] < 0) {
            arg0->ext.palette_animation.cursor += arg0->ext.palette_animation.cursor[1] * 2;
        }
        arg0->ext.palette_animation.timer = arg0->ext.palette_animation.cursor[1];
        arg0->ext.palette_animation.source = SP_ARC_30 + ((u8)arg0->ext.palette_animation.cursor[0] << 3);
        func_800B5C60(arg0);
    }
}
