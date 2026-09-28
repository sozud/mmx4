// QuadObj, quad_object_update_funcs[9]
// 800D67DC..800D6AD8
#include "common.h"

void func_800D69A8(struct QuadObj* arg0, struct PlayerObj* player, struct PlayerObj* target);

void func_800D67DC(struct QuadObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    struct PlayerObj* temp_a2 = arg0->unk5C;
    s32 var_a3 = 0;
    if (g_Player.input_locked != 0) {
        var_a3 = 1;
    }
    if (g_Player.capsule_state != 0) {
        var_a3 = 1;
    }
    if (g_Player.weapon != 6) {
        var_a3 = 1;
    }
    if (g_Player.hp == 0) {
        var_a3 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a3 = 1;
    }
    if (arg0->unk5C->active == 0) {
        var_a3 = 1;
    }
    if (arg0->unk5C->hp == 0) {
        var_a3 = 1;
    }
    if (var_a3 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->state == 0) {
        func_800D68D0(arg0, ptr, temp_a2);
        return;
    }
    func_800D6944(arg0, ptr, temp_a2);
}

void func_800D68D0(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    arg0->active = -0x7D;
    arg0->on_screen = 1;
    arg0->bg_offset = arg1->bg_offset;
    arg0->unk36 = 1;
    arg0->ext.unk_ext3.unk38 = 0x3C;
    arg0->unk34 = arg0->unk2 + 0xD;
    func_800D69A8(arg0, arg1, arg2);
    arg0->state++;
}

void func_800D6944(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    if (arg0->ext.unk_ext3.unk38 == 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->ext.unk_ext3.unk38 & 2) {
        arg0->on_screen ^= 1;
    }
    arg0->ext.unk_ext3.unk38 -= 1;
    func_800D69A8(arg0, arg1, arg2);
}

INCLUDE_ASM("main/nonmatchings/quads/quad_09", func_800D69A8);
