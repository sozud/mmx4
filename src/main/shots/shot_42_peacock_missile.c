// ShotObj, shot_object_update_funcs[42]
// 800A6374..800A6960
#include "common.h"

void peacock_missile_update(struct ShotObj* self)
{
    peacock_missile_state_funcs[self->state](self);
}

// peacock_missile_init
INCLUDE_ASM("main/nonmatchings/shots/shot_42_peacock_missile", func_800A63B0);

// peacock_missile_home
INCLUDE_ASM("main/nonmatchings/shots/shot_42_peacock_missile", func_800A6510);

void peacock_missile_explode_start(struct ShotObj* self)
{
    if (SHOT_OBJECT(self->backref)->state == 2) {
        self->unk50.data = NULL;
    } else {
        self->unk50.data = peacock_missile_explosion_box;
    }
    self->unk8C.word = 1;
    self->unk5 = 2;
    self->timer = 0x3C;
    self->unk60 = 6;
    set_animation(self, 0x1F);
}

// peacock_missile_spawn_explosion
INCLUDE_ASM("main/nonmatchings/shots/shot_42_peacock_missile", func_800A666C);

void peacock_missile_explode(struct ShotObj* self)
{
    s16 timer;

    timer = --self->timer;
    if (timer == 0) {
        self->state = 2;
        return;
    }
    if (!(timer & 3)) {
        func_800A666C(self, 0x10, 0x10);
    }
    animate_object(ANIMATED_OBJECT(self));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_42_peacock_missile", peacock_missile_hit_target);
#else
s32 peacock_missile_hit_target(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    if (weapon->active == 0) {
        self->unk5 = 1;
    } else if (weapon->id != 0x17) {
        self->unk5 = 1;
    } else if (func_8002C160(COLLISION_OBJECT(self), COLLISION_OBJECT(weapon)) != 0) {
        return 1;
    }
    return 0;
}
#endif

void peacock_missile_main(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    peacock_missile_step_funcs[self->unk5](self);
    func_8002D9BC(self);

    if (self->unk8C.word == 0) {
        if ((s8)func_8002DD04(MAIN_OBJECT(self)) < 0) {
            spawn_explosion(self);
            self->unk5 = 1;
            return;
        }

        if (func_8002BB80(self, &g_Player) != 0 || peacock_missile_hit_target(self) != 0) {
            self->unk5 = 1;
            return;
        }

        if (self->unk90.val == 0) {
            self->unk5 = 1;
            return;
        } else {
            self->unk90.val--;
        }
    }

    is_on_screen(BASE_OBJECT(self));
}

void peacock_missile_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

u8 peacock_missile_hit_box[4] = { 0xF8, 0xF8, 0x0F, 0x0E };

u8 peacock_missile_terrain_box[4] = { 0, 0, 4, 4 };

u8 peacock_missile_explosion_box[4] = { 0xF6, 0xF6, 0x13, 0x13 };

s16 peacock_missile_launch_offsets[8][2] = {
    { -0x18, 0 },
    { -0x16, -0x12 },
    { -0x0B, -0x20 },
    { 3, -0x2A },
    { 0x1B, -0x29 },
    { 0x2F, -0x23 },
    { 0x33, -0x10 },
    { 0x33, 2 },
};

u8 peacock_missile_turn_steps_ccw[8] = { 0x10, 0x0E, 0x0C, 0x0A, 6, 4, 2, 0 };

u8 peacock_missile_turn_steps_cw[8] = { 0, 2, 4, 6, 0x0A, 0x0C, 0x0E, 0x10 };

void (*peacock_missile_state_funcs[])(struct ShotObj*) = {
    func_800A63B0,
    peacock_missile_main,
    peacock_missile_despawn,
};

void (*peacock_missile_step_funcs[3])(struct ShotObj*) = {
    func_800A6510,
    peacock_missile_explode_start,
    peacock_missile_explode,
};
