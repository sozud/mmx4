// EffectObj, effect_object_update_funcs[1]
// 800B58A0..800B5960
#include "common.h"

void func_800B58A0(struct EffectObj* arg0)
{
    D_8010AFAC[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_01", func_800B58DC);

void func_800B58F4(struct EffectObj* arg0)
{
    if (++arg0->unk5 == 3) {
        arg0->unk5 = 0;
        if (++arg0->unk6 >= 5) {
            arg0->unk6 = 0;
        }
    }
    func_800DA984(arg0->unk6);
}

void (*D_8010AFAC[])(struct EffectObj*) = {
    func_800B58DC,
    func_800B58F4,
};
