// ShotObj, shot_object_update_funcs[57]
// 800AE450..800AEAC0
#include "common.h"

u16 D_80109F50[6][2] = {
    { 0x4AE, 0x29C },
    { 0x49F, 0x279 },
    { 0x49D, 0x259 },
    { 0x49B, 0x231 },
    { 0x49D, 0x259 },
    { 0x49D, 0x259 },
};

s16 D_80109F68[30][2] = {
    { -7040, 16672 },
    { -5984, 14112 },
    { -4672, 11296 },
    { -3104, 8224 },
    { -768, 5408 },
    { -1504, 3104 },
    { -704, 1568 },
    { 7040, 14368 },
    { 6048, 11808 },
    { 5312, 8736 },
    { 4320, 6176 },
    { 3072, 3872 },
    { 1824, 3088 },
    { 1328, 1808 },
    { 576, 1056 },
    { 13440, 14368 },
    { 11936, 10528 },
    { 10432, 7712 },
    { 8160, 5152 },
    { 5888, 3360 },
    { 3616, 1056 },
    { 576, 1056 },
    { 16604, 4172 },
    { 12533, 4157 },
    { 8217, 4132 },
    { 4156, 4108 },
    { 592, 4104 },
    { 23442, 12512 },
    { 23392, 12477 },
    { -22144, -5832 },
};

u8 D_80109FE0[6][2] = {
    { 22, 4 },
    { 15, 6 },
    { 7, 7 },
    { 0, 6 },
    { 29, 1 },
    { 27, 2 },
};

s16* D_80109FEC[30] = {
    D_80109F68[0],
    D_80109F68[1],
    D_80109F68[2],
    D_80109F68[3],
    D_80109F68[4],
    D_80109F68[5],
    D_80109F68[6],
    D_80109F68[7],
    D_80109F68[8],
    D_80109F68[9],
    D_80109F68[10],
    D_80109F68[11],
    D_80109F68[12],
    D_80109F68[13],
    D_80109F68[14],
    D_80109F68[15],
    D_80109F68[16],
    D_80109F68[17],
    D_80109F68[18],
    D_80109F68[19],
    D_80109F68[20],
    D_80109F68[21],
    D_80109F68[22],
    D_80109F68[23],
    D_80109F68[24],
    D_80109F68[25],
    D_80109F68[26],
    D_80109F68[27],
    D_80109F68[28],
    D_80109F68[29],
};

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
        func_80015DC8(ANIMATED_OBJECT(arg0));
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
            func_800AEA58(arg0, player);
            return;
        }
        player->unk8C = 0;
    }
}

void func_800AE88C(struct UnkObj* arg0, struct PlayerObj* arg1)
{
    if (arg1->unk8C == 0) {
        arg0->on_screen = 0;
        arg0->state = 0;
        return;
    }

    D_8010A194[arg0->unk5](arg0, arg1);
}
void func_800AE8E4(struct UnkObj* arg0, struct PlayerObj* player)
{
    if (arg0->ext.afterimage.position_timer != 0) {
        arg0->ext.afterimage.position_timer--;
    } else {
        arg0->ext.afterimage.position_timer = 3;
        func_800AEAA0(arg0);
    }
    if (player->unk8C < 0) {
        arg0->unk5++;
    }
}

void func_800AE95C(struct UnkObj* self, struct PlayerObj* player)
{
    s16 timer;
    s16 next_timer;

    if (player->unk8C > 0) {
        func_800AEA58(self, player);
        return;
    }

    timer = self->ext.afterimage.blink_timer;
    if (timer != 0) {
        next_timer = timer - 1;
        self->ext.afterimage.blink_timer = next_timer;
        if (next_timer & 1) {
            func_800AEAA0(self);
        }
    } else {
        self->unk5++;
    }
}

void func_800AE9D8(struct UnkObj* self, struct PlayerObj* player)
{
    if (player->unk8C > 0) {
        func_800AEA58(self, player);
        return;
    }
    if (self->ext.afterimage.palette_offset != 0) {
        func_800AEAA0(self);
        self->ext.afterimage.palette_offset--;
        return;
    }
    self->on_screen = 0;
    self->state = 0;
    if (self->unk2 == 2) {
        player->unk8C = 0;
    }
}

void func_800AEA58(struct UnkObj* self, struct PlayerObj* player)
{
    self->ext.afterimage.position_timer = 3;
    self->ext.afterimage.blink_timer = 8;
    self->ext.afterimage.palette_offset = (5 - self->unk2) * 2;
    self->x_pos.val = player->x_pos.val;
    self->y_pos.val = player->y_pos.val;
    self->state = 1;
    self->unk5 = 0;
}

void func_800AEAA0(struct UnkObj* arg0)
{
    struct PlayerObj* parent;

    parent = arg0->link.player;
    arg0->x_pos.val = parent->unk18;
    arg0->y_pos.val = parent->unk1C;
}

void (*D_8010A064[])(struct ShotObj*) = {
    func_800AE450,
    func_800AE4F0,
    func_800AE594,
    func_800AE63C,
};
