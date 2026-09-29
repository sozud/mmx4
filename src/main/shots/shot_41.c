// ShotObj, shot_object_update_funcs[41]
// 800A56E4..800A6374
#include "common.h"

// magma_fire_init
INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A56E4);

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
INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5AA4);

// magma_fire_pillar_erupt
INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5BA8);

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
    self->unk5 = 0;
    self->unk6 = 0;
    self->state++;
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
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
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
INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A5E60);

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
        func_8001540C(2, 6, self);
    }
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 7, self);
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
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
    }
}

void magma_fire_breath(struct ShotObj* self)
{
    magma_fire_breath_funcs[self->unk6](self);
}

// magma_fire_spread
INCLUDE_ASM("main/nonmatchings/shots/shot_41", func_800A60D0);

void magma_fire_burst(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
    }
}

void magma_fire_hit(struct ShotObj* self)
{
    enemy_hit_reaction(self);
}

void magma_fire_idle(struct ShotObj* self)
{
}

void magma_fire_main(struct ShotObj* self)
{
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
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

u8 magma_fire_pillar_hit_boxes[2][4] = {
    { 0xF7, 0xF2, 0x10, 0x18 },
    { 0xF7, 0xF7, 0x0F, 0x11 },
};

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
