// EffectObj, effect_object_update_funcs[9]
// 800B75C8..800B7EE8
#include "common.h"

struct Effect09MovementStep {
    u8 timer;
    s8 direction;
    u8 tile_offset;
    u8 pad;
};

void bg_wind_update(struct EffectObj* self)
{
    bg_wind_state_funcs[self->state](self);
}

void bg_wind_init(struct EffectObj* self)
{
    self->state++;
    background_objects[2].x_pos.val = 0;
    background_objects[2].y_pos.val = 0;
    self->ext.effect_9.transition_timer = 1;
}

void bg_wind_delay(struct EffectObj* self)
{

    if (--self->ext.effect_9.transition_timer == 0) {
        self->ext.effect_9.direction = 0;
        self->unk5 = 0;
        self->state++;
    }
}

void bg_wind_main(struct EffectObj* self)
{
    bg_wind_phase_funcs[self->unk5](self);
}

// bg_wind_calm
INCLUDE_ASM("main/nonmatchings/effects/effect_09_bg_wind", func_800B76A4);

extern struct Effect09MovementStep bg_wind_steps_fast[3];
extern struct Effect09MovementStep bg_wind_steps_slow[3];
extern struct Effect09MovementStep bg_wind_steps_medium[4];

void bg_wind_gust_slow(struct EffectObj* effect)
{
    s16* x_hi;
    s32 new_hi;
    s32 target_hi;

    if (--effect->ext.effect_9.movement_timer << 16 == 0) {
        effect->ext.effect_9.movement_table = (u8*)bg_wind_steps_slow;
        effect->ext.effect_9.timer = effect->ext.effect_9.movement_table[0];
        effect->ext.effect_9.frame = effect->ext.effect_9.movement_table[1];
        effect->ext.effect_9.target_x = effect->ext.effect_9.movement_table[2];
        effect->ext.effect_9.movement_timer = 0xB4;
        if (effect->ext.effect_9.direction != 0) {
            effect->unk5--;
        } else {
            effect->unk5++;
        }
        return;
    }
    if (--effect->ext.effect_9.timer == 0) {
        effect->ext.effect_9.movement_table = (u8*)&effect->ext.effect_9.movement_table[(effect->ext.effect_9.frame * 4)];
        effect->ext.effect_9.target_x = effect->ext.effect_9.movement_table[2];
        effect->ext.effect_9.timer = effect->ext.effect_9.movement_table[0];
        effect->ext.effect_9.frame = effect->ext.effect_9.movement_table[1];

        x_hi = &background_objects[2].x_pos.i.hi;
        new_hi = (effect->ext.effect_9.target_x << 9) + *(u8*)x_hi;
        *x_hi = (s16)new_hi;

        background_objects[2].unk4C = 1;
    }
    if (effect->ext.effect_9.direction != 0) {
        if (effect->ext.effect_9.velocity > FIXED(1.5)) {
            effect->ext.effect_9.velocity -= FIXED(1.0 / 64);
        }
    } else {
        if (effect->ext.effect_9.velocity < FIXED(1.5)) {
            effect->ext.effect_9.velocity += FIXED(1.0 / 64);
        }
    }
    background_objects[2].x_pos.val += effect->ext.effect_9.velocity;
    target_hi = effect->ext.effect_9.target_x << 9;
    if (background_objects[2].x_pos.i.hi >= (target_hi + 0xC0)) {
        background_objects[2].x_pos.i.hi = target_hi;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val += FIXED(-2);
    if (background_objects[2].y_pos.val == FIXED(256)) {
        background_objects[2].y_pos.val = FIXED(384);
        background_objects[2].unk4C = 1;
    }
}

void bg_wind_gust_fast(struct EffectObj* self)
{
    s32 shifted_target;
    if (--self->ext.effect_9.movement_timer << 16 == 0) {
        if (self->ext.effect_9.direction != 0) {
            self->ext.effect_9.movement_timer = 0x168;
            self->ext.effect_9.movement_table = (u8*)bg_wind_steps_fast;
            self->unk5--;
        } else {
            self->ext.effect_9.movement_timer = 0x78;
            self->ext.effect_9.movement_table = (u8*)bg_wind_steps_slow;
            self->unk5++;
        }
        self->ext.effect_9.timer = self->ext.effect_9.movement_table[0];
        self->ext.effect_9.frame = self->ext.effect_9.movement_table[1];
        self->ext.effect_9.target_x = self->ext.effect_9.movement_table[2];
        return;
    }
    if (--self->ext.effect_9.timer == 0) {
        s16* bg_hi;
        s32 final_target;

        self->ext.effect_9.movement_table = (u8*)&self->ext.effect_9.movement_table[(self->ext.effect_9.frame * 4)];
        self->ext.effect_9.target_x = self->ext.effect_9.movement_table[2];
        self->ext.effect_9.timer = self->ext.effect_9.movement_table[0];
        self->ext.effect_9.frame = self->ext.effect_9.movement_table[1];

        bg_hi = &background_objects[2].x_pos.i.hi;
        final_target = (self->ext.effect_9.target_x << 9) + *(u8*)bg_hi;
        *bg_hi = (s32)final_target;

        background_objects[2].unk4C = 1;
    }
    if (self->ext.effect_9.direction != 0) {
        if (self->ext.effect_9.velocity > FIXED(2.5)) {
            self->ext.effect_9.velocity -= FIXED(1.0 / 64);
        }
    } else {
        if (self->ext.effect_9.velocity < FIXED(2.5)) {
            self->ext.effect_9.velocity += FIXED(1.0 / 64);
        }
    }
    background_objects[2].x_pos.val += self->ext.effect_9.velocity;
    shifted_target = self->ext.effect_9.target_x << 9;
    if (background_objects[2].x_pos.i.hi >= (shifted_target + 0xC0)) {
        background_objects[2].x_pos.i.hi = shifted_target;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val += FIXED(-2);
    if (background_objects[2].y_pos.val == FIXED(256)) {
        background_objects[2].y_pos.val = FIXED(384);
        background_objects[2].unk4C = 1;
    }
}

void bg_wind_gust_medium(struct EffectObj* self)
{
    s32 shifted_target;
    if (0 == --self->ext.effect_9.movement_timer << 16) {
        if (self->ext.effect_9.direction != 0) {
            self->ext.effect_9.movement_timer = 0xB4;
            self->ext.effect_9.movement_table = (u8*)bg_wind_steps_slow;
            self->unk5--;
        } else {
            self->ext.effect_9.movement_timer = 0x96;
            self->ext.effect_9.movement_table = (u8*)bg_wind_steps_medium;
            self->unk5++;
        }
        self->ext.effect_9.timer = self->ext.effect_9.movement_table[0];
        self->ext.effect_9.frame = self->ext.effect_9.movement_table[1];
        self->ext.effect_9.target_x = self->ext.effect_9.movement_table[2];
        return;
    }
    if (--self->ext.effect_9.timer == 0) {
        s16* bg_hi;
        s32 final_target;

        self->ext.effect_9.movement_table = (u8*)&self->ext.effect_9.movement_table[(self->ext.effect_9.frame * 4)];
        self->ext.effect_9.target_x = self->ext.effect_9.movement_table[2];
        self->ext.effect_9.timer = self->ext.effect_9.movement_table[0];
        self->ext.effect_9.frame = self->ext.effect_9.movement_table[1];

        bg_hi = &background_objects[2].x_pos.i.hi;
        final_target = (self->ext.effect_9.target_x << 9) + *(u8*)bg_hi;
        *bg_hi = (s32)final_target;

        background_objects[2].unk4C = 1;
    }
    if (self->ext.effect_9.direction != 0) {
        if (self->ext.effect_9.velocity > FIXED(3.5)) {
            self->ext.effect_9.velocity -= FIXED(1.0 / 64);
        }
    } else {
        if (self->ext.effect_9.velocity < FIXED(3.5)) {
            self->ext.effect_9.velocity += FIXED(1.0 / 64);
        }
    }
    background_objects[2].x_pos.val += self->ext.effect_9.velocity;
    shifted_target = self->ext.effect_9.target_x << 9;
    if (background_objects[2].x_pos.i.hi >= (shifted_target + 0xC0)) {
        background_objects[2].x_pos.i.hi = shifted_target;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val += FIXED(-2);
    if (background_objects[2].y_pos.val == FIXED(256)) {
        background_objects[2].y_pos.val = FIXED(384);
        background_objects[2].unk4C = 1;
    }
}

// bg_wind_storm
INCLUDE_ASM("main/nonmatchings/effects/effect_09_bg_wind", func_800B7CFC);

u8 player_in_bounds(s16* bounds)
{
    s16 x;
    s16 y;

    x = g_Player.x_pos.i.hi;
    y = g_Player.y_pos.i.hi;
    if ((x > bounds[0]) && (x < bounds[1]) && (bounds[2] < y)) {
        if (y < bounds[3]) {
            return 1;
        }
    }
    return 0;
}

void (*bg_wind_state_funcs[])(struct EffectObj*) = {
    bg_wind_init,
    bg_wind_delay,
    bg_wind_main,
};

void (*bg_wind_phase_funcs[])(struct EffectObj*) = {
    func_800B76A4,
    bg_wind_gust_slow,
    bg_wind_gust_fast,
    bg_wind_gust_medium,
    func_800B7CFC,
};

struct Effect09MovementStep bg_wind_steps_medium[4] = {
    { 5, 1, 0, 0 },
    { 5, 1, 1, 0 },
    { 5, 1, 2, 0 },
    { 5, -3, 3, 0 },
};

struct Effect09MovementStep bg_wind_steps_slow[3] = {
    { 5, 1, 4, 0 },
    { 5, 1, 5, 0 },
    { 5, -2, 6, 0 },
};

struct Effect09MovementStep bg_wind_steps_fast[3] = {
    { 5, 1, 7, 0 },
    { 5, 1, 8, 0 },
    { 5, -2, 9, 0 },
};
