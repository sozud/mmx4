// ShotObj, shot_object_update_funcs[0]
// 800994A0..80099B30
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_00_dragon_shot.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"

extern u8 dragon_shot_flame_hit_box[4];

extern u8 dragon_shot_pulse_box[4];
extern u8 dragon_shot_burn_box[4];

// dragon_shot_state_funcs
extern void (*dragon_shot_state_funcs[])(struct ShotObj*);

void dragon_shot_flame(struct ShotObj*);
void dragon_shot_pulse(struct ShotObj*);
void dragon_shot_bomb(struct ShotObj*);
void dragon_shot_despawn(struct ShotObj*);
void dragon_shot_follow_owner(struct ShotObj*);
#include "weapon_resources.h"

u8 dragon_shot_flame_box[4] = { 0xB4, 0x1B, 0x52, 0x31 };
u8 dragon_shot_flame_hit_box[4] = { 0x9E, 0xAE, 0x2C, 0x72 };
u8 dragon_shot_pulse_hit_box[4] = { 0x24, 0xF4, 0x32, 0x52 };
u8 dragon_shot_pulse_box[4] = { 0x2B, 0x15, 0x29, 0x40 };
u8 dragon_shot_bomb_box[4] = { 0xF3, 0xF3, 0x1A, 0x18 };
u8 dragon_shot_burn_box[4] = { 0xF3, 0xF3, 0x1A, 0x18 };
u8 dragon_shot_box_0[4] = { 0x20, 0xA7, 0x20, 0x10 };
u8 dragon_shot_box_1[4] = { 0x00, 0x00, 0x00, 0x00 };
u8 dragon_shot_box_2[4] = { 0x01, 0xFE, 0x09, 0x09 };
u8 dragon_shot_box_3[4] = { 0xC1, 0x0B, 0x32, 0x40 };
u8 dragon_shot_box_4[4] = { 0x25, 0x08, 0x32, 0x40 };
u8 dragon_shot_box_5[4] = { 0x1A, 0x95, 0x27, 0x23 };

void dragon_shot_update(struct ShotObj* self)
{
    dragon_shot_state_funcs[self->state](self);
}

// dragon_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800994DC(struct ShotObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800994DC(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 animation;
    s32 x_offset;
    s32 velocity;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk5C = 0;
    arg0->unk42 = owner->unk42;

    switch (arg0->unk2) {
    case 0:
    case 1:
        arg0->unk16 = 1;
        arg0->unk60 = 5;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = owner->y_pos.val;
        arg0->bg_offset = owner->bg_offset;
        if (arg0->unk2 == 0) {
            owner->hurt_box = dragon_shot_box_3;
            arg0->unk50.data = dragon_shot_flame_box;
            arg0->state = 1;
            set_animation(arg0, 2);
        } else {
            owner->hurt_box = dragon_shot_box_4;
            arg0->unk50.data = dragon_shot_pulse_hit_box;
            arg0->state = 2;
            set_animation(arg0, 4);
        }
        break;
    case 2:
    case 3:
        arg0->unk16 = 1;
        arg0->unk60 = 5;
        arg0->unk68 = (struct Unk_unk68*)dragon_shot_box_2;
        arg0->bg_offset = 0;
        arg0->unk42 &= 0x7FFF;
        x_offset = owner->unk15 == 0 ? 0x280000 : -0x280000;
        arg0->x_pos.val
            = owner->x_pos.val + (background_objects[0].x_pos.val + x_offset);
        arg0->y_pos.val = owner->y_pos.val + background_objects[0].y_pos.val;
        if (arg0->unk2 == 2) {
            velocity = owner->unk15 != 0 ? (-0x40000 | 0x8000) : 0x38000;
        } else {
            velocity = owner->unk15 != 0 ? (-0x30000 | 0x8000) : 0x28000;
        }
        arg0->x_vel.val = velocity;
        arg0->y_vel.val = 0x18000;
        arg0->unk2C = 0x1000;
        arg0->unk50.data = dragon_shot_bomb_box;
        arg0->unk28 = 0;
        arg0->state = 3;
        set_animation(arg0, 0xA);
        break;
    case 4:
        arg0->unk60 = 5;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->bg_offset = 0;
        arg0->unk16 = VISUAL_SATURN_LAYER(6);
        arg0->state = 5;
        arg0->y_pos.val = owner->y_pos.val;
        if (owner->unk7E != 0) {
            set_animation(arg0, 0xE);
            arg0->unk50.data = dragon_shot_box_0;
            owner->hurt_box = dragon_shot_box_5;
        } else {
            set_animation(arg0, 0xC);
            arg0->unk50.data = dragon_shot_box_1;
        }
        break;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_00_dragon_shot", func_800994DC);
#endif

void dragon_shot_flame(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    self->x_pos.val = weapon->x_pos.val;
    self->y_pos.val = weapon->y_pos.val;
    self->unk42 = weapon->unk42;
    animate_object(self);
    update_on_screen((struct BaseObj*)self, 0x5A, 0x5A);
    if (self->animation_step.fields.relative_step < 0) {
        self->state = 4;
    }
    func_8002D9BC(self);
    if (self->animation_step.fields.event != 0) {
        self->unk50.data = dragon_shot_flame_hit_box;
        func_8002D9BC(self);
        self->unk50.data = dragon_shot_flame_box;
    }
}

void dragon_shot_pulse(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    self->x_pos.val = weapon->x_pos.val;
    self->y_pos.val = weapon->y_pos.val;
    self->unk42 = weapon->unk42;
    animate_object(self);
    update_on_screen((struct BaseObj*)self, 0x5A, 0x5A);
    if (self->animation_step.fields.relative_step < 0) {
        self->state = 4;
    }
    if (self->animation_step.fields.event != 0) {
        self->unk50.data = dragon_shot_pulse_hit_box;
    } else {
        self->unk50.data = dragon_shot_pulse_box;
    }
    func_8002D9BC(self);
}

void dragon_shot_bomb_fall(struct ShotObj* self)
{
    struct MiscObj* temp_v0;

    move_with_gravity(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x19, 0x19);

    if (self->unk70 & 8) {
        self->unk5 = self->unk5 + 1;
        self->unk68 = 0;
        self->unk60 = 5;
        self->unk50.data = dragon_shot_burn_box;
        set_animation(self, 0xB);

        if (!(self->unk70 & 3)) {
            temp_v0 = find_free_misc_obj();
            if (temp_v0 != 0) {
                temp_v0->active = 0x41;
                temp_v0->id = 4;
                temp_v0->unk2 = 0;
                temp_v0->state = 0;
                temp_v0->ext.pointer.unk50 = self->unk7C;
                temp_v0->x_pos.val = self->x_pos.val + (get_random() & 3);
                temp_v0->y_pos.val = self->y_pos.val + (get_random() & 3);
            }
        }
    }

    func_8002D9BC(self);
}

void dragon_shot_bomb_burn(struct ShotObj* self)
{
    animate_object(self);
    func_8002D9BC(self);
    update_on_screen((struct BaseObj*)self, 0x19, 0x19);
    if (self->animation_step.fields.relative_step < 0) {
        self->state = 4;
        self->unk5 = 0;
    }
}

void dragon_shot_bomb(struct ShotObj* self)
{
    if (self->unk5 == 0) {
        dragon_shot_bomb_fall(self);
    } else {
        dragon_shot_bomb_burn(self);
    }

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated((struct PlayerObj*)self);
}

void dragon_shot_follow_owner(struct ShotObj* self)
{
    struct WeaponObj* owner;

    owner = self->unk7C;
    self->x_pos.val = owner->x_pos.val;
    self->y_pos.val = owner->y_pos.val;
    self->unk42 = owner->unk42;
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x5A, 0x5A);
    if (self->animation_step.fields.relative_step < 0) {
        self->state = 4;
        self->unk5 = 0;
    }
}

void dragon_shot_despawn(struct ShotObj* self)
{
    self->unk7C->unk54 = NULL;
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*dragon_shot_state_funcs[])(struct ShotObj*) = {
    func_800994DC,
    dragon_shot_flame,
    dragon_shot_pulse,
    dragon_shot_bomb,
    dragon_shot_despawn,
    dragon_shot_follow_owner,
};
