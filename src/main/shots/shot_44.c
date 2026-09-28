// ShotObj, shot_object_update_funcs[44]
// 800A6FCC..800A7AF0
#include "common.h"

void iris_shot_update(struct ShotObj* self)
{
    iris_shot_state_funcs[self->state](self);
}

// iris_drone_init
INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A7008);

void iris_drone_run(struct ShotObj* self)
{
    u8 saved_unk61;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    iris_drone_funcs[self->unk5](self);
    if (self->unk7C->state >= 2) {
        func_800AF808(BASE_OBJECT(self));
        self->state = 2;
    }
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        func_800AF808(BASE_OBJECT(self));
        self->state = 2;
    }
    saved_unk61 = (u8)g_Player.invincibility_timer;
    g_Player.invincibility_timer = 0;
    if (func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) != 0) {
        g_Player.invincibility_timer = saved_unk61;
        func_800AF808(BASE_OBJECT(self));
        self->state = 2;
    } else {
        g_Player.invincibility_timer = saved_unk61;
    }
    func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
}

void iris_drone_despawn(struct ShotObj* self)
{
    MAIN_OBJECT(self->unk7C)->ext.main_66.drone_count--;
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void iris_laser_init(struct ShotObj* self)
{
    s16 x_pos;

    self->on_screen = 1;
    self->unk61 = 1;
    self->unk58.data = NULL;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk28 = 0;
    self->unk42 &= 0x7FFF;
    if (self->unk15 == 0) {
        x_pos = self->x_pos.i.hi - 0xA5;
    } else {
        x_pos = self->x_pos.i.hi + 0xA5;
    }
    self->x_pos.i.hi = x_pos;
    self->y_pos.i.hi -= 5;
    if (self->unk2 == 0) {
        self->unk16 = 0;
    } else {
        self->unk16 = 1;
    }
    self->timer = 0x3C;
    self->unk5C = 1;
    self->unk68 = NULL;
    self->unk54 = NULL;
    self->unk50.data = NULL;
    self->unk60 = 8;
    func_80015D60(self, self->unk2 + 0x17);
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
    func_8002B318(BASE_OBJECT(self), 0x200, 0x200);
}

void iris_laser_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

// iris_pillar_init
INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A73C4);

void iris_pillar_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    iris_pillar_funcs[self->unk5](self);
    if (self->unk7C->state >= 2) {
        self->state = 8;
    }
    func_8002D9BC(self);
    func_8002B318(BASE_OBJECT(self), 0x100, 0x100);
}

void iris_pillar_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void iris_drone_launch(struct ShotObj* self)
{
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->timer == 0) {
        self->unk5 = 1;
        self->unk28 = -(self->x_vel.val >> 4);
        self->unk2C = self->y_vel.val >> 4;
    }
}

void iris_drone_brake(struct ShotObj* self)
{
    iris_drone_move(self);
    func_80015DC8(ANIMATED_OBJECT(self));

    if (abs(self->x_vel.val) <= 0xFFFF) {
        if (abs(self->y_vel.val) <= 0xFFFF) {
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
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(self));
    temp_v0 = self->timer - 1;
    self->timer = temp_v0;
    if (temp_v0 == 0) {
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
INCLUDE_ASM("main/nonmatchings/shots/shot_44", func_800A766C);

void iris_drone_burst(struct ShotObj* self)
{
    func_80015DC8(self);
    if (self->animation_step.fields.event != 0) {
        func_80015D60(self, 0xF);
        self->unk5 = 5;
    }
}

void iris_drone_explode(struct ShotObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 2) {
        self->unk50.data = D_801099DC;
    }

    if (self->animation_step.fields.event == 1) {
        self->state = 2;
    }
}

void iris_laser_charge(struct ShotObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->timer == 0) {
        func_8001540C(2, 0xE3, self);
        func_80015D60(self, self->unk2 * 4 + 0x19);
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
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk50.data = D_801099E0;
    }
    temp_v0 = self->timer - 1;
    self->timer = temp_v0;
    if (temp_v0 == 0) {
        self->unk50.data = NULL;
        func_80015D60(self, (self->unk2 * 4) + 0x1A);
        self->unk5 = 2;
    }
}

void iris_laser_end(struct ShotObj* self)
{
    func_80015DC8(self);
    if (self->animation_step.fields.event != 0) {
        self->state = 5;
    }
}

void iris_pillar_fire(struct ShotObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk50.data = D_801099E4;
    }
    if (--self->timer == 0) {
        self->unk50.data = NULL;
        func_80015D60(self, 0x1C);
        self->unk5 = 1;
    }
}

void iris_pillar_end(struct ShotObj* self)
{
    func_80015DC8(self);
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

u8 D_801099D4[4] = { 0xFA, 0xFC, 0x0A, 0x07 };

u8 D_801099D8[4] = { 0xF6, 0xF9, 0x12, 0x0E };

u8 D_801099DC[4] = { 0xEE, 0xEB, 0x28, 0x2B };

u8 D_801099E0[4] = { 0x88, 0xEE, 0xE5, 0x22 };

u8 D_801099E4[4] = { 0xEE, 0x85, 0x22, 0xF5 };

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
