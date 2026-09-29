// EffectObj, effect_object_update_funcs[37]
// 800BD384..800BD654
#include "common.h"

void alarm_flash_update(struct EffectObj* self)
{
    alarm_flash_state_funcs[self->state](self);
}

// alarm_flash_init
INCLUDE_ASM("main/nonmatchings/effects/effect_37_alarm_flash", func_800BD3C0);

void alarm_flash_main(struct EffectObj* self)
{
    if (self->ext.effect_37.finished != 0) {
        alarm_flash_funcs[self->ext.effect_37.action](self);
        return;
    }

    if (--self->ext.effect_37.timer == 0) {
        self->ext.effect_37.finished = 1;
    }
}

void alarm_flash_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void alarm_flash_red(struct EffectObj* self)
{
    if (--self->ext.effect_37.unk19 == 0) {
        need_palette_load |= 5;
        self->ext.effect_37.timer = self->ext.effect_37.unk1E;
        self->ext.effect_37.unk19 = self->ext.effect_37.unk1F;
        if (self->ext.effect_37.unk22 == 0) {
            self->ext.effect_37.action ^= 1;
        }
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        self->ext.effect_37.finished = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
    }
}

void alarm_flash_white(struct EffectObj* self)
{
    if (--self->ext.effect_37.unk19 == 0) {
        need_palette_load |= 5;
        self->ext.effect_37.timer = self->ext.effect_37.unk21;
        self->ext.effect_37.unk19 = self->ext.effect_37.unk1F;
        if (self->ext.effect_37.unk22 == 0) {
            self->ext.effect_37.action ^= 1;
        }
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        self->ext.effect_37.finished = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}

void (*alarm_flash_state_funcs[])(struct EffectObj*) = {
    func_800BD3C0,
    alarm_flash_main,
    alarm_flash_despawn,
};

void (*alarm_flash_funcs[2])(struct EffectObj*) = {
    alarm_flash_red,
    alarm_flash_white,
};
