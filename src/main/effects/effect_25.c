// EffectObj, effect_object_update_funcs[25]
// 800BAF60..800BB1F0
#include "common.h"

void func_800BAF60(struct EffectObj* arg0)
{
    D_8010BE90[arg0->state](arg0);
}

void func_800BAF9C(struct EffectObj* arg0)
{
    arg0->unk5 = 2;
    arg0->ext.effect_25.unk14 = 3;
    arg0->state++;
    func_800BAFD4(arg0);
}

void func_800BAFD4(struct EffectObj* arg0)
{
    arg0->ext.effect_25.unk15 = arg0->ext.effect_25.unk14;
    func_800BB180(arg0);
    D_8010BE98[arg0->unk5](arg0);
}

void func_800BB028(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BB068(arg0);
    } else {
        func_800BB088(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_25", func_800BB068);

INCLUDE_ASM("main/nonmatchings/effects/effect_25", func_800BB088);

void func_800BB098(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BB0D8(arg0);
    } else {
        func_800BB0F8(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_25", func_800BB0D8);

INCLUDE_ASM("main/nonmatchings/effects/effect_25", func_800BB0F8);

void func_800BB108(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BB148(arg0);
    } else {
        func_800BB168(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_25", func_800BB148);

INCLUDE_ASM("main/nonmatchings/effects/effect_25", func_800BB168);

void func_800BB178(struct EffectObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/effects/effect_25", func_800BB180);

void (*D_8010BE90[])(struct EffectObj*) = {
    func_800BAF9C,
    func_800BAFD4,
};

void (*D_8010BE98[])(struct EffectObj*) = {
    func_800BB028,
    func_800BB098,
    func_800BB108,
    func_800BB178,
};
