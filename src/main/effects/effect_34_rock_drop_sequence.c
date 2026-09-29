// EffectObj, effect_object_update_funcs[34]
// 800BCE48..800BD1A4
#include "common.h"

void rock_drop_sequence_update(struct EffectObj* self)
{
    rock_drop_sequence_state_funcs[self->state](self);
}

void rock_drop_sequence_wait_player(struct EffectObj* self)
{
    if (engine_obj.checkpoint != 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }

    if (g_Player.x_pos.i.hi >= 0x241) {
        self->ext.effect_34.unk14 = 0;
        self->ext.effect_34.timer = rock_drop_sequence_delays[0];
        self->state = 1;
    }
}

void rock_drop_sequence_spawn(struct EffectObj* self)
{
    struct EffectObj* effect;
    u8 index;
    s16 timer;

    timer = self->ext.effect_34.timer - 1;
    self->ext.effect_34.timer = timer;
    if (timer == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x21;
            effect->unk2 = rock_drop_sequence_subtypes[self->ext.effect_34.unk14];
            effect->x_pos.u.hi = rock_drop_sequence_x_positions[self->ext.effect_34.unk14];
            effect->y_pos.u.hi = 0x270;
            effect->backref = NULL;
            effect->state = 0;
        }

        index = self->ext.effect_34.unk14 + 1;
        self->ext.effect_34.unk14 = index;
        timer = rock_drop_sequence_delays[index];
        self->ext.effect_34.timer = timer;
        if (timer == 0) {
            self->state = 2;
        }
    } else if (self->ext.effect_34.unk14 == 1 && !(background_objects[g_Player.bg_offset].unk34 & 0x10)) {
        start_screen_shake_x(8, 4, 2);
    }
}

void rock_drop_sequence_idle(struct EffectObj* self)
{
}

void palette_pulse_init(struct EffectObj* self)
{
    u16* src;
    u16* dst;
    u32 count;

    src = palette_pulse_palette;
    count = 0;
    self->ext.unk_effect.unk14 = 1;
    self->ext.unk_effect.unk15 = 0;
    self->state++;
    dst = SP_PALETTE;
    self->ext.effect_4.unk16 = 0x20;
    dst += 0x5E0 / 2;
    do {
        *dst++ = *src++;
        count++;
    } while (count < 0x10U);
}

// palette_pulse_step
INCLUDE_ASM("main/nonmatchings/effects/effect_34_rock_drop_sequence", func_800BD080);

s16 rock_drop_sequence_delays[10] = { 2, 2, 2, 0x46, 0x64, 0x46, 0x46, 0x46, 0x46, 0 };

u8 rock_drop_sequence_subtypes[12] = { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0, 0, 0 };

s16 rock_drop_sequence_x_positions[10] = { 0xC0, 0x140, 0x2A0, 0x1C0, 0x240, 0x300, 0x380, 0x410, 0x4C0, 0 };

void (*rock_drop_sequence_state_funcs[])(struct EffectObj*) = {
    rock_drop_sequence_wait_player,
    rock_drop_sequence_spawn,
    rock_drop_sequence_idle,
};
