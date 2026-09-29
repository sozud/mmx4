// MainObj, main_object_update_funcs[51]
// 80069A94..8006A50C
#include "common.h"
#include "func_tables.h"

void fortress_cannon_fire_volley(struct MainObj* arg0);

void fortress_cannon_update(struct MainObj* self)
{
    fortress_cannon_state_funcs[self->state](self);
}

// fortress_cannon_init
INCLUDE_ASM("main/nonmatchings/mains/main_51_fortress_cannon", func_80069AD0);

// fortress_cannon_main
INCLUDE_ASM("main/nonmatchings/mains/main_51_fortress_cannon", func_80069BE4);

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
    func_8001540C(2, 0xA1, self);
    if (self->unk2 == 0 && self->ext.main_51.unk84 == 2 && engine_obj.cur_character == 0) {
        fortress_cannon_fire_double_shot(self);
    } else {
        fortress_cannon_fire_shot(self);
    }
    self->unk7C = 0x4B;
    self->unk6++;
}

// fortress_cannon_fire_wait
INCLUDE_ASM("main/nonmatchings/mains/main_51_fortress_cannon", func_80069F28);

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
        func_8001540C(2, 0xA2, self);
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
        self->gravity = FIXED(0.2578125);
        self->unk6 = 0;
        self->y_speed = 0;
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
        shot->unk16 = 4;
    }
}

void fortress_cannon_fire_double_shot(struct MainObj* self)
{
    u8 i;
    struct MainObj* obj;
    struct ShotObj* shot;

    obj = self;
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
            shot->unk7C = (struct WeaponObj*)obj;
            shot->unk42 = obj->unk42;
            shot->animation_table = (u32**)fortress_cannon_animations;
            shot->unk3C = obj->sprite_frames;
            shot->unk40 = obj->unk40;
            shot->unk15 = obj->unk15;
            shot->bg_offset = (s8)(u8)obj->bg_offset;
            shot->unk16 = 4;
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
            shot->unk16 = 4;
        }
        i++;
    } while (i < 2);
}

struct Unk_unk68 D_800FFC54 = { -27, -35, 62, 66 };

struct Unk_unk68 D_800FFC58 = { -27, -32, 58, 66 };

struct Unk_unk68 D_800FFC5C = { 3, 0, 27, 32 };

union AnimationStep fortress_cannon_anim_0[] = {
    { 0x00010015 },
    { 0x01010016 },
    { 0x00010015 },
    { 0x02FD0014 },
};

union AnimationStep fortress_cannon_anim_1[] = {
    { 0x00010001 },
    { 0x03010002 },
    { 0x04010004 },
    { 0x05000007 },
};

union AnimationStep fortress_cannon_anim_2[] = {
    { 0x00010001 },
    { 0x06010002 },
    { 0x07010004 },
    { 0x05000007 },
};

union AnimationStep fortress_cannon_anim_3[] = {
    { 0x08010004 },
    { 0x09010004 },
    { 0x0A010004 },
    { 0x0B010004 },
    { 0x0C010006 },
    { 0x0D000008 },
};

union AnimationStep fortress_cannon_anim_4[] = {
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11FD0002 },
};

union AnimationStep fortress_cannon_anim_5[] = {
    { 0x00010005 },
    { 0x12010006 },
    { 0x13010007 },
    { 0x12010006 },
    { 0x00010007 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x1600000A },
};

union AnimationStep fortress_cannon_anim_6[] = {
    { 0x16010004 },
    { 0x17010004 },
    { 0x18010004 },
    { 0x19010005 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x00000003 },
};

union AnimationStep fortress_cannon_anim_7[] = {
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1FFD0001 },
};

union AnimationStep fortress_cannon_anim_8[] = {
    { 0x20000001 },
};

union AnimationStep fortress_cannon_anim_9[] = {
    { 0x21000001 },
};

union AnimationStep fortress_cannon_anim_10[] = {
    { 0x22000001 },
};

union AnimationStep fortress_cannon_anim_11[] = {
    { 0x23000001 },
};

union AnimationStep fortress_cannon_anim_12[] = {
    { 0x24000001 },
};

union AnimationStep fortress_cannon_anim_13[] = {
    { 0x25010003 },
    { 0x26010003 },
    { 0x27010003 },
    { 0x28010003 },
    { 0x29FC0003 },
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
