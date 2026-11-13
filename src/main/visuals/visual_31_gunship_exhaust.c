// VisualObj, visual_object_update_funcs[31]
// 800B4B64..800B4E34
#include "common.h"
#include "main/visuals/visual_31_gunship_exhaust.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/objects.h"

// gunship_exhaust_state_funcs
extern void (*gunship_exhaust_state_funcs[])(struct VisualObj*);
void gunship_exhaust_init(struct VisualObj*);
void gunship_exhaust_delay(struct VisualObj*);

void gunship_exhaust_despawn(struct VisualObj*);
#include "weapon_resources.h"

void gunship_exhaust_update(struct VisualObj* arg0)
{
    gunship_exhaust_state_funcs[arg0->state](arg0);
}

void gunship_exhaust_init(struct VisualObj* self)
{
    s16 timer;
    struct PlayerObj* player = self->unk50;

    self->unk15 = player->unk15;
    self->unk42 = self->unk42 & 0x7FFF;
    self->on_screen = 1;
    if (get_random() & 1) {
        set_animation(self, 0x15);
    } else {
        set_animation(self, 0x16);
    }
    switch (self->unk2) {
    case 0:
        self->x_pos.i.hi = player->x_pos.u.hi - 0x3C;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    case 1:
        self->x_pos.i.hi = player->x_pos.u.hi - 0x14;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    case 2:
        self->x_pos.i.hi = player->x_pos.u.hi + 0x14;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    case 3:
        self->x_pos.i.hi = player->x_pos.u.hi + 0x3C;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    }
    timer = get_random() & 0x1F;
    self->unk56 = timer;
    self->unk54 = 0x78 - timer;
    self->state++;
}

void gunship_exhaust_delay(struct VisualObj* arg0)
{
    if (arg0->unk56 == 0) {
        arg0->state++;
    } else {
        arg0->unk56--;
    }
}

void gunship_exhaust_main(struct VisualObj* self)
{
    struct PlayerObj* player;

    player = self->unk50;

    animate_object(ANIMATED_OBJECT(self));
    switch (self->unk2) {
    case 0:
        self->x_pos.i.hi = player->x_pos.u.hi - 0x3C;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    case 1:
        self->x_pos.i.hi = player->x_pos.u.hi - 0x14;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    case 2:
        self->x_pos.i.hi = player->x_pos.u.hi + 0x14;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    case 3:
        self->x_pos.i.hi = player->x_pos.u.hi + 0x3C;
        self->y_pos.i.hi = player->y_pos.u.hi - 9;
        break;
    }
    if (--self->unk54 == 0 || player->active == 0) {
        self->state++;
    }
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
}

void gunship_exhaust_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*gunship_exhaust_state_funcs[])(struct VisualObj*) = {
    gunship_exhaust_init,
    gunship_exhaust_delay,
    gunship_exhaust_main,
    gunship_exhaust_despawn,
};
