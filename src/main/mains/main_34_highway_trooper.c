// MainObj, main_object_update_funcs[34]
// 8005E570..8005EC58
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_34_highway_trooper.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"

extern u16 highway_trooper_stop_x[];
extern void (*highway_trooper_step_funcs[])(struct MainObj*);

// highway_trooper_state_funcs
extern void (*highway_trooper_state_funcs[])(struct MainObj*);

void highway_trooper_main(struct MainObj*);
void highway_trooper_despawn(struct MainObj* arg0);

// highway_trooper_step_funcs
void highway_trooper_ride_in(struct MainObj*);

void highway_trooper_attack(struct MainObj* arg0);

void highway_trooper_fall_away(struct MainObj*);
void highway_trooper_drift(struct MainObj* arg0);

void highway_trooper_attack_jump(struct MainObj*);
void highway_trooper_attack_land(struct MainObj*);
void highway_trooper_attack_end(struct MainObj*);

extern void (*highway_trooper_attack_funcs[])(struct MainObj*);

extern union AnimationStep* highway_trooper_animations[27];

void highway_trooper_update(struct MainObj* self)
{
    highway_trooper_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// highway_trooper_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005E5C0(struct MainObj* arg0);
void func_8005EB40(struct MainObj* arg0);
extern u16 D_800FE18C[8];
extern ret_u8 func_8002938C(s32);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005E5C0(struct MainObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    resource = func_8002938C(0x22);
    arg0->unk40 = OBJECT_STAGE_TEXTURE(resource);
    clut_x = func_8002938C(0x22);
    clut_y = func_8002938C(0x22);
#ifdef MMX4_SATURN
    arg0->unk42 = clut_x * 4 + 0x1A;
#else
    arg0->unk42 = ((clut_x * 4 + 0x1A) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
#endif
    resource = func_8002938C(0x22);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = D_800FE18C[arg0->unk2 * 2];
    arg0->y_pos.i.hi = D_800FE18C[arg0->unk2 * 2 + 1];
    arg0->animation_table = (const u8* const*)highway_trooper_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->x_speed = -0x1C000;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->attack_box = NULL;
    arg0->hurt_box = NULL;
    arg0->collision_data = NULL;
    arg0->invincibility_timer = 0;
    arg0->hp = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->unk2 != 2)
        arg0->terrain_box = &highway_trooper_terrain_box;
    set_animation(arg0, 1);
    arg0->state = 1;
    arg0->unk5 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_34_highway_trooper", func_8005E5C0);
#endif

void highway_trooper_main(struct MainObj* self)
{
    highway_trooper_step_funcs[self->unk5](self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
}

void highway_trooper_despawn(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void highway_trooper_ride_in(struct MainObj* self)
{
    if (self->x_pos.i.hi <= highway_trooper_stop_x[self->unk2]) {
        SP_CUR_MAIN_OBJ->ext.main_34.unk80 = 1;
        set_animation(self, 0);
        self->unk5 = 1;
    }
    move_object(MOVING_OBJECT(self));
}

void highway_trooper_wait(struct MainObj* self)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_34.unk80 <= 0) {
        set_animation(self, 2);
        self->unk5 = 2;
    }
}

void highway_trooper_attack(struct MainObj* self)
{
    highway_trooper_attack_funcs[self->unk6](self);
}

void highway_trooper_attack_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x13;
            shot->unk40 = self->unk40;
            shot->animation_table = (u32**)highway_trooper_animations;
            shot->unk42 = self->unk42;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk2 = 0;
            shot->bg_offset = self->bg_offset;
            shot->x_pos.val = self->x_pos.val - 0x10;
            shot->y_pos.val = self->y_pos.val - 0x20;
            shot->unk7C = self->backref;
            SP_CUR_MAIN_OBJ->ext.main_34.unk82 = 0;
            self->unk6++;
        }
    }
}

void highway_trooper_attack_ready_jump(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        if (self->unk2 == 2) {
            self->terrain_box = &highway_trooper_terrain_box;
        }
        self->unk6++;
        set_animation(self, 3);
    }
}

void highway_trooper_attack_jump(struct MainObj* self)
{
    s32 value24;

    self->x_speed = FIXED(-0.9375);
    value24 = FIXED(1.75);
    self->y_speed = value24;
    self->gravity = FIXED(0.5);
    self->air_state = 1;
    move_with_gravity(ANIMATED_OBJECT(self));
    self->unk6++;
}

void highway_trooper_attack_land(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        self->air_state = 0;
        if (++SP_CUR_MAIN_OBJ->ext.main_34.unk82 == 3) {
            self->unk6 = self->unk6 + 1;
        } else {
            self->unk6 = self->unk6 - 1;
        }
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void highway_trooper_attack_end(struct MainObj* self)
{
    set_animation(self, 4);
    SP_CUR_MAIN_OBJ->ext.main_34.unk80 = 0x30;
    self->unk5 = 3;
    self->unk6 = 0;
}

// highway_trooper_hit
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005EB40(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_34.unk80 > 0)
        return;
    if (arg0->unk2 == 0) {
        arg0->x_speed = -0x1C000;
        arg0->y_speed = 0xC000;
        arg0->gravity = 0x2000;
        arg0->terrain_box = NULL;
        set_animation(arg0, 5);
        arg0->unk5 = 4;
    } else {
        arg0->terrain_box = NULL;
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->x_speed = 0x38000;
        arg0->y_speed = 0;
        arg0->gravity = 0;
        set_animation(arg0, 1);
        arg0->unk5 = 5;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_34_highway_trooper", func_8005EB40);
#endif

void highway_trooper_fall_away(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi >= 0x210) {
        self->state = 2;
        self->unk5 = 0;
    }
}

void highway_trooper_drift(struct MainObj* self)
{
    move_object((struct MovingObj*)self);
}

struct Unk_unk68 highway_trooper_terrain_box = { 0, 0, 16, 21 };

u16 highway_trooper_stop_x[4] = { 0x09D0, 0x0E28, 0x14D8, 0x1B48 };

union AnimationStep highway_trooper_anim_0[] = {
    { 1, 0, 0, 0x00 },
};

union AnimationStep highway_trooper_anim_1[] = {
    { 4, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 3, 0, -7, 0x08 },
};

union AnimationStep highway_trooper_anim_2[] = {
    { 2, 0, 1, 0x09 },
    { 4, 0, 1, 0x0A },
    { 3, 0, 1, 0x0B },
    { 2, 1, 1, 0x0C },
    { 18, 2, 0, 0x0D },
};

union AnimationStep highway_trooper_anim_3[] = {
    { 6, 0, 1, 0x0D },
    { 4, 0, -1, 0x0E },
};

union AnimationStep highway_trooper_anim_4[] = {
    { 4, 0, 1, 0x0F },
    { 4, 0, -1, 0x10 },
};

union AnimationStep highway_trooper_anim_5[] = {
    { 4, 0, 0, 0x10 },
};

union AnimationStep highway_trooper_anim_6[] = {
    { 4, 0, 0, 0x11 },
};

union AnimationStep highway_trooper_anim_7[] = {
    { 15, 0, 1, 0x00 },
    { 14, 0, 1, 0x12 },
    { 15, 0, 1, 0x00 },
    { 16, 0, -3, 0x13 },
};

union AnimationStep highway_trooper_anim_8[] = {
    { 11, 0, 1, 0x00 },
    { 10, 0, 1, 0x14 },
    { 10, 0, 1, 0x15 },
    { 11, 0, 1, 0x16 },
    { 10, 0, 1, 0x15 },
    { 10, 0, -3, 0x14 },
};

union AnimationStep highway_trooper_anim_25[] = {
    { 2, 1, 1, 0x17 },
    { 3, 0, 1, 0x18 },
    { 5, 0, 1, 0x19 },
    { 6, 0, 1, 0x1A },
    { 7, 0, 0, 0x1B },
};

union AnimationStep highway_trooper_anim_9[] = {
    { 8, 0, 1, 0x1C },
    { 9, 0, -1, 0x27 },
};

union AnimationStep highway_trooper_anim_23[] = {
    { 10, 0, 1, 0x1D },
    { 7, 0, 1, 0x1E },
    { 6, 0, 0, 0x18 },
};

union AnimationStep highway_trooper_anim_10[] = {
    { 6, 0, 1, 0x1F },
    { 10, 0, 0, 0x20 },
};

union AnimationStep highway_trooper_anim_11[] = {
    { 10, 0, 1, 0x20 },
    { 6, 0, 0, 0x1F },
};

union AnimationStep highway_trooper_anim_12[] = {
    { 20, 0, 1, 0x21 },
    { 16, 3, 1, 0x22 },
    { 16, 0, 0, 0x22 },
};

union AnimationStep highway_trooper_anim_13[] = {
    { 20, 0, 1, 0x23 },
    { 16, 3, 1, 0x24 },
    { 16, 0, 0, 0x24 },
};

union AnimationStep highway_trooper_anim_14[] = {
    { 20, 0, 1, 0x25 },
    { 16, 3, 1, 0x26 },
    { 16, 0, 0, 0x26 },
};

union AnimationStep highway_trooper_anim_15[] = {
    { 2, 0, 1, 0x28 },
    { 3, 0, 1, 0x29 },
    { 5, 0, -1, 0x2A },
};

union AnimationStep highway_trooper_anim_24[] = {
    { 4, 0, 1, 0x2B },
    { 5, 0, 1, 0x2C },
    { 6, 0, 1, 0x2D },
    { 6, 0, 1, 0x2E },
    { 5, 0, 1, 0x2F },
    { 4, 0, 0, 0x30 },
};

union AnimationStep highway_trooper_anim_16[] = {
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 2, 0, -3, 0x3A },
};

union AnimationStep highway_trooper_anim_17[] = {
    { 2, 0, 0, 0x34 },
};

union AnimationStep highway_trooper_anim_18[] = {
    { 2, 0, 0, 0x35 },
};

union AnimationStep highway_trooper_anim_19[] = {
    { 2, 0, 0, 0x36 },
};

union AnimationStep highway_trooper_anim_20[] = {
    { 2, 0, 0, 0x37 },
};

union AnimationStep highway_trooper_anim_21[] = {
    { 2, 0, 0, 0x38 },
};

union AnimationStep highway_trooper_anim_22[] = {
    { 2, 0, 0, 0x39 },
};

union AnimationStep highway_trooper_anim_26[] = {
    { 8, 0, 1, 0x09 },
    { 5, 0, 1, 0x0A },
    { 4, 0, 1, 0x0B },
    { 3, 0, 1, 0x0C },
    { 18, 1, 1, 0x0D },
    { 3, 0, 0, 0x0D },
};

union AnimationStep* highway_trooper_animations[27] = {
    highway_trooper_anim_0,
    highway_trooper_anim_1,
    highway_trooper_anim_2,
    highway_trooper_anim_3,
    highway_trooper_anim_4,
    highway_trooper_anim_5,
    highway_trooper_anim_6,
    highway_trooper_anim_7,
    highway_trooper_anim_8,
    highway_trooper_anim_9,
    highway_trooper_anim_10,
    highway_trooper_anim_11,
    highway_trooper_anim_12,
    highway_trooper_anim_13,
    highway_trooper_anim_14,
    highway_trooper_anim_15,
    highway_trooper_anim_16,
    highway_trooper_anim_17,
    highway_trooper_anim_18,
    highway_trooper_anim_19,
    highway_trooper_anim_20,
    highway_trooper_anim_21,
    highway_trooper_anim_22,
    highway_trooper_anim_23,
    highway_trooper_anim_24,
    highway_trooper_anim_25,
    highway_trooper_anim_26,
};

void (*highway_trooper_state_funcs[3])() = {
    func_8005E5C0,
    highway_trooper_main,
    highway_trooper_despawn,
};

void (*highway_trooper_step_funcs[6])(struct MainObj*) = {
    highway_trooper_ride_in,
    highway_trooper_wait,
    highway_trooper_attack,
    func_8005EB40,
    highway_trooper_fall_away,
    highway_trooper_drift,
};

u16 D_800FE18C[8] = {
    0x0A48,
    0x0140,
    0x0EA8,
    0x0170,
    0x1528,
    0x014A,
    0x1BC8,
    0x0170,
};

void (*highway_trooper_attack_funcs[5])() = {
    highway_trooper_attack_fire,
    highway_trooper_attack_ready_jump,
    highway_trooper_attack_jump,
    highway_trooper_attack_land,
    highway_trooper_attack_end,
};
