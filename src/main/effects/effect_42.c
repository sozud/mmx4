// EffectObj, effect_object_update_funcs[42]
// 800BE2C4..800BE57C
#include "common.h"

void sigma_sequencer_fx_init(struct EffectObj* self)
{
    self->ext.effect_42.owner.main->ext.main_73_parts.unk8E = 0;
    switch (self->ext.effect_42.owner.main->ext.main_73_parts.object_id) {
    case 0:
    case 1:
    case 2:
        self->state = 1;
        break;
    default:
        self->ext.effect_42.owner.main->ext.main_73_parts.effect_state = 1;
        self->state = 2;
        break;
    }
}

void sigma_sequencer_fx_start(struct EffectObj* self)
{
    self->ext.effect_42.owner.main->ext.main_73_parts.effect_state = 1;
    self->unk5++;
}

void sigma_sequencer_fx_wait_player(struct EffectObj* self)
{
    if (g_Player.update_delay == 0) {
        self->ext.effect_42.owner.main->ext.main_73_parts.effect_state = 0;
        self->unk5++;
    }
}

// sigma_sequencer_fx_summon
INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE364);

void sigma_sequencer_fx_wait_parts(struct EffectObj* self)
{
    s32 count;
    s32 match;
    u32 i;

    count = 0;
    i = 0;
    match = 3;
    do {
        if (self->ext.effect_42.owner.main->ext.main_73_parts.parts[i]->unk5 == match) {
            count += 1;
        }
        i += 1;
    } while (i < 3U);
    if (count == 3) {
        self->unk5 = (u8)self->unk5 + 1;
        self->ext.effect_42.owner.main->ext.main_73_parts.effect_state = 3;
        self->ext.effect_42.timer = 0xC8;
    }
}

void sigma_sequencer_fx_hold(struct EffectObj* self)
{
    u8 timer;

    timer = self->ext.effect_42.timer - 1;
    self->ext.effect_42.timer = timer;
    if (timer == 0) {
        self->state = 2;
        self->unk5 = 0;
    }
}

void sigma_sequencer_fx_main(struct EffectObj* self)
{
    sigma_sequencer_fx_step_funcs[self->unk5](self);
}

void sigma_sequencer_fx_finish(struct EffectObj* self)
{
    if (g_Player.update_delay == 0) {
        self->ext.effect_42.owner.main->ext.main_73_parts.effect_state = 0;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void sigma_sequencer_fx_update(struct EffectObj* self)
{
    sigma_sequencer_fx_state_funcs[self->state](self);
}

void (*sigma_sequencer_fx_step_funcs[5])(struct EffectObj*) = {
    sigma_sequencer_fx_start,
    sigma_sequencer_fx_wait_player,
    func_800BE364,
    sigma_sequencer_fx_wait_parts,
    sigma_sequencer_fx_hold,
};

void (*sigma_sequencer_fx_state_funcs[])(struct EffectObj*) = {
    sigma_sequencer_fx_init,
    sigma_sequencer_fx_main,
    sigma_sequencer_fx_finish,
};
