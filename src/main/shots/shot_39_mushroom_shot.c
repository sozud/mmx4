// ShotObj, shot_object_update_funcs[39]
// 800A47C4..800A5348
#include "common.h"

void mushroom_shot_update(struct ShotObj* self)
{
    mushroom_shot_state_funcs[self->state](self);
}

void mushroom_shot_spore_init(struct ShotObj* self)
{
    u8 y_offset;

    self->state = 1;
    self->on_screen = 1;
    self->unk61 = 1;
    self->unk2C = FIXED(0.125);
    self->y_vel.val = FIXED(4.5);
    self->unk58.data = NULL;
    self->unk42 &= 0x7FFF;
    self->unk28 = mushroom_shot_spore_x_accels[self->unk2];
    if (self->unk15 == 0) {
        self->x_pos.i.hi += (s8)mushroom_shot_spore_offsets[self->unk2 * 2];
        self->x_vel.val = mushroom_shot_spore_x_speeds[self->unk2];
    } else {
        self->x_pos.i.hi -= (s8)mushroom_shot_spore_offsets[self->unk2 * 2];
        self->x_vel.val = -mushroom_shot_spore_x_speeds[self->unk2];
    }
    y_offset = mushroom_shot_spore_offsets[self->unk2 * 2 + 1];
    self->unk50.data = mushroom_shot_spore_hit_box;
    self->timer = 0x28;
    self->unk5C = 1;
    self->unk60 = 6;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = NULL;
    self->y_pos.i.hi += (s8)y_offset;
    set_animation(self, 0xB);
}

void mushroom_shot_spore_fly(struct ShotObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_vel.val == 0) {
        self->unk2C = FIXED(0.0625);
    }
    if (self->animation_step.fields.event == 1) {
        func_8002D9BC(self);
    }

    timer = (u16)self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        set_animation(self, 0xD);
        self->state = 2;
    }
    if (self->unk7C->state == 2) {
        self->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 1) {
        self->state = 2;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void mushroom_shot_spore_burst(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8002D9BC(self);
    }
    if (self->animation_step.fields.event == 2) {
        self->state = 3;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void mushroom_shot_spore_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void mushroom_shot_sprout_init(struct ShotObj* self)
{
    u16 x_pos;
    self->unk58.collision_bounds = D_801061F0;
    if (self->unk15 == 0) {
        x_pos = self->x_pos.u.hi - 0x20;
    } else {
        x_pos = self->x_pos.u.hi + 0x20;
    }
    self->x_pos.u.hi = x_pos;
    self->y_vel.val = FIXED(-3);
    self->unk5C = 1;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk16 = 0;
    self->unk60 = 6;
    set_animation(self, 0x10);
    self->state = 5;
    self->unk5 = 0;
}

void mushroom_shot_sprout_main(struct ShotObj* self)
{
    u8 color;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    mushroom_shot_sprout_step_funcs[self->unk5](self);
    self->unk42 &= 0x7FFF;
    if (self->unk5 != 6) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
    if (self->unk6 != 0) {
        func_8002D9BC(self);
        if (D_80141BD8.unk0 & 1) {
            if (++self->unk7 == 4) {
                self->unk7 = 0;
            }
            if (engine_obj.stage == 3) {
                color = mushroom_shot_sprout_palettes[self->unk7];
            } else {
                color = mushroom_shot_sprout_alt_palettes[self->unk7];
            }
            self->unk42 = (color & 0xF) | (((color >> 4) + 0x1E0) << 6);
        }
    }
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        self->state = 6;
    }
    if (self->unk7C->state == 2) {
        self->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        self->state = 6;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void mushroom_shot_sprout_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

// mushroom_shot_spray_init
INCLUDE_ASM("main/nonmatchings/shots/shot_39_mushroom_shot", func_800A4D20);

void mushroom_shot_spray_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8002D9BC(self);
    }
    if (self->animation_step.fields.event == 2) {
        self->state = 9;
    }
    if (self->unk7C->state == 2) {
        self->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 1) {
        self->state = 9;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void mushroom_shot_spray_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void mushroom_shot_sprout_grow(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;
    u32 var_v0;
    u8 var_v1;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 3);
        self->unk2C = FIXED(0.21875);
        self->unk5 = 1;
        self->unk6 = 1;
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->y_vel.val = 0;
        self->unk7 = 0;
        self->unk8A = 3;
        self->unk84.bytes[0] = 0;
        if (engine_obj.stage == 3) {
            var_v1 = mushroom_shot_sprout_palettes[self->unk7];
            var_v0 = var_v1 >> 4;
        } else {
            var_v1 = mushroom_shot_sprout_alt_palettes[self->unk7];
            var_v0 = var_v1 >> 4;
        }
        self->unk42 = (var_v1 & 0xF) | ((var_v0 + 0x1E0) << 6);
    }
}

void mushroom_shot_sprout_hop(struct ShotObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if ((self->unk84.bytes[0] == 0) && (self->y_vel.val < 0)) {
        set_animation(self, 3);
        self->unk84.bytes[0] = 1;
    }
    animate_object(self);
    if (self->unk70 & 8) {
        set_animation(self, 0xA);
        self->unk5 = 2;
    }
}

void mushroom_shot_sprout_land(struct ShotObj* self)
{
    s16 remaining;
    s8 state;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        remaining = self->unk8A - 1;
        self->unk8A = remaining;
        if (remaining == 0) {
            set_animation(self, 0);
            self->timer = 0x28;
            state = 3;
        } else {
            set_animation(self, 2);
            state = 4;
        }
        self->unk5 = state;
    }
}

void mushroom_shot_sprout_wait(struct ShotObj* self)
{
    if (--self->timer == 0) {
        set_animation(self, 0x16);
        self->timer = 0x28;
        self->unk5 = 5;
    }
}

void mushroom_shot_sprout_jump(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk84.bytes[0] = 0;
        self->y_vel.val = FIXED(4);
        move_with_gravity(ANIMATED_OBJECT(self));
        self->unk5 = 1;
    }
}

// mushroom_shot_sprout_chase
INCLUDE_ASM("main/nonmatchings/shots/shot_39_mushroom_shot", func_800A5194);

void mushroom_shot_sprout_fall(struct ShotObj* self)
{
    move_with_gravity((struct AnimatedObj*)self);
    animate_object(self);
}

u8 mushroom_shot_spore_hit_box[4] = { 0xF1, 0xF1, 0x19, 0x1C };

u8 mushroom_shot_sprout_hit_box[4] = { 0xF9, 0xF9, 0x0D, 0x0D };

u8 mushroom_shot_sprout_palettes[4] = { 0x3C, 0x3D, 0x3E, 0x3F };

u8 mushroom_shot_sprout_alt_palettes[4] = { 0x2C, 0x2D, 0x2E, 0x2F };

u8 mushroom_shot_spore_offsets[8] = { 0x0C, 0x0B, 0x06, 0x0F, 0xFC, 0x0F, 0xF5, 0x0D };

u8 mushroom_shot_spray_offsets[12] = { 0xFC, 0xED, 0xF4, 0xF0, 0x04, 0xF0, 0xF0, 0xF3, 0x08, 0xF3, 0, 0 };

s32 mushroom_shot_spore_x_speeds[4] = { -0x22000, -0x10000, 0x10000, 0x22000 };

s32 mushroom_shot_spore_x_accels[4] = { -0xA00, -0x600, 0x600, 0xA00 };

s32 mushroom_shot_spray_speeds[5] = { 0, 0x1000, -0x1000, 0x2000, -0x2000 };

void (*mushroom_shot_state_funcs[])(struct ShotObj*) = {
    mushroom_shot_spore_init,
    mushroom_shot_spore_fly,
    mushroom_shot_spore_burst,
    mushroom_shot_spore_despawn,
    mushroom_shot_sprout_init,
    mushroom_shot_sprout_main,
    mushroom_shot_sprout_despawn,
    func_800A4D20,
    mushroom_shot_spray_fly,
    mushroom_shot_spray_despawn,
};

void (*mushroom_shot_sprout_step_funcs[7])(struct ShotObj*) = {
    mushroom_shot_sprout_grow,
    mushroom_shot_sprout_hop,
    mushroom_shot_sprout_land,
    mushroom_shot_sprout_wait,
    mushroom_shot_sprout_jump,
    func_800A5194,
    mushroom_shot_sprout_fall,
};
