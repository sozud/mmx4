// ItemObj, item_object_update_funcs[23]
// 800C5C4C..800C6054
#include "common.h"

void laser_target_update(struct ItemObj* arg0)
{
    laser_target_state_funcs[arg0->state](arg0);
}

void laser_target_init(struct ItemObj* self)
{
    struct MainObj* owner;

    self->unk5 = 0;
    self->state = 1;
    self->on_screen = 1;
    owner = self->backref;
    self->unk7C.owner = owner;
    self->backref = NULL;
    self->unk16 = 2;
    self->ext.item_23.unk80 = 0x12C;
    self->ext.item_23.timer = 4;
    self->tail_ext.unk1.unk84.previous_value = 0;
    self->unk68 = &laser_target_terrain_box;
    self->unk2C = 0;
    self->unk28 = 0;
    set_velocity_from_angle(MOVING_OBJECT(self),
        angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
    self->x_vel.val *= 8;
    self->y_vel.val *= 8;
    set_animation(self, 0xA);
    func_8001540C(2, 0xC5, self);
}

void laser_target_track(struct ItemObj* arg0)
{
    u16 x_distance;
    u16 y_distance;

    if (arg0->ext.item_23.unk80 != 0) {
        if (--arg0->ext.item_23.timer == 0) {
            arg0->ext.item_23.timer = 1;
            x_distance = ABS(arg0->x_pos.i.hi, g_Player.x_pos.i.hi);
            y_distance = ABS(arg0->y_pos.i.hi, g_Player.y_pos.i.hi);
            set_velocity_from_angle(MOVING_OBJECT(arg0), (u8)angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)));
            if (x_distance > 16 || y_distance > 16) {
                arg0->x_vel.val *= 8;
                arg0->y_vel.val *= 8;
            } else if (x_distance > 8 || y_distance > 8) {
                arg0->x_vel.val *= 4;
                arg0->y_vel.val *= 4;
            } else if (x_distance > 4 || y_distance > 4) {
                arg0->x_vel.val *= 2;
                arg0->y_vel.val *= 2;
            } else if (x_distance > 2 || y_distance > 2) {
                arg0->x_vel.val *= 1;
                arg0->y_vel.val *= 1;
            } else {
                arg0->x_pos.val = g_Player.x_pos.val;
                arg0->y_pos.val = g_Player.y_pos.val;
            }
        }
        move_with_gravity(ANIMATED_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
    } else {
        arg0->unk5++;
        set_animation(arg0, 0xB);
    }
}

void laser_target_lock(struct ItemObj* arg0)
{
    arg0->unk5++;
    animate_object(arg0);
}

void laser_target_hold(struct ItemObj* arg0)
{
    animate_object(arg0);
}

void laser_target_fire(struct ItemObj* arg0)
{
    animate_object(arg0);
}

void laser_target_despawn(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

// laser_target_main
void func_800C5F90(struct ItemObj* self)
{
    struct MainObj* owner = self->unk7C.owner;

    if (owner->state != 1 || (owner->unk5 != 3 && owner->unk2 != 2)) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (owner->unk5 >= 4) {
        if (self->tail_ext.unk1.unk84.previous_value == 0) {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        return;
    }
    laser_target_step_funcs[self->unk5](self);
    laser_target_hold(self);
    is_on_screen(BASE_OBJECT(self));
}

struct Unk_unk68 laser_target_terrain_box = { 0, 0, 4, 4 };

void (*laser_target_state_funcs[])(struct ItemObj*) = {
    laser_target_init,
    func_800C5F90,
    laser_target_despawn,
};

void (*laser_target_step_funcs[])(struct ItemObj*) = {
    laser_target_track,
    laser_target_lock,
    laser_target_fire,
    laser_target_hold,
};
