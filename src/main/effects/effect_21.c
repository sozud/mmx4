// EffectObj, effect_object_update_funcs[21]
// 800B9EC0..800BA57C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_21", func_800B9EC0);

INCLUDE_ASM("main/nonmatchings/effects/effect_21", func_800B9F38);

INCLUDE_ASM("main/nonmatchings/effects/effect_21", func_800BA178);

INCLUDE_ASM("main/nonmatchings/effects/effect_21", func_800BA340);

void func_800BA4E4(struct EffectObj* arg0)
{
    D_8010BDF8[arg0->unk2](arg0);
}

void func_800BA520(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BA540(struct EffectObj* arg0)
{
    D_8010BE10[arg0->state](arg0);
}

void (*D_8010BDF8[])(struct EffectObj*) = {
    func_800B9F38,
    func_800BA178,
    func_800BA178,
    func_800BA340,
    func_800BA178,
    func_800BA178,
};

void (*D_8010BE10[])(struct EffectObj*) = {
    func_800B9EC0,
    func_800BA4E4,
    func_800BA520,
};
