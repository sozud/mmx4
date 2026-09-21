// EffectObj, effect_object_update_funcs[43]
// 800BE57C..800BE83C
#include "common.h"

void func_800BE57C(struct EffectObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->state = 1;
    } else {
        arg0->state = 2;
    }
}

void func_800BE598(struct EffectObj* arg0)
{
    u32 direction;

    arg0->ext.effect_9.transition_timer = 1;
    direction = D_801406A8[func_8002938C(0xA4)] >> 7;
    arg0->unk5++;
    arg0->ext.effect_9.direction = direction;
}

void func_800BE5F4(struct EffectObj* self)
{
    struct MiscObj* misc;
    u16 timer;

    if (D_80171EA8 == 0) {
        timer = self->ext.effect_9.transition_timer - 1;
        self->ext.effect_9.transition_timer = timer;
        if (!(timer & 0xFFFF)) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 0x39;
                misc->unk2 = ((u32)get_random() & 0xFF) % 6;
                misc->unk40 = self->ext.effect_16.saved_background_2A;
            }
            func_8001540C(5, 0, NULL);
            func_80028BAC(5, 2, 1);
            self->ext.effect_9.transition_timer = 5;
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void func_800BE6D8(struct EffectObj* arg0)
{
    D_8010C120[arg0->unk5](arg0);
}

void func_800BE714(struct EffectObj* arg0)
{
    arg0->ext.effect_43.unk14 = 1;
    arg0->ext.effect_43.unk16 = 1;
    arg0->unk5++;
}

void func_800BE730(struct EffectObj* arg0)
{
    if (--arg0->ext.effect_43.unk14 == 0) {
        func_8001540C(5, 0, NULL);
        func_80028B68(0xA, 2, 1);
        arg0->ext.effect_43.unk14 = 0xA;
    }

    if (--arg0->ext.effect_43.unk16 == 0) {
        func_8001540C(0, 0x13, NULL);
        arg0->ext.effect_43.unk16 = 0x28;
    }
}

void func_800BE7C4(struct EffectObj* arg0)
{
    D_8010C128[arg0->unk5](arg0);
}

void func_800BE800(struct EffectObj* arg0)
{
    D_8010C130[arg0->state](arg0);
}

void (*D_8010C120[2])(struct EffectObj*) = {
    func_800BE598,
    func_800BE5F4,
};

void (*D_8010C128[2])(struct EffectObj*) = {
    func_800BE714,
    func_800BE730,
};

void (*D_8010C130[])(struct EffectObj*) = {
    func_800BE57C,
    func_800BE6D8,
    func_800BE7C4,
};
