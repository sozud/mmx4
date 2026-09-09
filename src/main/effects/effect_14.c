// EffectObj, effect_object_update_funcs[14]
// 800B89B4..800B8AF8
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_14", func_800B89B4);

INCLUDE_ASM("main/nonmatchings/effects/effect_14", func_800B89CC);

void func_800B8A9C(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B8ABC(struct EffectObj* arg0)
{
    D_8010B6B8[arg0->state](arg0);
}

void (*D_8010B6B8[])(struct EffectObj*) = {
    func_800B89B4,
    func_800B89CC,
    func_800B8A9C,
};
