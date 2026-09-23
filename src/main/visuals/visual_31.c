// VisualObj, visual_object_update_funcs[31]
// 800B4B64..800B4E34
#include "common.h"

void func_800B4B64(struct VisualObj* arg0)
{
    D_8010A704[arg0->state](arg0);
}

void func_800B4BA0(struct VisualObj* self)
{
    s16 timer;
    s16 flags;
    s16 x;
    s8 type;
    struct PlayerObj* player = self->unk50;

    flags = self->unk42;
    type = player->unk15;
    self->unk42 = flags & 0x7FFF;
    self->on_screen = 1;
    self->unk15 = type;
    if (get_random() & 1) {
        func_80015D60(self, 0x15);
    } else {
        func_80015D60(self, 0x16);
    }
    type = self->unk2;
    switch (type) {
    case 0:
        x = player->x_pos.u.hi - 0x3C;
        goto set_position;
    case 1:
        x = player->x_pos.u.hi - 0x14;
        goto set_position;
    case 2:
        x = player->x_pos.u.hi + 0x14;
        goto set_position;
    case 3:
        x = player->x_pos.u.hi + 0x3C;
    set_position:
        self->x_pos.i.hi = x;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    }
    timer = get_random() & 0x1F;
    self->unk56 = timer;
    self->unk54 = 0x78 - timer;
    self->state++;
}

void func_800B4CC8(struct VisualObj* arg0)
{
    if (arg0->unk56 == 0) {
        arg0->state++;
    } else {
        arg0->unk56--;
    }
}

void func_800B4D00(struct VisualObj* self)
{
    s16 timer;
    s16 x;
    s8 type;
    struct PlayerObj* player = self->unk50;

    func_80015DC8(ANIMATED_OBJECT(self));
    type = self->unk2;
    switch (type) {
    case 0:
        x = player->x_pos.u.hi - 0x3C;
        goto set_position;
    case 1:
        x = player->x_pos.u.hi - 0x14;
        goto set_position;
    case 2:
        x = player->x_pos.u.hi + 0x14;
        goto set_position;
    case 3:
        x = player->x_pos.u.hi + 0x3C;
        goto set_position;
    }
    goto update_timer;
set_position:
    self->x_pos.i.hi = x;
    self->y_pos.i.hi = player->y_pos.u.hi - 9;
update_timer:
    timer = (u16)self->unk54 - 1;
    self->unk54 = timer;
    if (timer == 0 || player->active == 0) {
        self->state++;
    }
    func_8002B318(BASE_OBJECT(self), 0x30, 0x30);
}

void func_800B4E14(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A704[])(struct VisualObj*) = {
    func_800B4BA0,
    func_800B4CC8,
    func_800B4D00,
    func_800B4E14,
};
