// MainObj, main_object_update_funcs[51]
// 80069A94..8006A50C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_51_fortress_cannon.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"

extern struct Unk_unk68 D_800FFC54;
extern struct Unk_unk68 D_800FFC58;
extern struct Unk_unk68 D_800FFC5C;

extern union AnimationStep* fortress_cannon_animations[14];

// fortress_cannon_state_funcs
extern void (*fortress_cannon_state_funcs[])(struct MainObj*);

void fortress_cannon_explode(struct MainObj*);
void fortress_cannon_despawn(struct MainObj* arg0);

// fortress_cannon_step_funcs
void fortress_cannon_resume_step(struct MainObj* arg0);
void fortress_cannon_wait(struct MainObj* arg0);
void fortress_cannon_fire(struct MainObj* arg0);
void fortress_cannon_volley(struct MainObj* arg0);
void fortress_cannon_lower(struct MainObj* arg0);

// fortress_cannon_wait_funcs
extern void (*fortress_cannon_wait_funcs[])(struct MainObj*);
void fortress_cannon_wait_timer(struct MainObj*);

// fortress_cannon_fire_funcs
extern void (*fortress_cannon_fire_funcs[])(struct MainObj*);

// fortress_cannon_volley_funcs
extern void (*fortress_cannon_volley_funcs[])(struct MainObj*);
void fortress_cannon_volley_raise(struct MainObj*);
void fortress_cannon_volley_fire(struct MainObj*);

void fortress_cannon_volley_wait(struct MainObj*);

// fortress_cannon_lower_funcs
extern void (*fortress_cannon_lower_funcs[])(struct MainObj*);
void fortress_cannon_lower_start(struct MainObj*);
void fortress_cannon_lower_end(struct MainObj*);

void fortress_cannon_fire_volley(struct MainObj* arg0);

void fortress_cannon_update(struct MainObj* self)
{
    fortress_cannon_state_funcs[self->state](self);
}

// fortress_cannon_init
void func_80069AD0(struct MainObj* obj)
{
    obj->active = 0x41;
    obj->hp = 0x1E;
    obj->contact_damage = 4;
    obj->invincibility_timer = 0;
    obj->bg_offset = g_Player.bg_offset;
    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    obj->collision_data = &D_80107778;
    obj->x_speed = 0;
    obj->y_speed = 0;
    obj->x_accel = 0;
    obj->gravity = 0;
    obj->air_state = 0;
    obj->animation_table = (const u8* const*)fortress_cannon_animations;
    obj->unk16 = VISUAL_SATURN_LAYER(5);
    obj->terrain_box = &D_800FFC5C;
    obj->hurt_box = &D_800FFC54;
    obj->attack_box = &D_800FFC58;
    obj->unk15 = obj->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    set_animation(obj, 0);
    obj->ext.raw[0] = 0;
    obj->ext.raw[1] = 0;
    obj->ext.raw[2] = 0;
    obj->ext.raw[3] = 0;
    obj->ext.raw[4] = 0;
    obj->ext.raw[5] = 0;
    obj->state++;
    obj->unk5 = 2;
    obj->unk6 = 0;
    obj->unk7C = 0x28;
}

// fortress_cannon_main
void func_80069BE4(struct MainObj* self)
{
    s32 check;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;

    fortress_cannon_step_funcs[self->unk5](self);
    check = func_8002DD04(self);
    func_8002D9BC(self);
    CollisionRelated(self);
    fortress_cannon_check_fall(self);

    if (self->unk5 != 0) {
        self->ext.main_51.saved_unk5 = self->unk5;
    }

    if (check < 0) {
        spawn_debris(5, fortress_cannon_debris, self);
        self->unk7C = 0x1E;
        self->on_screen = 0;
        self->unk7E = 5;
        self->state++;
        return;
    }

    if (func_8002B1E8(BASE_OBJECT(self), 0x60, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
        return;
    }
    self->state = 3;
}

void fortress_cannon_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        drop_item(BASE_OBJECT(self), 8);
        self->state++;
    } else if (--self->unk7E == 0) {
        func_800AF878(BASE_OBJECT(self), 1, 0x20, 0x20);
        self->unk7E = 5;
    }
}

void fortress_cannon_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void fortress_cannon_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_51.saved_unk5;
}

void fortress_cannon_wait(struct MainObj* self)
{
    fortress_cannon_wait_funcs[self->unk6](self);
}

void fortress_cannon_wait_timer(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void fortress_cannon_fire(struct MainObj* self)
{
    fortress_cannon_fire_funcs[self->unk6](self);
}

void fortress_cannon_fire_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (engine_obj.cur_character != (self->ext.main_51.unk84 & 1)) {
        set_animation(self, 2);
    } else {
        set_animation(self, 1);
    }
    func_8001540C(2, SATURN_SOUND(0xA1, 0x71), self);
    if (self->unk2 == 0 && self->ext.main_51.unk84 == 2 && engine_obj.cur_character == 0) {
        fortress_cannon_fire_double_shot(self);
    } else {
        fortress_cannon_fire_shot(self);
    }
    self->unk7C = 0x4B;
    self->unk6++;
}

// fortress_cannon_fire_wait
void func_80069F28(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C != 0) {
        return;
    }
    self->unk6 = 0;
    if (self->unk2 == 0) {
        if ((s32)++self->ext.main_51.unk84 < engine_obj.cur_character + 3) {
            return;
        }
    } else if ((s32)++self->ext.main_51.unk84 < 4) {
        return;
    }
    self->unk5 = 4;
    self->unk7C = 0x14;
    self->ext.main_51.unk84 = 0;
}

void fortress_cannon_volley(struct MainObj* self)
{
    fortress_cannon_volley_funcs[self->unk6](self);
}

void fortress_cannon_volley_raise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 5);
        self->unk7C = 0x29;
        self->unk6++;
    }
}

void fortress_cannon_volley_fire(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_8001540C(2, SATURN_SOUND(0xA2, 0x72), self);
        fortress_cannon_fire_volley(self);
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void fortress_cannon_volley_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void fortress_cannon_lower(struct MainObj* self)
{
    fortress_cannon_lower_funcs[self->unk6](self);
}

void fortress_cannon_lower_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 6);
    self->unk7C = 0x1A;
    self->unk6++;
}

void fortress_cannon_lower_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7C = 0x28U;
    }
}

void fortress_cannon_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 0;
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
}

void fortress_cannon_check_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 6;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 1;
    }
}

void fortress_cannon_fire_shot(struct MainObj* self)
{
    struct MainObj* source;
    s8 side;
    struct ShotObj* shot;

    source = self;
    shot = find_free_shot_obj();
    if (shot != 0) {
        shot->active = 0x41;
        shot->id = 0x1E;
        side = engine_obj.cur_character ^ (source->ext.main_51.unk84 & 1);
        shot->unk2 = side;
        if ((source->ext.main_51.unk84 == 3) && (engine_obj.cur_character == 0)) {
            shot->unk2 = side + 1;
        }
        shot->unk7C = (struct WeaponObj*)source;
        shot->unk42 = source->unk42;
        shot->animation_table = (u32**)fortress_cannon_animations;
        shot->unk3C = source->sprite_frames;
        shot->unk40 = source->unk40;
        shot->unk15 = source->unk15;
        shot->bg_offset = (s8)(u8)source->bg_offset;
        shot->unk16 = VISUAL_SATURN_LAYER(4);
    }
}

void fortress_cannon_fire_double_shot(struct MainObj* self)
{
    u8 i;
    struct ShotObj* shot;

    i = 0;
    do {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x1E;
            if (i == 0) {
                shot->unk2 = 0;
            } else {
                shot->unk2 = 2;
            }
            shot->unk7C = (struct WeaponObj*)self;
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)fortress_cannon_animations;
            shot->unk3C = self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->unk15 = self->unk15;
            shot->bg_offset = (s8)(u8)self->bg_offset;
            shot->unk16 = VISUAL_SATURN_LAYER(4);
        }
        i++;
    } while (i < 2);
}

void fortress_cannon_fire_volley(struct MainObj* self)
{
    u8 i;
    struct ShotObj* shot;

    i = 0;
    do {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x1D;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)fortress_cannon_animations;
            shot->unk3C = (u8*)self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->unk15 = self->unk15;
            shot->bg_offset = self->bg_offset;
            shot->unk16 = VISUAL_SATURN_LAYER(4);
        }
        i++;
    } while (i < 2);
}

struct Unk_unk68 D_800FFC54 = { -27, -35, 62, 66 };

struct Unk_unk68 D_800FFC58 = { -27, -32, 58, 66 };

struct Unk_unk68 D_800FFC5C = { 3, 0, 27, 32 };

union AnimationStep fortress_cannon_anim_0[] = {
    { 21, 0, 1, 0x00 },
    { 22, 0, 1, 0x01 },
    { 21, 0, 1, 0x00 },
    { 20, 0, -3, 0x02 },
};

union AnimationStep fortress_cannon_anim_1[] = {
    { 1, 0, 1, 0x00 },
    { 2, 0, 1, 0x03 },
    { 4, 0, 1, 0x04 },
    { 7, 0, 0, 0x05 },
};

union AnimationStep fortress_cannon_anim_2[] = {
    { 1, 0, 1, 0x00 },
    { 2, 0, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 7, 0, 0, 0x05 },
};

union AnimationStep fortress_cannon_anim_3[] = {
    { 4, 0, 1, 0x08 },
    { 4, 0, 1, 0x09 },
    { 4, 0, 1, 0x0A },
    { 4, 0, 1, 0x0B },
    { 6, 0, 1, 0x0C },
    { 8, 0, 0, 0x0D },
};

union AnimationStep fortress_cannon_anim_4[] = {
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, -3, 0x11 },
};

union AnimationStep fortress_cannon_anim_5[] = {
    { 5, 0, 1, 0x00 },
    { 6, 0, 1, 0x12 },
    { 7, 0, 1, 0x13 },
    { 6, 0, 1, 0x12 },
    { 7, 0, 1, 0x00 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x15 },
    { 10, 0, 0, 0x16 },
};

union AnimationStep fortress_cannon_anim_6[] = {
    { 4, 0, 1, 0x16 },
    { 4, 0, 1, 0x17 },
    { 4, 0, 1, 0x18 },
    { 5, 0, 1, 0x19 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 3, 0, 0, 0x00 },
};

union AnimationStep fortress_cannon_anim_7[] = {
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 0, -3, 0x1F },
};

union AnimationStep fortress_cannon_anim_8[] = {
    { 1, 0, 0, 0x20 },
};

union AnimationStep fortress_cannon_anim_9[] = {
    { 1, 0, 0, 0x21 },
};

union AnimationStep fortress_cannon_anim_10[] = {
    { 1, 0, 0, 0x22 },
};

union AnimationStep fortress_cannon_anim_11[] = {
    { 1, 0, 0, 0x23 },
};

union AnimationStep fortress_cannon_anim_12[] = {
    { 1, 0, 0, 0x24 },
};

union AnimationStep fortress_cannon_anim_13[] = {
    { 3, 0, 1, 0x25 },
    { 3, 0, 1, 0x26 },
    { 3, 0, 1, 0x27 },
    { 3, 0, 1, 0x28 },
    { 3, 0, -4, 0x29 },
};

union AnimationStep* fortress_cannon_animations[14] = {
    fortress_cannon_anim_0,
    fortress_cannon_anim_1,
    fortress_cannon_anim_2,
    fortress_cannon_anim_3,
    fortress_cannon_anim_4,
    fortress_cannon_anim_5,
    fortress_cannon_anim_6,
    fortress_cannon_anim_7,
    fortress_cannon_anim_8,
    fortress_cannon_anim_9,
    fortress_cannon_anim_10,
    fortress_cannon_anim_11,
    fortress_cannon_anim_12,
    fortress_cannon_anim_13,
};

u8 fortress_cannon_debris[8] = { 8, 9, 10, 11, 12, 0, 0, 0 };

void (*fortress_cannon_state_funcs[4])(struct MainObj*) = {
    func_80069AD0,
    func_80069BE4,
    fortress_cannon_explode,
    fortress_cannon_despawn,
};

void (*fortress_cannon_step_funcs[7])(struct MainObj*) = {
    enemy_hit_reaction,
    fortress_cannon_resume_step,
    fortress_cannon_wait,
    fortress_cannon_fire,
    fortress_cannon_volley,
    fortress_cannon_lower,
    fortress_cannon_fall,
};

void (*fortress_cannon_wait_funcs[1])(struct MainObj*) = {
    fortress_cannon_wait_timer,
};

void (*fortress_cannon_fire_funcs[2])(struct MainObj*) = {
    fortress_cannon_fire_start,
    func_80069F28,
};

void (*fortress_cannon_volley_funcs[3])(struct MainObj*) = {
    fortress_cannon_volley_raise,
    fortress_cannon_volley_fire,
    fortress_cannon_volley_wait,
};

void (*fortress_cannon_lower_funcs[2])(struct MainObj*) = {
    fortress_cannon_lower_start,
    fortress_cannon_lower_end,
};
