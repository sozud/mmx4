// MainObj, main_object_update_funcs[72]
// 8008ADFC..8008BA38
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_72_unused_ride_armor.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/mains/main_71_ride_armor_pilot.h"
#include "main/object_motion.h"

extern void* unused_ride_armor_animations[];
extern struct Unk_unk68 unused_ride_armor_hit_box;
extern struct Unk_unk68 unused_ride_armor_terrain_box;

extern struct Unk_unk68 unused_ride_armor_debris[2];
extern void (*unused_ride_armor_step_funcs[])(struct MainObj*);

// unused_ride_armor_step_funcs
void unused_ride_armor_reset(struct MainObj* arg0);
void func_8008B020(struct MainObj* arg0);
void func_8008B188(struct MainObj* arg0);

void func_8008B4B8(struct MainObj* arg0);

void func_8008B69C(struct MainObj* arg0);

// unused_ride_armor_despawn_funcs
void unused_ride_armor_despawn_remove(struct MainObj* arg0);
void unused_ride_armor_despawn_idle(void);
void unused_ride_armor_despawn_idle2(void);

// unused_ride_armor_state_funcs
extern void (*unused_ride_armor_state_funcs[])(struct MainObj*);
void unused_ride_armor_init(struct MainObj*);
void unused_ride_armor_main(struct MainObj*);
void unused_ride_armor_despawn(struct MainObj* arg0);

extern void (*unused_ride_armor_despawn_funcs[])(struct MainObj*);

void unused_ride_armor_init(struct MainObj* self)
{
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk7C = 0;
    self->on_screen = 0;
    self->hp = 0x18;
    self->contact_damage = 6;
    self->invincibility_timer = 0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->animation_table = (const u8* const*)unused_ride_armor_animations;
    self->hurt_box = (const u8*)&unused_ride_armor_hit_box;
    self->attack_box = (const u8*)&unused_ride_armor_hit_box;
    self->terrain_box = &unused_ride_armor_terrain_box;
    self->collision_data = (const u16*)D_80108184;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = VISUAL_SATURN_LAYER(5);
}

void unused_ride_armor_face_player(struct MainObj* self)
{
    if ((self->x_pos.val - g_Player.x_pos.val) < 0) {
        self->unk15 = PLAYER_FACING_RIGHT;
        return;
    }

    self->unk15 = 0;
}

void unused_ride_armor_set_step(struct BaseObj* self, s8 arg1)
{
    self->unk5 = arg1;
    self->unk6 = 0;
}

void unused_ride_armor_apply_x_speed(struct MainObj* self)
{
    self->x_pos.val += self->x_speed;
}

void unused_ride_armor_set_walk_speed(struct MainObj* self)
{
    if (self->unk15 != 0) {
        self->x_speed = FIXED(1.375);
    } else {
        self->x_speed = FIXED(-1.375);
    }
}

void unused_ride_armor_set_jump_speed(struct MainObj* self)
{
    s32 value;

    value = self->ext.main_72.unk84 * 0x100;
    if (self->unk15 == 0) {
        value = -value;
    }
    self->x_speed = value;
}

void unused_ride_armor_spawn_shot(struct MainObj* self, s32 arg1)
{
    u8 v;
    struct ShotObj* obj = find_free_shot_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x2F;
        obj->unk2 = arg1;
        obj->x_pos.i.hi = self->x_pos.i.hi;
        obj->y_pos.i.hi = self->y_pos.i.hi;
        obj->animation_table = self->animation_table;
        obj->unk40 = self->unk40;
        obj->unk3C = self->sprite_frames;
        v = (u8)func_8002938C(0x48);
        obj->unk42 = VISUAL_STAGE_PALETTE(v);
        obj->unk16 = self->unk16;
        obj->unk7C = self;
        obj->unk15 = self->unk15;
    }
}

// unused_ride_armor_idle
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_72_unused_ride_armor", func_8008B020);
#else
void func_8008B020(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        self->air_state = 1;
        set_animation(self, 8);
        self->ext.main_72.lifetime = get_random() & 63;
        unused_ride_armor_face_player(self);
    }
    if (self->ext.main_72.lifetime == 0) {
        if ((self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0 ? self->x_pos.i.hi - g_Player.x_pos.i.hi : g_Player.x_pos.i.hi - self->x_pos.i.hi) <= 0x60) {
            if (self->y_pos.i.hi - g_Player.y_pos.i.hi <= -0x30) {
                if (get_random() & 1)
                    unused_ride_armor_set_step(BASE_OBJECT(self), 9);
                else
                    unused_ride_armor_set_step(BASE_OBJECT(self), 10);
            } else {
                if (get_random() & 1)
                    unused_ride_armor_set_step(BASE_OBJECT(self), 8);
                else
                    unused_ride_armor_set_step(BASE_OBJECT(self), 6);
            }
        } else {
            if (get_random() & 1)
                unused_ride_armor_set_step(BASE_OBJECT(self), 8);
            else
                unused_ride_armor_set_step(BASE_OBJECT(self), 3);
        }
    } else {
        self->ext.main_72.lifetime--;
        animate_object(self);
    }
}
#endif

// unused_ride_armor_walk
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_72_unused_ride_armor", func_8008B188);
#else
#define RIDE_ARMOR_WALK_ATTACK 0x160
#define RIDE_ARMOR_WALK_FRAMES 64

void func_8008B188(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        set_animation(self, 8);
        self->ext.main_72.unk84 = RIDE_ARMOR_WALK_ATTACK;
        unused_ride_armor_face_player(self);
        self->ext.main_72.lifetime = (get_random() & 31) + RIDE_ARMOR_WALK_FRAMES;
    }
    if (--self->ext.main_72.lifetime != 0) {
        unused_ride_armor_set_walk_speed(self);
        unused_ride_armor_apply_x_speed(self);
        animate_object(self);
        if (self->animation_step.fields.event != 0)
            func_8001540C(2, SATURN_SOUND(0x45, 0x149), self);
    } else if (self->collision_flags & 8) {
        unused_ride_armor_set_step(BASE_OBJECT(self), 5);
    } else {
        unused_ride_armor_set_step(BASE_OBJECT(self), 2);
    }
}
#endif

void unused_ride_armor_shoot(struct MainObj* self)
{
    struct Main72Ext* main_72;
    s8 state;
    u8 timer1;
    u8 timer2;

    state = self->unk6;
    if (state == 0) {
        self->unk6++;
        set_animation(self, 8);
        self->ext.main_72.lifetime = 0x40;
        self->ext.main_72.spawn_timer = 0x10;
        unused_ride_armor_face_player(self);
        func_8001540C(2, SATURN_SOUND(0x4C, 0x14F), self);
    }

    timer1 = self->ext.main_72.lifetime - 1;
    main_72 = &self->ext.main_72;
    main_72->lifetime = timer1;
    if (timer1 != 0) {
        timer2 = self->ext.main_72.spawn_timer - 1;
        main_72->spawn_timer = timer2;
        if (timer2 == 0) {
            unused_ride_armor_spawn_shot(self, 0);
            self->ext.main_72.spawn_timer = 0x10;
        }
        animate_object(ANIMATED_OBJECT(self));
    } else {
        unused_ride_armor_set_step(BASE_OBJECT(self), 2);
    }
}

void unused_ride_armor_jump(struct MainObj* self)
{
    s8 state;

    state = self->unk6;
    if (state == 0) {
        self->unk6 = state + 1;
        unused_ride_armor_face_player(self);
        self->y_speed = FIXED(5.5);
        self->gravity = FIXED(0.2578125);
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 1;
        set_animation(self, 2);
        self->collision_flags &= 0xF7;
        func_8001540C(2, SATURN_SOUND(0x48, 0x14C), self);
    }
    self->x_speed = 0;
    unused_ride_armor_set_jump_speed(self);
    if (!(self->collision_flags & 4) && self->y_speed >= 0 && self->y_pos.i.hi - g_Player.y_pos.i.hi >= 0) {
        move_with_gravity(ANIMATED_OBJECT(self));
        return;
    }
    unused_ride_armor_set_step(BASE_OBJECT(self), 2);
}

void unused_ride_armor_land(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        self->air_state = 0;
        set_animation(self, 4);
        self->collision_flags |= 8;
        func_8001540C(2, SATURN_SOUND(0x45, 0x149), self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        unused_ride_armor_set_step(BASE_OBJECT(self), 7);
        return;
    }
    animate_object(self);
}

// unused_ride_armor_dash
#define RIDE_ARMOR_DASH_ATTACK 0x420
#define RIDE_ARMOR_DASH_SPEED FIXED(4.125)
#define RIDE_ARMOR_DASH_FLASH 30

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_72_unused_ride_armor", func_8008B4B8);
#else
void func_8008B4B8(struct MainObj* self)
{
    if (self->unk6 == 0) {
        unused_ride_armor_face_player(self);
        self->unk6 = 1;
        self->ext.main_72.unk84 = RIDE_ARMOR_DASH_ATTACK;
        if (self->unk15 != 0)
            self->x_speed = RIDE_ARMOR_DASH_SPEED;
        else
            self->x_speed = -RIDE_ARMOR_DASH_SPEED;
        self->gravity = 0;
        self->y_speed = 0;
        self->ext.main_72.unk86 = RIDE_ARMOR_DASH_FLASH;
        set_animation(self, 7);
        func_8001540C(2, SATURN_SOUND(0x47, 0x14B), self);
        self->ext.main_72.lifetime = ABS(g_Player.x_pos.i.hi, self->x_pos.i.hi) / 4;
    }
    if (--self->ext.main_72.lifetime == 0) {
        unused_ride_armor_set_step(BASE_OBJECT(self), 2);
        return;
    }
    unused_ride_armor_apply_x_speed(self);
    animate_object(self);
}
#endif

void unused_ride_armor_fall(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->air_state = 1;
        set_animation(self, 3);
    }
    if (self->collision_flags & 8) {
        unused_ride_armor_set_step(BASE_OBJECT(self), 5);
        return;
    }
    if ((self->y_pos.i.hi - g_Player.y_pos.i.hi) >= -0x30) {
        unused_ride_armor_set_step(BASE_OBJECT(self), 2);
        return;
    }
    self->x_speed = 0;
    unused_ride_armor_set_jump_speed(self);
    if (self->y_speed < FIXED(-5.875)) {
        self->y_speed = FIXED(-5.875);
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

// unused_ride_armor_jump_shoot
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_72_unused_ride_armor", func_8008B69C);
#else
#define RIDE_ARMOR_FALL_LIMIT FIXED(-5.875)

void func_8008B69C(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->air_state = 1;
        set_animation(self, 3);
        unused_ride_armor_face_player(self);
        func_8001540C(2, SATURN_SOUND(0x4C, 0x14F), self);
    }
    if (self->collision_flags & 8) {
        unused_ride_armor_set_step(BASE_OBJECT(self), 5);
    } else if (self->y_pos.i.hi - g_Player.y_pos.i.hi >= 0) {
        unused_ride_armor_set_step(BASE_OBJECT(self), 2);
    } else {
        self->x_speed = 0;
        unused_ride_armor_set_jump_speed(self);
        if (self->y_speed < RIDE_ARMOR_FALL_LIMIT)
            self->y_speed = RIDE_ARMOR_FALL_LIMIT;
        move_with_gravity(ANIMATED_OBJECT(self));
        if (--self->ext.main_72.lifetime != 0) {
            if (--self->ext.main_72.spawn_timer & 15)
                unused_ride_armor_spawn_shot(self, 0);
            animate_object(self);
        } else {
            unused_ride_armor_set_step(BASE_OBJECT(self), 2);
        }
    }
}
#endif

void unused_ride_armor_rapid_fire(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        set_animation(self, 9);
        self->ext.main_72.lifetime = 0x80;
        self->ext.main_72.spawn_timer = 0x30;
        unused_ride_armor_face_player(self);
        func_8001540C(2, SATURN_SOUND(0x4C, 0x14F), self);
    }

    if (--(&self->ext.main_72)->lifetime != 0) {
        if ((--(&self->ext.main_72)->spawn_timer & 0xF) != 0) {
            unused_ride_armor_spawn_shot(self, 1);
        }
        animate_object(ANIMATED_OBJECT(self));
    } else {
        unused_ride_armor_set_step(BASE_OBJECT(self), 2);
    }
}

void unused_ride_armor_reset(struct MainObj* self)
{
    unused_ride_armor_set_step(BASE_OBJECT(self), 2);
}

void unused_ride_armor_main(struct MainObj* self)
{
    s32 result;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    unused_ride_armor_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    func_8002D9BC(self);
    result = func_8002DD04(self);
    if (result < 0) {
        spawn_debris(7, unused_ride_armor_debris, self);
        self->state = 2;
        self->unk5 = 0;
    } else if (result != 0) {
        ride_armor_pilot_spawn_dust(VISUAL_OBJECT(self), 8);
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
}

void unused_ride_armor_despawn_remove(struct MainObj* self)
{
    self->unk42 &= 0x7FFF;
    despawn_object(OBJECT_HEADER(self));
}

void unused_ride_armor_despawn_idle(void)
{
}

void unused_ride_armor_despawn_idle2(void)
{
}

void unused_ride_armor_despawn(struct MainObj* self)
{
    unused_ride_armor_despawn_funcs[self->unk5](self);
}

void unused_ride_armor_update(struct MainObj* self)
{
    unused_ride_armor_state_funcs[self->state](self);
}

struct Unk_unk68 unused_ride_armor_anim_0[5] = {
    { 100, 0, 1, 0 },
    { 7, 0, 1, 11 },
    { 1, 1, 1, 12 },
    { 49, 0, 1, 12 },
    { 8, 0, -4, 11 },
};

struct Unk_unk68 unused_ride_armor_anim_1[9] = {
    { 6, 0, 1, 0 },
    { 6, 0, 1, 1 },
    { 6, 1, 1, 2 },
    { 6, 0, 1, 3 },
    { 6, 0, 1, 4 },
    { 6, 0, 1, 5 },
    { 6, 0, 1, 6 },
    { 6, 0, 1, 7 },
    { 6, 0, -8, 8 },
};

union AnimationStep unused_ride_armor_anim_2[] = {
    { 6, 0, 0, 0x09 },
};

union AnimationStep unused_ride_armor_anim_3[] = {
    { 6, 0, 0, 0x0A },
};

union AnimationStep unused_ride_armor_anim_4[] = {
    { 2, 0, 1, 0x0B },
    { 8, 0, 1, 0x0C },
    { 7, 0, 1, 0x0B },
    { 8, 0, 0, 0x00 },
};

union AnimationStep unused_ride_armor_anim_5[] = {
    { 4, 0, 1, 0x0D },
    { 8, 0, 0, 0x0E },
};

union AnimationStep unused_ride_armor_anim_6[] = {
    { 4, 0, 0, 0x0D },
};

union AnimationStep unused_ride_armor_anim_7[] = {
    { 2, 0, 1, 0x10 },
    { 3, 0, 1, 0x20 },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1F },
    { 19, 0, 0, 0x20 },
};

struct Unk_unk68 unused_ride_armor_anim_8[4] = {
    { 1, 0, 1, 21 },
    { 1, 0, 1, 22 },
    { 1, 0, 1, 23 },
    { 1, 0, -3, 24 },
};

struct Unk_unk68 unused_ride_armor_anim_9[4] = {
    { 1, 0, 1, 25 },
    { 1, 0, 1, 26 },
    { 1, 0, 1, 27 },
    { 1, 0, -3, 28 },
};

union AnimationStep unused_ride_armor_anim_10[] = {
    { 1, 0, 0, 0x0F },
};

union AnimationStep unused_ride_armor_anim_11[] = {
    { 5, 0, 1, 0x25 },
    { 8, 0, 1, 0x26 },
    { 6, 0, 0, 0x25 },
};

union AnimationStep unused_ride_armor_anim_15[] = {
    { 5, 0, 1, 0x27 },
    { 5, 0, 1, 0x28 },
    { 5, 0, 1, 0x29 },
    { 5, 0, 1, 0x2A },
    { 5, 0, 1, 0x2B },
    { 5, 0, 1, 0x2C },
    { 5, 0, 1, 0x2D },
    { 5, 0, 1, 0x2E },
    { 5, 0, 0, 0x2F },
};

struct Unk_unk68 unused_ride_armor_anim_14[12] = {
    { 2, 0, 1, 48 },
    { 2, 0, 1, 49 },
    { 2, 0, 1, 50 },
    { 2, 0, 1, 51 },
    { 2, 0, 1, 52 },
    { 2, 0, 1, 53 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, -11, 53 },
};

union AnimationStep unused_ride_armor_anim_24[] = {
    { 2, 0, 0, 0x36 },
};

union AnimationStep unused_ride_armor_anim_25[] = {
    { 2, 0, 0, 0x37 },
};

union AnimationStep unused_ride_armor_anim_26[] = {
    { 2, 0, 0, 0x38 },
};

union AnimationStep unused_ride_armor_anim_27[] = {
    { 2, 0, 0, 0x39 },
};

union AnimationStep unused_ride_armor_anim_28[] = {
    { 2, 0, 0, 0x3A },
};

union AnimationStep unused_ride_armor_anim_29[] = {
    { 2, 0, 0, 0x3B },
};

union AnimationStep unused_ride_armor_anim_30[] = {
    { 2, 0, 0, 0x3C },
};

struct Unk_unk68 unused_ride_armor_anim_12[4] = {
    { 2, 0, 1, 61 },
    { 2, 0, 1, 62 },
    { 2, 0, 1, 63 },
    { 2, 0, -3, 64 },
};

struct Unk_unk68 unused_ride_armor_anim_13[4] = {
    { 2, 0, 1, 65 },
    { 2, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, -3, 68 },
};

void* unused_ride_armor_animations[33] = {
    unused_ride_armor_anim_0,
    unused_ride_armor_anim_1,
    unused_ride_armor_anim_2,
    unused_ride_armor_anim_3,
    unused_ride_armor_anim_4,
    unused_ride_armor_anim_5,
    unused_ride_armor_anim_6,
    unused_ride_armor_anim_7,
    unused_ride_armor_anim_8,
    unused_ride_armor_anim_9,
    unused_ride_armor_anim_10,
    unused_ride_armor_anim_11,
    unused_ride_armor_anim_12,
    unused_ride_armor_anim_13,
    unused_ride_armor_anim_14,
    unused_ride_armor_anim_15,
    unused_ride_armor_anim_14,
    unused_ride_armor_anim_15,
    unused_ride_armor_anim_14,
    unused_ride_armor_anim_15,
    unused_ride_armor_anim_15,
    unused_ride_armor_anim_14,
    unused_ride_armor_anim_14,
    unused_ride_armor_anim_14,
    unused_ride_armor_anim_24,
    unused_ride_armor_anim_25,
    unused_ride_armor_anim_26,
    unused_ride_armor_anim_27,
    unused_ride_armor_anim_28,
    unused_ride_armor_anim_29,
    unused_ride_armor_anim_30,
    unused_ride_armor_anim_12,
    unused_ride_armor_anim_13,
};

struct Unk_unk68 unused_ride_armor_hit_box = { -14, -18, 28, 52 };

struct Unk_unk68 unused_ride_armor_terrain_box = { 0, -1, 15, 33 };

struct Unk_unk68 unused_ride_armor_debris[2] = {
    { 24, 25, 26, 27 },
    { 28, 29, 30, 0 },
};

void (*unused_ride_armor_step_funcs[11])(struct MainObj*) = {
    enemy_hit_reaction,
    unused_ride_armor_reset,
    func_8008B020,
    func_8008B188,
    unused_ride_armor_fall,
    unused_ride_armor_land,
    func_8008B4B8,
    unused_ride_armor_jump,
    unused_ride_armor_shoot,
    func_8008B69C,
    unused_ride_armor_rapid_fire,
};

void (*unused_ride_armor_despawn_funcs[3])() = {
    unused_ride_armor_despawn_remove,
    unused_ride_armor_despawn_idle,
    unused_ride_armor_despawn_idle2,
};

void (*unused_ride_armor_state_funcs[3])() = {
    unused_ride_armor_init,
    unused_ride_armor_main,
    unused_ride_armor_despawn,
};
