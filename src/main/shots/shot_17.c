// ShotObj, shot_object_update_funcs[17]
// 8009C5F0..8009CAC0
#include "common.h"

u8 depth_charge_sink_box[4] = { 0xFB, 0xFB, 0x08, 0x09 };
u8 depth_charge_boxes[8] = { 0xFF, 0xFF, 0x04, 0x05, 0xF8, 0xF6, 0x0E, 0x0E };

void depth_charge_update(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    depth_charge_state_funcs[self->state](self);
}

// depth_charge_init
INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C638);

// depth_charge_launch
INCLUDE_ASM("main/nonmatchings/shots/shot_17", func_8009C784);

void depth_charge_fall(struct ShotObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    if ((u32)(self->x_pos.u.hi - 0x1721) >= 0xFF) {
        self->x_vel.val = 0;
        self->y_vel.val = FIXED(-2);
    }
    if (self->y_pos.i.hi - background_objects[self->bg_offset].y_pos.i.hi >= 0xAC && self->y_vel.val < 0) {
        set_animation(self, 6);
        self->unk60 = 4;
        self->unk50.data = depth_charge_sink_box;
        self->unk5 = (u8)self->unk5 + 1;
        self->y_pos.val = (background_objects[self->bg_offset].y_pos.i.hi + 0xAC) << 16;
        self->y_vel.val = FIXED(0.5);
        self->x_vel.val = 0;
    }
}

void depth_charge_sink(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 0;
        self->state++;
        spawn_explosion(BASE_OBJECT(self));
    }
}

void depth_charge_idle(struct ShotObj* self)
{
}

void depth_charge_hit(struct ShotObj* self)
{
    enemy_hit_reaction(self);
}

void depth_charge_main(struct ShotObj* self)
{
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        self->unk5 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        spawn_explosion(BASE_OBJECT(self));
        return;
    }

    depth_charge_step_funcs[self->unk5](self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }

    ZeroObjectState(OBJECT_HEADER(self));
}

void depth_charge_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*depth_charge_state_funcs[])(struct ShotObj*) = {
    func_8009C638,
    depth_charge_main,
    depth_charge_despawn,
};

void (*depth_charge_step_funcs[])(struct ShotObj*) = {
    depth_charge_hit,
    depth_charge_idle,
    func_8009C784,
    depth_charge_fall,
    depth_charge_sink,
};

u8 aimed_bullet_hit_box[4] = { 0xFC, 0xFD, 0x06, 0x05 };
