// MiscObj, misc_object_update_funcs[6]
// 800C91B0..800C938C
#include "common.h"

void homing_point_update(struct MiscObj* self)
{
    homing_point_state_funcs[self->state](self);
}

// homing_point_init
INCLUDE_ASM("main/nonmatchings/misc/misc_06_homing_point", func_800C91EC);

void homing_point_wait(struct MiscObj* self)
{
    s8 timer = self->ext.misc_6.timer - 1;
    self->ext.misc_6.timer = timer;
    if (timer == 0) {
        self->state = 2;
    }
}

void homing_point_move(struct MiscObj* self)
{
    s16 x_center;
    s16 x_pos;
    s16 y_center;
    s16 y_pos;

    move_object(MOVING_OBJECT(self));

    x_center = self->ext.misc_6.saved_position.position.x;
    x_pos = self->x_pos.i.hi;
    if (x_pos >= x_center - 0x10) {
        if (x_pos <= x_center + 0x10) {
            y_center = self->ext.misc_6.saved_position.position.y;
            y_pos = self->y_pos.i.hi;
            if (y_pos >= y_center - 0x10) {
                if (y_pos <= y_center + 0x10) {
                    self->state = 3;
                }
            }
        }
    }

    update_on_screen(BASE_OBJECT(self), 0x140, 0x140);
}

void homing_point_despawn(struct MiscObj* self)
{
    self->ext.misc_6.saved_position.packed = 0;
    self->ext.misc_6.timer = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*homing_point_state_funcs[4])(struct MiscObj*) = {
    func_800C91EC,
    homing_point_wait,
    homing_point_move,
    homing_point_despawn,
};
