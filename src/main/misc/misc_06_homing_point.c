// MiscObj, misc_object_update_funcs[6]
// 800C91B0..800C938C
#include "common.h"
#include "main/misc/misc_06_homing_point.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/55C4.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#endif

// homing_point_state_funcs
extern void (*homing_point_state_funcs[])(struct MiscObj*);

void homing_point_wait(struct MiscObj*);
void homing_point_move(struct MiscObj*);
void homing_point_despawn(struct MiscObj*);

void homing_point_update(struct MiscObj* self)
{
    homing_point_state_funcs[self->state](self);
}

// homing_point_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C91EC(struct MiscObj* arg0);
#endif

void func_800C91EC(struct MiscObj* arg0)
{
    set_animation(arg0, arg0->unk2 + 0x11);
    arg0->ext.misc_6.saved_position.position.x = arg0->x_pos.i.hi;
    arg0->ext.misc_6.saved_position.position.y = arg0->y_pos.i.hi;
    set_velocity_from_angle(MOVING_OBJECT(arg0), (arg0->unk2 * 4) & 0xFC);
    arg0->ext.misc_6.timer = 0x14;
    arg0->state = 1;
    arg0->x_pos.val += arg0->x_vel.val * 180;
    arg0->y_pos.val -= arg0->y_vel.val * 180;
    arg0->x_vel.val = -(arg0->x_vel.val * 4);
    arg0->y_vel.val = -(arg0->y_vel.val * 4);
}

void homing_point_wait(struct MiscObj* self)
{
    s8 timer = self->ext.misc_6.timer - 1;
    self->ext.misc_6.timer = timer;
    if (0 == timer) {
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

    x_pos = self->x_pos.i.hi;
    x_center = self->ext.misc_6.saved_position.position.x;
    if (x_pos >= x_center - 0x10) {
        if (x_pos <= x_center + 0x10) {
            y_pos = self->y_pos.i.hi;
            y_center = self->ext.misc_6.saved_position.position.y;
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
