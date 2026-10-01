// EffectObj, effect_object_update_funcs[26]
// 800BB1F0..800BB9B8
#include "common.h"

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
INCLUDE_ASM("main/nonmatchings/effects/effect_26_boss_death_fx", func_800BB364);

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
INCLUDE_ASM("main/nonmatchings/effects/effect_26_boss_death_fx", func_800BB750);

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/effects/effect_26_boss_death_fx", boss_death_fx_wait);
#else
void boss_death_fx_wait(struct EffectObj* self)
{
    u16 timer;

    timer = self->ext.effect_26.timer;
    self->ext.effect_26.timer = timer - 1;
    if (timer == 0) {
        self->state = (u8)self->state + 1;
    }
}
#endif

// boss_death_fx_fade_in
INCLUDE_ASM("main/nonmatchings/effects/effect_26_boss_death_fx", func_800BB888);

void boss_death_fx_finish(struct EffectObj* self)
{
    if (!(self->active & 0x80)) {
        player_end_script_action();
    }
    engine_obj.unk1C = 1;
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
