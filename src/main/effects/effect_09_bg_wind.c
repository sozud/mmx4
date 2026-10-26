// EffectObj, effect_object_update_funcs[9]
// 800B75C8..800B7EE8
#include "common.h"
#include "main/effects/effect_09_bg_wind.h"

// bg_wind_state_funcs
extern void (*bg_wind_state_funcs[])(struct EffectObj*);
void bg_wind_init(struct EffectObj*);

void bg_wind_main(struct EffectObj*);

// bg_wind_phase_funcs
extern void (*bg_wind_phase_funcs[])(struct EffectObj*);

void bg_wind_gust_slow(struct EffectObj*);
void bg_wind_gust_fast(struct EffectObj*);
void bg_wind_gust_medium(struct EffectObj*);
void func_800B7CFC(struct EffectObj*);

struct Effect09MovementStep {
    u8 timer;
    s8 direction;
    u8 tile_offset;
    u8 pad;
};

#ifdef MMX4_SATURN
#include "saturn/game_low.h"

void bg_wind_update(struct EffectObj* self)
{
    bg_wind_state_funcs[self->state](self);
    background_objects[2].unk4C = 1;
}

static void bg_wind_next_step(struct EffectObj* effect)
{
    struct Effect9Ext* ext = &effect->ext.effect_9;

    ext->movement_table = &ext->movement_table[ext->frame * 4];
    ext->target_x = ext->movement_table[2];
    ext->timer = ext->movement_table[0];
    ext->frame = ext->movement_table[1];
    saturn_frame_dma_pending = 1;
    saturn_frame_dma_arg_0 = SATURN_BG_WIND_CELL_VRAM;
    saturn_frame_dma_arg_1 = saturn_stage_work_pointer_3 + ((u32)ext->target_x << 11);
    saturn_frame_dma_count = SATURN_BG_WIND_CELL_BYTES;
}

static void bg_wind_advance(struct EffectObj* effect, s32 limit, s32 both_ways)
{
    struct Effect9Ext* ext = &effect->ext.effect_9;

    if (--ext->timer == 0) {
        bg_wind_next_step(effect);
    }
    if (!both_ways) {
        if (ext->velocity < limit) {
            ext->velocity += FIXED(1.0 / 64);
        }
    } else if (ext->direction != 0) {
        if (ext->velocity > limit) {
            ext->velocity -= FIXED(1.0 / 64);
        }
    } else {
        if (ext->velocity < limit) {
            ext->velocity += FIXED(1.0 / 64);
        }
    }
    background_objects[2].x_pos.val = (background_objects[2].x_pos.val + ext->velocity) & 0xFFFFFF;
    background_objects[2].y_pos.val += FIXED(-2);
    if (background_objects[2].y_pos.val == FIXED(256)) {
        background_objects[2].y_pos.val = FIXED(384);
    }
}
#else
void bg_wind_update(struct EffectObj* self)
{
    bg_wind_state_funcs[self->state](self);
}
#endif

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

extern struct Effect09MovementStep bg_wind_steps_fast[3];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B76A4(struct EffectObj* arg0);
#endif

#if defined(MMX4_SATURN)
void func_800B76A4(struct EffectObj* arg0)
{
    struct Effect9Ext* ext = &arg0->ext.effect_9;

    if (ext->direction != 0) {
        background_objects[2].y_pos.val = 0;
        ext->transition_timer = 1;
        saturn_display_mode = SATURN_DISPLAY_MODE_BG_WIND_CALM;
        arg0->state--;
        arg0->unk5 = 0;
        return;
    }
    background_objects[2].y_pos.val = 0x1800000;
    saturn_display_mode = SATURN_DISPLAY_MODE_BG_WIND_GUST;
    ext->movement_timer = 0x168;
    ext->movement_table = (u8*)bg_wind_steps_fast;
    ext->timer = ext->movement_table[0];
    ext->frame = ext->movement_table[1];
    ext->target_x = ext->movement_table[2];
    ext->velocity = 0x10000;
    arg0->unk5++;
}
#elif defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/effects/effect_09_bg_wind", func_800B76A4);
#else
void func_800B76A4(struct EffectObj* arg0)
{
    struct Effect9Ext* ext = &arg0->ext.effect_9;
    s32 x;

    if (ext->direction != 0) {
        background_objects[2].y_pos.val = 0;
        ext->transition_timer = 1;
        background_objects[2].unk4C = 1;
        arg0->unk5 = 0;
        arg0->state--;
        return;
    }
    background_objects[2].y_pos.val = 0x1800000;
    background_objects[2].unk4C = 1;
    ext->movement_timer = 0x168;
    ext->movement_table = (u8*)bg_wind_steps_fast;
    ext->timer = ext->movement_table[0];
    ext->frame = ext->movement_table[1];
    ext->target_x = ext->movement_table[2];
    x = (ext->target_x << 9) + (u8)background_objects[2].x_pos.i.hi;
    background_objects[2].x_pos.i.hi = x;
    ext->velocity = 0x10000;
    arg0->unk5++;
}
#endif

extern struct Effect09MovementStep bg_wind_steps_fast[3];
extern struct Effect09MovementStep bg_wind_steps_slow[3];
extern struct Effect09MovementStep bg_wind_steps_medium[4];

#if defined(MMX4_SATURN)
void bg_wind_gust_slow(struct EffectObj* effect)
{
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
    bg_wind_advance(effect, FIXED(1.5), 1);
}
#elif defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/effects/effect_09_bg_wind", bg_wind_gust_slow);
#else
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
#endif

#ifdef MMX4_SATURN
void bg_wind_gust_fast(struct EffectObj* self)
{
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
    bg_wind_advance(self, FIXED(2.5), 1);
}
#else
void bg_wind_gust_fast(struct EffectObj* self)
{
    s32 shifted_target;
    struct Effect9Ext* effect_9 = &self->ext.effect_9;

    /* The promoted-width test preserves the retail load and branch sequence. */
    if ((effect_9->movement_timer = self->ext.effect_9.movement_timer - 1) << 16 == 0) {
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
    if ((effect_9->timer = self->ext.effect_9.timer - 1) == 0) {
        s32 final_target;

        self->ext.effect_9.movement_table = (u8*)&self->ext.effect_9.movement_table[(self->ext.effect_9.frame * 4)];
        self->ext.effect_9.target_x = self->ext.effect_9.movement_table[2];
        self->ext.effect_9.timer = self->ext.effect_9.movement_table[0];
        self->ext.effect_9.frame = self->ext.effect_9.movement_table[1];

        final_target = (self->ext.effect_9.target_x << 9) + (u8)background_objects[2].x_pos.i.hi;
        background_objects[2].x_pos.i.hi = (s32)final_target;
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

#endif

#if defined(MMX4_SATURN)
void bg_wind_gust_medium(struct EffectObj* self)
{
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
    bg_wind_advance(self, FIXED(3.5), 1);
}
#elif defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/effects/effect_09_bg_wind", bg_wind_gust_medium);
#else
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
#endif

// bg_wind_storm
#if defined(MMX4_SATURN)
void func_800B7CFC(struct EffectObj* effect)
{
    if (--effect->ext.effect_9.movement_timer << 16 == 0) {
        effect->ext.effect_9.direction = 1;
        effect->ext.effect_9.movement_timer = 0x78;
        effect->ext.effect_9.movement_table = (u8*)bg_wind_steps_slow;
        effect->ext.effect_9.timer = effect->ext.effect_9.movement_table[0];
        effect->ext.effect_9.frame = effect->ext.effect_9.movement_table[1];
        effect->ext.effect_9.target_x = effect->ext.effect_9.movement_table[2];
        effect->unk5--;
        return;
    }
    bg_wind_advance(effect, FIXED(4.5), 0);
}
#elif defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/effects/effect_09_bg_wind", func_800B7CFC);
#else
void func_800B7CFC(struct EffectObj* effect)
{
    s32 new_hi;
    s32 target_hi;

    if (--effect->ext.effect_9.movement_timer << 16 == 0) {
        effect->ext.effect_9.direction = 1;
        effect->ext.effect_9.movement_timer = 0x78;
        effect->ext.effect_9.movement_table = (u8*)bg_wind_steps_slow;
        effect->ext.effect_9.timer = effect->ext.effect_9.movement_table[0];
        effect->ext.effect_9.frame = effect->ext.effect_9.movement_table[1];
        effect->ext.effect_9.target_x = effect->ext.effect_9.movement_table[2];
        effect->unk5--;
        return;
    }
    if (--effect->ext.effect_9.timer == 0) {
        effect->ext.effect_9.movement_table = (u8*)&effect->ext.effect_9.movement_table[(effect->ext.effect_9.frame * 4)];
        effect->ext.effect_9.target_x = effect->ext.effect_9.movement_table[2];
        effect->ext.effect_9.timer = effect->ext.effect_9.movement_table[0];
        effect->ext.effect_9.frame = effect->ext.effect_9.movement_table[1];

        new_hi = (effect->ext.effect_9.target_x << 9) + background_objects[2].x_pos.bytes[2];
        background_objects[2].x_pos.i.hi = new_hi;

        background_objects[2].unk4C = 1;
    }
    if (effect->ext.effect_9.velocity <= FIXED(4.5) - 1) {
        effect->ext.effect_9.velocity += FIXED(1.0 / 64);
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
#endif

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
