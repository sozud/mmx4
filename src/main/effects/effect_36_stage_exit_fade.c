// EffectObj, effect_object_update_funcs[36]
// 800BD1E4..800BD384
#include "common.h"

void stage_exit_fade_init(struct EffectObj* self)
{
    struct EffectObj* spawned;

    spawned = find_free_effect_obj();
    if (spawned != NULL) {
        spawned->active = 1;
        spawned->id = 2;
        spawned->unk2 = 0xC;
        self->ext.effect_36.spawned_effect = spawned;
        self->state = 1;
    }
    self->ext.effect_36.timer = 0x1E;
}

void stage_exit_fade_wait_filter(struct EffectObj* self)
{
    struct EffectObj* spawned = self->ext.effect_36.spawned_effect;
    if ((spawned->active == 0) || (spawned->id != 2)) {
        self->state = 2;
        g_Player.invincibility_timer = 0x78;
    }
}

void stage_exit_fade_whiteout(struct EffectObj* self)
{
    u32 i;

    g_Player.invincibility_timer = 0x78;
    if (--self->ext.effect_36.timer == 0) {
        self->state = 3;
        for (i = 0; i < 4; i++) {
            D_8013E188[i] = -1;
        }
        g_FilterModeR = 1;
        g_FilterModeG = 2;
        g_FilterModeB = 4;
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}

void stage_exit_fade_finish(struct EffectObj* self)
{
    engine_obj.unkF = 0x40;
    ZeroObjectState(OBJECT_HEADER(self));
}

void stage_exit_fade_update(struct EffectObj* self)
{
    stage_exit_fade_state_funcs[self->state](self);
}

u16 palette_pulse_palette[16] = {
    0,
    0xFFFF,
    0xAB3F,
    0x829F,
    0x81FF,
    0x815F,
    0x80DD,
    0x84D8,
    0x84B4,
    0x8470,
    0xAB3F,
    0x829F,
    0x81FF,
    0x815F,
    0x80DD,
    0x84D4,
};

void (*stage_exit_fade_state_funcs[])(struct EffectObj*) = {
    stage_exit_fade_init,
    stage_exit_fade_wait_filter,
    stage_exit_fade_whiteout,
    stage_exit_fade_finish,
};
