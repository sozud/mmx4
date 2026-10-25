// EffectObj, effect_object_update_funcs[26]
// 800BB1F0..800BB9B8
#include "common.h"
#include "main/effects/effect_26_boss_death_fx.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/visuals/visual_03_small_effect.h"
#include "main/55C4.h"
#include "main/1AC84.h"

// boss_death_fx_state_funcs
extern void (*boss_death_fx_state_funcs[])(struct EffectObj*);

void boss_death_fx_burst(struct EffectObj*);
void boss_death_fx_rays(struct EffectObj*);

void boss_death_fx_wait(struct EffectObj*);

void boss_death_fx_finish(struct EffectObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1AC84.h"
#include "main/55C4.h"
#endif

void boss_death_fx_init(struct EffectObj* self)
{
    struct QuadObj* quad;

    self->unk2 = get_random() & 0x1F;

    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 4;
        quad->unk2 = self->unk2;
        quad->x_pos.u.hi = self->x_pos.u.hi;
        quad->y_pos.u.hi = self->y_pos.u.hi;
    }

    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 4;
        quad->unk2 = (self->unk2 + 10) & 0x1F;
        quad->x_pos.u.hi = self->x_pos.u.hi;
        quad->y_pos.u.hi = self->y_pos.u.hi;
    }

    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 4;
        quad->unk2 = (self->unk2 + 21) & 0x1F;
        quad->x_pos.u.hi = self->x_pos.u.hi;
        quad->y_pos.u.hi = self->y_pos.u.hi;
    }

    self->ext.effect_26.timer = 8;
    self->ext.effect_26.quad_timer = 4;
    self->state++;
}

void boss_death_fx_spawn_explosions(struct EffectObj* self)
{
    s8 temp_v0;

    temp_v0 = self->ext.effect_26.quad_timer - 1;
    self->ext.effect_26.quad_timer = temp_v0;
    if (temp_v0 == 0) {
        self->ext.effect_26.quad_timer = 4;
        func_800AF95C(OBJECT_HEADER(self), 1, 0x60, 0x60, 2);
    }
}

// boss_death_fx_start_flash

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static void effect_26_spawn_spark(struct EffectObj* arg0, u8 angle);
void func_800BB364(struct EffectObj* arg0);
void func_800BB750(struct EffectObj* arg0);
void func_800BB888(struct EffectObj* arg0);
void boss_death_fx_spawn_ray(struct EffectObj* arg0);
void boss_death_fx_spawn_ring(struct EffectObj* arg0);
static void effect_26_spawn_spark(struct EffectObj* arg0, u8 angle)
{
    struct QuadObj* quad = find_free_quad_obj();

    if (quad == NULL)
        return;
    quad->active = 1;
    quad->id = 4;
    quad->unk2 = angle;
    quad->x_pos.i.hi = arg0->x_pos.i.hi;
    quad->y_pos.i.hi = arg0->y_pos.i.hi;
}
#endif

void func_800BB364(struct EffectObj* arg0)
{
    struct QuadObj* quad;

    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 4;
        quad->unk2 = arg0->unk2;
        quad->x_pos.i.hi = arg0->x_pos.i.hi;
        quad->y_pos.i.hi = arg0->y_pos.i.hi;
    }
    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 4;
        quad->unk2 = (arg0->unk2 + 0xA) & 0x1F;
        quad->x_pos.i.hi = arg0->x_pos.i.hi;
        quad->y_pos.i.hi = arg0->y_pos.i.hi;
    }
    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 4;
        quad->unk2 = (arg0->unk2 + 0x15) & 0x1F;
        quad->x_pos.i.hi = arg0->x_pos.i.hi;
        quad->y_pos.i.hi = arg0->y_pos.i.hi;
    }
    ((void (*)(s32, s32))func_8002B560)(0x82, 0);
    if (arg0->ext.effect_26.timer != 0) {
        arg0->ext.effect_26.timer--;
        spawn_explosion(BASE_OBJECT(arg0));
    } else {
        arg0->ext.effect_26.timer = 0x64;
        arg0->state++;
        g_FilterModeR = 0;
        g_FilterModeG = 0;
        g_FilterModeB = 0;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
#ifdef MMX4_SATURN
        D_8013E188[0] = 0x7F;
#else
        D_8013E188[0] = -1;
        D_8013E188[1] = -1;
        D_8013E188[2] = -1;
        D_8013E188[3] = -1;
#endif
#ifdef MMX4_SATURN
        saturn_music_stop();
#else
        func_80016F0C();
#endif
        engine_obj.unk42 = 0;
    }
}

void boss_death_fx_spawn_ray(struct EffectObj* self)
{
    struct QuadObj* quad;

    if (!(get_random_nonzero() % 2)) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 4;
            quad->unk2 = get_random() & 0x1F;
            quad->x_pos.u.hi = self->x_pos.u.hi;
            quad->y_pos.u.hi = self->y_pos.u.hi;
        }
    }
}

void boss_death_fx_spawn_ring(struct EffectObj* self)
{
    struct QuadObj* quad;

    if (!(get_random() & 3)) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 6;
            quad->x_pos.i.hi = self->x_pos.i.hi;
            quad->y_pos.i.hi = self->y_pos.i.hi;
        }
    }
}

void boss_death_fx_burst(struct EffectObj* self)
{
    struct QuadObj* quad;
    u16 timer;

    timer = self->ext.effect_26.timer;
    if (timer != 0) {
        self->ext.effect_26.timer = timer - 1;
        boss_death_fx_spawn_explosions(self);
        boss_death_fx_spawn_ray(self);
        return;
    }
    self->state++;
    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 8;
        quad->x_pos.i.hi = self->x_pos.i.hi;
        quad->y_pos.i.hi = self->y_pos.i.hi;
    }
    self->ext.effect_26.timer = 10;
}

void boss_death_fx_rays(struct EffectObj* self)
{
    s32 i;
    struct QuadObj* quad;
    u16 timer;

    timer = self->ext.effect_9.transition_timer;
    if (timer != 0) {
        self->ext.effect_9.transition_timer = timer - 1;
        boss_death_fx_spawn_explosions(self);
        boss_death_fx_spawn_ray(self);
        return;
    }

    i = 0;
    do {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 6;
            quad->x_pos.i.hi = self->x_pos.i.hi;
            quad->y_pos.i.hi = self->y_pos.i.hi;
            quad->unk6 = i;
        }
        i++;
    } while ((u32)i < 0x10U);
    self->state++;
}

// boss_death_fx_whiteout
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/effects/effect_26_boss_death_fx", func_800BB750);
#else
void func_800BB750(struct EffectObj* arg0)
{
    arg0->ext.effect_26.timer++;
    boss_death_fx_spawn_explosions(arg0);
    boss_death_fx_spawn_ray(arg0);
    do {
        boss_death_fx_spawn_ring(arg0);
        if (arg0->ext.effect_26.timer % 5 == 0) {
            g_FilterAmountR += 1;
            g_FilterAmountG += 0x20;
            g_FilterAmountB += 0x400;
            if (g_FilterAmountR == 0x1F) {
                arg0->state++;
                if (arg0->active & 0x80)
                    arg0->ext.effect_26.timer = 0xC8;
                else
                    arg0->ext.effect_26.timer = 0x28;
                arg0->unk7 = 1;
                engine_obj.enable_boss = 0;
                func_8001540C(0, 5, NULL);
            }
        }
    } while (0);
}
#endif

void boss_death_fx_wait(struct EffectObj* self)
{
    if (self->ext.effect_26.timer-- == 0) {
        self->state = (u8)self->state + 1;
    }
}

// boss_death_fx_fade_in
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/effects/effect_26_boss_death_fx", func_800BB888);
#else
void func_800BB888(struct EffectObj* arg0)
{
    do {
        if (++arg0->ext.effect_26.timer % 5 == 0) {
            g_FilterAmountR -= 1;
            g_FilterAmountG -= 0x20;
            g_FilterAmountB -= 0x400;
            if (g_FilterAmountR == 0)
                arg0->state++;
        }
    } while (0);
}
#endif

void boss_death_fx_finish(struct EffectObj* self)
{
    if (!(self->active & 0x80)) {
        player_end_script_action();
    }
    engine_obj.gameplay_locked = 1;
    ZeroObjectState(OBJECT_HEADER(self));
}

void boss_death_fx_update(struct EffectObj* self)
{
    boss_death_fx_state_funcs[self->state](self);
}

void (*boss_death_fx_state_funcs[])(struct EffectObj*) = {
    boss_death_fx_init,
    func_800BB364,
    boss_death_fx_burst,
    boss_death_fx_rays,
    func_800BB750,
    boss_death_fx_wait,
    func_800BB888,
    boss_death_fx_finish,
};
