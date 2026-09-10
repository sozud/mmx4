// EffectObj, effect_object_update_funcs[44]
// 800BE83C..800BE9A0
#include "common.h"

void func_800BE83C(struct EffectObj* arg0)
{
    D_8010C13C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_44", func_800BE878);

INCLUDE_ASM("main/nonmatchings/effects/effect_44", func_800BE8E4);

void func_800BE960(struct EffectObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_80036B18();
        func_8002B108(arg0);
    }
}

void (*D_8010C13C[])(struct EffectObj*) = {
    func_800BE878,
    func_800BE8E4,
    func_800BE960,
};
