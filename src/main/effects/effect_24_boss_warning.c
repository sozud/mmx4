// EffectObj, effect_object_update_funcs[24]
// 800BABA8..800BAF60
#include "common.h"
#include "main/effects/effect_24_boss_warning.h"
#include "main/55C4.h"
#include "main/objects.h"

// boss_warning_step_funcs
extern void (*boss_warning_step_funcs[])(struct EffectObj*);

void boss_warning_wait(struct EffectObj*);

void boss_warning_advance_tiles(struct EffectObj*);
void boss_warning_finish(struct EffectObj*);

// boss_warning_state_funcs
extern void (*boss_warning_state_funcs[])(struct EffectObj*);

void boss_warning_main(struct EffectObj*);
void boss_warning_despawn(struct EffectObj*);

// boss_warning_init
#ifdef MMX4_PC
void func_800BABA8(struct EffectObj* arg0);
void func_800BAC58(struct EffectObj* arg0);
#endif

#ifdef MMX4_PC
// src/main/effects/effect_24_boss_warning.c

void func_800BABA8(struct EffectObj* arg0)
{
    struct EffectObj* spawned;
    s32 stage = engine_obj.stage;

    if (stage >= 1 && stage <= 8
        && ((engine_obj.palette_flags >> (stage - 1)) & 1) != 0) {
        engine_obj.unkF = 1;
        return;
    }

    spawned = find_free_effect_obj();
    if (spawned != NULL) {
        spawned->active = 1;
        spawned->id = 4;
        arg0->ext.effect_24.spawned_effect = spawned;
    }
    arg0->ext.effect_24.timer = 0;
    arg0->ext.effect_24.unk1A = 5;
    arg0->ext.effect_24.unk1B = 0;
    arg0->state++;
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_24_boss_warning", func_800BABA8);
#endif

// boss_warning_spawn_tiles
#ifdef MMX4_PC
void func_800BAC58(struct EffectObj* arg0)
{
    struct QuadObj* quad;

    if (arg0->ext.effect_24.timer != 0) {
        arg0->ext.effect_24.timer--;
        return;
    }

    quad = find_free_quad_obj();
    if (quad == NULL)
        return;
    quad->active = -0x7D;
    quad->id = 3;
    quad->unk2 = arg0->ext.effect_24.unk1B;
    boss_warning_tiles[arg0->ext.effect_24.unk1B] = (struct EffectObj*)quad;
    arg0->ext.effect_24.timer = 2;
    arg0->ext.effect_24.unk1B++;
    if (arg0->ext.effect_24.unk1B == 0x16) {
        arg0->ext.effect_24.unk1B = 0;
        arg0->ext.effect_24.timer = 0xB4;
        arg0->unk5++;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_24_boss_warning", func_800BAC58);
#endif

void boss_warning_wait(struct EffectObj* self)
{
    if (--self->ext.effect_24.timer == 0) {
        self->unk5++;
    }
}

void boss_warning_wait_tiles(struct EffectObj* self)
{
    struct EffectObj* spawned;
    struct EffectObj** entry;
    u32 index;
    s32 count;
    s32 expected;

    spawned = self->ext.effect_24.spawned_effect;
    if (spawned->id != 4 || *(u16*)spawned == 0x400) {
        index = 0;
        count = 0;
        expected = 1;
        entry = boss_warning_tiles;
        do {
            if ((*entry)->unk5 == expected) {
                count++;
            }
            index++;
            entry++;
        } while (index < 0x16U);
        if (count == 0x16) {
            self->ext.effect_24.unk1B = 0;
            self->unk5++;
        }
    }
}

void boss_warning_advance_tiles(struct EffectObj* self)
{
    struct EffectObj* effect;
    u8 old_unk5;

    effect = boss_warning_tiles[self->ext.effect_24.unk1B];
    effect->unk5++;
    self->ext.effect_24.unk1B++;
    if (self->ext.effect_24.unk1B == 0x16) {
        old_unk5 = self->unk5;
        self->unk5 = old_unk5 + 1;
        self->ext.effect_24.timer = 0x3C;
        if (engine_obj.stage == 0) {
            func_8001653C();
        }
    }
}

void boss_warning_finish(struct EffectObj* self)
{
    self->ext.effect_24.unk1A = 0xA;
    if (--self->ext.effect_24.timer == 0) {
        self->state++;
    }
}

void boss_warning_main(struct EffectObj* self)
{
    boss_warning_step_funcs[self->unk5](self);
    if (self->ext.effect_24.unk1A == 0) {
        func_8001540C(0, 0x13, 0);
        self->ext.effect_24.unk1A = 0x3C;
    } else {
        self->ext.effect_24.unk1A--;
    }
}

void boss_warning_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void boss_warning_update(struct EffectObj* self)
{
    boss_warning_state_funcs[self->state](self);
}

void (*boss_warning_step_funcs[5])(struct EffectObj*) = {
    func_800BAC58,
    boss_warning_wait,
    boss_warning_wait_tiles,
    boss_warning_advance_tiles,
    boss_warning_finish,
};

void (*boss_warning_state_funcs[])(struct EffectObj*) = {
    func_800BABA8,
    boss_warning_main,
    boss_warning_despawn,
};
