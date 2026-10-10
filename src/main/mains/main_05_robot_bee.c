// MainObj, main_object_update_funcs[5]
// 80044F4C..80046B30
#include "common.h"
#include "func_tables.h"

extern s32 D_800FA130[];

void robot_bee_update(struct MainObj* self)
{
    robot_bee_state_funcs[self->state](self);
}

// robot_bee_init
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80044F88);

void robot_bee_main(struct MainObj* self)
{
    s32 collision;
    s8 subtype;

    robot_bee_check_dive(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        collision = func_8002DD04(self);
        subtype = self->unk5;
        if (subtype != 0) {
            self->ext.main_5.saved_unk5 = subtype;
        }
        if (collision < 0) {
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(5, robot_bee_debris, self);
            drop_item(BASE_OBJECT(self), 0);
            self->state = 2;
            return;
        }
        robot_bee_step_funcs[self->unk5](self);
        func_8002D9BC(self);
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state = 2;
    }
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
}

void robot_bee_despawn(struct MainObj* self)
{
    struct MainObj* target;
    u8 subtype;
    stop_sound(2, 0x13);
    stop_sound(2, 0x14);
    self->on_screen = 0;
    subtype = self->unk2;
    if ((subtype == 3) || (subtype == 4)) {
        target = self->ext.main_5.owner;
        if ((target->active != 0) && (target->id == 0x16)) {
            target->ext.main_22.parts_mask ^= 1 << self->ext.main_5.part_index;
        }
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    despawn_object(OBJECT_HEADER(self));
}

void robot_bee_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_5.saved_unk5;
}

void robot_bee_wait(struct MainObj* self)
{
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
    robot_bee_wait_funcs[self->unk6](self);
}

void robot_bee_wait_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    func_8001540C(2, 0x13, self);
    self->unk6++;
}

void robot_bee_wait_for_player(struct MainObj* self)
{
    s32 object_x;
    s32 player_x;
    s32 x_vel;

    animate_object(ANIMATED_OBJECT(self));
    object_x = self->x_pos.val;
    player_x = g_Player.x_pos.val;
    if (ABS(object_x, player_x) <= FIXED(144)) {
        x_vel = robot_bee_approach_speeds[!(self->unk15 & 0x40)];
        self->y_speed = 0;
        self->unk5 = 3;
        self->x_speed = x_vel;
    }
}

void robot_bee_glide(struct MainObj* self)
{
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
    robot_bee_glide_funcs[self->unk6](self);
}

void robot_bee_glide_start(struct MainObj* self)
{
    s32 x_vel;

    animate_object(ANIMATED_OBJECT(self));
    x_vel = robot_bee_approach_speeds[!(self->unk15 & 0x40)];
    self->y_speed = FIXED(1);
    self->x_speed = x_vel;
    self->unk6++;
}

void robot_bee_glide_move(struct MainObj* self)
{
    self->gravity = FIXED(0.04296875);
    self->x_accel = FIXED(0.0234375);
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void robot_bee_dash(struct MainObj* self)
{
    if (is_sound_finished(0x14, self) != 0) {
        func_8001540C(2, 0x14, self);
    }
    robot_bee_dash_funcs[self->unk6](self);
}

void robot_bee_dash_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    stop_sound(2, 0x13);
    func_8001540C(2, 0x14, self);
    self->unk6++;
}

void robot_bee_dash_wind_up(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7C-- == 4) {
        self->unk6++;
    }
}

void robot_bee_dash_charge(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    self->x_speed = robot_bee_charge_speeds[(self->unk15 & 0x40) ? 1 : 0];
    if (self->unk7C-- == 0) {
        self->unk6++;
        set_animation(self, 9);
        self->x_accel = FIXED(0.1875);
        self->gravity = FIXED(-0.03125);
    }
}

void robot_bee_dash_accelerate(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->x_speed >= 0x150000) {
        self->x_accel = 0;
    }
}

void robot_bee_sting(struct MainObj* self)
{
#ifdef VERSION_EU
    if (self->unk6 > 3) {
        if (is_sound_finished(0x14, self) != 0) {
            func_8001540C(2, 0x14, self);
        }
    } else if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
#else
    if (self->unk6 > 3) {
        if (is_sound_finished(0x14, self) != 0) {
            func_8001540C(2, 0x14, self);
        } else if (is_sound_finished(0x13, self) != 0) {
            func_8001540C(2, 0x13, self);
        }
    }
#endif
    robot_bee_sting_funcs[self->unk6](self);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", robot_bee_sting_start);
#else
void robot_bee_sting_start(struct MainObj* self)
{
    s32* velocity;

    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    stop_sound(2, 0x13);
    func_8001540C(2, 0x13, self);
    velocity = robot_bee_sting_speeds;
    if (self->unk15 & 0x40) {
        velocity++;
    }
    self->x_speed = *velocity;
    self->unk6++;
}
#endif

void robot_bee_sting_approach(struct MainObj* self)
{
    s32 player_x;
    s32 object_x;
    s32 delta;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    player_x = g_Player.x_pos.val;
    object_x = self->x_pos.val;
    delta = player_x - object_x;
    if (delta >= 0 ? delta <= FIXED(96) - 1 : object_x - player_x <= FIXED(96) - 1) {
        set_animation(self, 2);
        self->unk7C = 0xF;
        self->unk6++;
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", robot_bee_sting_brake);
#else
void robot_bee_sting_brake(struct MainObj* self)
{
    s32* velocity;

    animate_object(ANIMATED_OBJECT(self));

    if (self->unk7C-- <= 4) {
        velocity = robot_bee_lunge_speeds;
        if (self->unk15 & 0x40) {
            velocity++;
        }
        self->x_speed = *velocity;
        self->unk6++;
    }
}
#endif

void robot_bee_sting_lunge(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (self->unk7C-- <= 0) {
        self->unk7C = 8;
        self->ext.main_5.unk80 = 0;
        stop_sound(2, 0x13);
        func_8001540C(2, 0x14, self);
        set_animation(self, 0xB);
        self->unk6++;
    }
}

// robot_bee_sting_strike
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80045940);

void robot_bee_sting_recoil(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (self->unk7C-- == 0) {
        self->unk7C = 8;
        self->unk6++;
    }
}

// robot_bee_sting_return
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80045DD8);

void robot_bee_sting_fly_off(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void robot_bee_circle(struct MainObj* self)
{
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
    robot_bee_circle_funcs[self->unk6](self);
}

// robot_bee_circle_start
void func_8004619C(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    func_8001540C(2, 0x13, self);
    self->x_accel = 0x400;
    self->ext.main_5.unk80 = self->unk15;
    self->x_speed = 0;
    self->y_speed = D_800FA130[0];
    self->gravity = -0x400;
    self->ext.main_5.unk81 = 0;
    self->unk7C = 0x3C;
    self->unk6++;
}

// robot_bee_circle_orbit
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80046220);

void robot_bee_drop(struct MainObj* self)
{
#ifdef VERSION_EU
    if (self->unk6 > 1) {
        if (is_sound_finished(0x14, self) != 0) {
            func_8001540C(2, 0x14, self);
        }
    } else if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
#else
    if (self->unk6 > 1) {
        if (is_sound_finished(0x14, self) != 0) {
            func_8001540C(2, 0x14, self);
        } else if (is_sound_finished(0x13, self) != 0) {
            func_8001540C(2, 0x13, self);
        }
    }
#endif
    robot_bee_drop_funcs[self->unk6](self);
}

// robot_bee_drop_start
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80046400);

void robot_bee_drop_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void robot_bee_swarm(struct MainObj* self)
{
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
    robot_bee_swarm_funcs[self->unk6](self);
}

void robot_bee_swarm_start(struct MainObj* arg0)
{
    struct MainObj* self = arg0;
    u8 angle;

    set_animation(self, 1);
    func_8001540C(2, 0x13, self);
    animate_object(ANIMATED_OBJECT(self));
    angle = angle_to_point(
        OBJECT_HEADER(self),
        self->ext.main_5.target_y << 0x10,
        self->ext.main_5.target_x << 0x10);
    set_velocity_from_angle(MOVING_OBJECT(self), angle & 0xFF);

    self->unk7C = 0x14;
    if (self->unk15 == 0) {
        if (self->ext.main_5.part_index % 2) {
            self->unk7C = 0x16;
        }
    }
    if (self->unk15 != 0) {
        if (!(self->ext.main_5.part_index % 2)) {
            self->unk7C += 2;
        }
    }
    self->unk6++;
}

void robot_bee_swarm_fly(struct MainObj* self)
{
    s16 timer;
    s16 next_delay;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    timer = --self->unk7C;
    if (timer == 0) {
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;

        next_delay = get_random() & 0x7F;
        self->unk7C = next_delay;
        if (next_delay < 0x78) {
            self->unk7C = next_delay + 0x78;
        } else if (next_delay > 0xF0) {
            self->unk7C = 0xF0;
        }
        self->unk6++;
    }
}

void robot_bee_swarm_hover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void robot_bee_swarm_return(struct MainObj* self)
{
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
    robot_bee_swarm_return_funcs[self->unk6](self);
}

void robot_bee_swarm_return_start(struct MainObj* self)
{
    u8 angle;

    set_animation(self, 1);
    func_8001540C(2, 0x13, self);
    animate_object(ANIMATED_OBJECT(self));
    angle = angle_to_point(OBJECT_HEADER(self),
        self->ext.main_5.target_y << 0x10,
        self->ext.main_5.target_x << 0x10);
    set_velocity_from_angle(MOVING_OBJECT(self), angle);

    self->unk7C = 0x14;
    if (self->unk15 == 0) {
        if (self->ext.main_5.part_index % 2) {
            self->unk7C = 0x16;
        }
    }
    if (self->unk15 != 0) {
        if (!(self->ext.main_5.part_index % 2)) {
            self->unk7C += 2;
        }
    }
    self->unk6++;
}

void robot_bee_swarm_return_fly(struct MainObj* self)
{
    s16 timer;
    s16 next_delay;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    timer = --self->unk7C;
    if (timer == 0) {
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;

        next_delay = get_random() & 0x7F;
        self->unk7C = next_delay;
        if (next_delay < 0x78) {
            self->unk7C = next_delay + 0x78;
        } else if (next_delay > 0xF0) {
            self->unk7C = 0xF0;
        }
        self->unk6++;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void robot_bee_swarm_return_hover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 2);
        self->unk5 = 7;
        self->unk6 = 0;
    }
}

void robot_bee_check_dive(struct MainObj* self)
{
    if ((self->unk5 == 3) && (self->y_pos.val + FIXED(16) >= g_Player.y_pos.val)) {
        self->unk15 = g_Player.x_pos.val > self->x_pos.val ? 0x40 : 0;
        self->unk5 = 4;
        self->unk6 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        self->unk7C = 0xF;
        set_animation(self, 2);
    }
}

struct Unk_unk68 D_800FA100 = { -10, -12, 19, 24 };

struct Unk_unk68 D_800FA104 = { -3, -4, 8, 9 };

s32 robot_bee_approach_speeds[] = {
    (s32)0xFFFF0000,
    (s32)0x00010000,
};

s32 robot_bee_charge_speeds[] = {
    (s32)0xFFFD0000,
    (s32)0x00030000,
};

s32 robot_bee_sting_speeds[] = {
    (s32)0xFFFE0000,
    (s32)0x00020000,
};

s32 robot_bee_lunge_speeds[] = {
    (s32)0xFFFD0000,
    (s32)0x00030000,
};

s32 D_800FA128[] = {
    (s32)0xFFF9E000,
    (s32)0x00062000,
};

s32 D_800FA130[] = {
    (s32)0xFFFF8000,
    (s32)0x00008000,
};

union AnimationStep robot_bee_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep robot_bee_anim_1[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0E010001 },
    { 0x0FF10001 },
};

union AnimationStep robot_bee_anim_2[] = {
    { 0x10010002 },
    { 0x11010009 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15000001 },
};

union AnimationStep robot_bee_anim_3[] = {
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25F10002 },
};

union AnimationStep robot_bee_anim_4[] = {
    { 0x26010003 },
    { 0x27010003 },
    { 0x28010003 },
    { 0x29FD0003 },
};

union AnimationStep robot_bee_anim_5[] = {
    { 0x2A000001 },
};

union AnimationStep robot_bee_anim_6[] = {
    { 0x2B000001 },
};

union AnimationStep robot_bee_anim_7[] = {
    { 0x2C000001 },
};

union AnimationStep robot_bee_anim_8[] = {
    { 0x2D000001 },
};

union AnimationStep robot_bee_anim_9[] = {
    { 0x2E010001 },
    { 0x2F010001 },
    { 0x30010001 },
    { 0x31FD0001 },
};

union AnimationStep robot_bee_anim_10[] = {
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x3F010002 },
    { 0x40010002 },
    { 0x41F10002 },
};

union AnimationStep robot_bee_anim_11[] = {
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010017 },
    { 0x39010001 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x3F010002 },
    { 0x40010002 },
    { 0x41010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36000002 },
};

union AnimationStep robot_bee_anim_12[] = {
    { 0x16010002 },
    { 0x25010002 },
    { 0x24010002 },
    { 0x23010002 },
    { 0x22000002 },
};

union AnimationStep robot_bee_anim_13[] = {
    { 0x16010002 },
    { 0x25010002 },
    { 0x24010002 },
    { 0x23000002 },
};

union AnimationStep robot_bee_anim_14[] = {
    { 0x16010002 },
    { 0x25010002 },
    { 0x24000002 },
};

union AnimationStep robot_bee_anim_15[] = {
    { 0x16010002 },
    { 0x25000002 },
};

union AnimationStep* robot_bee_animations[] = {
    robot_bee_anim_0,
    robot_bee_anim_1,
    robot_bee_anim_2,
    robot_bee_anim_3,
    robot_bee_anim_4,
    robot_bee_anim_5,
    robot_bee_anim_6,
    robot_bee_anim_7,
    robot_bee_anim_8,
    robot_bee_anim_9,
    robot_bee_anim_10,
    robot_bee_anim_11,
    robot_bee_anim_12,
    robot_bee_anim_13,
    robot_bee_anim_14,
    robot_bee_anim_15,
};

u8 robot_bee_debris[] = {
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x00,
    0x00,
    0x00,
};

s32 D_800FA348[] = {
    (s32)0x00001AC2,
    (s32)0x00003539,
    (s32)0x0000681F,
    (s32)0x00009679,
    (s32)0x0000BE3E,
    (s32)0x0000DDB3,
    (s32)0x0000F378,
    (s32)0x0000FE99,
};

s32 D_800FA368[] = {
    (s32)0x0000FE99,
    (s32)0x0000FA67,
    (s32)0x0000E9DE,
    (s32)0x0000CF1B,
    (s32)0x0000AB4C,
    (s32)0x00008000,
    (s32)0x00004F1B,
    (s32)0x00001AC2,
};

void (*robot_bee_state_funcs[])(struct MainObj*) = {
    func_80044F88,
    robot_bee_main,
    robot_bee_despawn,
};

void (*robot_bee_step_funcs[])() = {
    enemy_hit_reaction,
    robot_bee_resume_step,
    robot_bee_wait,
    robot_bee_glide,
    robot_bee_dash,
    robot_bee_sting,
    robot_bee_circle,
    robot_bee_drop,
    robot_bee_swarm,
    robot_bee_swarm_return,
};

void (*robot_bee_wait_funcs[])(struct MainObj*) = {
    robot_bee_wait_start,
    robot_bee_wait_for_player,
};

void (*robot_bee_glide_funcs[])(struct MainObj*) = {
    robot_bee_glide_start,
    robot_bee_glide_move,
};

void (*robot_bee_dash_funcs[])(struct MainObj*) = {
    robot_bee_dash_start,
    robot_bee_dash_wind_up,
    robot_bee_dash_charge,
    robot_bee_dash_accelerate,
};

void (*robot_bee_sting_funcs[])(struct MainObj*) = {
    robot_bee_sting_start,
    robot_bee_sting_approach,
    robot_bee_sting_brake,
    robot_bee_sting_lunge,
    func_80045940,
    robot_bee_sting_recoil,
    func_80045DD8,
    robot_bee_sting_fly_off,
};

void (*robot_bee_circle_funcs[])(struct MainObj*) = {
    func_8004619C,
    func_80046220,
};

void (*robot_bee_drop_funcs[])(struct MainObj*) = {
    func_80046400,
    robot_bee_drop_fall,
};

void (*robot_bee_swarm_funcs[])(struct MainObj*) = {
    robot_bee_swarm_start,
    robot_bee_swarm_fly,
    robot_bee_swarm_hover,
};

void (*robot_bee_swarm_return_funcs[])(struct MainObj*) = {
    robot_bee_swarm_return_start,
    robot_bee_swarm_return_fly,
    robot_bee_swarm_return_hover,
};
