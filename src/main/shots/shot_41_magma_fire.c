// ShotObj, shot_object_update_funcs[41]
// 800A56E4..800A6374
#include "common.h"
#include "main/shots/shot_41_magma_fire.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/collision_bounds.h"
#include "main/stage_objects.h"

// magma_fire_pillar_funcs
extern void (*magma_fire_pillar_funcs[])(struct ShotObj*);

// magma_fire_breath_funcs
extern void (*magma_fire_breath_funcs[])(struct ShotObj*);
void magma_fire_breath_follow(struct ShotObj*);
void magma_fire_breath_drop(struct ShotObj*);

void magma_fire_breath_rise(struct ShotObj*);
void magma_fire_breath_exit(struct ShotObj*);

// magma_fire_step_funcs
extern void (*magma_fire_step_funcs[])(struct ShotObj*);
void magma_fire_hit(struct ShotObj*);
void magma_fire_idle(struct ShotObj*);
void magma_fire_wave(struct ShotObj*);
void magma_fire_pillar(struct ShotObj*);
void magma_fire_breath(struct ShotObj*);

void magma_fire_burst(struct ShotObj*);

// magma_fire_state_funcs
extern void (*magma_fire_state_funcs[])(struct ShotObj*);

void magma_fire_main(struct ShotObj*);
void magma_fire_despawn(struct ShotObj*);
#include "weapon_resources.h"

extern u8 magma_fire_breath_hit_box[4];
extern u8 magma_fire_burst_hit_box[4];
extern u8 magma_fire_burst_terrain_box[4];
extern u8 magma_fire_column_hit_box[4];
extern u8 magma_fire_ember_hit_box[4];
extern u8 magma_fire_ember_terrain_box[4];
extern u8 magma_fire_pillar_hit_boxes[][4];
extern u16 magma_fire_pillar_positions[8];
extern u8 magma_fire_wave_hit_box[4];
extern s16 magma_fire_wave_offsets[8];

// magma_fire_init

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_41_magma_fire", func_800A56E4);
#else
void func_800A56E4(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 vel;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->unk5C = 0;
    arg0->unk16 = 1;
    arg0->bg_offset = owner->bg_offset;
    switch (arg0->unk2) {
    case 0:
        arg0->unk15 = owner->unk15;
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk54 = NULL;
        arg0->unk60 = 9;
        arg0->x_pos.val = owner->x_pos.val + (arg0->unk15 != 0 ? 0x180000 : -0x180000);
        arg0->y_pos.val = owner->y_pos.val + 0x100000;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x60000 : -0x60000;
        arg0->y_vel.val = 0x20000;
        arg0->unk5 = 2;
        arg0->timer = 7;
        arg0->unk50.data = magma_fire_wave_hit_box;
        arg0->unk68 = NULL;
        arg0->state++;
        set_animation(arg0, 0x1C);
        break;
    case 1:
        arg0->unk58.data = (u8*)D_80105FF0;
        arg0->unk15 = 0;
        arg0->unk54 = NULL;
        arg0->unk60 = 4;
        arg0->x_pos.val = owner->x_pos.val + (owner->unk15 != 0 ? -0x100000 : 0x100000);
        arg0->y_pos.val = owner->y_pos.val - 0x200000;
        if (arg0->unk15 != 0)
            vel = -((s16)magma_fire_wave_offsets[arg0->unk7] << 12);
        else
            vel = (s16)magma_fire_wave_offsets[arg0->unk7] << 12;
        arg0->x_vel.val = vel;
        arg0->y_vel.val = 0x50000;
        arg0->unk5 = 3;
        arg0->unk50.data = (u8*)magma_fire_pillar_hit_boxes;
        arg0->unk68 = NULL;
        arg0->state++;
        set_animation(arg0, 0x1D);
        break;
    case 2:
        arg0->unk15 = owner->unk15;
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk50.data = magma_fire_ember_hit_box;
        arg0->unk54 = NULL;
        arg0->unk68 = (struct Unk_unk68*)magma_fire_ember_terrain_box;
        arg0->unk60 = 4;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = owner->y_pos.val - 0x400000;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x40000 : -0x40000;
        arg0->y_vel.val = 0x1C000;
        arg0->unk28 = 0;
        arg0->unk2C = 0x1300;
        arg0->unk5 = 4;
        arg0->state++;
        set_animation(arg0, 0x1F);
        break;
    case 3:
        arg0->unk15 = owner->unk15;
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk50.data = magma_fire_burst_hit_box;
        arg0->unk68 = (struct Unk_unk68*)magma_fire_burst_terrain_box;
        arg0->unk60 = 6;
        arg0->unk5 = 5;
        arg0->unk54 = NULL;
        arg0->timer = 3;
        arg0->state++;
        set_animation(arg0, 0x1B);
        break;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}
#endif

void magma_fire_wave(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    func_8002D9BC(self);
    if (--self->timer == 0) {
        self->timer = 7;
        self->y_vel.val = -self->y_vel.val;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x100, 0x100) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
    } else {
        self->unk5 = 0;
        self->state++;
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

// magma_fire_pillar_rise
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_41_magma_fire", func_800A5AA4);
#else
void func_800A5AA4(struct ShotObj* arg0)
{
    struct BaseObj* owner = (struct BaseObj*)arg0->unk7C;

    func_8002D9BC(arg0);
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->on_screen != 0)
        return;
    if (owner->state != 1) {
        arg0->unk5 = 0;
        arg0->state++;
        return;
    }
    set_animation(arg0, 0x1E);
    arg0->unk54 = magma_fire_breath_hit_box;
    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + magma_fire_pillar_positions[arg0->unk7] + (get_random() & 0x1F);
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi - 0x20;
    arg0->x_vel.val = -0x60000;
    arg0->y_vel.val = -0x60000;
    arg0->timer = (arg0->unk7 << 3) + 0x64;
    arg0->unk8A = 4;
    arg0->unk6++;
}
#endif

// magma_fire_pillar_erupt
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_41_magma_fire", func_800A5BA8);
#else
void func_800A5BA8(struct ShotObj* arg0)
{
    if (arg0->timer > 1) {
        arg0->timer--;
        return;
    }
    if (arg0->timer == 1) {
        arg0->timer--;
        start_screen_shake_y(0x78, 4, 2);
    }
    func_8002D9BC(arg0);
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (engine_obj.stage == 0xC) {
        if (arg0->y_pos.i.hi > 0x6C8) {
            set_animation(arg0, 0x20);
            arg0->y_pos.i.hi = 0x6C8;
            arg0->unk6++;
        }
    } else if (arg0->y_pos.i.hi > 0x2B8) {
        set_animation(arg0, 0x20);
        arg0->y_pos.i.hi = 0x2B8;
        arg0->unk6++;
    }
}
#endif

void magma_fire_pillar_repeat(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
        return;
    }
    if (--self->unk8A == 0) {
        self->unk6 -= 2;
        return;
    }
    self->state++;
    self->unk5 = 0;
    self->unk6 = 0;
}

void magma_fire_pillar(struct ShotObj* self)
{
    magma_fire_pillar_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x30, 0x30);
}

void magma_fire_breath_follow(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    func_8002D9BC(self);
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
    if (weapon->unk5 != 7) {
        self->state++;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void magma_fire_breath_drop(struct ShotObj* self)
{
    func_8002D9BC(self);
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk50.data = 0;
        self->unk6++;
        set_animation(self, 0x20);
    }
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
}

// magma_fire_breath_burn
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_41_magma_fire", func_800A5E60);
#else
void func_800A5E60(struct ShotObj* arg0)
{
    func_8002D9BC(arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        arg0->unk60 = 9;
        set_animation(arg0, 0x23);
        if (engine_obj.stage == 0xC)
            arg0->x_pos.i.hi = arg0->unk15 == 0 ? 0x138 : 0x2C8;
        else
            arg0->x_pos.i.hi = arg0->unk15 == 0 ? 0x1418 : 0x15A8;
        arg0->y_pos.i.hi += 0x12C;
        arg0->unk50.data = magma_fire_column_hit_box;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0x40000;
        arg0->timer = 0xC8;
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0x80);
    } else {
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
    }
}
#endif

void magma_fire_breath_rise(struct ShotObj* self)
{
    func_8002D9BC(self);
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if ((self->y_pos.i.hi - background_objects[0].y_pos.i.hi) < 0x78) {
        self->y_vel.val = 0;
    }

    if (--self->timer == 0) {
        self->unk68 = NULL;
        self->y_vel.val = FIXED(-4);
        self->unk6++;
    }

    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, SATURN_SOUND(6, 0x83), self);
    }
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, SATURN_SOUND(7, 0x84), self);
    }

    update_on_screen(BASE_OBJECT(self), 0x30, 0x80);
}

void magma_fire_breath_exit(struct ShotObj* self)
{
    func_8002D9BC(self);
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x30, 0x80);
    if (self->on_screen == 0) {
        self->state++;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void magma_fire_breath(struct ShotObj* self)
{
    magma_fire_breath_funcs[self->unk6](self);
}

// magma_fire_spread
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_41_magma_fire", func_800A60D0);
#else
void func_800A60D0(struct ShotObj* arg0)
{
    struct ShotObj* child;

    animate_object(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
    if (--arg0->timer == 0 && (arg0->unk70 & 3) == 0) {
        child = find_free_shot_obj();
        if (child != NULL) {
            child->active = 0x41;
            child->id = 0x29;
            child->unk2 = 3;
            child->unk7C = (struct WeaponObj*)arg0;
            child->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 0x18 : -0x18);
            child->y_pos.i.hi = arg0->y_pos.i.hi;
            child->timer = 3;
        }
    }
    if (arg0->animation_step.fields.frame_index == 0x8A)
        arg0->unk50.data = NULL;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->state++;
    }
}
#endif

void magma_fire_burst(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
    if (self->animation_step.fields.relative_step < 0) {
        self->state++;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void magma_fire_hit(struct ShotObj* self)
{
    enemy_hit_reaction(MAIN_OBJECT(self));
}

void magma_fire_idle(struct ShotObj* self)
{
}

void magma_fire_main(struct ShotObj* self)
{
    s32 hit;

    hit = func_8002DD04(MAIN_OBJECT(self));
    if (hit < 0) {
        self->unk5 = 0;
        self->state++;
        spawn_explosion(BASE_OBJECT(self));
    } else {
        magma_fire_step_funcs[self->unk5](self);
    }
}

void magma_fire_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void magma_fire_update(struct ShotObj* self)
{
    struct WeaponObj* temp_s0 = self->unk7C;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated(self);
    if (temp_s0->state == 2) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    magma_fire_state_funcs[self->state](self);
}

u8 magma_fire_wave_hit_box[4] = { 0xEE, 0xF3, 0x18, 0x19 };

u8 magma_fire_pillar_hit_boxes[1][4] = { { 0xF7, 0xF2, 0x10, 0x18 } };

u8 D_801098D8[1][4] = { { 0xF7, 0xF7, 0x0F, 0x11 } };

u8 magma_fire_breath_hit_box[4] = { 0xF2, 0xF0, 0x1D, 0x1D };

u8 magma_fire_ember_hit_box[4] = { 0xF6, 0xF6, 0x13, 0x13 };

u8 magma_fire_ember_terrain_box[4] = { 0, 0, 0x0A, 9 };

u8 magma_fire_column_hit_box[4] = { 0xEC, 0x85, 0x26, 0xFA };

u8 magma_fire_burst_hit_box[4] = { 0xF6, 0xF6, 0x13, 0x13 };

u8 magma_fire_burst_terrain_box[4] = { 1, 0, 0x0A, 9 };

s16 magma_fire_wave_offsets[8] = { 0, 8, -4, -0x0C, 4, -8, 0, 0x0C };

u16 magma_fire_pillar_positions[8] = { 0x90, 0xB0, 0x150, 0x1D0, 0xE0, 0x180, 0x1A0, 0x120 };

void (*magma_fire_pillar_funcs[3])(struct ShotObj*) = {
    func_800A5AA4,
    func_800A5BA8,
    magma_fire_pillar_repeat,
};

void (*magma_fire_breath_funcs[5])(struct ShotObj*) = {
    magma_fire_breath_follow,
    magma_fire_breath_drop,
    func_800A5E60,
    magma_fire_breath_rise,
    magma_fire_breath_exit,
};

void (*magma_fire_step_funcs[7])(struct ShotObj*) = {
    magma_fire_hit,
    magma_fire_idle,
    magma_fire_wave,
    magma_fire_pillar,
    magma_fire_breath,
    func_800A60D0,
    magma_fire_burst,
};

void (*magma_fire_state_funcs[])(struct ShotObj*) = {
    func_800A56E4,
    magma_fire_main,
    magma_fire_despawn,
};
