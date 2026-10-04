// QuadObj, quad_object_update_funcs[10]
// 800D6AD8..800D6F94
#include "common.h"

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
INCLUDE_ASM("main/nonmatchings/quads/quad_10_aiming_laser_charged_beam", func_800D6B9C);

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
    state->history[0] = (player_data[1] - 8) & 0x1F;
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

    state->history[0] = (player_state->unk8D - 8) & 0x1F;
    if (state->counter == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    state->progress -= 4;
    state->counter--;
    func_800D6DC4(arg0, arg1, arg2);
}

// aiming_laser_charged_beam_place
INCLUDE_ASM("main/nonmatchings/quads/quad_10_aiming_laser_charged_beam", func_800D6DC4);

void (*aiming_laser_charged_beam_state_funcs[])(struct QuadObj*, struct PlayerObj*, struct PlayerObj*) = {
    func_800D6B9C,
    aiming_laser_charged_beam_extend,
    aiming_laser_charged_beam_sweep,
    aiming_laser_charged_beam_retract,
};

u8 aiming_laser_charged_beam_delays[4] = { 9, 6, 3, 0 };
