// MainObj, main_object_update_funcs[5]
// 80044F4C..80046B30
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_05_robot_bee.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/objects.h"

extern s32 robot_bee_approach_speeds[2];
extern s32 robot_bee_charge_speeds[2];
extern s32 robot_bee_sting_speeds[2];

extern s32 robot_bee_lunge_speeds[2];

void robot_bee_main(struct MainObj* arg0);
void robot_bee_despawn(struct MainObj*);

// robot_bee_step_funcs
void robot_bee_resume_step(struct MainObj* arg0);
void robot_bee_wait(struct MainObj* arg0);
void robot_bee_glide(struct MainObj* arg0);
void robot_bee_dash(struct MainObj* arg0);
void robot_bee_sting(struct MainObj* arg0);
void robot_bee_circle(struct MainObj* arg0);
void robot_bee_drop(struct MainObj* arg0);
void robot_bee_swarm(struct MainObj* arg0);
void robot_bee_swarm_return(struct MainObj* arg0);

// robot_bee_wait_funcs
extern void (*robot_bee_wait_funcs[])(struct MainObj*);
void robot_bee_wait_start(struct MainObj*);
void robot_bee_wait_for_player(struct MainObj*);

// robot_bee_glide_funcs
extern void (*robot_bee_glide_funcs[])(struct MainObj*);
void robot_bee_glide_start(struct MainObj*);
void robot_bee_glide_move(struct MainObj*);

// robot_bee_dash_funcs
extern void (*robot_bee_dash_funcs[])(struct MainObj*);
void robot_bee_dash_start(struct MainObj*);
void robot_bee_dash_wind_up(struct MainObj*);
void robot_bee_dash_charge(struct MainObj*);
void robot_bee_dash_accelerate(struct MainObj*);

// robot_bee_sting_funcs
extern void (*robot_bee_sting_funcs[])(struct MainObj*);
void robot_bee_sting_start(struct MainObj*);
void robot_bee_sting_approach(struct MainObj*);
void robot_bee_sting_brake(struct MainObj*);
void robot_bee_sting_lunge(struct MainObj*);

void robot_bee_sting_recoil(struct MainObj*);

void robot_bee_sting_fly_off(struct MainObj*);

// robot_bee_circle_funcs
extern void (*robot_bee_circle_funcs[])(struct MainObj*);
void func_8004619C(struct MainObj*);

// robot_bee_drop_funcs
extern void (*robot_bee_drop_funcs[])(struct MainObj*);

void robot_bee_drop_fall(struct MainObj*);

// robot_bee_swarm_funcs
extern void (*robot_bee_swarm_funcs[])(struct MainObj*);
void robot_bee_swarm_start(struct MainObj*);
void robot_bee_swarm_fly(struct MainObj*);
void robot_bee_swarm_hover(struct MainObj*);

// robot_bee_swarm_return_funcs
extern void (*robot_bee_swarm_return_funcs[])(struct MainObj*);
void robot_bee_swarm_return_start(struct MainObj*);
void robot_bee_swarm_return_fly(struct MainObj*);
void robot_bee_swarm_return_hover(struct MainObj*);

extern void (*robot_bee_state_funcs[])(struct MainObj*);

extern s32 D_800FA130[];

void robot_bee_update(struct MainObj* self)
{
    robot_bee_state_funcs[self->state](self);
}

// robot_bee_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80044F88(struct MainObj* arg0);
void func_80046220(struct MainObj* self);
void func_80046400(struct MainObj* self);
static u32 robot_bee_arc_origin(struct MainObj* self, unsigned offset);
static void robot_bee_save_arc_origin(struct MainObj* self, s32 y_offset);
static void robot_bee_arc_position(struct MainObj* self, int index, int x_positive, int y_positive);
void func_80045940(struct MainObj* self);
void func_80045DD8(struct MainObj* self);
extern union AnimationStep* robot_bee_animations[];
extern struct Unk_unk68 D_800FA100;
extern struct Unk_unk68 D_800FA104;
extern u16 D_80106570[];
extern s32 D_800FA128[], D_800FA348[], D_800FA368[];
static u32 robot_bee_arc_origin(struct MainObj* self, unsigned offset)
{
    u32 value;
    memcpy(&value, (u8*)&self->ext.main_5 + offset, sizeof(value));
    return value;
}
static void robot_bee_save_arc_origin(struct MainObj* self, s32 y_offset)
{
    u32 x = (u32)self->x_pos.val;
    u32 y = (u32)self->y_pos.val + (u32)y_offset;
    memcpy((u8*)&self->ext.main_5 + 4, &x, sizeof(x));
    memcpy((u8*)&self->ext.main_5 + 8, &y, sizeof(y));
}
static void robot_bee_arc_position(struct MainObj* self, int index,
    int x_positive, int y_positive)
{
    u32 x = robot_bee_arc_origin(self, 4);
    u32 y = robot_bee_arc_origin(self, 8);
    u32 dx = (u32)D_800FA368[index] * 53u;
    u32 dy = (u32)D_800FA348[index] * 53u;
    self->x_pos.val = (s32)(x_positive ? x + dx : x - dx);
    self->y_pos.val = (s32)(y_positive ? y + dy : y - dy);
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80044F88(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk7C = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)robot_bee_animations;
    arg0->hurt_box = (const u8*)&D_800FA100;
    arg0->attack_box = (const u8*)&D_800FA104;
    arg0->collision_data = D_80106570;
    arg0->contact_damage = 3;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
    arg0->terrain_box = NULL;
    arg0->hp = 2;
    arg0->invincibility_timer = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    if (arg0->unk2 == 1)
        arg0->unk5 = 5;
    else if (arg0->unk2 == 2)
        arg0->unk5 = 6;
    else if (arg0->unk2 == 3)
        arg0->unk5 = 8;
    else if (arg0->unk2 == 4)
        arg0->unk5 = 9;
    set_animation(arg0, 1);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80044F88);
#endif

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
#ifdef MMX4_SATURN
    func_8001540C(6, 5, NULL);
#else
    stop_sound(2, 0x13);
    stop_sound(2, 0x14);
#endif
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
#ifndef MMX4_SATURN
#ifndef MMX4_SATURN
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
#endif
#endif
    robot_bee_wait_funcs[self->unk6](self);
}

void robot_bee_wait_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    func_8001540C(2, SATURN_SOUND(0x13, 0x12), self);
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
        x_vel = robot_bee_approach_speeds[!(self->unk15 & PLAYER_FACING_RIGHT)];
        self->y_speed = 0;
        self->unk5 = 3;
        self->x_speed = x_vel;
    }
}

void robot_bee_glide(struct MainObj* self)
{
#ifndef MMX4_SATURN
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
#endif
    robot_bee_glide_funcs[self->unk6](self);
}

void robot_bee_glide_start(struct MainObj* self)
{
    s32 x_vel;

    animate_object(ANIMATED_OBJECT(self));
    x_vel = robot_bee_approach_speeds[!(self->unk15 & PLAYER_FACING_RIGHT)];
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
#ifndef MMX4_SATURN
    if (is_sound_finished(0x14, self) != 0) {
        func_8001540C(2, 0x14, self);
    }
#endif
    robot_bee_dash_funcs[self->unk6](self);
}

void robot_bee_dash_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    STOP_SOUND(2, 0x13, 0x5);
    func_8001540C(2, SATURN_SOUND(0x14, 0x13), self);
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
    self->x_speed = robot_bee_charge_speeds[(self->unk15 & PLAYER_FACING_RIGHT) ? 1 : 0];
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
#if defined(MMX4_SATURN)
#elif defined(VERSION_EU)
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
    STOP_SOUND(2, 0x13, 0x5);
    func_8001540C(2, SATURN_SOUND(0x13, 0x12), self);
    velocity = robot_bee_sting_speeds;
    if (self->unk15 & PLAYER_FACING_RIGHT) {
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
        if (self->unk15 & PLAYER_FACING_RIGHT) {
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
        STOP_SOUND(2, 0x13, 0x5);
        func_8001540C(2, SATURN_SOUND(0x14, 0x13), self);
        set_animation(self, 0xB);
        self->unk6++;
    }
}

// robot_bee_sting_strike
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80045940(struct MainObj* self)
{
    u8 phase = self->ext.main_5.unk80;
    int timer = self->unk7C;
    int right = self->unk15 == PLAYER_FACING_RIGHT;

    switch (phase) {
    case 0:
        robot_bee_save_arc_origin(self, -FIXED(53));
        self->ext.main_5.unk80++;
        break;
    case 1:
        robot_bee_arc_position(self, timer, right, 1);
        break;
    case 2:
        robot_bee_arc_position(self, 7 - timer, right, 0);
        break;
    case 3:
        robot_bee_arc_position(self, timer, !right, 0);
        break;
    case 4:
        robot_bee_arc_position(self, 7 - timer, !right, 1);
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C;
    self->unk7C = (s16)((u16)timer - 1);
    if (timer <= 0) {
        self->unk7C = 7;
        phase = self->ext.main_5.unk80;
        if (phase < 4) {
            self->ext.main_5.unk80++;
        } else {
            self->unk7C = 0x17;
            self->x_speed = D_800FA128[(self->unk15 & PLAYER_FACING_RIGHT) != 0];
            self->y_speed = FIXED(4);
            self->ext.main_5.unk80 = 0;
            self->unk6++;
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80045940);
#endif

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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80045DD8(struct MainObj* self)
{
    u8 phase = self->ext.main_5.unk80;
    int timer = self->unk7C;
    int right = self->unk15 == PLAYER_FACING_RIGHT;

    switch (phase) {
    case 0:
        robot_bee_save_arc_origin(self, FIXED(53));
        self->ext.main_5.unk80++;
        break;
    case 1:
        robot_bee_arc_position(self, timer, right, 0);
        break;
    case 2:
        robot_bee_arc_position(self, 7 - timer, right, 1);
        break;
    case 3:
        robot_bee_arc_position(self, timer, !right, 1);
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C;
    self->unk7C = (s16)((u16)timer - 1);
    if (timer <= 0) {
        self->unk7C = 7;
        phase = self->ext.main_5.unk80;
        if (phase < 3) {
            self->ext.main_5.unk80++;
        } else {
            self->x_speed = 0;
            self->y_speed = FIXED(5);
            self->unk6++;
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80045DD8);
#endif

void robot_bee_sting_fly_off(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void robot_bee_circle(struct MainObj* self)
{
#ifndef MMX4_SATURN
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
#endif
    robot_bee_circle_funcs[self->unk6](self);
}

// robot_bee_circle_start
void func_8004619C(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    func_8001540C(2, SATURN_SOUND(0x13, 0x12), self);
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
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80046220);
#else
void func_80046220(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0x1E) {
        self->ext.main_5.unk81 = self->ext.main_5.unk81 == 0;
        self->gravity = -self->gravity;
        self->y_speed = D_800FA130[self->ext.main_5.unk81 ? 1 : 0];
    }
    if (self->unk7C == 0) {
        self->ext.main_5.unk80 = self->ext.main_5.unk80 == 0;
        self->x_speed = 0;
        self->ext.main_5.unk81 = self->ext.main_5.unk81 == 0;
        self->x_accel = -self->x_accel;
        self->gravity = -self->gravity;
        self->y_speed = D_800FA130[self->ext.main_5.unk81 ? 1 : 0];
        self->unk7C = 0x3C;
    }
    if ((g_Player.x_pos.val - self->x_pos.val >= 0 ? g_Player.x_pos.val - self->x_pos.val : self->x_pos.val - g_Player.x_pos.val) <= 0x6FFFFF) {
        set_animation(self, 2);
        self->unk5 = 7;
        self->unk6 = 0;
    }
}
#endif

void robot_bee_drop(struct MainObj* self)
{
#if defined(MMX4_SATURN)
#elif defined(VERSION_EU)
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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80046400(struct MainObj* self)
{
    s16 timer = self->unk7C;
    u8 direction;
    s32 speed;

    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = timer - 1;
    if (timer >= 5)
        return;

    func_8001540C(2, SATURN_SOUND(0x14, 0x13), self);
    direction = (u8)angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    if (self->unk15 == 0 && self->x_speed > 0)
        self->unk15 = PLAYER_FACING_RIGHT;
    if (self->unk15 == PLAYER_FACING_RIGHT && self->x_speed < 0)
        self->unk15 = 0;
    if (self->y_speed > 0)
        self->y_speed = 0;
    if ((self->x_speed >= 0 && self->x_speed + self->y_speed == 0)
        || (self->x_speed < 0 && self->x_speed == self->y_speed))
        self->x_speed = self->unk15 ? 0x10000 : -0x10000;

    if (direction == 0x11 || direction == 0x1F)
        set_animation(self, 0xF);
    else if (direction >= 0x12 && direction <= 0x1E && direction != 0x17 && direction != 0x18 && direction != 0x19)
        set_animation(self, 0xE);
    else if (direction == 0x17 || direction == 0x19)
        set_animation(self, 0xD);
    else if (direction == 0x18)
        set_animation(self, 0xC);
    else {
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7C = 5;
    }

    self->x_speed *= 3;
    self->y_speed *= 3;
    speed = self->x_speed;
    self->x_accel = (speed < 0 ? -speed : speed) >> 6;
    speed = self->y_speed;
    self->gravity = (speed < 0 ? -speed : speed) >> 6;
    self->unk6++;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_05_robot_bee", func_80046400);
#endif

void robot_bee_drop_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void robot_bee_swarm(struct MainObj* self)
{
#ifndef MMX4_SATURN
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
#endif
    robot_bee_swarm_funcs[self->unk6](self);
}

void robot_bee_swarm_start(struct MainObj* arg0)
{
    struct MainObj* self = arg0;
    u8 angle;

    set_animation(self, 1);
    func_8001540C(2, SATURN_SOUND(0x13, 0x12), self);
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
#ifndef MMX4_SATURN
    if (is_sound_finished(0x13, self) != 0) {
        func_8001540C(2, 0x13, self);
    }
#endif
    robot_bee_swarm_return_funcs[self->unk6](self);
}

void robot_bee_swarm_return_start(struct MainObj* self)
{
    u8 angle;

    set_animation(self, 1);
    func_8001540C(2, SATURN_SOUND(0x13, 0x12), self);
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
        self->unk15 = g_Player.x_pos.val > self->x_pos.val ? PLAYER_FACING_RIGHT : 0;
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
    { 1, 0, 0, 0x00 },
};

union AnimationStep robot_bee_anim_1[] = {
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x05 },
    { 1, 0, 1, 0x06 },
    { 1, 0, 1, 0x07 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x09 },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x0C },
    { 1, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 1, 0, -15, 0x0F },
};

union AnimationStep robot_bee_anim_2[] = {
    { 2, 0, 1, 0x10 },
    { 9, 0, 1, 0x11 },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 0, 0x15 },
};

union AnimationStep robot_bee_anim_3[] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 2, 0, -15, 0x25 },
};

union AnimationStep robot_bee_anim_4[] = {
    { 3, 0, 1, 0x26 },
    { 3, 0, 1, 0x27 },
    { 3, 0, 1, 0x28 },
    { 3, 0, -3, 0x29 },
};

union AnimationStep robot_bee_anim_5[] = {
    { 1, 0, 0, 0x2A },
};

union AnimationStep robot_bee_anim_6[] = {
    { 1, 0, 0, 0x2B },
};

union AnimationStep robot_bee_anim_7[] = {
    { 1, 0, 0, 0x2C },
};

union AnimationStep robot_bee_anim_8[] = {
    { 1, 0, 0, 0x2D },
};

union AnimationStep robot_bee_anim_9[] = {
    { 1, 0, 1, 0x2E },
    { 1, 0, 1, 0x2F },
    { 1, 0, 1, 0x30 },
    { 1, 0, -3, 0x31 },
};

union AnimationStep robot_bee_anim_10[] = {
    { 2, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 2, 0, 1, 0x34 },
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 2, 0, 1, 0x3C },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x3E },
    { 2, 0, 1, 0x3F },
    { 2, 0, 1, 0x40 },
    { 2, 0, -15, 0x41 },
};

union AnimationStep robot_bee_anim_11[] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 23, 0, 1, 0x18 },
    { 1, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 2, 0, 1, 0x3C },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x3E },
    { 2, 0, 1, 0x3F },
    { 2, 0, 1, 0x40 },
    { 2, 0, 1, 0x41 },
    { 2, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 2, 0, 1, 0x34 },
    { 2, 0, 1, 0x35 },
    { 2, 0, 0, 0x36 },
};

union AnimationStep robot_bee_anim_12[] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 0, 0x22 },
};

union AnimationStep robot_bee_anim_13[] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 0, 0x23 },
};

union AnimationStep robot_bee_anim_14[] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 0, 0x24 },
};

union AnimationStep robot_bee_anim_15[] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 0, 0x25 },
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
