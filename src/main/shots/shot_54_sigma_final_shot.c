// ShotObj, shot_object_update_funcs[54]
// 800ABE08..800AC8C4
#include "common.h"

// sigma_final_shot_init
INCLUDE_ASM("main/nonmatchings/shots/shot_54_sigma_final_shot", func_800ABE08);

void sigma_final_shot_fireball(struct ShotObj* self)
{
    s16 timer;

    timer = self->timer;
    if (timer != 0) {
        timer--;
        self->timer = timer;
        if (timer == 0) {
            self->y_vel.val = 0;
        }
    }
    move_object(MOVING_OBJECT(self));
    animate_object(self);
    update_on_screen(BASE_OBJECT(self), 0x28, 0x28);
}

void sigma_lightning_aim(struct ShotObj* self)
{
    if (--self->timer == 0) {
        self->unk6++;
        set_velocity_from_angle(MOVING_OBJECT(self),
            angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
        self->x_vel.val *= 4;
        self->y_vel.val *= 4;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void sigma_lightning_fly(struct ShotObj* self)
{
    s8 shot_type = 5;
    struct ShotObj* shot;

    if (self->unk70 & 0xF) {
        self->timer = 10;
        self->unk6++;
        if (self->unk70 & 0xC) {
            shot_type = 3;
        }
        func_8001540C(2, 2, self);
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x36;
            shot->unk2 = shot_type;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk7C = self->unk7C;
        }
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x36;
            shot->unk2 = shot_type + 1;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk7C = self->unk7C;
        }
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void sigma_lightning_fade(struct ShotObj* self)
{
    self->timer--;
    if (self->timer == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    animate_object(self);
}

void sigma_final_shot_lightning(struct ShotObj* self)
{
    sigma_lightning_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x28, 0x28);
}

void sigma_ice_fall(struct ShotObj* self)
{
    s32 x_vel;

    if (self->unk70 & 8) {
        if (get_random() & 1) {
            x_vel = FIXED(2);
        } else {
            x_vel = FIXED(-2);
        }
        self->x_vel.val = x_vel;
        self->y_vel.val = 0;
        self->unk28 = 0;
        self->unk2C = 0;
        self->timer = 0x20;
        self->unk6++;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(self);
}

void sigma_ice_slide(struct ShotObj* self)
{

    if (--self->timer == 0) {
        set_animation(self, 0x11);
        self->unk6++;
    }
    move_object(MOVING_OBJECT(self));
    animate_object(self);
}

void sigma_ice_melt(struct ShotObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    move_object(MOVING_OBJECT(self));
    animate_object(self);
}

void sigma_final_shot_ice(struct ShotObj* self)
{
    sigma_ice_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x28, 0x28);
}

void sigma_spike_extend(struct ShotObj* self)
{

    if (--self->timer == 0) {
        self->unk50.data = sigma_spike_box;
        self->timer = 0xD2;
        self->unk6++;
    }
    if (self->timer & 1) {
        update_on_screen(BASE_OBJECT(self), 0x28, 0x28);
    }
}

void sigma_spike_active(struct ShotObj* self)
{

    if (--self->timer == 0) {
        self->timer = 0x3C;
        self->unk50.data = NULL;
        self->unk6++;
    }
    update_on_screen(BASE_OBJECT(self), 0x28, 0x28);
}

void sigma_spike_retract(struct ShotObj* self)
{
    self->timer--;
    if (self->timer == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    if (self->timer & 1) {
        update_on_screen(BASE_OBJECT(self), 0x28, 0x28);
    }
}

void sigma_final_shot_spike(struct ShotObj* self)
{
    sigma_spike_funcs[self->unk6](self);
}

void sigma_final_shot_lightning_split(struct ShotObj* self)
{
    move_object((struct MovingObj*)self);
    animate_object(self);
    update_on_screen((struct BaseObj*)self, 0x28, 0x28);
}

void sigma_final_shot_resume(struct ShotObj* self)
{
    enemy_hit_reaction(self);
}

void sigma_final_shot_idle(struct ShotObj* self)
{
}

void sigma_final_shot_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        self->state = 2;
        self->unk5 = 0;
        spawn_explosion(self);
        return;
    }

    sigma_final_shot_step_funcs[self->unk5](self);
    CollisionRelated(self);
    func_8002D9BC(self);
    if (self->unk5 != 5 && func_8002B1E8(BASE_OBJECT(self), 0x28, 0x28) != 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void sigma_final_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void sigma_final_shot_update(struct ShotObj* self)
{
    if (self->unk7C->unk94 != 0) {
        self->state = 2;
        self->unk5 = 0;
    }
    self->on_screen = 0;
    sigma_final_shot_state_funcs[self->state](self);
}

u8 sigma_final_shot_at_position(struct ShotObj* self, s16 arg1, s16 arg2)
{
    s16 x;
    s16 y;

    x = self->x_pos.i.hi;
    if ((x - arg1 >= 0) ? (x - arg1 < 3) : (arg1 - x < 3)) {
        y = self->y_pos.i.hi;
        if ((y - arg2 >= 0) ? (y - arg2 < 3) : (arg2 - y < 3)) {
            return 1;
        }
    }
    return 0;
}

u8 sigma_final_shot_box_0[4] = { 0xF5, 0xFB, 9, 9 };

u8 sigma_final_shot_box_1[4] = { 0xF9, 0xF9, 0x0C, 0x0C };

u8 sigma_final_shot_box_2[4] = { 0xF6, 0xF8, 0x0E, 0x0E };

u8 sigma_final_shot_tall_box[4] = { 0xFC, 0xE7, 5, 0x35 };

u8 sigma_final_shot_wide_box[4] = { 0xE5, 0xFC, 0x35, 5 };

u8 sigma_spike_box[4] = { 0xF1, 0xFA, 0x15, 9 };

u8 sigma_final_shot_terrain_box_0[4] = { 0xFF, 0xFF, 6, 6 };

u8 sigma_final_shot_terrain_box_1[4] = { 0xFE, 0, 0x0B, 0x0C };

s16 sigma_final_shot_offsets[4] = { 2, 1, 0, -1 };

void (*sigma_lightning_funcs[3])(struct ShotObj*) = {
    sigma_lightning_aim,
    sigma_lightning_fly,
    sigma_lightning_fade,
};

void (*sigma_ice_funcs[3])(struct ShotObj*) = {
    sigma_ice_fall,
    sigma_ice_slide,
    sigma_ice_melt,
};

void (*sigma_spike_funcs[3])(struct ShotObj*) = {
    sigma_spike_extend,
    sigma_spike_active,
    sigma_spike_retract,
};

void (*sigma_final_shot_step_funcs[7])(struct ShotObj*) = {
    sigma_final_shot_resume,
    sigma_final_shot_idle,
    sigma_final_shot_fireball,
    sigma_final_shot_lightning,
    sigma_final_shot_ice,
    sigma_final_shot_spike,
    sigma_final_shot_lightning_split,
};

void (*sigma_final_shot_state_funcs[])(struct ShotObj*) = {
    func_800ABE08,
    sigma_final_shot_run,
    sigma_final_shot_despawn,
};
