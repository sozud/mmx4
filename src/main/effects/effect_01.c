// EffectObj, effect_object_update_funcs[1]
// 800B58A0..800B5960
#include "common.h"

void func_800B58A0(struct EffectObj* arg0)
{
    D_8010AFAC[arg0->state](arg0);
}

void func_800B58DC(struct EffectObj* arg0)
{
    arg0->unk6 = 0;
    arg0->unk5 = 0;
    arg0->state++;
}

void func_800B58F4(struct EffectObj* arg0, s32 arg1, s32 arg2)
{
    if (++arg0->unk5 == 3) {
        arg0->unk5 = 0;
        if (++arg0->unk6 >= 5) {
            arg0->unk6 = 0;
        }
    }
    func_800DA984((u8)arg0->unk6, arg1, arg2);
}

void (*D_8010AFAC[])(struct EffectObj*) = {
    func_800B58DC,
    func_800B58F4,
};
