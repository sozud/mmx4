// MainObj, main_object_update_funcs[25]
// 80057100..80058158
#include "common.h"
#include "func_tables.h"

void caterkiller_update(struct MainObj* self)
{
    caterkiller_state_funcs[self->state](self);
    if (self->ext.main_25.unk88 == 0) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// caterkiller_init
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057160);

// caterkiller_main
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057308);

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
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_8005754C);

void caterkiller_crawl_end(struct MainObj* self)
{
    s32 distance;
    s32 player_y;
    s32 object_y;

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
    player_y = g_Player.y_pos.i.hi;
    object_y = self->y_pos.i.hi;
    distance = player_y - object_y;
    if (distance >= 0 ? distance < 0x1A : object_y - player_y <= 0x19) {
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
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057874);

void caterkiller_lunge_end(struct MainObj* self)
{
    s32 distance;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_25.unk84 = 1;
    }
    if (self->animation_step.fields.event == 1) {
        self->ext.main_25.unk84 = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed == 0) {
        distance = g_Player.y_pos.i.hi - self->y_pos.i.hi;
        if (distance > -1) {
            if (distance <= 0x19) {
                self->unk6 = 0;
            } else {
                set_animation(self, 0);
                self->unk5 = 2;
                self->unk6 = 0;
                self->ext.main_25.unk80 = 0x40;
                self->ext.main_25.unk84 = 0;
            }
        } else {
            distance = self->y_pos.i.hi - g_Player.y_pos.i.hi;
            if (distance < 0x1A) {
                self->unk6 = 0;
            } else {
                set_animation(self, 0);
                self->unk5 = 2;
                self->unk6 = 0;
                self->ext.main_25.unk80 = 0x40;
                self->ext.main_25.unk84 = 0;
            }
        }
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
INCLUDE_ASM("main/nonmatchings/mains/main_25_caterkiller", func_80057C00);

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
        self->y_pos.u.hi -= 0x18;
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
            self->x_pos.u.hi -= 2;
        } else {
            self->x_pos.u.hi += 2;
        }
        self->gravity = FIXED(0.2578125);
        self->ext.main_25.unk84 = 2;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
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
};

struct Unk_unk68* D_800FD04C[] = {
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
