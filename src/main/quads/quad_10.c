// QuadObj, quad_object_update_funcs[10]
// 800D6AD8..800D6F94
#include "common.h"

void func_800D6AD8(struct QuadObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    struct PlayerObj* temp_a2 = arg0->unk5C;
    s32 var_a1 = 0;
    if (g_Player.unkC3 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unkC4 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unk93 != 6) {
        var_a1 = 1;
    }
    if (g_Player.unk5C == 0) {
        var_a1 = 1;
    }
    if (g_Player.unkBF != 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    D_8010FCB8[arg0->state](arg0, ptr, temp_a2);
}

INCLUDE_ASM("main/nonmatchings/quads/quad_10", func_800D6B9C);

void func_800D6C48(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct Quad10Ext* state;
    u8 value;

    state = &arg0->ext.quad_10;
    value = state->progress;
    state->counter -= 1;
    if (value >= 0x78U) {
        state->progress = 0x78;
        arg0->state++;
    } else {
        state->progress = value + 4;
    }
    func_800D6DC4(arg0, arg1, arg2);
}

void func_800D6CA0(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct Quad10Ext* state = &arg0->ext.quad_10;
    u8* player_data = &arg2->unk8D - 1;
    u8* entry;
    s32 i;
    s32 velocity;

    for (i = 0xF; i != 0; i--) {
        entry = (u8*)state + i;
        entry[0xD] = entry[0xC];
    }

    velocity = state->counter;
    state->history[0] = (player_data[1] - 8) & 0x1F;
    if (velocity == 0x1E) {
        arg0->state++;
    } else {
        if (arg0->unk2 == 3) {
            if (velocity & 2) {
                arg0->on_screen = 1;
            } else {
                arg0->on_screen = 0;
            }
        }
        state->counter--;
    }
    func_800D6DC4(arg0, arg1, arg2);
}

void func_800D6D48(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct Quad10Ext* state;
    struct PlayerUnk8CFields* player_state;
    u8* cursor;
    u8 value;
    s32 index;

    state = &arg0->ext.quad_10;
    player_state = (struct PlayerUnk8CFields*)&arg2->unk8C;
    index = 0xF;
    do {
        cursor = (u8*)state + index;
        value = cursor[0xC];
        index--;
        cursor[0xD] = value;
    } while (index != 0);

    state->history[0] = (player_state->unk8D - 8) & 0x1F;
    if (state->counter == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    state->progress -= 4;
    state->counter--;
    func_800D6DC4(arg0, arg1, arg2);
}

INCLUDE_ASM("main/nonmatchings/quads/quad_10", func_800D6DC4);
