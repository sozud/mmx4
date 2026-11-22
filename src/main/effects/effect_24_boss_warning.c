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
#include "weapon_resources.h"
#ifdef MMX4_GAMECUBE
extern u8 gc_stage_music_opened;
#endif

// boss_warning_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BABA8(struct EffectObj* arg0);
void func_800BAC58(struct EffectObj* arg0);
#endif

void func_800BABA8(struct EffectObj* arg0)
{
    struct EffectObj* spawned;

#ifndef VERSION_DEMO
    if (engine_obj.stage > 0 && engine_obj.stage < 9
        && ((u8)engine_obj.palette_flags & (1 << (engine_obj.stage - 1)))) {
        engine_obj.unkF = 1;
        return;
    }
#endif
    spawned = find_free_effect_obj();
    if (spawned != NULL) {
        spawned->active = 1;
        spawned->id = 4;
#ifndef VERSION_DEMO
        arg0->ext.effect_24.spawned_effect = spawned;
#endif
    }
    arg0->state++;
    arg0->ext.effect_24.timer = 0;
    arg0->ext.effect_24.unk1A = 5;
    arg0->ext.effect_24.unk1B = 0;
#ifdef VERSION_DEMO
    arg0->ext.effect_24.spawned_effect = NULL;
#endif
}

// boss_warning_spawn_tiles
void func_800BAC58(struct EffectObj* arg0)
{
    struct QuadObj* quad;

    if (arg0->ext.effect_24.timer == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = -0x7D;
            quad->id = 3;
            quad->unk2 = arg0->ext.effect_24.unk1B;
            boss_warning_tiles[arg0->ext.effect_24.unk1B] = (struct EffectObj*)quad;
            arg0->ext.effect_24.unk1B++;
            arg0->ext.effect_24.timer = 2;
            if (arg0->ext.effect_24.unk1B == 0x16) {
                arg0->ext.effect_24.unk1B = 0;
                arg0->ext.effect_24.timer = DEMO_ALT(0xB4, 120);
                arg0->unk5++;
            }
        }
    } else {
        arg0->ext.effect_24.timer--;
    }
}

#ifndef VERSION_DEMO
void boss_warning_wait(struct EffectObj* self)
{
    if (--self->ext.effect_24.timer == 0) {
        self->unk5++;
    }
}
#endif

#ifndef VERSION_DEMO
void boss_warning_wait_tiles(struct EffectObj* self)
{
    struct EffectObj* spawned;
    struct EffectObj** entry;
    u32 index;
    s32 count;
    s32 expected;

    spawned = self->ext.effect_24.spawned_effect;
#ifdef MMX4_SATURN
    if (spawned->id != 4 || *(u16*)spawned == 0x0004) {
#elif defined(MMX4_BIG_ENDIAN)
    if (spawned->id != 4 || (spawned->id == 4 && spawned->active == 0)) {
#else
    if (spawned->id != 4 || *(u16*)spawned == 0x400) {
#endif
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
            self->unk5++;
            self->ext.effect_24.unk1B = 0;
        }
    }
}
#endif

#ifdef VERSION_DEMO
void boss_warning_advance_tiles(struct EffectObj* self)
{
    struct EffectObj* effect;

    if (self->ext.effect_24.timer == 0) {
        effect = boss_warning_tiles[self->ext.effect_24.unk1B];
        effect->unk5++;
        self->ext.effect_24.unk1B++;
        self->ext.effect_24.timer = 2;
        if (self->ext.effect_24.unk1B == 0x16) {
            self->state++;
        }
    } else {
        self->ext.effect_24.timer--;
    }
}
#else
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
#ifdef MMX4_SATURN
            saturn_music_play(0x12, 0);
#else
            func_8001653C();
#endif
        }
    }
}
#endif

#ifndef VERSION_DEMO
void boss_warning_finish(struct EffectObj* self)
{
    self->ext.effect_24.unk1A = 0xA;
    if (--self->ext.effect_24.timer == 0) {
        self->state++;
    }
}
#endif

void boss_warning_main(struct EffectObj* self)
{
    boss_warning_step_funcs[self->unk5](self);
#ifndef VERSION_DEMO
    if (self->ext.effect_24.unk1A == 0) {
#ifdef MMX4_GAMECUBE
        if (gc_stage_music_opened == 0) {
            func_8001540C(0, SATURN_SOUND(0x13, 0x15), 0);
            self->ext.effect_24.unk1A = 0x3C;
        }
#else
        func_8001540C(0, SATURN_SOUND(0x13, 0x15), 0);
        self->ext.effect_24.unk1A = 0x3C;
#endif
    } else {
        self->ext.effect_24.unk1A--;
    }
#endif
}

void boss_warning_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void boss_warning_update(struct EffectObj* self)
{
    boss_warning_state_funcs[self->state](self);
}

#ifdef VERSION_DEMO
void (*boss_warning_step_funcs[])(struct EffectObj*) = {
    func_800BAC58,
    boss_warning_advance_tiles,
};

void (*boss_warning_state_funcs[])(struct EffectObj*) = {
    func_800BABA8,
    boss_warning_main,
    boss_warning_despawn,
};
#else
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
#endif
