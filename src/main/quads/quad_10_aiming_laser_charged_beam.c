// QuadObj, quad_object_update_funcs[10]
// 800D6AD8..800D6F94
#include "common.h"
#include "main/quads/quad_10_aiming_laser_charged_beam.h"
#include "main/objects.h"
#include "main/sprite_animations.h"
#include "main/object_motion.h"

struct PlayerUnk8CFields {
    s8 unk8C;
    u8 unk8D;
};

// aiming_laser_charged_beam_state_funcs
extern void (*aiming_laser_charged_beam_state_funcs[])(struct QuadObj*, struct PlayerObj*, struct PlayerObj*);

void aiming_laser_charged_beam_extend(struct QuadObj*, struct PlayerObj*, struct PlayerObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/object_motion.h"
#include "main/sprite_animations.h"
#endif

void aiming_laser_charged_beam_update(struct QuadObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    struct PlayerObj* temp_a2 = arg0->unk5C;
    s32 var_a1 = 0;
    if (g_Player.input_locked != 0) {
        var_a1 = 1;
    }
    if (g_Player.capsule_state != 0) {
        var_a1 = 1;
    }
    if (g_Player.weapon != 6) {
        var_a1 = 1;
    }
    if (g_Player.hp == 0) {
        var_a1 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    aiming_laser_charged_beam_state_funcs[arg0->state](arg0, ptr, temp_a2);
}

// aiming_laser_charged_beam_init

extern u8 aiming_laser_charged_beam_delays[4];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800D6B9C(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner);
void func_800D6DC4(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner);
// src/main/quads/quad_10_aiming_laser_charged_beam.c

#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_10_aiming_laser_charged_beam", func_800D6B9C);
#else
void func_800D6B9C(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner)
{
    struct Quad10Ext* ext;
    struct Weapon6Ext* weapon;
    u32 i;

    ext = &self->ext.quad_10;
    weapon = &((struct WeaponObj*)owner)->ext.weapon_6;
    if (self->unk2 == 3)
        self->active = 0x83;
    else
        self->active = 0x93;
    self->on_screen = 1;
    self->bg_offset = player->bg_offset;
    self->unk34 = 0xD;
    self->unk36 = 1;
    ext->counter = 0xF0;
    ext->progress = 1;
    ext->history[0] = (weapon->adjusted_direction - 8) & 0x1F;
    for (i = 1; i < 16; i++)
        ext->history[i] = ext->history[0];
    self->state++;
    func_800D6DC4(self, player, owner);
}
#endif

void aiming_laser_charged_beam_extend(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct Quad10Ext* state;
    u8 value;

    state = &arg0->ext.quad_10;
    state->counter -= 1;
    value = state->progress;
    if (value >= 0x78U) {
        state->progress = 0x78;
        arg0->state++;
    } else {
        state->progress = value + 4;
    }
    func_800D6DC4(arg0, arg1, arg2);
}

void aiming_laser_charged_beam_sweep(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct Quad10Ext* state = &arg0->ext.quad_10;
    u8* player_data = &arg2->unk8D - 1;
    s32 i;

    for (i = 0xF; (u32)i > 0; i--) {
        state->history[i] = state->history[i - 1];
    }
#ifdef MMX4_PC
    state->history[0] = (((struct WeaponObj*)arg2)->ext.weapon_6.adjusted_direction - 8) & 0x1F;
#else
    state->history[0] = (player_data[1] - 8) & 0x1F;
#endif
    if (state->counter == 0x1E) {
        arg0->state++;
    } else {
        if (arg0->unk2 == 3) {
            if (BLINK_CLOCK(state->counter) & 2) {
                arg0->on_screen = 1;
            } else {
                arg0->on_screen = 0;
            }
        }
        state->counter--;
    }
    func_800D6DC4(arg0, arg1, arg2);
}

void aiming_laser_charged_beam_retract(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct Quad10Ext* state;
    struct PlayerUnk8CFields* player_state;
    s32 index;

    state = &arg0->ext.quad_10;
    player_state = (struct PlayerUnk8CFields*)&arg2->afterimage;
    for (index = 0xF; index != 0; index--) {
        state->history[index] = state->history[index - 1];
    }

#ifdef MMX4_PC
    state->history[0] = (((struct WeaponObj*)arg2)->ext.weapon_6.adjusted_direction - 8) & 0x1F;
#else
    state->history[0] = (player_state->unk8D - 8) & 0x1F;
#endif
    if (state->counter == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    state->progress -= 4;
    state->counter--;
    func_800D6DC4(arg0, arg1, arg2);
}

// aiming_laser_charged_beam_place
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/quads/quad_10_aiming_laser_charged_beam", func_800D6DC4);
#else
void func_800D6DC4(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner)
{
    struct Quad10Ext* ext = &self->ext.quad_10;
    s16 x;
    s16 y;
    s32 direction;

    if (player->unk15 == 0)
        x = player->x_pos.i.hi + (s8)((u8*)&D_8011B230)[player->animation_step.fields.frame_index * 2] + 2;
    else
        x = player->x_pos.i.hi - (s8)((u8*)&D_8011B230)[player->animation_step.fields.frame_index * 2] - 2;
    y = player->y_pos.i.hi + (s8)((u8*)&D_8011B230)[player->animation_step.fields.frame_index * 2 + 1];
    direction = ext->history[aiming_laser_charged_beam_delays[self->unk2]];
    self->x_pos.i.hi = x;
    self->y_pos.i.hi = y;
    self->vertices[0].x.val = 0;
    self->vertices[0].y.val = 0;
    func_8002B9F0(&ext->x_step, &ext->y_step, (direction - 1) & 0x1F);
    self->vertices[1].x.val = ext->x_step * ext->progress;
    self->vertices[1].y.val = ext->y_step * ext->progress;
    func_8002B9F0(&ext->x_step, &ext->y_step, direction);
    self->vertices[2].x.val = ext->x_step * (ext->progress + 0xC);
    self->vertices[2].y.val = ext->y_step * (ext->progress + 0xC);
    func_8002B9F0(&ext->x_step, &ext->y_step, (direction + 1) & 0x1F);
    self->vertices[3].x.val = ext->x_step * ext->progress;
    self->vertices[3].y.val = ext->y_step * ext->progress;
#ifdef MMX4_SATURN
    if (self->on_screen != 0) {
        saturn_queue_frozen_quad(self);
    }
#endif
}
#endif

void (*aiming_laser_charged_beam_state_funcs[])(struct QuadObj*, struct PlayerObj*, struct PlayerObj*) = {
    func_800D6B9C,
    aiming_laser_charged_beam_extend,
    aiming_laser_charged_beam_sweep,
    aiming_laser_charged_beam_retract,
};

u8 aiming_laser_charged_beam_delays[4] = { 9, 6, 3, 0 };
