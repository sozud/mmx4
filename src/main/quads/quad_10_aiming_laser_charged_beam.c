// QuadObj, quad_object_update_funcs[10]
// 800D6AD8..800D6F94
#include "common.h"
#include "main/quads/quad_10_aiming_laser_charged_beam.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/object_motion.h"
#include "main/sprite_animations.h"
#endif

struct PlayerUnk8CFields {
    s8 unk8C;
    u8 unk8D;
};

// aiming_laser_charged_beam_state_funcs
extern void (*aiming_laser_charged_beam_state_funcs[])(struct QuadObj*, struct PlayerObj*, struct PlayerObj*);

void aiming_laser_charged_beam_extend(struct QuadObj*, struct PlayerObj*, struct PlayerObj*);

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
#ifdef MMX4_PC
void func_800D6B9C(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner);
void func_800D6DC4(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner);
// src/main/quads/quad_10_aiming_laser_charged_beam.c

extern u8 aiming_laser_charged_beam_delays[4];
#endif

#ifdef MMX4_PC
void func_800D6B9C(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner)
{
    struct Quad10Ext* ext = &self->ext.quad_10;
    const struct WeaponObj* weapon = (const struct WeaponObj*)owner;
    s32 i;
    self->active = self->unk2 == 3 ? 0x83 : 0x93;
    self->on_screen = 1;
    self->bg_offset = player->bg_offset;
    self->unk34 = 0xD;
    self->unk36 = 1;
    ext->counter = 0xF0;
    ext->progress = 1;
    for (i = 0; i < 16; i++)
        ext->history[i] = (weapon->ext.weapon_6.adjusted_direction - 8) & 0x1F;
    self->state++;
    func_800D6DC4(self, player, owner);
}
#else
INCLUDE_ASM("main/nonmatchings/quads/quad_10_aiming_laser_charged_beam", func_800D6B9C);
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
#ifdef MMX4_PC
void func_800D6DC4(struct QuadObj* self, struct PlayerObj* player, struct PlayerObj* owner)
{
    struct Quad10Ext* ext = &self->ext.quad_10;
    const s8* offsets = D_8011B230.components;
    s32 direction = ext->history[aiming_laser_charged_beam_delays[(u8)self->unk2]];
    s32 x_offset = offsets[player->animation_step.fields.frame_index * 2];
    (void)owner;
    self->x_pos.u.hi = player->x_pos.u.hi + (player->unk15 ? -x_offset - 2 : x_offset + 2);
    self->y_pos.u.hi = player->y_pos.u.hi + offsets[player->animation_step.fields.frame_index * 2 + 1];
    self->vertices[0].x.val = self->vertices[0].y.val = 0;
    func_8002B9F0(&ext->x_step, &ext->y_step, (direction - 1) & 0x1F);
    self->vertices[1].x.val = ext->x_step * ext->progress;
    self->vertices[1].y.val = ext->y_step * ext->progress;
    func_8002B9F0(&ext->x_step, &ext->y_step, direction);
    self->vertices[2].x.val = ext->x_step * (ext->progress + 0xC);
    self->vertices[2].y.val = ext->y_step * (ext->progress + 0xC);
    func_8002B9F0(&ext->x_step, &ext->y_step, (direction + 1) & 0x1F);
    self->vertices[3].x.val = ext->x_step * ext->progress;
    self->vertices[3].y.val = ext->y_step * ext->progress;
}
#else
INCLUDE_ASM("main/nonmatchings/quads/quad_10_aiming_laser_charged_beam", func_800D6DC4);
#endif

void (*aiming_laser_charged_beam_state_funcs[])(struct QuadObj*, struct PlayerObj*, struct PlayerObj*) = {
    func_800D6B9C,
    aiming_laser_charged_beam_extend,
    aiming_laser_charged_beam_sweep,
    aiming_laser_charged_beam_retract,
};

u8 aiming_laser_charged_beam_delays[4] = { 9, 6, 3, 0 };
