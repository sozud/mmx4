// ShotObj, shot_object_update_funcs[45]
// 800A7AF0..800A8628
#include "common.h"

s16 colonel_wave_offsets[2][2] = {
    { 0x45, -0x12 },
    { 0x45, 0x10 },
};

s8 colonel_shot_boxes[14][4] = {
    { -1, -18, 15, 35 },
    { -4, -25, 19, 49 },
    { -1, 11, 10, 20 },
    { -1, 4, 10, 27 },
    { -4, -20, 15, 51 },
    { -1, -18, 15, 35 },
    { -11, -45, 28, 76 },
    { -11, -54, 28, 85 },
    { -15, -64, 33, 95 },
    { -18, -6, 41, 9 },
    { -6, -13, 12, 43 },
    { -11, -13, 23, 24 },
    { -64, -24, 35, 54 },
    { -62, -32, 30, 61 },
};

void colonel_shot_update(struct ShotObj* self)
{
    colonel_shot_state_funcs[self->state](self);
}

void colonel_shot_init(struct ShotObj* self)
{
    struct WeaponObj* weapon;
    u8 temp_unk15;
    s32 temp_y;

    weapon = self->unk7C;
    self->unk3C = weapon->unk3C;
    self->unk40 = weapon->unk40;
    self->unk42 = weapon->unk42 & 0x7FFF;
    self->bg_offset = weapon->bg_offset;
    self->animation_table = weapon->animation_table;
    temp_unk15 = weapon->unk15;
    self->unk58.data = NULL;
    self->unk54 = NULL;
    self->unk50.data = NULL;
    self->unk15 = temp_unk15;
    self->x_pos.val = weapon->x_pos.val;
    temp_y = weapon->y_pos.val;
    self->state++;
    self->unk5 = (s8)(u8)self->unk2 >> 4;
    self->y_pos.val = temp_y;
    self->unk2 &= 0xF;
}

void colonel_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void colonel_shot_run(struct ShotObj* self)
{
    colonel_shot_kind_funcs[self->unk5](self);
#ifdef MMX4_PC
    if (self->unk8C.object == NULL) {
        return;
    }
#endif
    if (self->unk8C.object->state == 2) {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void colonel_wave(struct ShotObj* self)
{
    colonel_wave_funcs[self->unk6](self);
    func_8002D9BC(self);
    if (engine_obj.stage == 0xA) {
        func_8002DD04(MAIN_OBJECT(self));
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
    self->unk6 = 0;
}

// colonel_wave_start
INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A7CE8);

void colonel_wave_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object((struct MovingObj*)self);
}

void colonel_streak(struct ShotObj* self)
{
    colonel_streak_funcs[self->unk6](self);
    func_8002D9BC(self);
    is_on_screen((struct BaseObj*)self);
}

void colonel_streak_start(struct ShotObj* arg)
{
    struct ShotObj* self = arg;

    set_animation(self, 0x10);
    self->unk5C = 5;
    self->unk60 = 6;
    if (self->unk2 != 0) {
        self->x_vel.val = FIXED(6);
        self->unk15 = 0x40;
    } else {
        self->x_vel.val = FIXED(-6);
        self->unk15 = 0;
    }
    self->unk50.data = (u8*)&colonel_shot_boxes[9];
    self->timer = 5;
    self->unk8A = 0x32;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk58.data = 0;
    self->unk54 = 0;
    self->y_pos.i.hi = (u16)self->y_pos.i.hi + 0x20;
    self->unk6++;
}

void colonel_streak_move(struct ShotObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (--self->timer == 0) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x2D;
            shot->unk2 = 0x20;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk8C.object = self->unk8C.object;
        }
        self->timer = 0xA;
    }

    if (--self->unk8A == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void colonel_marker(struct ShotObj* self)
{
    colonel_marker_funcs[self->unk6](self);
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void colonel_marker_start(struct ShotObj* self)
{
    set_animation(self, 0x11);
    self->unk5C = 5;
    self->unk60 = 6;
    self->timer = 0;
    self->unk58.data = NULL;
    self->unk54 = NULL;
    self->unk50.data = (const u8*)colonel_shot_boxes[11];
    self->unk6++;
}

void colonel_marker_wait(struct ShotObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    shot = SHOT_OBJECT(self->unk7C);
    if (shot->state != 2) {
        return;
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x2D;
        shot->unk2 = self->timer + 0x30;
        shot->timer = self->timer + 1;
        shot->unk7C = WEAPON_OBJECT(self);
    }
    self->state = 2;
    self->unk5 = 0;
    self->unk6 = 0;
}

void colonel_bolt(struct ShotObj* self)
{
    colonel_bolt_funcs[self->unk6](self);
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void colonel_bolt_start(struct ShotObj* self)
{
    set_animation(self, 0xF);
    self->unk5C = 5;
    self->unk60 = 9;
    self->y_vel.val = FIXED(8);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk58.data = NULL;
    self->unk54 = NULL;
    self->unk50.data = (const u8*)colonel_shot_boxes[10];
    if (self->unk2 == 0) {
        func_8001540C(2, 0xD7, self);
    }
    self->unk6++;
}

void colonel_bolt_fall(struct ShotObj* self)
{
    animate_object(self);
    move_object((struct MovingObj*)self);
}

void colonel_slash(struct ShotObj* self)
{
    colonel_slash_funcs[self->unk6](self);
    func_8002D9BC(self);
}

void colonel_slash_start(struct ShotObj* self)
{
    self->unk5C = 0;
    self->unk60 = 9;
    self->unk58.data = NULL;
    self->unk54 = NULL;
    if (self->unk2 == 0) {
        self->unk50.data = (const u8*)colonel_shot_boxes[12];
    } else {
        self->unk50.data = (const u8*)colonel_shot_boxes[13];
    }
    self->timer = 5;
    self->unk6++;
}

void colonel_slash_wait(struct ShotObj* self)
{
    if (--self->timer == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void colonel_shockwave(struct ShotObj* self)
{
    colonel_shockwave_funcs[self->unk6](self);
    func_8002D9BC(self);
    is_on_screen((struct BaseObj*)self);
}

// colonel_shockwave_start
INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A83C4);

void colonel_shockwave_spread(struct ShotObj* self)
{
    struct ShotObj* object = self;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(object));
    func_800A858C(object);
    move_object(MOVING_OBJECT(object));

    if ((object->animation_step.fields.event == 1) && (object->timer < 0x10)) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x2D;
            shot->unk2 = (u8)object->timer + 0x50;
            shot->timer = (u16)object->timer + 1;
            shot->unk7C = WEAPON_OBJECT(object);
        }
    }

    if (object->animation_step.fields.relative_step == 0) {
        object->state = 2;
        object->unk5 = 0;
        object->unk6 = 0;
    }
}

// colonel_shockwave_move
INCLUDE_ASM("main/nonmatchings/shots/shot_45", func_800A858C);

void (*colonel_shot_state_funcs[])(struct ShotObj*) = {
    colonel_shot_init,
    colonel_shot_run,
    colonel_shot_despawn,
};

void (*colonel_shot_kind_funcs[])(struct ShotObj*) = {
    colonel_wave,
    colonel_streak,
    colonel_marker,
    colonel_bolt,
    colonel_slash,
    colonel_shockwave,
};

void (*colonel_wave_funcs[])(struct ShotObj*) = {
    func_800A7CE8,
    colonel_wave_fly,
};

void (*colonel_streak_funcs[])(struct ShotObj*) = {
    colonel_streak_start,
    colonel_streak_move,
};

void (*colonel_marker_funcs[])(struct ShotObj*) = {
    colonel_marker_start,
    colonel_marker_wait,
};

void (*colonel_bolt_funcs[])(struct ShotObj*) = {
    colonel_bolt_start,
    colonel_bolt_fall,
};

void (*colonel_slash_funcs[])(struct ShotObj*) = {
    colonel_slash_start,
    colonel_slash_wait,
};

void (*colonel_shockwave_funcs[])(struct ShotObj*) = {
    func_800A83C4,
    colonel_shockwave_spread,
};
