// MainObj, main_object_update_funcs[34]
// 8005E570..8005EC58
#include "common.h"

extern union AnimationStep* highway_trooper_animations[27];
#include "func_tables.h"

void highway_trooper_update(struct MainObj* self)
{
    highway_trooper_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// highway_trooper_init
INCLUDE_ASM("main/nonmatchings/mains/main_34_highway_trooper", func_8005E5C0);

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
    if (highway_trooper_stop_x[self->unk2] >= self->x_pos.i.hi) {
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
        if (self->unk2 == self->animation_step.fields.event) {
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
INCLUDE_ASM("main/nonmatchings/mains/main_34_highway_trooper", func_8005EB40);

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
    { 0x00000001 },
};

union AnimationStep highway_trooper_anim_1[] = {
    { 0x01010004 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05010004 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08F90003 },
};

union AnimationStep highway_trooper_anim_2[] = {
    { 0x09010002 },
    { 0x0A010004 },
    { 0x0B010003 },
    { 0x0C010102 },
    { 0x0D000212 },
};

union AnimationStep highway_trooper_anim_3[] = {
    { 0x0D010006 },
    { 0x0EFF0004 },
};

union AnimationStep highway_trooper_anim_4[] = {
    { 0x0F010004 },
    { 0x10FF0004 },
};

union AnimationStep highway_trooper_anim_5[] = {
    { 0x10000004 },
};

union AnimationStep highway_trooper_anim_6[] = {
    { 0x11000004 },
};

union AnimationStep highway_trooper_anim_7[] = {
    { 0x0001000F },
    { 0x1201000E },
    { 0x0001000F },
    { 0x13FD0010 },
};

union AnimationStep highway_trooper_anim_8[] = {
    { 0x0001000B },
    { 0x1401000A },
    { 0x1501000A },
    { 0x1601000B },
    { 0x1501000A },
    { 0x14FD000A },
};

union AnimationStep highway_trooper_anim_25[] = {
    { 0x17010102 },
    { 0x18010003 },
    { 0x19010005 },
    { 0x1A010006 },
    { 0x1B000007 },
};

union AnimationStep highway_trooper_anim_9[] = {
    { 0x1C010008 },
    { 0x27FF0009 },
};

union AnimationStep highway_trooper_anim_23[] = {
    { 0x1D01000A },
    { 0x1E010007 },
    { 0x18000006 },
};

union AnimationStep highway_trooper_anim_10[] = {
    { 0x1F010006 },
    { 0x2000000A },
};

union AnimationStep highway_trooper_anim_11[] = {
    { 0x2001000A },
    { 0x1F000006 },
};

union AnimationStep highway_trooper_anim_12[] = {
    { 0x21010014 },
    { 0x22010310 },
    { 0x22000010 },
};

union AnimationStep highway_trooper_anim_13[] = {
    { 0x23010014 },
    { 0x24010310 },
    { 0x24000010 },
};

union AnimationStep highway_trooper_anim_14[] = {
    { 0x25010014 },
    { 0x26010310 },
    { 0x26000010 },
};

union AnimationStep highway_trooper_anim_15[] = {
    { 0x28010002 },
    { 0x29010003 },
    { 0x2AFF0005 },
};

union AnimationStep highway_trooper_anim_24[] = {
    { 0x2B010004 },
    { 0x2C010005 },
    { 0x2D010006 },
    { 0x2E010006 },
    { 0x2F010005 },
    { 0x30000004 },
};

union AnimationStep highway_trooper_anim_16[] = {
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x3AFD0002 },
};

union AnimationStep highway_trooper_anim_17[] = {
    { 0x34000002 },
};

union AnimationStep highway_trooper_anim_18[] = {
    { 0x35000002 },
};

union AnimationStep highway_trooper_anim_19[] = {
    { 0x36000002 },
};

union AnimationStep highway_trooper_anim_20[] = {
    { 0x37000002 },
};

union AnimationStep highway_trooper_anim_21[] = {
    { 0x38000002 },
};

union AnimationStep highway_trooper_anim_22[] = {
    { 0x39000002 },
};

union AnimationStep highway_trooper_anim_26[] = {
    { 0x09010008 },
    { 0x0A010005 },
    { 0x0B010004 },
    { 0x0C010003 },
    { 0x0D010112 },
    { 0x0D000003 },
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
