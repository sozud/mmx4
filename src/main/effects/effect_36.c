// EffectObj, effect_object_update_funcs[36]
// 800BD1E4..800BD384
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_36", func_800BD1E4);

INCLUDE_ASM("main/nonmatchings/effects/effect_36", func_800BD23C);

INCLUDE_ASM("main/nonmatchings/effects/effect_36", func_800BD280);

void func_800BD31C(struct EffectObj* arg0)
{
    engine_obj.unkF = 0x40;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BD348(struct EffectObj* arg0)
{
    D_8010C008[arg0->state](arg0);
}

void (*D_8010C008[])(struct EffectObj*) = {
    func_800BD1E4,
    func_800BD23C,
    func_800BD280,
    func_800BD31C,
};
