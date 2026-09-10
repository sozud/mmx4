// ShotObj, shot_object_update_funcs[57]
// 800AE450..800AEAC0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE450);

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE4F0);

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE594);

void func_800AE63C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800AE65C(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->state = 3;
    }
    D_8010A064[arg0->state](arg0);
}

void func_800AE6B4(struct BazObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;

    if (arg0->state == 0) {
        func_800AE714(arg0, ptr);

    } else {
        func_800AE790(arg0, ptr);
    }
}

void func_800AE714(struct BazObj* arg0, struct PlayerObj* arg1)
{
    PlayerChargeState charge_state = arg0->unk2 == 0 ? PLAYER_CHARGE_FULL : PLAYER_CHARGE_PARTIAL;

    if (arg1->charge_state[0] == charge_state || arg1->charge_state[1] == charge_state) {
        arg0->on_screen = 1;
        func_80015D60(arg0, arg0->unk2 + 8);
        arg0->state++;
    }
}

void func_800AE790(struct BazObj* arg0, struct PlayerObj* arg1)
{
    if ((arg1->charge_state[0] == PLAYER_CHARGE_NONE) && (arg1->charge_state[1] == PLAYER_CHARGE_NONE)) {
        arg0->on_screen = 0;
        arg0->state = 0;
    } else {
        func_80015DC8(arg0);
    }
}

void func_800AE7DC(struct UnkObj* arg0)
{
    struct PlayerObj* player = &g_Player;

    arg0->animation_step.fields.frame_index = player->animation_step.fields.frame_index;
    arg0->unk15 = player->unk15;
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;

    if (arg0->state == 0) {
        func_800AE848(arg0, player);
    } else {
        func_800AE88C(arg0, player);
    }
}

void func_800AE848(struct UnkObj* arg0, struct PlayerObj* player)
{
    if (player->unk8C != 0) {
        if (player->unk8C > 0) {
            arg0->on_screen = 1;
            func_800AEA58();
            return;
        }
        player->unk8C = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE88C);

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE8E4);

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE95C);

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE9D8);

void func_800AEA58(struct MiscObj* self, struct EffectObj* parent)
{
    self->ext.ready_text.unk54 = 3;
    self->ext.ready_text.stay_up_timer = 8;
    self->ext.ready_text.palette_pos = (5 - self->unk2) * 2;
    self->x_pos.val = parent->x_pos.val;
    self->y_pos.val = parent->y_pos.val;
    self->state = 1;
    self->unk5 = 0;
}

void func_800AEAA0(struct ShotObj* arg0)
{
    struct PlayerObj* parent;

    parent = arg0->unk50.player;
    arg0->x_pos.val = parent->unk18;
    arg0->y_pos.val = parent->unk1C;
}

void (*D_8010A064[])(struct ShotObj*) = {
    func_800AE450,
    func_800AE4F0,
    func_800AE594,
    func_800AE63C,
};
