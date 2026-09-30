// ShotObj, shot_object_update_funcs[44]
// 800A6FCC..800A7AF0
#include "common.h"

void iris_shot_update(struct ShotObj* self)
{
    iris_shot_state_funcs[self->state](self);
}

// iris_drone_init
INCLUDE_ASM("main/nonmatchings/shots/shot_44_iris_shot", func_800A7008);

void iris_drone_run(struct ShotObj* self)
{
    u8 saved_unk61;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    iris_drone_funcs[self->unk5](self);
    if (self->unk7C->state >= 2) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
    }
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
    }
    saved_unk61 = (u8)g_Player.invincibility_timer;
    g_Player.invincibility_timer = 0;
    if (func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) != 0) {
        g_Player.invincibility_timer = saved_unk61;
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
    } else {
        g_Player.invincibility_timer = saved_unk61;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void iris_drone_despawn(struct ShotObj* self)
{
    MAIN_OBJECT(self->unk7C)->ext.main_66.drone_count--;
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void iris_laser_init(struct ShotObj* self)
{
    self->on_screen = 1;
    self->unk58.data = NULL;
    self->unk61 = 1;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk28 = 0;
    self->unk42 &= 0x7FFF;
    if (self->unk15 == 0) {
        self->x_pos.i.hi = self->x_pos.i.hi - 0xA5;
    } else {
        self->x_pos.i.hi = self->x_pos.i.hi + 0xA5;
    }
    self->y_pos.i.hi -= 5;
    if (self->unk2 == 0) {
        self->unk16 = 0;
    } else {
        self->unk16 = 1;
    }
    self->timer = 0x3C;
    self->unk68 = NULL;
    self->unk54 = NULL;
    self->unk50.data = NULL;
    self->unk5C = 1;
    self->unk60 = 8;
    set_animation(self, self->unk2 + 0x17);
    self->state = 4;
    self->unk5 = 0;
}

void iris_laser_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    iris_laser_funcs[self->unk5](self);
    if (self->unk7C->state >= 2) {
        self->state = 5;
    }
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x200, 0x200);
}

void iris_laser_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

// iris_pillar_init
INCLUDE_ASM("main/nonmatchings/shots/shot_44_iris_shot", func_800A73C4);

void iris_pillar_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    iris_pillar_funcs[self->unk5](self);
    if (self->unk7C->state >= 2) {
        self->state = 8;
    }
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}

void iris_pillar_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void iris_drone_launch(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (--self->timer == 0) {
        self->unk28 = -(self->x_vel.val >> 4);
        self->unk2C = self->y_vel.val >> 4;
        self->unk5 = 1;
    }
}

void iris_drone_brake(struct ShotObj* self)
{
    iris_drone_move(self);
    animate_object(ANIMATED_OBJECT(self));

    if (abs(self->x_vel.val) < 0x10000) {
        if (abs(self->y_vel.val) < 0x10000) {
            self->unk5 = 2;
            self->unk61 = 0;
            self->x_vel.val = 0;
            self->y_vel.val = 0;
            self->unk28 = 0;
            self->unk2C = 0;
            self->timer = 0x3C;
        }
    }
}

void iris_drone_hover(struct ShotObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->timer == 0) {
        self->unk5 = 3;
        if (self->unk2 == 0) {
            self->timer = 0x78;
        } else {
            self->timer = 0xB4;
        }
        self->unk8A = 0x1E0;
    }
}

// iris_drone_chase
INCLUDE_ASM("main/nonmatchings/shots/shot_44_iris_shot", func_800A766C);

void iris_drone_burst(struct ShotObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 0xF);
        self->unk5 = 5;
    }
}

void iris_drone_explode(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 2) {
        self->unk50.data = iris_drone_explode_box;
    }

    if (self->animation_step.fields.event == 1) {
        self->state = 2;
    }
}

void iris_laser_charge(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->timer == 0) {
        func_8001540C(2, 0xE3, self);
        set_animation(self, self->unk2 * 4 + 0x19);
        if (self->unk2 != 0) {
            if (self->unk15 == 0) {
                self->x_pos.i.hi -= 0xC1;
            } else {
                self->x_pos.i.hi += 0xC1;
            }
        }
        self->timer = 0x78;
        self->unk5 = 1;
    }
}

void iris_laser_fire(struct ShotObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk50.data = iris_laser_box;
    }
    if (--self->timer == 0) {
        self->unk50.data = NULL;
        set_animation(self, (self->unk2 * 4) + 0x1A);
        self->unk5 = 2;
    }
}

void iris_laser_end(struct ShotObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        self->state = 5;
    }
}

void iris_pillar_fire(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk50.data = iris_pillar_box;
    }
    if (--self->timer == 0) {
        self->unk50.data = NULL;
        set_animation(self, 0x1C);
        self->unk5 = 1;
    }
}

void iris_pillar_end(struct ShotObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        self->state = 8;
    }
}

void iris_drone_move(struct ShotObj* self)
{
    self->x_pos.val += self->x_vel.val;
    self->y_pos.val -= self->y_vel.val;
    self->x_vel.val += self->unk28;
    self->y_vel.val -= self->unk2C;
    if (self->y_vel.val < FIXED(-6.5)) {
        self->y_vel.val = FIXED(-6.5);
    }
}

u8 iris_drone_attack_box[4] = { 0xFA, 0xFC, 0x0A, 0x07 };

u8 iris_drone_hurt_box[4] = { 0xF6, 0xF9, 0x12, 0x0E };

u8 iris_drone_explode_box[4] = { 0xEE, 0xEB, 0x28, 0x2B };

u8 iris_laser_box[4] = { 0x88, 0xEE, 0xE5, 0x22 };

u8 iris_pillar_box[4] = { 0xEE, 0x85, 0x22, 0xF5 };

void (*iris_shot_state_funcs[])(struct ShotObj*) = {
    func_800A7008,
    iris_drone_run,
    iris_drone_despawn,
    iris_laser_init,
    iris_laser_run,
    iris_laser_despawn,
    func_800A73C4,
    iris_pillar_run,
    iris_pillar_despawn,
};

void (*iris_drone_funcs[])(struct ShotObj*) = {
    iris_drone_launch,
    iris_drone_brake,
    iris_drone_hover,
    func_800A766C,
    iris_drone_burst,
    iris_drone_explode,
};

void (*iris_laser_funcs[])(struct ShotObj*) = {
    iris_laser_charge,
    iris_laser_fire,
    iris_laser_end,
};

void (*iris_pillar_funcs[])(struct ShotObj*) = {
    iris_pillar_fire,
    iris_pillar_end,
};
