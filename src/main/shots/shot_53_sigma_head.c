// ShotObj, shot_object_update_funcs[53]
// 800AAC98..800ABE08
#include "common.h"

s8 sigma_head_boxes[3][4] = {
    { -34, -40, 67, 79 },
    { -54, -19, 20, 25 },
    { 0, 4, 26, 35 },
};

s16 sigma_head_formation_start[8][3][2] = {
    { { 0x3E0, 0x278 }, { 0x610, 0x258 }, { 0x610, 0x2A8 } },
    { { 0x3E0, 0x2B8 }, { 0x4D8, 0x1D0 }, { 0x610, 0x2B8 } },
    { { 0x3E0, 0x2B8 }, { 0x3E0, 0x258 }, { 0x610, 0x288 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2A8 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2A8 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2B8 } },
    { { 0x568, 0x1D0 }, { 0x528, 0x1D0 }, { 0x448, 0x1D0 } },
    { { 0x598, 0x308 }, { 0x448, 0x1D0 }, { 0x4E8, 0x308 } },
};

s16 sigma_head_formation_end[8][3][2] = {
    { { 0x448, 0x278 }, { 0x598, 0x258 }, { 0x598, 0x2A8 } },
    { { 0x448, 0x2B8 }, { 0x4D8, 0x248 }, { 0x598, 0x2B8 } },
    { { 0x448, 0x2B8 }, { 0x448, 0x258 }, { 0x598, 0x288 } },
    { { 0x578, 0x2B8 }, { 0x498, 0x258 }, { 0x498, 0x2A8 } },
    { { 0x598, 0x2B8 }, { 0x498, 0x258 }, { 0x498, 0x2A8 } },
    { { 0x578, 0x2B8 }, { 0x408, 0x258 }, { 0x448, 0x2B8 } },
    { { 0x568, 0x248 }, { 0x528, 0x258 }, { 0x448, 0x248 } },
    { { 0x598, 0x2B8 }, { 0x448, 0x248 }, { 0x4E8, 0x2B8 } },
};

u8 sigma_head_formation_next[8][3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 2 },
    { 1, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 1 },
};

void (*sigma_head_move_funcs[])(struct ShotObj*) = {
    sigma_head_move_start,
    sigma_head_move,
};

void (*sigma_head_fire_wall_funcs[])(struct ShotObj*) = {
    sigma_head_fire_wall_start,
    func_800AB170,
    sigma_head_fire_wall_shoot,
};

void (*sigma_head_lightning_funcs[])(struct ShotObj*) = {
    sigma_head_lightning_start,
    sigma_head_lightning_shoot,
};

void (*sigma_head_freeze_funcs[])(struct ShotObj*) = {
    sigma_head_freeze_start,
    sigma_head_freeze_open,
    sigma_head_freeze_drop,
};

void (*sigma_head_chomp_funcs[])(struct ShotObj*) = {
    sigma_head_chomp_start,
    sigma_head_chomp_wait,
};

void (*sigma_head_shift_funcs[])(struct ShotObj*) = {
    sigma_head_shift_start,
    sigma_head_shift_move,
};

void (*sigma_head_vanish_funcs[])(struct ShotObj*) = {
    sigma_head_vanish_start,
    sigma_head_vanish_blink,
};

void (*sigma_head_step_funcs[])(struct ShotObj*) = {
    sigma_head_resume,
    sigma_head_idle,
    sigma_head_move_to_formation,
    func_800AB050,
    sigma_head_fire_wall,
    sigma_head_lightning,
    sigma_head_freeze,
    sigma_head_vanish,
    sigma_head_shift,
    sigma_head_chomp,
};

// sigma_head_init
INCLUDE_ASM("main/nonmatchings/shots/shot_53_sigma_head", func_800AAC98);

void sigma_head_resume(struct ShotObj* self)
{
    enemy_hit_reaction(self);
}

void sigma_head_idle(struct ShotObj* self)
{
}

void sigma_head_move_start(struct ShotObj* self)
{
    s8 direction;

    self->unk8C.bytes[2] = MAIN_OBJECT(self->unk7C)->ext.main_74.effect_state;
    self->unk15 = 0;
    self->unk5C = 0x30;
    self->x_pos.i.hi = sigma_head_formation_start[self->unk8C.bytes[2]][self->unk2][0];
    self->y_pos.i.hi = sigma_head_formation_start[self->unk8C.bytes[2]][self->unk2][1];
    direction = angle_to_point(OBJECT_HEADER(self),
        sigma_head_formation_end[self->unk8C.bytes[2]][self->unk2][0] << 16,
        sigma_head_formation_end[self->unk8C.bytes[2]][self->unk2][1] << 16);
    self->unk8C.bytes[1] = direction;
    set_velocity_from_angle(MOVING_OBJECT(self), direction & 0xFF);
    set_animation(self, 7);
    self->unk8C.byte = 1;
    self->unk68 = (struct Unk_unk68*)sigma_head_boxes[2];
    self->x_vel.val *= 3;
    self->y_vel.val *= 3;
    self->unk6++;
}

void sigma_head_move(struct ShotObj* self)
{
    u8 index;
    s8 variant;

    move_object(MOVING_OBJECT(self));
    if ((angle_to_point(OBJECT_HEADER(self),
             sigma_head_formation_end[self->unk8C.bytes[2]][self->unk2][0] << 16,
             sigma_head_formation_end[self->unk8C.bytes[2]][self->unk2][1] << 16)
            ^ (s8)self->unk8C.bytes[1])
        & 0x10) {
        self->unk6 = 0;
        self->x_pos.i.hi = sigma_head_formation_end[self->unk8C.bytes[2]][self->unk2][0];
        self->y_pos.i.hi = sigma_head_formation_end[self->unk8C.bytes[2]][self->unk2][1];
        index = self->unk8C.bytes[2];
        variant = self->unk2;
        if (sigma_head_formation_next[index][variant] != 0) {
            self->unk5 = 9;
            if (sigma_head_formation_next[self->unk8C.bytes[2]][self->unk2] == 2) {
                self->unk15 = 0x40;
            }
        } else if (index == 5 && variant != 0) {
            self->unk5 = 8;
            self->unk15 = 0x40;
        } else {
            self->unk5 = 3;
        }
    }
}

void sigma_head_move_to_formation(struct ShotObj* self)
{
    sigma_head_move_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x80, 0x80);
}

// sigma_head_wait
INCLUDE_ASM("main/nonmatchings/shots/shot_53_sigma_head", func_800AB050);

void sigma_head_fire_wall_start(struct ShotObj* self)
{
    set_animation(self, 8);
    self->timer = 0x3C;
    self->unk8A = 4;
    self->unk6++;
}

// sigma_head_fire_wall_track
INCLUDE_ASM("main/nonmatchings/shots/shot_53_sigma_head", func_800AB170);

void sigma_head_fire_wall_shoot(struct ShotObj* self)
{
    struct WeaponObj* owner;
    struct ShotObj* shot;
    u32 i;

    owner = self->unk7C;
    self->timer--;
    if (self->timer == 0) {
        i = 0;
        do {
            func_8001540C(2, 3, self);
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x36;
                shot->unk2 = 0;
                shot->unk7 = i;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val;
                shot->unk7C = owner;
            }
            i++;
        } while (i < 4);
        self->timer = 0x28;
        self->unk8A--;
        if (self->unk8A == 0) {
            self->unk5 = 3;
            self->unk6 = 0;
            MAIN_OBJECT(owner)->ext.main_74.unk8E = 1;
            return;
        }
        self->unk6--;
    }
}

void sigma_head_fire_wall(struct ShotObj* self)
{
    sigma_head_fire_wall_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void sigma_head_lightning_start(struct ShotObj* self)
{
    self->timer = 1;
    self->unk8A = 6;
    self->unk6++;
}

void sigma_head_lightning_shoot(struct ShotObj* self)
{
    s16 timer;
    s16 count;
    struct ShotObj* shot;
    struct MiscObj* misc;
    struct WeaponObj* owner;

    owner = self->unk7C;
    timer = (u16)self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 8, self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x36;
            shot->unk2 = 1;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val - FIXED(24);
            shot->unk7C = owner;
        }
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x37;
            misc->unk2 = 3;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val - FIXED(24);
            misc->ext.misc_55.owner = MAIN_OBJECT(shot);
        }
        self->timer = 0x1E;
        count = (u16)self->unk8A - 1;
        self->unk8A = count;
        if (count == 0) {
            self->unk5 = 3;
            self->unk6 = 0;
            MAIN_OBJECT(owner)->ext.main_74.unk8E = 1;
        }
    }
}

void sigma_head_lightning(struct ShotObj* self)
{
    sigma_head_lightning_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void sigma_head_freeze_start(struct ShotObj* self)
{
    set_animation(self, 9);
    self->timer = 1;
    self->x_vel.val = FIXED(-1);
    self->y_vel.val = 0;
    self->unk6++;
}

void sigma_head_freeze_open(struct ShotObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
    }
    animate_object(self);
}

void sigma_head_freeze_drop(struct ShotObj* self)
{
    s16 timer;
    struct ShotObj* shot;
    struct WeaponObj* owner;

    owner = self->unk7C;
    timer = self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 7, self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x36;
            shot->unk2 = 2;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk7C = owner;
        }
        self->timer = 6;
    }
    move_object(MOVING_OBJECT(self));
    if (self->x_pos.i.hi < 0x4D8) {
        self->unk5 = 3;
        self->unk6 = 0;
        MAIN_OBJECT(owner)->ext.main_74.unk8E = 1;
    }
}

void sigma_head_freeze(struct ShotObj* self)
{
    sigma_head_freeze_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void sigma_head_chomp_start(struct ShotObj* self)
{
    set_animation(self, 0xB);
    func_8001540C(2, 4, self);
    self->unk6++;
}

void sigma_head_chomp_wait(struct ShotObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }

    if (self->animation_step.fields.event == 1) {
        self->animation_step.fields.event = 0;
        self->unk50.data = (const u8*)sigma_head_boxes[1];
    }

    animate_object(ANIMATED_OBJECT(self));
}

void sigma_head_chomp(struct ShotObj* self)
{
    sigma_head_chomp_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void sigma_head_shift_start(struct ShotObj* self)
{
    set_animation(self, 9);
    self->x_vel.val = FIXED(2);
    self->y_vel.val = 0;
    self->unk28 = self->x_pos.val + FIXED(112);
    self->unk6++;
}

void sigma_head_shift_move(struct ShotObj* self)
{
    s32 limit;

    move_object(MOVING_OBJECT(self));
    animate_object(self);
    limit = self->unk28;
    if (limit < self->x_pos.val) {
        self->x_pos.val = limit;
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void sigma_head_shift(struct ShotObj* self)
{
    sigma_head_shift_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void sigma_head_vanish_start(struct ShotObj* self)
{
    self->timer = 0x32;
    self->unk8A = 2;
    self->unk50.data = NULL;
    self->unk8C.byte = 1;
    self->unk6++;
}

void sigma_head_vanish_blink(struct ShotObj* self)
{
    s16 timer;
    s16 blink_timer;

    timer = self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk68 = NULL;
        self->unk76 = 0;
        self->unk77 = 0;
        self->x_pos.i.hi = 0;
        self->y_pos.i.hi = 0;
        self->unk8C.byte = 0;
        self->unk15 = 0;
        return;
    }

    blink_timer = self->unk8A - 1;
    self->unk8A = blink_timer;
    if (blink_timer == 0) {
        self->unk8A = 2;
        self->unk8C.byte ^= 1;
    }
    if ((u8)self->unk8C.byte != 0) {
        update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
    }
}

void sigma_head_vanish(struct ShotObj* self)
{
    sigma_head_vanish_funcs[self->unk6](self);
}

void sigma_head_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        self->unk8C.byte = 0;
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk50.data = NULL;
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi + 20, 0);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi + 20, 1);
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi, -1);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi, -1);
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi - 20, -1);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi - 20, -1);
        self->x_pos.i.hi = 0;
        self->y_pos.i.hi = 0;
        self->unk5C = 0x30;
        return;
    }
    sigma_head_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    collide_with_players(PLAYER_OBJECT(self));
}

void sigma_head_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void sigma_head_update(struct ShotObj* self)
{
    struct WeaponObj* temp_s1 = self->unk7C;
    if (temp_s1->unk94 == 2) {
        self->state = 2;
        self->unk5 = 0;
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi + 20, 0);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi + 20, 1);
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi + 0, -1);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi + 0, -1);
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi - 20, -1);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi - 20, -1);
    }
    if (temp_s1->unk94 == 1) {
        self->unk8C.byte = 0;
        self->state = 1;
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk7 = 1;
        self->unk50.data = NULL;
        temp_s1->ext.weapon_6.direction = 0;
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi + 20, 0);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi + 20, 1);
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi + 0, -1);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi + 0, -1);
        spawn_explosion_at(0, self->x_pos.i.hi + 15, self->y_pos.i.hi - 20, -1);
        spawn_explosion_at(0, self->x_pos.i.hi - 15, self->y_pos.i.hi - 20, -1);
        self->x_pos.i.hi = 0;
        self->y_pos.i.hi = 0;
        self->unk5C = 0x30;
        return;
    }
    self->on_screen = 0;
    sigma_head_state_funcs[self->state](self);
}

void (*sigma_head_state_funcs[])(struct ShotObj*) = {
    func_800AAC98,
    sigma_head_run,
    sigma_head_despawn,
};
