// UnkObj, foo_objects
// 800AE7DC..800AEAC0
#include "common.h"

void func_800AE7DC(struct UnkObj* arg0)
{
    struct PlayerObj* player = &g_Player;

    arg0->animation_step.fields.frame_index = player->animation_step.fields.frame_index;
    arg0->unk15 = player->unk15;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

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
    arg0->x_pos.val = parent->unk18.val;
    arg0->y_pos.val = parent->unk1C.val;
}

void (*D_8010A194[])(struct UnkObj*, struct PlayerObj*) = {
    func_800AE8E4,
    func_800AE95C,
    func_800AE9D8,
};
