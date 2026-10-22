// ShotObj, shot_object_update_funcs[46]
// 800A8628..800A9964
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_46_sigma_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"

#ifdef MMX4_PC
#include "main/collision_bounds.h"
#include "main/misc/misc_02_rubble.h"
#include "main/stage_objects.h"
#endif

// sigma_bolt_funcs
extern void (*sigma_bolt_funcs[])(struct ShotObj*);
void sigma_bolt_gather(struct ShotObj*);
void sigma_bolt_launch(struct ShotObj*);
void sigma_bolt_bounce_wall(struct ShotObj*);
void sigma_bolt_bounce_floor(struct ShotObj*);
void sigma_bolt_bounce_wall(struct ShotObj*);
void sigma_bolt_idle(struct ShotObj*);

// sigma_planted_scythe_funcs
extern void (*sigma_planted_scythe_funcs[])(struct ShotObj*);

void sigma_planted_scythe_stuck(struct ShotObj*);
void sigma_planted_scythe_recall(struct ShotObj*);
void sigma_planted_scythe_return(struct ShotObj*);

// sigma_dart_funcs
extern void (*sigma_dart_funcs[])(struct ShotObj*);
void sigma_dart_spread(struct ShotObj*);
void sigma_dart_wait(struct ShotObj*);
void sigma_dart_strike(struct ShotObj*);
void sigma_dart_aim(struct ShotObj*);
void sigma_dart_fly(struct ShotObj*);

// sigma_shot_subtype_funcs
extern void (*sigma_shot_subtype_funcs[])(struct ShotObj*);
void sigma_shot_cloak_scythe(struct ShotObj*);
void sigma_shot_bolt(struct ShotObj*);
void sigma_shot_planted_scythe(struct ShotObj*);
void sigma_shot_drift(struct ShotObj*);
void sigma_shot_drift(struct ShotObj*);
void sigma_shot_dart(struct ShotObj*);

void sigma_shot_cloak_fire(struct ShotObj*);
void sigma_shot_dropped_scythe(struct ShotObj*);

// sigma_shot_state_funcs
extern void (*sigma_shot_state_funcs[])(struct ShotObj*);

void sigma_shot_run(struct ShotObj*);
void sigma_shot_despawn(struct ShotObj*);

s8 sigma_shot_boxes[10][4] = {
    { 0, -1, 10, 10 },
    { -7, -8, 13, 14 },
    { -6, -7, 11, 12 },
    { -10, -10, 19, 19 },
    { -25, 82, 71, 24 },
    { -23, -25, 46, 48 },
    { 0, -11, 18, 14 },
    { -31, -5, 62, 7 },
    { -4, -33, 7, 63 },
    { -128, -18, -116, 25 },
};

u8 sigma_shot_debris[20] = {
    0x27,
    0x28,
    0x27,
    0x28,
    0x27,
    0x28,
    0,
    0,
    0x0F,
    6,
    0x16,
    0xF0,
    0xF8,
    0x16,
    2,
    0xFF,
    0x0D,
    0x0C,
    0x0D,
    0x0B,
};

u8 sigma_shot_init_box[4] = { 0xDD, 0xF1, 0x0F, 0x23 };

s8 sigma_bolt_x_offsets[2][2] = {
    { 0x20, -0x20 },
    { 0x10, -0x10 },
};
s8 sigma_bolt_y_offsets[2][2] = {
    { 0x20, 0 },
    { -0x20, 0x28 },
};

void (*sigma_bolt_funcs[])(struct ShotObj*) = {
    sigma_bolt_gather,
    sigma_bolt_launch,
    sigma_bolt_bounce_wall,
    sigma_bolt_bounce_floor,
    sigma_bolt_bounce_wall,
    sigma_bolt_idle,
};

void (*sigma_planted_scythe_funcs[])(struct ShotObj*) = {
    func_800A8E50,
    sigma_planted_scythe_stuck,
    sigma_planted_scythe_recall,
    sigma_planted_scythe_return,
};

void (*sigma_dart_funcs[])(struct ShotObj*) = {
    sigma_dart_spread,
    sigma_dart_wait,
    sigma_dart_strike,
    sigma_dart_aim,
    sigma_dart_fly,
};

void (*sigma_shot_subtype_funcs[])(struct ShotObj*) = {
    sigma_shot_cloak_scythe,
    sigma_shot_bolt,
    sigma_shot_bolt,
    sigma_shot_planted_scythe,
    sigma_shot_drift,
    sigma_shot_drift,
    sigma_shot_dart,
    func_800A9544,
    sigma_shot_cloak_fire,
    sigma_shot_dropped_scythe,
    sigma_shot_flash,
};

// sigma_shot_init
#ifdef MMX4_PC
void func_800A8628(struct ShotObj* self);
void func_800A9544(struct ShotObj* self);
void func_800A8E50(struct ShotObj* self);
void func_80021DBC(s16* arg0, s16* arg1, s32 arg2);
#endif

#ifdef MMX4_PC
void func_800A8628(struct ShotObj* self)
{
    struct WeaponObj* parent = self->unk7C;
    s32 subtype = (s8)self->unk2;
    s32 direction;

    self->state = 1;
    self->unk40 = parent->unk40;
    self->animation_table = parent->animation_table;
    self->unk3C = parent->unk3C;
    self->unk42 = parent->unk42;
    self->unk15 = parent->unk15;
    self->bg_offset = parent->bg_offset;
    self->x_pos = parent->x_pos;
    self->y_pos = parent->y_pos;
    self->unk16 = 5;
    self->unk58.data = NULL;
    self->unk50.data = NULL;
    self->unk54 = NULL;
    self->unk68 = NULL;

    switch (subtype) {
    case 0:
        self->unk60 = 9;
        set_animation(self, 5);
        break;
    case 1:
    case 2:
        self->unk58.collision_data = D_80106070;
        self->unk68 = (struct Unk_unk68*)sigma_shot_boxes[0];
        self->unk50.data = (u8*)sigma_shot_boxes[1];
        self->unk60 = 6;
        set_animation(self, 3);
        break;
    case 3:
        direction = (u8)angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
        if ((u8)direction < 9)
            direction = 0;
        else if ((u8)(direction - 9) < 8)
            direction = 0x10;
        self->unk94 = direction;
        self->unk60 = 9;
        self->y_pos.u.hi -= 0x15;
        self->x_pos.i.hi += self->unk15 ? 0x21 : -0x21;
        self->unk68 = (struct Unk_unk68*)sigma_shot_boxes[6];
        self->unk50.data = (u8*)sigma_shot_boxes[5];
        set_velocity_from_angle(MOVING_OBJECT(self), (u8)self->unk94);
        set_animation(self, 0x1E);
        func_8001540C(2, 5, self);
        break;
    case 4:
        self->x_vel.val = 0;
        self->y_vel.val = self->timer == 0 ? -0x80000 : 0x80000;
        self->unk50.data = (u8*)sigma_shot_boxes[8];
        self->unk60 = 6;
        set_animation(self, 0x23);
        func_8001540C(2, 7, self);
        break;
    case 5:
        self->x_vel.val = self->timer == 0 ? -0x80000 : 0x80000;
        self->y_vel.val = 0;
        self->unk50.data = (u8*)sigma_shot_boxes[7];
        self->unk60 = 6;
        set_animation(self, 0x25);
        func_8001540C(2, 7, self);
        break;
    case 6:
        self->unk58.data = (const u8*)D_801060F0;
        self->unk50.data = (u8*)sigma_shot_boxes[2];
        self->unk54 = (u8*)sigma_shot_boxes[3];
        self->unk95 = (u8)self->timer;
        self->unk60 = 6;
        self->unk90.i.lo = self->x_pos.i.hi + (self->unk15 ? -1 : 1) * (s8)sigma_shot_init_box[self->unk95];
        self->unk90.i.hi = self->y_pos.i.hi - 0x40;
        set_animation_frame(ANIMATED_OBJECT(self), 0x21, 2);
        break;
    case 7:
        self->unk96 = 6;
        self->unk60 = 9;
        self->unk50.data = (u8*)sigma_shot_boxes[5];
        self->unk94 = self->unk15 ? 5 : 7;
        set_animation(self, 0x1E);
        func_8001540C(2, 5, self);
        break;
    case 8: {
        struct QuadObj* quad = (struct QuadObj*)self->unk7C;
        struct MainObj* owner = (struct MainObj*)quad->unk5C;

        self->unk16 = 5;
        self->unk40 = owner->unk40;
        self->animation_table = (u32**)owner->animation_table;
        self->unk3C = (void*)owner->sprite_frames;
        self->unk42 = owner->unk42;
        self->unk15 = owner->unk15 ^ 0x40;
        self->bg_offset = owner->bg_offset;
        self->x_pos.i.hi = quad->x_pos.i.hi + quad->vertices[2].x.i.hi + 4;
        self->unk50.data = (u8*)sigma_shot_boxes[9];
        self->unk60 = 9;
        self->y_pos.i.hi = quad->y_pos.i.hi + quad->vertices[2].y.i.hi - 8;
        set_animation(self, 0x26);
        func_8001540C(2, 0xC, self);
        break;
    }
    case 9:
        self->y_vel.val = 0x60000;
        self->unk2C = 0x4200;
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->unk68 = (struct Unk_unk68*)sigma_shot_boxes[6];
        set_animation(self, 0x1E);
        break;
    case 10:
        set_animation(self, 0x2A);
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", func_800A8628);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_shot_at_position);
#else
s32 sigma_shot_at_position(struct ShotObj* self, s32 arg1, s32 arg2)
{
    POS_BOUNDS_CHECK_FAIL_RET0(self->x_pos.val, arg1)
    POS_BOUNDS_CHECK_FAIL_RET0(self->y_pos.val, arg2)
    return 1;
}
#endif

void sigma_shot_cloak_scythe(struct ShotObj* self)
{
    struct ShotObj* shot;
    struct WeaponObj* weapon;

    shot = self;
    weapon = shot->unk7C;
    animate_object(ANIMATED_OBJECT(shot));
    if (shot->animation_step.fields.event != 0) {
        shot->unk50.data = (u8*)sigma_shot_boxes[4];
    } else {
        shot->unk50.data = 0;
    }
    shot->unk15 = weapon->unk15;
    shot->x_pos.val = weapon->x_pos.val;
    shot->y_pos.val = weapon->y_pos.val;
    shot->on_screen = 0;
    if (weapon->on_screen != 0) {
        is_on_screen(BASE_OBJECT(shot));
        return;
    }
    shot->unk50.data = 0;
}

void sigma_bolt_gather(struct ShotObj* self)
{
    s8 collision;
    s32 x;
    s32 y;
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    if (self->unk2 == 1) {
        x = weapon->x_pos.val + FIXED(sigma_bolt_x_offsets[0][self->unk99]);
        y = weapon->y_pos.val + FIXED(sigma_bolt_y_offsets[0][self->unk9A]);
    } else {
        x = weapon->x_pos.val + FIXED(sigma_bolt_x_offsets[1][self->unk99]);
        y = weapon->y_pos.val + FIXED(sigma_bolt_y_offsets[1][1]);
    }
    collision = angle_to_point(OBJECT_HEADER(self), x, y);
    if (sigma_shot_at_position(self, x, y) & 0xFF) {
        self->timer = 0x14;
        self->unk5 = (u8)self->unk5 + 1;
    }
    set_velocity_from_angle(MOVING_OBJECT(self), collision & 0xFF);
}

void sigma_bolt_launch(struct ShotObj* self)
{
    struct ShotObj* shot;
    s32 velocity;
    s8 frame;

    shot = self;
    animate_object(ANIMATED_OBJECT(shot));
    if (--shot->timer == 0) {
        if (shot->unk2 == 1) {
            velocity = shot->unk99 != 0 ? FIXED(-5) : FIXED(5);
            shot->x_vel.val = velocity;
            shot->y_vel.val = 0;
            frame = (u8)shot->unk5 + 1;
        } else {
            frame = (u8)shot->unk5 + 2;
            velocity = FIXED(-5);
            shot->x_vel.val = 0;
            shot->y_vel.val = velocity;
        }
        shot->unk5 = frame;
    }
}

void sigma_bolt_bounce_wall(struct ShotObj* self)
{
    if (self->unk70 & 3) {
        self->x_vel.val = 0;
        if (self->unk5 == 2) {
            self->y_vel.val = FIXED(-5);
        } else {
            self->y_vel.val = FIXED(5);
        }
        self->unk5++;
    }
}

void sigma_bolt_bounce_floor(struct ShotObj* self)
{
    if (self->unk70 & 8) {
        self->unk5++;
        self->x_vel.val = self->unk99 != 0 ? FIXED(5) : FIXED(-5);
        if (self->unk2 == 2) {
            self->x_vel.val *= -1;
        }
        self->y_vel.val = 0;
    }
}

void sigma_bolt_idle(struct ShotObj* self)
{
}

void sigma_shot_bolt(struct ShotObj* self)
{
    sigma_bolt_funcs[self->unk5](self);
    if (func_8002DD04(MAIN_OBJECT(self)) != 0) {
        self->state = 2;
    }
    animate_object(self);
    move_object(MOVING_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7C->state == 4) {
        self->state = 2;
    }
}

// sigma_planted_scythe_fly
#ifdef MMX4_PC
void func_800A8E50(struct ShotObj* self)
{
    s32 x_speed;
    s32 y_speed;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)self->unk94);
    self->x_vel.val *= 6;
    self->y_vel.val *= 6;
    if (self->unk70 & 3) {
        self->unk5++;
        start_screen_shake_x(0x14, 4, 2);
        set_animation(self, 0x1F);
        self->timer = 0x18;
        self->unk15 = ((self->unk70 & 2) == 0) << 6;
        self->unk95 = 3;
        x_speed = self->unk15 != 0 ? 0xFFED0000 : 0x130000;
        y_speed = 0xFFEA0000;
    } else if (self->unk70 & 8) {
        self->unk5++;
        self->unk15 ^= 0x40;
        start_screen_shake_y(0x14, 4, 2);
        set_animation(self, 0x20);
        self->timer = 0x24;
        self->unk95 = 4;
        x_speed = self->unk15 != 0 ? 0xFFF10000 : 0xF0000;
        y_speed = 0;
    } else {
        return;
    }
    spawn_debris_offset(6, sigma_shot_debris, MAIN_OBJECT(self), x_speed, y_speed);
    stop_sound(2, 5);
    func_8001540C(2, 6, self);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", func_800A8E50);
#endif

void sigma_planted_scythe_stuck(struct ShotObj* self)
{
    struct VisualObj* visual;

    MAIN_OBJECT(self->unk7C)->ext.main_68.next_attack = self->unk95 - 2;
    animate_object(ANIMATED_OBJECT(self));
    if (--self->timer == 0) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = self->unk95;
            visual->unk50 = (struct PlayerObj*)self;
            self->timer = (self->unk95 == 4) ? 0x24 : 0x18;
        }
    }
}

void sigma_planted_scythe_recall(struct ShotObj* self)
{
    s32 x;
    s32 target_x;
    struct WeaponObj* weapon;

    self->unk5++;
    weapon = self->unk7C;
    x = weapon->x_pos.i.hi;
    if (weapon->unk15 == 0) {
        target_x = x - 0x21;
    } else {
        target_x = x + 0x21;
    }
    self->unk90.i.lo = target_x;
    self->unk90.u.hi = weapon->y_pos.u.hi - 0x15;
    set_animation(self, 0x1E);
    func_8001540C(2, 5, self);
}

void sigma_planted_scythe_return(struct ShotObj* self)
{
    struct WeaponObj* owner;

    owner = self->unk7C;
    self->unk94 = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(owner));
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)self->unk94);
    self->x_vel.val *= 6;
    self->y_vel.val *= 6;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (sigma_shot_at_position(self, owner->x_pos.val, owner->y_pos.val) & 0xFF) {
        self->state = 2;
        MAIN_OBJECT(owner)->ext.main_68.scythe = NULL;
    }
}

void sigma_shot_planted_scythe(struct ShotObj* self)
{
    sigma_planted_scythe_funcs[self->unk5](self);
    is_on_screen((struct BaseObj*)self);
    if (self->unk7C->state == 2) {
        self->state = 2;
    }
}

void sigma_shot_drift(struct ShotObj* self)
{
    animate_object(self);
    move_object((struct MovingObj*)self);
    is_on_screen((struct BaseObj*)self);
}

void sigma_dart_spread(struct ShotObj* self)
{
    self->unk94 = angle_to_point(OBJECT_HEADER(self), self->unk90.i.lo << 0x10, self->unk90.i.hi << 0x10);
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)self->unk94);
    self->x_vel.val *= 3;
    self->y_vel.val *= 3;
    move_object(MOVING_OBJECT(self));
    if (sigma_shot_at_position(self,
            self->unk90.i.lo << 0x10, self->unk90.i.hi << 0x10)
        & 0xFF) {
        self->unk5++;
        self->timer = (self->unk95 + 1) * 0x28;
    }
}

void sigma_dart_wait(struct ShotObj* self)
{
    struct PlayerObj* player = &g_Player;

    if (--self->timer == 0) {
        self->unk5++;
        self->unk90.u.lo = player->x_pos.u.hi;
        self->unk90.u.hi = player->y_pos.u.hi;
        func_8001540C(2, 0xB, self);
    }
}

void sigma_dart_strike(struct ShotObj* self)
{
    self->unk94 = angle_to_point(OBJECT_HEADER(self), self->unk90.i.lo << 0x10, self->unk90.i.hi << 0x10);
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)self->unk94);
    self->x_vel.val *= 6;
    self->y_vel.val *= 6;
    if ((sigma_shot_at_position(self,
             self->unk90.i.lo << 0x10, self->unk90.i.hi << 0x10)
            & 0xFF)
        || (self->unk98 != 0)) {
        self->timer = 0xF0;
        self->unk5++;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_dart_aim);
#else
void sigma_dart_aim(struct ShotObj* self)
{
    if (--self->timer == 0) {
        self->unk5++;
        self->unk94 = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
        set_velocity_from_angle(MOVING_OBJECT(self), self->unk94 & 0xFF);
        self->x_vel.val *= 6;
        self->y_vel.val *= 6;
        func_8001540C(2, 0xB, self);
    }
    animate_object(ANIMATED_OBJECT(self));
}
#endif

void sigma_dart_fly(struct ShotObj* self)
{
    animate_object(self);
    move_object((struct MovingObj*)self);
}

void sigma_shot_dart(struct ShotObj* self)
{
    self->unk98 = func_8002DD04(MAIN_OBJECT(self));
    sigma_dart_funcs[self->unk5](self);
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7C->state == 2) {
        self->state = 2;
    }
}

// sigma_shot_spin_scythe
#ifdef MMX4_PC
void func_800A9544(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;
    u8* angle = (u8*)&self->unk94;
    u8* delay = (u8*)&self->unk96;

    if (--*delay == 0) {
        if (self->unk15 != 0)
            *angle = (*angle - 1) & 0xF;
        else
            *angle = (*angle + 1) & 0xF;
        *delay = 6;
    }
    self->unk90.i.lo = 0x40;
    self->unk90.i.hi = 0x40;
    func_80021DBC(&self->unk90.i.lo, &self->unk90.i.hi, *angle);
    self->x_pos.i.hi = owner->x_pos.i.hi + (self->unk15 != 0 ? self->unk90.i.lo + 0x30 : self->unk90.i.lo - 0x30);
    self->y_pos.i.hi = owner->y_pos.i.hi + self->unk90.i.hi + 0x30;
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (*angle == 6)
        self->state = 2;
    if (self->unk7C->state == 2)
        self->state = 2;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", func_800A9544);
#endif

void sigma_shot_cloak_fire(struct ShotObj* self)
{
    struct WeaponObj* owner;

    owner = self->unk7C;
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
    }
    self->x_pos.u.hi = owner->x_pos.u.hi + owner->y_vel.u.hi;
    self->y_pos.u.hi = owner->y_pos.u.hi + owner->unk28.u.hi;
    if (!(main_bss_state.frame_counter % 8)) {
        spawn_debris(6, sigma_shot_debris, self);
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_shot_dropped_scythe(struct ShotObj* self)
{
    switch (self->unk5) {
    case 0:
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->y_vel.val < 0) {
            self->y_vel.val = 0;
            self->unk5++;
        }
        break;
    case 1:
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->unk70 & 8) {
            self->unk5++;
            set_animation(self, 0x20);
            func_8001540C(2, 6, self);
        }
        break;
    }

    is_on_screen(BASE_OBJECT(self));
}

void sigma_shot_flash(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    self->x_pos.u.hi = weapon->x_pos.u.hi;
    self->y_pos.u.hi = weapon->y_pos.u.hi;
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
    }
}

void sigma_shot_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    func_8002D9BC(self);
    sigma_shot_subtype_funcs[self->unk2](self);
    self->unk42 &= 0x7FFF;
    if (self->unk2 != 0) {
        if (func_8002B160(BASE_OBJECT(self)) == 0) {
            CollisionRelated(PLAYER_OBJECT(self));
            return;
        }
        self->state = 2;
    }
}

void sigma_shot_despawn(struct ShotObj* self)
{
    s8 state = self->unk2;

    switch (state) {
    case 1:
    case 2:
        MAIN_OBJECT(self->unk7C)->ext.main_68.active_shots--;
        break;
    case 6:
        MAIN_OBJECT(self->unk7C)->ext.main_68.count--;
        break;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void sigma_shot_update(struct ShotObj* self)
{
    sigma_shot_state_funcs[self->state](self);
}

void (*sigma_shot_state_funcs[])(struct ShotObj*) = {
    func_800A8628,
    sigma_shot_run,
    sigma_shot_despawn,
};
