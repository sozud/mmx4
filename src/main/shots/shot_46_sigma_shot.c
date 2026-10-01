// ShotObj, shot_object_update_funcs[46]
// 800A8628..800A9964
#include "common.h"

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

s8 sigma_bolt_offsets[4][2] = {
    { 0x20, -0x20 },
    { 0x10, -0x10 },
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
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", func_800A8628);

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_bolt_gather);
#else
void sigma_bolt_gather(struct ShotObj* self)
{
    s8 collision;
    s32 x;
    s32 y;
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    if (self->unk2 == 1) {
        x = weapon->x_pos.val + (sigma_bolt_offsets[0][self->unk99] << 16);
        y = weapon->y_pos.val + (sigma_bolt_offsets[2][self->pad9A[0]] << 16);
    } else {
        x = weapon->x_pos.val + (sigma_bolt_offsets[1][self->unk99] << 16);
        y = weapon->y_pos.val + (sigma_bolt_offsets[3][1] << 16);
    }
    collision = angle_to_point(OBJECT_HEADER(self), x, y);
    if (sigma_shot_at_position(self, x, y) & 0xFF) {
        self->timer = 0x14;
        self->unk5 = (u8)self->unk5 + 1;
    }
    set_velocity_from_angle(MOVING_OBJECT(self), collision & 0xFF);
}
#endif

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
    s32 var_a1;

    var_a1 = FIXED(-5);
    if (self->unk70 & 8) {
        self->unk5++;
        if (self->unk99 != 0) {
            var_a1 = FIXED(5);
        }
        self->x_vel.val = var_a1;
        if (self->unk2 == 2) {
            self->x_vel.val = -var_a1;
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
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", func_800A8E50);

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_planted_scythe_return);
#else
void sigma_planted_scythe_return(struct ShotObj* self)
{
    struct WeaponObj* owner;

    owner = self->unk7C;
    self->pad94 = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(owner));
    set_velocity_from_angle(MOVING_OBJECT(self), self->pad94 & 0xFF);
    self->x_vel.val *= 6;
    self->y_vel.val *= 6;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (sigma_shot_at_position(self, owner->x_pos.val, owner->y_pos.val) & 0xFF) {
        self->state = 2;
        MAIN_OBJECT(owner)->ext.main_68.scythe = NULL;
    }
}
#endif

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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_dart_spread);
#else
void sigma_dart_spread(struct ShotObj* self)
{

    set_velocity_from_angle(MOVING_OBJECT(self), (u8)(self->pad94 = angle_to_point(OBJECT_HEADER(self), self->unk90.i.lo << 0x10, self->unk90.i.hi << 0x10)));
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
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_dart_wait);
#else
void sigma_dart_wait(struct ShotObj* self)
{
    if (--self->timer == 0) {
        self->unk5++;
        self->unk90.u.lo = g_Player.x_pos.u.hi;
        self->unk90.u.hi = g_Player.y_pos.u.hi;
        func_8001540C(2, 0xB, self);
    }
}
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_dart_strike);
#else
void sigma_dart_strike(struct ShotObj* self)
{
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)(self->pad94 = angle_to_point(OBJECT_HEADER(self), self->unk90.i.lo << 0x10, self->unk90.i.hi << 0x10)));
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
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", sigma_dart_aim);
#else
void sigma_dart_aim(struct ShotObj* self)
{
    if (--self->timer == 0) {
        self->unk5++;
        self->pad94 = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
        set_velocity_from_angle(MOVING_OBJECT(self), self->pad94 & 0xFF);
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
INCLUDE_ASM("main/nonmatchings/shots/shot_46_sigma_shot", func_800A9544);

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
    if (!(D_80141BD8.unk0 % 8)) {
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
