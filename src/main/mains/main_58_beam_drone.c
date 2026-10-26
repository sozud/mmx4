// MainObj, main_object_update_funcs[58]
// 800743FC..80074E84
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_58_beam_drone.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#endif

// beam_drone_state_funcs
extern void (*beam_drone_state_funcs[])(struct MainObj*);

void beam_drone_despawn(struct MainObj*);

// beam_drone_step_funcs
void beam_drone_resume_step(struct MainObj* arg0);
void beam_drone_drop(struct MainObj* arg0);
void beam_drone_charge(struct MainObj* arg0);
void beam_drone_fire(struct MainObj* arg0);
void beam_drone_leave(struct MainObj* arg0);

// beam_drone_drop_funcs
extern void (*beam_drone_drop_funcs[])(struct MainObj*);
void beam_drone_drop_start(struct MainObj*);
void beam_drone_drop_fall(struct MainObj*);

// beam_drone_charge_funcs
extern void (*beam_drone_charge_funcs[])(struct MainObj*);
void beam_drone_charge_start(struct MainObj*);
void beam_drone_charge_wait(struct MainObj* arg0);

// beam_drone_fire_funcs
extern void (*beam_drone_fire_funcs[])(struct MainObj*);
void beam_drone_fire_start(struct MainObj*);
void beam_drone_fire_beam(struct MainObj*);
void beam_drone_fire_fade(struct MainObj*);
void beam_drone_fire_end(struct MainObj*);

// beam_drone_leave_funcs
extern void (*beam_drone_leave_funcs[])(struct MainObj*);
void beam_drone_leave_start(struct MainObj*);
void beam_drone_leave_move(struct MainObj*);

void beam_drone_update(struct MainObj* self)
{
    beam_drone_state_funcs[self->state](self);
}

// beam_drone_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern struct Unk_unk68 D_80107AF8[];
extern struct Unk_unk68 beam_drone_hit_box;
extern struct Unk_unk68 beam_drone_debris;
extern void (*beam_drone_step_funcs[6])(struct MainObj*);
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800745E8(struct MainObj* self);
void func_80074438(struct MainObj* self);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_58_beam_drone", func_80074438);
#else
void func_80074438(struct MainObj* self)
{
    self->active = 0x41;
    self->hp = 5;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->collision_data = D_80107AF8;
    if (self->unk2 == 0)
        self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    switch (self->unk2) {
    case 0:
        self->x_speed = 0;
        self->y_speed = 0;
        self->unk7E = 0x28;
        break;
    case 1:
        self->x_speed = 0;
        self->y_speed = self->y_pos.val < g_Player.y_pos.val ? -0x18000 : 0x18000;
        self->unk7E = 0x3C;
        break;
    case 2:
        self->x_speed = self->x_pos.val > g_Player.x_pos.val ? -0x15000 : 0x15000;
        self->y_speed = 0;
        self->unk7E = 0x3C;
        break;
    }
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->animation_table = (const u8* const*)beam_drone_animations;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->terrain_box = NULL;
    self->hurt_box = &beam_drone_hit_box;
    self->attack_box = &beam_drone_hit_box;
    set_animation(self, 0);
    self->ext.main_58.saved_unk5 = 0;
    self->ext.main_58.unk84 = 0;
    self->ext.main_58.unk88 = 0;
    self->ext.main_58.unk8C = 0;
    self->ext.main_58.unk90 = 0;
    self->ext.main_58.unk94 = 0;
    self->unk7C = 0;
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
}
#endif

// beam_drone_main
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_58_beam_drone", func_800745E8);
#else
void func_800745E8(struct MainObj* self)
{
    s32 status;
    s32 x_margin;
    s32 y_margin;

#ifdef MMX4_PC
    x_margin = 0;
    y_margin = 0;
#endif
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (self->unk5 != 4 && func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1)
        self->unk5 = 2;
    beam_drone_step_funcs[self->unk5](self);
    status = func_8002DD04(self);
    func_8002D9BC(self);
    if (self->unk5 != 0)
        self->ext.main_58.saved_unk5 = self->unk5;
    if (status < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(3, &beam_drone_debris, self);
        if (self->unk2 == 0)
            drop_item(BASE_OBJECT(self), 8);
        self->ext.main_58.unk88 = 2;
        self->state = 2;
        return;
    }
    if (self->unk2 != 0 && engine_obj.character_state.fields.active != 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(3, &beam_drone_debris, self);
        self->ext.main_58.unk88 = 2;
        self->state = 2;
        return;
    }
    switch (self->unk2) {
    case 0:
        x_margin = 0x60;
        y_margin = 0x40;
        break;
    case 1:
        x_margin = 0x40;
        y_margin = 0x50;
        break;
    case 2:
        x_margin = 0x50;
        y_margin = 0x40;
        break;
    }
    if (func_8002B1E8(BASE_OBJECT(self), x_margin, y_margin) == 0) {
        if (self->active != 0)
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else if (self->unk5 != 4) {
        self->state = 2;
    }
}
#endif

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

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        self->x_speed = 0;
        self->y_speed = 0;
        self->unk5 = 3;
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
    func_8001540C(2, SATURN_SOUND(0x2D, 0x7A), self);
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
    func_8001540C(2, SATURN_SOUND(0x2C, 0x79), self);
    self->unk7C = 0x12;
    self->unk6++;
}

void beam_drone_fire_beam(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 2);
        self->ext.main_58.unk88 = 2;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void beam_drone_fire_fade(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->ext.main_58.unk88 = 0;
        self->unk7C = 0x2A;
        self->unk6++;
    }
}

void beam_drone_fire_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 0);
        if (self->unk2 == 0) {
            self->unk5 = 2;
        } else {
            self->unk5 = 5;
        }
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
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->unk7C = 0x3C;
    if (self->unk2 == 1) {
        self->y_speed = (self->y_pos.i.hi > 0x368 ? -0x18000 : 0x18000);
    } else {
        self->x_speed = self->x_pos.i.hi > 0x950 ? 0x18000 : -0x18000;
    }
    self->unk6++;
}

void beam_drone_leave_move(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
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
        obj->unk16 = VISUAL_SATURN_LAYER(4);
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
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 4, 0, 1, 0x0A },
    { 4, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 0, 0x0F },
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
    { 1, 0, 1, 0x22 },
    { 1, 0, 1, 0x21 },
    { 1, 0, 1, 0x20 },
    { 1, 0, 1, 0x1F },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1D },
    { 2, 0, 0, 0x1C },
};

union AnimationStep beam_drone_anim_6[] = {
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 0, 0x23 },
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
    { 1, 0, 0, 0x2A },
};

union AnimationStep beam_drone_anim_10[] = {
    { 1, 0, 0, 0x2B },
};

union AnimationStep beam_drone_anim_11[] = {
    { 1, 0, 0, 0x2C },
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
