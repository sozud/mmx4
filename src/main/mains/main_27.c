// MainObj, main_object_update_funcs[27]
// 800586F0..80059C48
#include "common.h"
#include "func_tables.h"

void dash_gunner_update(struct MainObj* self)
{
    dash_gunner_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// dash_gunner_init
INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80058740);

// dash_gunner_main
INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80058AC8);

void dash_gunner_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->state = 3;
    } else if (--self->unk7E == 0) {
        self->unk7E = 6;
        func_800AF878(self, 1, 16, 16);
    }
}

void dash_gunner_despawn(struct MainObj* self)
{
    self->unk7A = 0;
    self->ext.raw[0] = 0;
    self->ext.raw[1] = 0;
    self->ext.raw[2] = 0;
    self->ext.raw[3] = 0;
    self->ext.raw[5] = 0;
    despawn_object(OBJECT_HEADER(self));
}

void dash_gunner_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_27.saved_unk5;
}

void dash_gunner_run(struct MainObj* self)
{
    dash_gunner_run_funcs[self->unk6](self);
}

void dash_gunner_run_move(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_27.unk8C == 0) {
        set_animation(self, 3);
        self->x_speed = 0;
        stop_sound(2, 0x51);
        self->unk5 = 5;
        self->unk6 = 0;
        return;
    }
    if (self->ext.main_27.unk90 != 0 && --self->ext.main_27.unk91 == 0) {
        if (self->ext.main_27.unk90 == 2) {
            self->ext.main_27.unk91 = 0x30;
            if (--self->ext.main_27.unk92 == 0) {
                self->ext.main_27.unk92 = 2;
                set_animation(self, 3);
                self->x_speed = 0;
                stop_sound(2, 0x51);
                self->unk5 = 5;
                self->unk6 = 0;
                return;
            }
        } else {
            self->ext.main_27.unk91 = 0x60;
        }
        self->unk7C = 0x14;
        self->y_speed = 0;
        self->unk5 = 4;
        self->unk6 = 0;
    }
    if (self->unk15 == 0 ? (self->collision_flags & 2) : (self->collision_flags & 1)) {
        self->unk7C = 0x14;
        self->y_speed = 0;
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

void dash_gunner_wait_for_player(struct MainObj* self)
{
    s8 next_state;

    if ((g_Player.x_pos.i.hi - self->x_pos.i.hi) >= 0xBD) {
        func_8001540C(2, 0x51, self);
        self->unk7A = 0;
        if (self->ext.main_27.unk80 == 0) {
            next_state = 2;
        } else {
            self->unk7C = 1;
            next_state = 7;
        }
        self->unk5 = next_state;
        self->unk6 = 0;
    }
}

void dash_gunner_turn(struct MainObj* self)
{
    dash_gunner_turn_funcs[self->unk6](self);
}

void dash_gunner_turn_brake(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed == 0) {
        self->x_accel = 0;
    }
    if (--self->unk7C == 0) {
        set_animation(self, 2);
        self->unk6 = 1;
    }
}

void dash_gunner_turn_flip(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk15 ^= 0x40;
        set_animation(self, 1);
        self->unk7C = 0x14;
        if (self->ext.main_27.unk8A == 0) {
            self->unk6 = 2;
        } else {
            if (self->unk15 == 0) {
                self->x_speed = FIXED(-4);
            } else {
                self->x_speed = FIXED(4);
            }
            set_animation(self, 7);
            self->unk5 = 7;
            self->unk6 = 1;
        }
    }
}

// dash_gunner_turn_end
INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059154);

void dash_gunner_shoot(struct MainObj* self)
{
    dash_gunner_shoot_funcs[self->unk6](self);
}

void dash_gunner_shoot_raise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_27.unk8B = 1;
    }
    if (self->animation_step.fields.event == 1) {
        self->unk7C = 4;
        self->unk7E = 0x1E;
        self->unk6 = 1;
    }
}

void dash_gunner_shoot_aim(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        if (self->unk15 == 0) {
            self->x_pos.u.hi -= 6;
        } else {
            self->x_pos.u.hi += 6;
        }
        self->ext.main_27.collision_direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
        if (self->unk15 == 0) {
            self->x_pos.u.hi += 6;
        } else {
            self->x_pos.u.hi -= 6;
        }
        self->unk6 = 2;
    }
}

void dash_gunner_shoot_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    u8 direction;

    animate_object(ANIMATED_OBJECT(self));
    direction = self->ext.main_27.collision_direction;
    if ((u32)(direction - 9) < 0xF) {
        if (self->unk15 != 0) {
            self->unk7C = 0xA;
            self->unk6 = 3;
        }
    } else if ((u32)(direction - 8) >= 0x11 && self->unk15 == 0) {
        self->unk7C = 0xA;
        self->unk6 = 3;
    }
    if (self->unk6 == 3) {
        return;
    }
    set_animation(self, 4);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0xE;
        shot->unk2 = self->unk2;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        set_velocity_from_angle(MOVING_OBJECT(shot), self->ext.main_27.collision_direction);
        shot->state = 0;
        shot->x_vel.val *= 3;
        shot->y_vel.val *= 3;
    }
    if (--self->unk7C == 0) {
        self->unk7C = 0xA;
        self->unk6 = 3;
    } else {
        self->unk7E = 0x14;
        self->unk6 = 1;
    }
}

void dash_gunner_shoot_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 6);
        self->unk6 = 4;
    }
}

void dash_gunner_shoot_lower(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_27.unk8B = 0;
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 1);
        self->unk7C = 10;
        self->unk6 = 5;
    }
}

// dash_gunner_shoot_end
INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059590);

// dash_gunner_hop
INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059640);

void dash_gunner_dash(struct MainObj* self)
{
    dash_gunner_dash_funcs[self->unk6](self);
}

void dash_gunner_dash_start(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer != 0) {
        return;
    }

    self->ext.main_27.unk8A = 1;
    if (self->unk15 == 0) {
        if (g_Player.x_pos.i.hi > self->x_pos.i.hi) {
            goto action;
        }
        goto common;
    }
    if (g_Player.x_pos.i.hi < self->x_pos.i.hi) {
        goto action;
    }
    goto common;

action:
    set_animation(self, 2);
    self->unk5 = 4;
    self->unk6 = 1;
    self->unk7C = 1;
    return;

common:
    self->unk7C = 0x14;
    self->unk6 = 1;
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-4);
    } else {
        self->x_speed = FIXED(4);
    }
}

void dash_gunner_dash_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->ext.main_27.unk8C != 1) {
        self->ext.main_27.unk8C--;
    }
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        self->x_accel = FIXED(-0.125);
        self->unk6 = 2;
    }
}

void dash_gunner_dash_brake(struct MainObj* self)
{
    if (self->ext.main_27.unk8C != 1) {
        self->ext.main_27.unk8C--;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed == 0) {
        self->unk7C = 10;
        self->x_accel = 0;
        self->x_speed = 0;
        self->ext.main_27.unk88 = 0;
        self->unk6 = 3;
    }
}

void dash_gunner_dash_end(struct MainObj* self)
{
    s16 timer;

    if (self->ext.main_27.unk8C != 1) {
        self->ext.main_27.unk8C--;
    }
    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->ext.main_27.unk89 = 0;
        self->ext.main_27.unk8A = 0;
        if (self->unk15 == 0) {
            if (g_Player.x_pos.i.hi > self->x_pos.i.hi) {
                timer = 0x14;
                self->unk7C = timer;
                timer = 4;
                self->x_accel = 0;
                self->y_speed = 0;
            } else {
                timer = 6;
            }
        } else if (g_Player.x_pos.i.hi < self->x_pos.i.hi) {
            timer = 0x14;
            self->unk7C = timer;
            timer = 4;
            self->x_accel = 0;
            self->y_speed = 0;
        } else {
            timer = 6;
        }
        self->unk5 = timer;
        self->unk6 = 0;
    }
}

struct Unk_unk68 dash_gunner_boxes[10] = {
    { -17, -16, 10, 34 },
    { -21, -26, 42, 16 },
    { -8, -2, 33, 6 },
    { -8, -7, 34, 16 },
    { 0, 7, 25, 23 },
    { -24, -27, 17, 54 },
    { -42, -33, 80, 17 },
    { -15, -2, 39, 6 },
    { -15, -7, 40, 16 },
    { 0, 7, 32, 39 },
};

union AnimationStep dash_gunner_anim_0[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03FD0003 },
};

union AnimationStep dash_gunner_anim_1[] = {
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A010003 },
    { 0x0BF90103 },
};

union AnimationStep dash_gunner_anim_2[] = {
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010001 },
    { 0x11000101 },
};

union AnimationStep dash_gunner_anim_3[] = {
    { 0x12010002 },
    { 0x13010006 },
    { 0x14010003 },
    { 0x15010003 },
    { 0x16010004 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010202 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010009 },
    { 0x1A000101 },
};

union AnimationStep dash_gunner_anim_4[] = {
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1A000101 },
};

union AnimationStep dash_gunner_anim_5[] = {
    { 0x1F010003 },
    { 0x20010003 },
    { 0x21010003 },
    { 0x22010003 },
    { 0x23010003 },
    { 0x24FB0003 },
};

union AnimationStep dash_gunner_anim_6[] = {
    { 0x1A010006 },
    { 0x17010002 },
    { 0x16010202 },
    { 0x25010002 },
    { 0x16010004 },
    { 0x15010003 },
    { 0x14010003 },
    { 0x13010006 },
    { 0x12010002 },
    { 0x26010002 },
    { 0x27010001 },
    { 0x27000101 },
};

union AnimationStep dash_gunner_anim_7[] = {
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29010001 },
    { 0x2A010001 },
    { 0x2B010002 },
    { 0x2C010002 },
    { 0x2D010001 },
    { 0x2E010001 },
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010001 },
    { 0x36010002 },
    { 0x37F10002 },
};

union AnimationStep dash_gunner_anim_8[] = {
    { 0x38000101 },
};

union AnimationStep dash_gunner_anim_9[] = {
    { 0x39000101 },
};

union AnimationStep dash_gunner_anim_10[] = {
    { 0x3A000101 },
};

union AnimationStep dash_gunner_anim_11[] = {
    { 0x3B000101 },
};

union AnimationStep* dash_gunner_animations[] = {
    dash_gunner_anim_0,
    dash_gunner_anim_1,
    dash_gunner_anim_2,
    dash_gunner_anim_3,
    dash_gunner_anim_4,
    dash_gunner_anim_5,
    dash_gunner_anim_6,
    dash_gunner_anim_7,
    dash_gunner_anim_8,
    dash_gunner_anim_9,
    dash_gunner_anim_10,
    dash_gunner_anim_11,
};

u8 dash_gunner_debris[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
};

void (*dash_gunner_state_funcs[])() = {
    func_80058740,
    func_80058AC8,
    dash_gunner_explode,
    dash_gunner_despawn,
};

void (*dash_gunner_step_funcs[])() = {
    enemy_hit_reaction,
    dash_gunner_resume_step,
    dash_gunner_run,
    dash_gunner_wait_for_player,
    dash_gunner_turn,
    dash_gunner_shoot,
    func_80059640,
    dash_gunner_dash,
};

void (*dash_gunner_run_funcs[])() = {
    dash_gunner_run_move,
};

void (*dash_gunner_turn_funcs[])(struct MainObj*) = {
    dash_gunner_turn_brake,
    dash_gunner_turn_flip,
    func_80059154,
};

void (*dash_gunner_shoot_funcs[])(struct MainObj*) = {
    dash_gunner_shoot_raise,
    dash_gunner_shoot_aim,
    dash_gunner_shoot_fire,
    dash_gunner_shoot_wait,
    dash_gunner_shoot_lower,
    func_80059590,
};

void (*dash_gunner_dash_funcs[])() = {
    dash_gunner_dash_start,
    dash_gunner_dash_move,
    dash_gunner_dash_brake,
    dash_gunner_dash_end,
};
