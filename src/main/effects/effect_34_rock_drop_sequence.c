// EffectObj, effect_object_update_funcs[34]
// 800BCE48..800BD1A4
#include "common.h"
#include "main/effects/effect_34_rock_drop_sequence.h"
#include "main/objects.h"
#include "main/effects/effect_35_palette_pulse.h"
#include "main/stage_objects.h"

#ifdef MMX4_PC
#include "main/object_motion.h"
#endif

// rock_drop_sequence_state_funcs
extern void (*rock_drop_sequence_state_funcs[])(struct EffectObj*);
void rock_drop_sequence_wait_player(struct EffectObj*);

void rock_drop_sequence_idle(struct EffectObj*);

void rock_drop_sequence_update(struct EffectObj* self)
{
    rock_drop_sequence_state_funcs[self->state](self);
}

void rock_drop_sequence_wait_player(struct EffectObj* self)
{
    if (0 != engine_obj.checkpoint) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }

    if (g_Player.x_pos.i.hi > 0x240) {
        self->ext.effect_34.unk14 = 0;
        self->ext.effect_34.timer = rock_drop_sequence_delays[0];
        self->state = 1;
    }
}

void rock_drop_sequence_spawn(struct EffectObj* self)
{
    struct EffectObj* effect;
    s16 timer;

    timer = --self->ext.effect_34.timer;
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

        self->ext.effect_34.unk14 += 1;
        timer = rock_drop_sequence_delays[self->ext.effect_34.unk14];
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
    self->ext.effect_4.unk16 = 0x20;
    self->state++;
    dst = SP_PALETTE;
    dst += 0x5E0 / 2;
    do {
        *dst++ = *src++;
        count++;
    } while (count < 0x10U);
}

// palette_pulse_step
#ifdef MMX4_PC
void func_800BD080(struct EffectObj* arg0);
#endif

#ifdef MMX4_PC
void func_800BD080(struct EffectObj* arg0)
{
    struct MainObj* main;
    s32 x;
    s32 y;
    u32 i;

    if (--arg0->ext.unk_effect.unk14 != 0)
        return;
    x = background_objects[0].x_pos.u.hi + (u16)arg0->ext.effect_4.unk16;
    y = background_objects[0].y_pos.i.hi + (arg0->ext.unk_effect.unk15 != 0 ? 0x20 : 0x10);
    for (i = 0; i < 5; i++) {
        main = find_free_main_obj();
        if (main == NULL)
            continue;
        main->active = 0x21;
        main->id = 0x3B;
        main->unk2 = 0;
        main->x_pos.i.hi = x + (get_random() & 0xF);
        main->y_pos.i.hi = y + (get_random() & 0x1F);
        y += 0x20;
        main->unk7C = get_random() & 0xF;
    }
    arg0->ext.unk_effect.unk14 = 7;
    arg0->ext.unk_effect.unk15 ^= 1;
    if ((s16)arg0->ext.effect_4.unk16 < 0x70)
        arg0->ext.effect_4.unk16 += 3;
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_34_rock_drop_sequence", func_800BD080);
#endif

s16 rock_drop_sequence_delays[10] = { 2, 2, 2, 0x46, 0x64, 0x46, 0x46, 0x46, 0x46, 0 };

u8 rock_drop_sequence_subtypes[12] = { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0, 0, 0 };

s16 rock_drop_sequence_x_positions[10] = { 0xC0, 0x140, 0x2A0, 0x1C0, 0x240, 0x300, 0x380, 0x410, 0x4C0, 0 };

void (*rock_drop_sequence_state_funcs[])(struct EffectObj*) = {
    rock_drop_sequence_wait_player,
    rock_drop_sequence_spawn,
    rock_drop_sequence_idle,
};
