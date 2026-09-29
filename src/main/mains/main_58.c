// MainObj, main_object_update_funcs[58]
// 800743FC..80074E84
#include "common.h"
#include "func_tables.h"

void beam_drone_update(struct MainObj* self)
{
    beam_drone_state_funcs[self->state](self);
}

// beam_drone_init
INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074438);

// beam_drone_main
INCLUDE_ASM("main/nonmatchings/mains/main_58", func_800745E8);

void beam_drone_despawn(struct MainObj* self)
{
    self->ext.main_58.unk88 = 2;
    if (self->unk2 == 0) {
        despawn_object(OBJECT_HEADER(self));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void beam_drone_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_58.saved_unk5;
}

void beam_drone_drop(struct MainObj* self)
{
    beam_drone_drop_funcs[self->unk6](self);
}

void beam_drone_drop_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(ANIMATED_OBJECT(self), 0);
    self->unk6++;
}

void beam_drone_drop_fall(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    timer = self->unk7E - 1;
    self->unk7E = timer;
    if (timer == 0) {
        self->unk5 = 3;
        self->x_speed = 0;
        self->y_speed = 0;
        self->unk7E = 0x14;
        self->unk6 = 0;
    }
}

void beam_drone_charge(struct MainObj* self)
{
    beam_drone_charge_funcs[self->unk6](self);
}

void beam_drone_charge_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 7);
    beam_drone_spawn_charge(ANIMATED_OBJECT(self));
    func_8001540C(2, 0x2D, self);
    self->unk7C = 0x50;
    self->unk6++;
}

void beam_drone_charge_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 4;
        self->ext.main_58.unk88 = 1;
        self->unk6 = 0;
    }
}

void beam_drone_fire(struct MainObj* self)
{
    beam_drone_fire_funcs[self->unk6](self);
}

void beam_drone_fire_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    beam_drone_spawn_beam(self);
    func_8001540C(2, 0x2C, self);
    self->unk7C = 0x12;
    self->unk6++;
}

void beam_drone_fire_beam(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        set_animation(self, 2);
        self->ext.main_58.unk88 = 2;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void beam_drone_fire_fade(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->ext.main_58.unk88 = 0;
        self->unk7C = 0x2A;
        self->unk6++;
    }
}

void beam_drone_fire_end(struct MainObj* self)
{
    s32 state;
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 0);
        state = self->unk2;
        if (state != 0) {
            state = 5;
        } else {
            state = 2;
        }
        self->unk5 = state;
        self->unk6 = 0;
        self->unk7E = 0x28;
    }
}

void beam_drone_leave(struct MainObj* self)
{
    beam_drone_leave_funcs[self->unk6](self);
}

void beam_drone_leave_start(struct MainObj* self)
{
    s32 velocity;

    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->unk7C = 0x3C;
    if (self->unk2 == 1) {
        velocity = 0x18000;
        if (self->y_pos.i.hi >= 0x369) {
            velocity = -0x18000;
        }
        self->y_speed = velocity;
    } else {
        velocity = -0x18000;
        if (self->x_pos.i.hi >= 0x951) {
            velocity = 0x18000;
        }
        self->x_speed = velocity;
    }
    self->unk6++;
}

void beam_drone_leave_move(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->ext.main_58.unk88 = 2;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void beam_drone_spawn_beam(struct VisualObj* self)
{
    struct ShotObj* shot;
    u8 i;

    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x24;
            shot->unk2 = i;
            shot->unk7C = (struct WeaponObj*)self;
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)beam_drone_animations;
            shot->unk3C = self->unk3C;
            shot->unk40 = self->unk40;
            shot->unk15 = self->unk15;
            shot->bg_offset = self->bg_offset;
            if (self->unk15 == 0) {
                shot->unk16 = 0;
            } else {
                shot->unk16 = 1;
            }
        }
    }
}

void beam_drone_spawn_charge(struct AnimatedObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 0;
        obj->unk50 = PLAYER_OBJECT(self);
        obj->unk42 = self->unk42;
        obj->animation_table = beam_drone_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

struct Unk_unk68 beam_drone_hit_box = { -10, -10, 20, 20 };

struct Unk_unk68 beam_drone_anim_0[4] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, -3, 3 },
};

union AnimationStep beam_drone_anim_1[] = {
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010004 },
    { 0x0C010004 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F000002 },
};

struct Unk_unk68 beam_drone_anim_2[4] = {
    { 2, 0, 1, 16 },
    { 2, 0, 1, 17 },
    { 2, 0, 1, 18 },
    { 2, 0, -3, 19 },
};

struct Unk_unk68 beam_drone_anim_3[7] = {
    { 2, 0, 1, 28 },
    { 2, 0, 1, 29 },
    { 2, 0, 1, 30 },
    { 1, 0, 1, 31 },
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, -2, 34 },
};

struct Unk_unk68 beam_drone_anim_4[7] = {
    { 2, 0, 1, 35 },
    { 2, 0, 1, 36 },
    { 2, 0, 1, 37 },
    { 1, 0, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, 1, 40 },
    { 1, 0, -2, 41 },
};

union AnimationStep beam_drone_anim_5[] = {
    { 0x22010001 },
    { 0x21010001 },
    { 0x20010001 },
    { 0x1F010001 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1C000002 },
};

union AnimationStep beam_drone_anim_6[] = {
    { 0x29010001 },
    { 0x28010001 },
    { 0x27010001 },
    { 0x26010001 },
    { 0x25010002 },
    { 0x24010002 },
    { 0x23000002 },
};

struct Unk_unk68 beam_drone_anim_7[8] = {
    { 2, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 2, 0, 1, 4 },
    { 3, 0, 1, 1 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 8 },
    { 3, 0, -7, 9 },
};

struct Unk_unk68 beam_drone_anim_8[13] = {
    { 4, 0, 1, 20 },
    { 4, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 0, 1, 23 },
    { 2, 0, 1, 20 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 22 },
    { 2, 0, 1, 23 },
    { 2, 0, 1, 24 },
    { 2, 0, 1, 25 },
    { 2, 0, 1, 26 },
    { 2, 0, 1, 25 },
    { 2, 0, -4, 27 },
};

union AnimationStep beam_drone_anim_9[] = {
    { 0x2A000001 },
};

union AnimationStep beam_drone_anim_10[] = {
    { 0x2B000001 },
};

union AnimationStep beam_drone_anim_11[] = {
    { 0x2C000001 },
};

void* beam_drone_animations[12] = {
    beam_drone_anim_0,
    beam_drone_anim_1,
    beam_drone_anim_2,
    beam_drone_anim_3,
    beam_drone_anim_4,
    beam_drone_anim_5,
    beam_drone_anim_6,
    beam_drone_anim_7,
    beam_drone_anim_8,
    beam_drone_anim_9,
    beam_drone_anim_10,
    beam_drone_anim_11,
};

struct Unk_unk68 beam_drone_debris = { 9, 10, 11, 0 };

void (*beam_drone_state_funcs[3])() = {
    func_80074438,
    func_800745E8,
    beam_drone_despawn,
};

void (*beam_drone_step_funcs[6])() = {
    enemy_hit_reaction,
    beam_drone_resume_step,
    beam_drone_drop,
    beam_drone_charge,
    beam_drone_fire,
    beam_drone_leave,
};

void (*beam_drone_drop_funcs[2])() = {
    beam_drone_drop_start,
    beam_drone_drop_fall,
};

void (*beam_drone_charge_funcs[2])() = {
    beam_drone_charge_start,
    beam_drone_charge_wait,
};

void (*beam_drone_fire_funcs[4])() = {
    beam_drone_fire_start,
    beam_drone_fire_beam,
    beam_drone_fire_fade,
    beam_drone_fire_end,
};

void (*beam_drone_leave_funcs[2])() = {
    beam_drone_leave_start,
    beam_drone_leave_move,
};
