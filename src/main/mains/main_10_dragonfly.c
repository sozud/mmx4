// MainObj, main_object_update_funcs[10]
// 800498C8..8004A718
#include "common.h"

void dragonfly_update(struct MainObj* self)
{
    dragonfly_state_funcs[self->state](self);
}

void dragonfly_init(struct MainObj* self)
{
    self->hp = 6;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->collision_data = D_80106770;
    self->bg_offset = g_Player.bg_offset;
    self->unk16 = 6;
    self->animation_table = dragonfly_animations;
    self->terrain_box = &dragonfly_terrain_box;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->hurt_box = dragonfly_body_boxes;
    self->attack_box = dragonfly_body_boxes;
    self->unk62 = 0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    set_animation(self, 0);

    switch (self->unk2) {
    case 0:
        if (self->x_pos.val > g_Player.x_pos.val) {
            self->unk15 = 0;
        } else {
            self->unk15 = 0x40;
        }
        self->ext.main_10.hold_state = 1;
        self->ext.main_10.can_grab = 1;
        break;
    case 1:
        self->unk7A = 1;
        self->unk15 = 0x40;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 1;
        break;
    case 2:
        self->unk7A = 1;
        self->unk15 = 0;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 1;
        break;
    case 3:
    case 4:
    case 9:
    case 10:
        self->unk7A = 1;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 0;
        break;
    case 5:
    case 6:
    case 11:
    case 12:
        self->unk7A = 1;
        self->gravity = -0x600;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 0;
        break;
    case 7:
    case 8:
    case 13:
    case 14:
        self->unk7A = 1;
        self->gravity = 0x600;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 0;
        break;
    }
    self->unk7C = 1;
    self->state = 1;
    self->ext.main_10.turn_delay = 0;
    self->unk5 = 2;
    self->unk6 = 0;
}

void dragonfly_run(struct MainObj* self)
{
    s32 hit;
    s8* held;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    dragonfly_step_funcs[self->unk5](self);
    if (self->ext.main_10.hold_state != 0) {
        if (self->ext.main_10.can_grab != 0) {
            held = &g_Player.stun_timer;
            if ((*held == 0) && (func_8002D9BC(self) != 0) && (*held != 0)) {
                g_Player.hit_facing = self->unk15;
                self->ext.main_10.hold_state = 3;
            }
        }
        self->ext.main_10.saved_unk5 = self->unk5;
        hit = func_8002DD04(self);
        if (hit < 0) {
            spawn_explosion(self);
            spawn_debris(6, &dragonfly_debris, self);
            drop_item(self, 0x11);
            self->state = 2;
        } else if (func_8002B1E8(self, 0x40, 0x40) == 0) {
            update_on_screen(self, 0x20, 0x20);
            if (--self->unk7C == 0) {
                func_8001540C(2, 0xD, self);
                self->unk7C = 0x3C;
            }
        } else {
            self->state = 2;
        }
    }
}

void dragonfly_finish(struct MainObj* self)
{
    self->unk7A = 0;
    self->unk62 = 0;
    stop_sound(2, 0xD);
    if (self->ext.main_10.hold_state == 3) {
        g_Player.stun_timer = 0;
    }
    self->ext.main_10.timer = 0;
    self->ext.main_10.turn_delay = 0;
    self->ext.main_10.struggle = 0;
    self->ext.main_10.hold_state = 0;
    self->ext.main_10.can_grab = 0;
    self->ext.main_10.saved_unk5 = 0;
    self->state = 3;
}

void dragonfly_despawn(struct MainObj* self)
{
    if (self->unk2 < 3) {
        despawn_object(OBJECT_HEADER(self));
        return;
    }
    despawn_object_permanently(OBJECT_HEADER(self));
}

void dragonfly_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_10.saved_unk5;
}

void dragonfly_wait(struct MainObj* self)
{
    switch (self->unk2) {
    case 0:
        self->unk7A = 0;
        self->unk5 = 3;
        break;
    case 1:
        if (g_Player.x_pos.i.hi - self->x_pos.i.hi >= 0xC1) {
            self->ext.main_10.hold_state = 1;
            self->unk7A = 0;
            self->unk5 = 3;
        }
        break;
    case 2:
        if (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0xC1) {
            self->ext.main_10.hold_state = 1;
            self->unk7A = 0;
            self->unk5 = 3;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0xC0) {
            self->unk7A = 0;
            self->ext.main_10.hold_state = 1;
            self->unk15 = 0x40;
            if (!(self->unk2 & 1)) {
                self->x_speed = FIXED(8);
            } else {
                self->x_speed = FIXED(6);
            }
            self->unk5 = 6;
        }
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        self->unk7A = 0;
        self->unk15 = 0;
        self->ext.main_10.hold_state = 1;
        if (!(self->unk2 & 1)) {
            self->x_speed = FIXED(-8);
        } else {
            self->x_speed = FIXED(-6);
        }
        self->unk5 = 6;
    }
}

void dragonfly_hunt(struct MainObj* self)
{
    dragonfly_hunt_funcs[self->unk6](self);
}

void dragonfly_hunt_start(struct MainObj* self)
{
    s32 velocity = self->unk15;
    if (velocity == 0) {
        velocity = FIXED(-4);
        self->x_speed = velocity;
        self->ext.main_10.timer = 0xB4;
        self->unk6 = 1;
        animate_object(ANIMATED_OBJECT(self));
    } else {
        velocity = FIXED(4);
        self->x_speed = velocity;
        self->ext.main_10.timer = 0xB4;
        self->unk6 = 1;
        animate_object(ANIMATED_OBJECT(self));
    }
}
// dragonfly_hunt_fly
INCLUDE_ASM("main/nonmatchings/mains/main_10_dragonfly", func_80049E68);

void dragonfly_hunt_hover(struct MainObj* self)
{
    if (self->ext.main_10.turn_delay == 0) {
        dragonfly_face_player(self);
    } else {
        self->ext.main_10.turn_delay--;
    }

    if (--self->ext.main_10.timer == 0) {
        if (get_random() & 1) {
            dragonfly_face_player(self);
            set_animation(self, 1);
            self->unk5 = 4;
            self->unk6 = 0;
            return;
        }

        if (self->y_pos.i.hi > g_Player.y_pos.i.hi - 0x18) {
            self->y_speed = FIXED(3);
        } else {
            self->y_speed = FIXED(-3);
        }
        self->unk6 = 3;
    }

    animate_object(self);
}

void dragonfly_hunt_close(struct MainObj* self)
{
    move_object((struct MovingObj*)self);
    if (self->ext.main_10.turn_delay == 0) {
        dragonfly_face_player(self);
    } else {
        self->ext.main_10.turn_delay--;
    }
    if (self->y_speed < 0
            ? (g_Player.y_pos.i.hi - 0x18) < self->y_pos.i.hi
            : self->x_pos.i.hi < (g_Player.x_pos.i.hi - 0x18)) {
        dragonfly_face_player(self);
        set_animation(self, 1);
        self->unk5 = 4;
        self->unk6 = 0;
    }
    animate_object(self);
}

void dragonfly_carry(struct MainObj* self)
{
    dragonfly_carry_funcs[self->unk6](self);
    CollisionRelated((struct PlayerObj*)self);
}

void dragonfly_carry_grab(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        dragonfly_face_player(self);
        self->attack_box = dragonfly_grab_box;
        self->unk62 = 3;
        self->contact_damage = 0;
        set_animation(self, 2);
        self->unk6 = 1;
        self->ext.main_10.timer = 0xB4;
        return;
    }

    animate_object(self);
}

// dragonfly_carry_hold
INCLUDE_ASM("main/nonmatchings/mains/main_10_dragonfly", func_8004A178);

void dragonfly_carry_lift(struct MainObj* self)
{
    dragonfly_hold_player(self);
    if (self->animation_step.fields.event != 0) {
        self->y_speed = FIXED(1.5);
        self->ext.main_10.timer = 0x32;
        self->ext.main_10.struggle = 0;
        self->unk6 = 3;
    }
    animate_object(ANIMATED_OBJECT(self));
}
void dragonfly_carry_rise(struct MainObj* self)
{
    u32 timer;

    dragonfly_hold_player(self);
    self->ext.main_10.struggle += func_8002BAA4();
    if (self->ext.main_10.struggle >= 0x15) {
        g_Player.stun_timer = 0;
        self->attack_box = dragonfly_body_boxes;
        self->unk62 = 0;
        set_animation(self, 5);
        self->y_speed = 0x20000;
        self->attack_box = NULL;
        self->unk5 = 5;
        self->unk6 = 0;
        return;
    }

    timer = self->ext.main_10.timer - 1;
    self->ext.main_10.timer = timer;
    if (timer == 0) {
        set_animation(self, 4);
        self->ext.main_10.timer = 0xA;
        self->y_speed = 0;
        self->unk7E = 1;
        self->unk6 = 4;
    } else {
        animate_object(self);
    }

    if (!(dragonfly_tile_above(self) & 0xFF)) {
        move_object(MOVING_OBJECT(self));
    }
}

void dragonfly_carry_squeeze(struct MainObj* self)
{
    u32 squeeze;

    if (--self->unk7E == 0) {
        func_8001540C(2, 0xE, self);
        self->unk7E = 0x14;
    }

    dragonfly_hold_player(self);
    self->ext.main_10.struggle += func_8002BAA4();
    if (self->ext.main_10.struggle >= 0x15) {
        stop_sound(2, 0xE);
        g_Player.stun_timer = 0;
        self->attack_box = NULL;
        self->unk62 = 0;
        set_animation(self, 5);
        self->y_speed = 0x20000;
        self->unk5 = 5;
        self->unk6 = 0;
        return;
    }

    if (self->animation_step.fields.event != 0) {
        squeeze = --self->ext.main_10.timer;
        if (squeeze == 9 || squeeze == 4) {
            player_damage(2);
        }
        if (self->ext.main_10.timer == 0) {
            stop_sound(2, 0xE);
            g_Player.stun_timer = 0;
            self->unk62 = 0;
            set_animation(self, 5);
            self->attack_box = NULL;
            self->y_speed = 0x20000;
            self->unk5 = 5;
            self->unk6 = 0;
            return;
        }
    }

    animate_object(self);
}

void dragonfly_flee(struct MainObj* self)
{
    move_object((struct MovingObj*)self);
    animate_object(self);
}

void dragonfly_face_player(struct MainObj* self)
{
    if (self->unk15 != 0) {
        if (self->x_pos.val > g_Player.x_pos.val) {
            self->unk15 = 0;
            self->ext.main_10.turn_delay = 0x10;
        }
    } else if (self->x_pos.val < g_Player.x_pos.val) {
        self->unk15 = 0x40;
        self->ext.main_10.turn_delay = 0x10;
    }
}

void dragonfly_hold_player(struct MainObj* self)
{
    g_Player.y_pos.i.hi = self->y_pos.i.hi + 0x18;
    if (self->unk15 == 0) {
        g_Player.x_pos.i.hi = self->x_pos.i.hi - 0x18;
    } else {
        g_Player.x_pos.i.hi = self->x_pos.i.hi + 0x18;
    }
}

u8 dragonfly_tile_above(struct MainObj* self)
{
    struct Unk_unk68* offsets;
    s16 x, y;

    offsets = self->terrain_box;
    x = self->x_pos.i.hi + offsets->unk0;
    y = self->y_pos.i.hi - offsets->unk1;

    return func_8002D724(
               PLAYER_OBJECT(self),
               x,
               y)
        & 0xFF;
}
void dragonfly_fly_past(struct MainObj* self)
{
    move_with_gravity((struct AnimatedObj*)self);
    animate_object(self);
}

u8 dragonfly_body_boxes[8] = { 0xEE, 0xEC, 0x2A, 0x24, 0xD7, 0xEA, 0x3F, 0x35 };

u8 dragonfly_grab_box[4] = { 0xDB, 0x09, 0x20, 0x17 };

struct Unk_unk68 dragonfly_terrain_box = { -24, 3, 0x0A, 0x02 };

u8 dragonfly_anim_0[0xC] = {
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0xFE,
    0x02,
};

u8 dragonfly_anim_1[0xF0] = {
    0x01,
    0x00,
    0x01,
    0x03,
    0x01,
    0x00,
    0x01,
    0x04,
    0x01,
    0x00,
    0x01,
    0x05,
    0x01,
    0x00,
    0x01,
    0x06,
    0x01,
    0x00,
    0x01,
    0x07,
    0x01,
    0x00,
    0x01,
    0x08,
    0x01,
    0x00,
    0x01,
    0x09,
    0x01,
    0x00,
    0x01,
    0x0A,
    0x01,
    0x00,
    0x01,
    0x0B,
    0x01,
    0x00,
    0x01,
    0x0C,
    0x01,
    0x00,
    0x01,
    0x0D,
    0x01,
    0x00,
    0x01,
    0x0E,
    0x01,
    0x00,
    0x01,
    0x0F,
    0x01,
    0x00,
    0x01,
    0x10,
    0x01,
    0x00,
    0x01,
    0x11,
    0x01,
    0x00,
    0x01,
    0x12,
    0x01,
    0x00,
    0x01,
    0x13,
    0x01,
    0x00,
    0x01,
    0x14,
    0x01,
    0x00,
    0x01,
    0x15,
    0x01,
    0x00,
    0x01,
    0x16,
    0x01,
    0x00,
    0x01,
    0x17,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x1B,
    0x01,
    0x00,
    0x01,
    0x1C,
    0x01,
    0x00,
    0x01,
    0x1D,
    0x01,
    0x00,
    0x01,
    0x1E,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x1F,
    0x01,
    0x00,
    0x01,
    0x20,
    0x01,
    0x00,
    0x01,
    0x21,
    0x01,
    0x00,
    0x01,
    0x22,
    0x01,
    0x00,
    0x01,
    0x23,
    0x01,
    0x00,
    0x01,
    0x24,
    0x01,
    0x00,
    0x01,
    0x25,
    0x01,
    0x00,
    0x01,
    0x26,
    0x01,
    0x00,
    0x01,
    0x27,
    0x01,
    0x00,
    0x01,
    0x28,
    0x01,
    0x00,
    0x01,
    0x29,
    0x01,
    0x00,
    0x01,
    0x2A,
    0x01,
    0x00,
    0x01,
    0x2B,
    0x01,
    0x00,
    0x01,
    0x2C,
    0x01,
    0x00,
    0x01,
    0x2D,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x01,
    0x00,
    0x1A,
};

u8 dragonfly_anim_2[0xC] = {
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x01,
    0xFE,
    0x1A,
};

u8 dragonfly_anim_3[0x3C] = {
    0x01,
    0x00,
    0x01,
    0x2E,
    0x01,
    0x00,
    0x01,
    0x2F,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x32,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x33,
    0x01,
    0x00,
    0x01,
    0x34,
    0x01,
    0x00,
    0x01,
    0x35,
    0x01,
    0x00,
    0x01,
    0x36,
    0x01,
    0x00,
    0x01,
    0x37,
    0x01,
    0x00,
    0x01,
    0x38,
    0x01,
    0x00,
    0x01,
    0x36,
    0x01,
    0x01,
    0xFE,
    0x37,
};

u8 dragonfly_anim_4[0x3C] = {
    0x01,
    0x00,
    0x01,
    0x37,
    0x01,
    0x00,
    0x01,
    0x39,
    0x01,
    0x00,
    0x01,
    0x3A,
    0x01,
    0x00,
    0x01,
    0x3B,
    0x01,
    0x00,
    0x01,
    0x3C,
    0x01,
    0x00,
    0x01,
    0x3D,
    0x01,
    0x00,
    0x01,
    0x3E,
    0x01,
    0x00,
    0x01,
    0x3F,
    0x01,
    0x00,
    0x01,
    0x40,
    0x01,
    0x00,
    0x01,
    0x41,
    0x01,
    0x00,
    0x01,
    0x42,
    0x01,
    0x00,
    0x01,
    0x43,
    0x01,
    0x00,
    0x01,
    0x44,
    0x01,
    0x00,
    0x01,
    0x45,
    0x01,
    0x01,
    0xF5,
    0x46,
};

u8 dragonfly_anim_5[0x24] = {
    0x01,
    0x00,
    0x01,
    0x34,
    0x01,
    0x00,
    0x01,
    0x35,
    0x01,
    0x00,
    0x01,
    0x33,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x32,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0xFE,
    0x19,
};

u8 dragonfly_anim_6[4] = { 0x01, 0x01, 0x00, 0x47 };
u8 dragonfly_anim_7[4] = { 0x01, 0x01, 0x00, 0x48 };
u8 dragonfly_anim_8[4] = { 0x01, 0x01, 0x00, 0x49 };
u8 dragonfly_anim_9[4] = { 0x01, 0x01, 0x00, 0x4A };
u8 dragonfly_anim_10[4] = { 0x01, 0x01, 0x00, 0x4B };
u8 dragonfly_anim_11[4] = { 0x01, 0x01, 0x00, 0x4C };

const u8* dragonfly_animations[12] = {
    dragonfly_anim_0,
    dragonfly_anim_1,
    dragonfly_anim_2,
    dragonfly_anim_3,
    dragonfly_anim_4,
    dragonfly_anim_5,
    dragonfly_anim_6,
    dragonfly_anim_7,
    dragonfly_anim_8,
    dragonfly_anim_9,
    dragonfly_anim_10,
    dragonfly_anim_11,
};

u8 dragonfly_debris[8] = { 6, 7, 8, 9, 10, 11, 0, 0 };

void (*dragonfly_state_funcs[])(struct MainObj*) = {
    dragonfly_init,
    dragonfly_run,
    dragonfly_finish,
    dragonfly_despawn,
};

void (*dragonfly_step_funcs[])(struct MainObj*) = {
    enemy_hit_reaction,
    dragonfly_resume_step,
    dragonfly_wait,
    dragonfly_hunt,
    dragonfly_carry,
    dragonfly_flee,
    dragonfly_fly_past,
};

void (*dragonfly_hunt_funcs[])(struct MainObj*) = {
    dragonfly_hunt_start,
    func_80049E68,
    dragonfly_hunt_hover,
    dragonfly_hunt_close,
};

void (*dragonfly_carry_funcs[])(struct MainObj*) = {
    dragonfly_carry_grab,
    func_8004A178,
    dragonfly_carry_lift,
    dragonfly_carry_rise,
    dragonfly_carry_squeeze,
};
