#include "saturn.h"
#include <stddef.h>

#define VDP1_GROUP_ENTRY __attribute__((noipa))

extern volatile SaturnSpriteCommand saturn_sprite_commands[SATURN_SPRITE_COMMAND_LIMIT];
extern volatile u16 saturn_sprite_command_count, saturn_sprite_pending;
extern volatile u16 saturn_vdp1_uploaded_pending, saturn_vdp1_link_slots[16];
extern const volatile u16 saturn_vdp1_local_x, saturn_vdp1_local_y;
extern void saturn_vdp1_copy_bytes(u32, u32, u32);
extern u32 saturn_vdp1_dma_result(void);

extern volatile u16 saturn_vdp1_saved_link, saturn_vdp1_group_start;
extern volatile u8 saturn_vdp1_active_group;
extern const volatile u16 saturn_vdp1_ticks;
extern volatile u16 saturn_vdp1_draw_trigger, saturn_vdp1_phase, saturn_vdp1_submitted_phase;

static const SaturnVdp1PresentState vdp1_present_state = {
    &saturn_vdp1_ticks, &saturn_vdp1_draw_trigger, &saturn_vdp1_phase, &saturn_vdp1_submitted_phase
};

static const SaturnVdp1GroupState vdp1_group_state = {
    saturn_sprite_commands, &saturn_sprite_command_count, saturn_vdp1_link_slots,
    &saturn_vdp1_saved_link, &saturn_vdp1_active_group, &saturn_vdp1_group_start, 0x25C00000
};

static const SaturnVdp1IO vdp1_io = { saturn_vdp1_copy_bytes, saturn_vdp1_dma_result };

static const SaturnVdp1State vdp1_state = {
    saturn_sprite_commands, &saturn_sprite_command_count, &saturn_sprite_pending,
    &saturn_vdp1_uploaded_pending, saturn_vdp1_link_slots, &saturn_vdp1_local_x,
    &saturn_vdp1_local_y, 0x25C00000
};

static void vdp1_quad(volatile SaturnSpriteCommand* command, u16 color,
    const s16 coordinates[8])
{
    command->words[0] = 4;
    command->words[2] = 0xC0;
    command->words[3] = color;
    for (unsigned i = 0; i < 8; ++i)
        command->words[6 + i] = (u16)coordinates[i];
    command->words[14] = 0xFFFF;
}

void saturn_vdp1_init_state(const SaturnVdp1State* state)
{
    volatile SaturnSpriteCommand* commands = state->commands;
    commands[0].words[0] = 9;
    commands[0].words[10] = 319;
    commands[0].words[11] = 239;
    commands[1].words[0] = 8;
    commands[1].words[6] = 0;
    commands[1].words[7] = 0;
    commands[1].words[10] = 319;
    commands[1].words[11] = 239;
    commands[2].words[0] = 10;
    commands[2].words[6] = 0;
    commands[2].words[7] = 0;
    static const s16 lower_quad[8] = { 0, 110, 319, 110, 319, 239, 0, 239 };
    vdp1_quad(&commands[3], 0, lower_quad);
    commands[4].words[0] = 10;
    commands[4].words[6] = *state->local_x;
    commands[4].words[7] = *state->local_y;
    for (unsigned i = 0; i < 16; ++i) {
        unsigned slot = i + 5;
        commands[slot].words[0] = 0x5000;
        commands[slot].words[1] = (u16)((u32)(state->video_commands + (slot + 1) * 32) >> 3);
        state->link_slots[i] = (u16)slot;
    }
    static const s16 borders[4][8] = {
        { -16, -16, 336, -16, 336, -1, -16, -1 },
        { 320, 0, 336, 0, 336, 239, 320, 239 },
        { -16, 240, 336, 240, 336, 256, -16, 256 },
        { -16, 0, -1, 0, -1, 256, -16, 256 }
    };
    for (unsigned i = 0; i < 4; ++i)
        vdp1_quad(&commands[21 + i], 0x8000, borders[i]);
    commands[25].words[0] = 0x8000;
    *state->count = 26;
}

void saturn_vdp1_init_commands(void) { saturn_vdp1_init_state(&vdp1_state); }

VDP1_GROUP_ENTRY void saturn_vdp1_present_state(const SaturnVdp1PresentState* state)
{
    while (*state->ticks < 2) { }
    *state->draw_trigger = 1;
    *state->submitted_phase = *state->phase;
    *state->phase = 0;
}

void saturn_vdp1_present(void) { saturn_vdp1_present_state(&vdp1_present_state); }

void saturn_vdp1_begin_group_state(const SaturnVdp1GroupState* state, u32 group)
{
    *state->saved_link = state->commands[state->link_slots[group]].words[1];
    state->commands[state->link_slots[group]].words[1] = (u16)((u32)(state->video_commands + (u32)*state->count * 32) >> 3);
    *state->active_group = (u8)group;
    *state->group_start = *state->count;
}

void saturn_vdp1_begin_group(u32 group) { saturn_vdp1_begin_group_state(&vdp1_group_state, group); }

void saturn_vdp1_end_group_state(const SaturnVdp1GroupState* state)
{
    u16 count = *state->count;
    if (*state->group_start == count) {
        state->commands[state->link_slots[*state->active_group]].words[1] = *state->saved_link;
    } else {
        volatile SaturnSpriteCommand* last = &state->commands[(u32)count - 1];
        last->words[0] |= 0x1000;
        last->words[1] = *state->saved_link;
        state->link_slots[*state->active_group] = (u16)(count - 1);
    }
}

void saturn_vdp1_end_group(void) { saturn_vdp1_end_group_state(&vdp1_group_state); }

void saturn_vdp1_upload_state(const SaturnVdp1State* state, const SaturnVdp1IO* io)
{
    *state->uploaded_pending = *state->pending;
    if (*state->pending) {
        io->copy_bytes(state->video_commands, (u32)state->commands, (u32)*state->count * 32);
        while (io->result() == 2) { }
        saturn_vdp1_init_state(state);
        *state->pending = 0;
    } else {
        saturn_vdp1_init_state(state);
    }
}

void saturn_vdp1_upload_commands(void) { saturn_vdp1_upload_state(&vdp1_state, &vdp1_io); }
