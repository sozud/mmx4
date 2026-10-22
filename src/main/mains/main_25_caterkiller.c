// MainObj, main_object_update_funcs[25]
// 80057100..80058158
#include "common.h"
#include "main/mains/main_25_caterkiller.h"
#include "main/1CF60.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/1E1BC.h"
#endif

void caterkiller_despawn(struct MainObj* arg0);

// caterkiller_step_funcs
void caterkiller_resume_step(struct MainObj* arg0);
void caterkiller_crawl(struct MainObj* arg0);
void caterkiller_lunge(struct MainObj* arg0);
void caterkiller_fall(struct MainObj* arg0);
void caterkiller_climb(struct MainObj* arg0);
void caterkiller_wait_above(struct MainObj* arg0);

extern void (*caterkiller_state_funcs[])(struct MainObj*);
extern void (*caterkiller_crawl_funcs[])(struct MainObj*);
extern void (*caterkiller_lunge_funcs[])(struct MainObj*);
extern void (*caterkiller_fall_funcs[])(struct MainObj*);
extern void (*caterkiller_climb_funcs[])(struct MainObj*);

#ifdef MMX4_PC
void caterkiller_check_fall(struct MainObj*);
extern void (*caterkiller_step_funcs[])(struct MainObj*);
extern union AnimationStep* caterkiller_animations[10];
extern struct Unk_unk68 D_800FCFD4[];
extern struct Unk_unk68 D_800FCFE4[];
extern struct Unk_unk68 D_800FCFF4[];
extern struct Unk_unk68 D_800FD004[];
extern struct Unk_unk68 D_800FD014[];
extern struct Unk_unk68* D_800FD018[12];
extern struct Unk_unk68* D_800FD048[];
extern struct Unk_unk68* D_800FD04C[];
extern struct Unk_unk68 D_80106EF4[];
extern u8 caterkiller_debris[4];
#endif

void caterkiller_update(struct MainObj* self)
{
    caterkiller_state_funcs[self->state](self);
    if (self->ext.main_25.unk88 == 0) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// caterkiller_init
#ifdef MMX4_PC
void func_80057160(struct MainObj* self);
void func_80057308(struct MainObj* self);
void func_8005754C(struct MainObj* self);
void func_80057874(struct MainObj* self);
void func_80057C00(struct MainObj* self);
#endif

#ifdef MMX4_PC
// src/main/mains/main_25_caterkiller.c

void func_80057160(struct MainObj* self)
{
    self->hp = 3;
    self->contact_damage = 3;
    self->collision_data = D_80106EF4;
    self->animation_table = (const u8* const*)caterkiller_animations;
    self->invincibility_timer = 0;
    self->unk16 = 6;
    self->terrain_box = D_800FD014;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    caterkiller_face_player(self);

    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    if (self->unk2 == 0) {
        set_animation(self, 0);
        self->unk5 = 2;
        self->ext.main_25.unk80 = 0x40;
        self->hurt_box = D_800FCFD4;
        self->attack_box = D_800FCFF4;
        self->gravity = 0;
        self->air_state = 0;
        self->ext.main_25.unk84 = 0;
    } else if (self->unk2 == 1 || self->unk2 == 2) {
        set_animation(self, 4);
        self->gravity = 0x4200;
        self->hurt_box = D_800FCFE4;
        self->attack_box = D_800FD004;
        self->unk6 = 1;
        self->air_state = 1;
        if (self->unk2 == 1) {
            self->unk5 = 4;
            self->ext.main_25.unk84 = 2;
        } else {
            self->unk5 = 6;
            self->ext.main_25.unk84 = 2;
        }
    }
    self->ext.main_25.unk88 = 0;
    self->state = 1;
    self->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057160);
#endif

// caterkiller_main
#ifdef MMX4_PC
void func_80057308(struct MainObj* self)
{
    unsigned index;

    caterkiller_check_fall(self);
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    caterkiller_step_funcs[self->unk5](self);
    if (self->y_speed < -0x50000)
        self->y_speed = -0x50000;
    if (self->unk5 == 6)
        return;

    self->ext.main_25.saved_unk5 = self->unk5;
    index = self->ext.main_25.unk84 * 2;
    self->attack_box = index == 0 ? D_800FD048[0] : D_800FD04C[index - 1];
    func_8002D9BC(self);
    self->attack_box = D_800FD04C[index];
    func_8002D9BC(self);
    self->hurt_box = D_800FD018[index];
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, caterkiller_debris, self);
        drop_item(BASE_OBJECT(self), 0xC);
        self->state = 2;
        return;
    }
    self->hurt_box = D_800FD018[index + 1];
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, caterkiller_debris, self);
        drop_item(BASE_OBJECT(self), 0xC);
        self->state = 2;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x28) != 0) {
        self->state = 2;
    } else {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057308);
#endif

void caterkiller_despawn(struct MainObj* self)
{
    self->ext.main_25.unk80 = 0;
    self->ext.main_25.unk84 = 0;
    self->ext.main_25.unk88 = 0;
    self->ext.main_25.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void caterkiller_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_25.saved_unk5;
}

void caterkiller_crawl(struct MainObj* self)
{
    caterkiller_crawl_funcs[self->unk6](self);
}

void caterkiller_crawl_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    caterkiller_face_player(self);
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-1);
    } else {
        self->x_speed = FIXED(1);
    }
    self->unk6 = 1;
}

// caterkiller_crawl_move
#ifdef MMX4_PC
void func_8005754C(struct MainObj* self)
{
    s32 dy;
    s32 dx;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2)
        self->ext.main_25.unk84 = 1;
    if (self->animation_step.fields.event == 1)
        self->ext.main_25.unk84 = 0;

    self->ext.main_25.unk80--;
    if (self->ext.main_25.unk80 == 0 || (self->unk15 == 0 && (self->collision_flags & 2)) || (self->unk15 != 0 && (self->collision_flags & 1))) {
        self->unk6 = 2;
        self->x_accel = -0x1000;
        self->ext.main_25.unk80 = 0x80;
    }

    dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
    if (dy > -0x1A && dy < 0x1A) {
        set_animation(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
        self->ext.main_25.unk84 = 0;
    }

    if (dy >= 0x49) {
        dx = g_Player.x_pos.i.hi - self->x_pos.i.hi;
        if (dx > -0x31 && dx < 0x31) {
            self->air_state = 1;
            self->x_speed = 0;
            self->x_accel = 0;
            set_animation(self, 2);
            self->ext.main_25.unk88 = 1;
            self->unk5 = 5;
            self->unk6 = 0;
            self->ext.main_25.unk84 = 5;
        }
    }
    move_object(MOVING_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_8005754C);
#endif

void caterkiller_crawl_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_25.unk84 = 1;
    }
    if (self->animation_step.fields.event == 1) {
        self->ext.main_25.unk84 = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed != 0) {
        return;
    }
    self->x_accel = 0;
    if (ABS(g_Player.y_pos.i.hi, self->y_pos.i.hi) <= 0x19) {
        set_animation(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
        self->ext.main_25.unk84 = 0;
        return;
    }
    if (self->unk15 == 0) {
        self->unk15 = 0x40;
        self->x_speed = FIXED(1);
    } else {
        self->unk15 = 0;
        self->x_speed = FIXED(-1);
    }
    self->unk6 = 1;
}

void caterkiller_lunge(struct MainObj* self)
{
    caterkiller_lunge_funcs[self->unk6](self);
}

void caterkiller_lunge_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    caterkiller_face_player(self);
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-2);
    } else {
        self->x_speed = FIXED(2);
    }
    self->unk6 = 1;
}

// caterkiller_lunge_move
#ifdef MMX4_PC
void func_80057874(struct MainObj* self)
{
    s32 dy;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2)
        self->ext.main_25.unk84 = 1;
    if (self->animation_step.fields.event == 1)
        self->ext.main_25.unk84 = 0;
    move_object(MOVING_OBJECT(self));

    dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
    if (dy <= -0x1A || dy >= 0x1A) {
        set_animation(self, 0);
        self->unk5 = 2;
        self->unk6 = 0;
        self->ext.main_25.unk80 = 0x40;
        self->ext.main_25.unk84 = 0;
        return;
    }
    if ((self->unk15 == 0 && self->x_pos.i.hi < g_Player.x_pos.i.hi) || (self->unk15 != 0 && g_Player.x_pos.i.hi < self->x_pos.i.hi)) {
        self->x_accel = -0x1000;
        self->unk6 = 2;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057874);
#endif

void caterkiller_lunge_end(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_25.unk84 = 1;
    }
    if (self->animation_step.fields.event == 1) {
        self->ext.main_25.unk84 = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed == 0) {
        if (ABS(g_Player.y_pos.i.hi, self->y_pos.i.hi) <= 0x19) {
            self->unk6 = 0;
            return;
        }
        set_animation(self, 0);
        self->unk5 = 2;
        self->unk6 = 0;
        self->ext.main_25.unk80 = 0x40;
        self->ext.main_25.unk84 = 0;
    }
}

void caterkiller_fall(struct MainObj* self)
{
    caterkiller_fall_funcs[self->unk6](self);
}

void caterkiller_fall_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->gravity = FIXED(0.2578125);
    }
    if (self->animation_step.fields.event == 1) {
        self->ext.main_25.unk84 = 2;
        set_animation(self, 4);
        self->unk6 = 1;
    }
}

void caterkiller_fall_drop(struct MainObj* self)
{
    s16 tx;
    s16 ty;
    u8 hits;

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    tx = self->x_pos.u.hi + self->terrain_box->unk0;
    ty = self->terrain_box->unk3 + (self->y_pos.u.hi + self->terrain_box->unk1) + 0x1B;

    hits = func_8002D724(PLAYER_OBJECT(self), tx, ty);
    tx -= self->terrain_box->unk2;
    hits |= func_8002D724(PLAYER_OBJECT(self), tx, ty);
    hits |= func_8002D724(PLAYER_OBJECT(self), tx + self->terrain_box->unk2 * 2, ty);

    if (hits != 0 && hits != 0x24) {
        set_animation(self, 5);
        self->gravity = 0;
        self->y_speed = 0;
        self->unk6 = 2;
    }
}

// caterkiller_fall_land
#ifdef MMX4_PC
void func_80057C00(struct MainObj* self)
{
    s32 dy;

    animate_object(ANIMATED_OBJECT(self));
    switch (self->animation_step.fields.event) {
    case 1:
        dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
        if (dy > -0x1A && dy < 0x1A) {
            set_animation(self, 1);
            self->unk5 = 3;
            self->unk6 = 0;
        } else {
            set_animation(self, 0);
            self->unk5 = 2;
            self->unk6 = 0;
            self->ext.main_25.unk80 = 0x40;
        }
        self->ext.main_25.unk84 = 0;
        break;
    case 2:
        self->y_pos.u.hi += 5;
        break;
    case 3:
        self->ext.main_25.unk84 = 3;
        self->y_pos.u.hi += 0xC;
        break;
    case 4:
        self->ext.main_25.unk84 = 4;
        self->y_speed = -0x50000;
        self->y_pos.u.hi += 0xC;
        break;
    case 5:
        if (self->collision_flags & 8) {
            self->air_state = 0;
            self->y_speed = 0;
        } else {
            move_object(MOVING_OBJECT(self));
        }
        break;
    case 6:
        self->ext.main_25.unk84 = 5;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057C00);
#endif

void caterkiller_climb(struct MainObj* self)
{
    caterkiller_climb_funcs[self->unk6](self);
}

void caterkiller_climb_start(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (self->animation_step.fields.event != 0) {
        set_animation((struct Unk19*)self, 3);
        self->unk6 = 1;
    }
}

void caterkiller_climb_hop(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 4);
        self->ext.main_25.unk84 = 2;
        self->gravity = FIXED(0.2578125);
        self->unk6 = 2;
    }
}

void caterkiller_climb_rise(struct MainObj* self)
{
    s16 tx;
    s16 ty;
    u8 r;
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    tx = self->x_pos.u.hi + self->terrain_box->unk0;
    ty = (self->y_pos.u.hi + self->terrain_box->unk1) - self->terrain_box->unk3;
    r = func_8002D724(PLAYER_OBJECT(self), tx, ty);
    tx -= self->terrain_box->unk2;
    r = r | func_8002D724(PLAYER_OBJECT(self), tx, ty);
    r = r | func_8002D724(PLAYER_OBJECT(self), tx + self->terrain_box->unk2 * 2, ty);
    if (r != 0 && r != 0x24) {
        self->unk6 = 3;
    }
}

void caterkiller_climb_cling(struct MainObj* self)
{
    s16 tx;
    s16 ty;
    u8 r;
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    tx = self->x_pos.u.hi + self->terrain_box->unk0;
    ty = (self->y_pos.u.hi + self->terrain_box->unk1) - self->terrain_box->unk3;
    r = func_8002D724(PLAYER_OBJECT(self), tx, ty);
    tx -= self->terrain_box->unk2;
    r = r | func_8002D724(PLAYER_OBJECT(self), tx, ty);
    r = r | func_8002D724(PLAYER_OBJECT(self), tx + self->terrain_box->unk2 * 2, ty);
    if (r == 0 || r == 0x24) {
        self->ext.main_25.unk88 = 0;
        self->unk5 = 4;
        self->unk6 = 1;
    }
}

void caterkiller_wait_above(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0x10) {
        self->unk5 = 4;
        self->y_pos.i.hi -= 0x18;
    }
}

void caterkiller_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

void caterkiller_check_fall(struct MainObj* self)
{
    if ((self->unk5 != 4) && (self->unk5 != 6) && !(self->collision_flags & 8)) {
        set_animation(self, 3);
        self->unk5 = 4;
        self->unk6 = 0;
        if (self->unk15 == 0) {
            self->x_pos.i.hi -= 2;
        } else {
            self->x_pos.u.hi += 2;
        }
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_accel = 0;
        self->ext.main_25.unk84 = 2;
        self->air_state = 1;
    }
}

struct Unk_unk68 D_800FCFD4[] = {
    { -3, -5, 0x29, 8 },
};

struct Unk_unk68 D_800FCFD8[] = {
    { -2, -24, 0xC, 0x1C },
};

struct Unk_unk68 D_800FCFDC[] = {
    { -16, -16, 0x13, 0x14 },
};

struct Unk_unk68 D_800FCFE0[] = {
    { -23, -6, 0x12, 0xA },
};

struct Unk_unk68 D_800FCFE4[] = {
    { -6, -28, 0xC, 0x37 },
};

struct Unk_unk68 D_800FCFE8[] = {
    { -10, -5, 0xF, 0x15 },
};

struct Unk_unk68 D_800FCFEC[] = {
    { 8, -20, 0xE, 0x13 },
};

struct Unk_unk68 D_800FCFF0[] = {
    { -2, -19, 0x13, 0x15 },
};

struct Unk_unk68 D_800FCFF4[] = {
    { 0, -2, 0x24, 5 },
};

struct Unk_unk68 D_800FCFF8[] = {
    { -1, -21, 9, 0x18 },
};

struct Unk_unk68 D_800FCFFC[] = {
    { -12, -13, 0xE, 0x10 },
};

struct Unk_unk68 D_800FD000[] = {
    { -20, -4, 0x11, 7 },
};

struct Unk_unk68 D_800FD004[] = {
    { -4, -26, 8, 0x33 },
};

struct Unk_unk68 D_800FD008[] = {
    { -8, -3, 0xD, 0x13 },
};

struct Unk_unk68 D_800FD00C[] = {
    { 9, -18, 0xB, 0x10 },
};

struct Unk_unk68 D_800FD010[] = {
    { 0, -16, 0xF, 0x11 },
};

struct Unk_unk68 D_800FD014[] = {
    { 0, -4, 0xD, 8 },
};

struct Unk_unk68* D_800FD018[] = {
    D_800FCFD4,
    D_800FCFD8,
    D_800FCFD4,
    D_800FCFDC,
    D_800FCFE4,
    D_800FCFE4,
    D_800FCFE8,
    D_800FCFEC,
    D_800FCFD4,
    D_800FCFF0,
    D_800FCFD4,
    D_800FCFE0,
};

struct Unk_unk68* D_800FD048[] = {
    D_800FCFF4,
#ifndef MMX4_WIN32
};

struct Unk_unk68* D_800FD04C[] = {
#endif
    D_800FCFF8,
    D_800FCFF4,
    D_800FCFFC,
    D_800FD004,
    D_800FD004,
    D_800FD008,
    D_800FD00C,
    D_800FCFF4,
    D_800FD010,
    D_800FCFF4,
    D_800FD000,
};

union AnimationStep caterkiller_anim_0[] = {
    { 0x0001000C },
    { 0x0101020C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x04FC010C },
};

union AnimationStep caterkiller_anim_1[] = {
    { 0x00010006 },
    { 0x01010206 },
    { 0x02010006 },
    { 0x03010006 },
    { 0x04FC0106 },
};

union AnimationStep caterkiller_anim_2[] = {
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010002 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x05010009 },
    { 0x05000101 },
};

union AnimationStep caterkiller_anim_3[] = {
    { 0x05010002 },
    { 0x09010201 },
    { 0x09010005 },
    { 0x0A010003 },
    { 0x0A000101 },
};

union AnimationStep caterkiller_anim_4[] = {
    { 0x0B010006 },
    { 0x0CFF0106 },
};

union AnimationStep caterkiller_anim_5[] = {
    { 0x0D010201 },
    { 0x0D010003 },
    { 0x0E010301 },
    { 0x0E010004 },
    { 0x0F010401 },
    { 0x0F010504 },
    { 0x10010601 },
    { 0x10010004 },
    { 0x11010007 },
    { 0x11000101 },
};

union AnimationStep caterkiller_anim_6[] = {
    { 0x12000101 },
};

union AnimationStep caterkiller_anim_7[] = {
    { 0x13000101 },
};

union AnimationStep caterkiller_anim_8[] = {
    { 0x14000101 },
};

union AnimationStep caterkiller_anim_9[] = {
    { 0x15000101 },
};

union AnimationStep* caterkiller_animations[] = {
    caterkiller_anim_0,
    caterkiller_anim_1,
    caterkiller_anim_2,
    caterkiller_anim_3,
    caterkiller_anim_4,
    caterkiller_anim_5,
    caterkiller_anim_6,
    caterkiller_anim_7,
    caterkiller_anim_8,
    caterkiller_anim_9,
};

u8 caterkiller_debris[] = {
    0x06,
    0x07,
    0x08,
    0x09,
};

void (*caterkiller_state_funcs[])() = {
    func_80057160,
    func_80057308,
    caterkiller_despawn,
};

void (*caterkiller_step_funcs[])() = {
    enemy_hit_reaction,
    caterkiller_resume_step,
    caterkiller_crawl,
    caterkiller_lunge,
    caterkiller_fall,
    caterkiller_climb,
    caterkiller_wait_above,
};

void (*caterkiller_crawl_funcs[])() = {
    caterkiller_crawl_start,
    func_8005754C,
    caterkiller_crawl_end,
};

void (*caterkiller_lunge_funcs[])() = {
    caterkiller_lunge_start,
    func_80057874,
    caterkiller_lunge_end,
};

void (*caterkiller_fall_funcs[])() = {
    caterkiller_fall_start,
    caterkiller_fall_drop,
    func_80057C00,
};

void (*caterkiller_climb_funcs[])() = {
    caterkiller_climb_start,
    caterkiller_climb_hop,
    caterkiller_climb_rise,
    caterkiller_climb_cling,
};
