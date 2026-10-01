// MainObj, main_object_update_funcs[6]
// 80046B30..800473C8
#include "common.h"
#include "func_tables.h"

void bulldozer_update(struct MainObj* self)
{
    bulldozer_state_funcs[self->state](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

// bulldozer_init
INCLUDE_ASM("main/nonmatchings/mains/main_06_bulldozer", func_80046B80);

// bulldozer_main
INCLUDE_ASM("main/nonmatchings/mains/main_06_bulldozer", func_80046C8C);

void bulldozer_cleanup(struct MainObj* self)
{
    self->ext.main_6.armor_broken = 0;
    self->ext.main_6.ground_probe_distance = 0;
    self->ext.main_6.armor_health = 0;
    self->ext.main_6.core_health = 0;
    self->ext.main_6.hitbox_toggle = 0;
    self->ext.main_6.saved_step = 0;
    despawn_object(OBJECT_HEADER(self));
    stop_sound(2, 2);
}

void bulldozer_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_6.saved_step;
}

void bulldozer_rev(struct MainObj* self)
{
    bulldozer_rev_funcs[self->unk6](self);
}

void bulldozer_rev_begin(struct MainObj* self)
{
    if (self->ext.main_6.armor_broken == 0) {
        self->ext.main_6.ground_probe_distance = 0x48;
        set_animation(self, 0);
    } else {
        self->ext.main_6.ground_probe_distance = 8;
        set_animation(self, 1);
    }
    self->unk7C = 0x28;
    self->unk6 = 1;
    animate_object(ANIMATED_OBJECT(self));
    func_8001540C(2, 2, self);
}

void bulldozer_rev_wait(struct MainObj* self)
{
    if (self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    } else {
        self->unk7C--;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void bulldozer_charge(struct MainObj* self)
{
    bulldozer_charge_funcs[self->unk6](self);
}

void bulldozer_charge_start(struct MainObj* self)
{
    if (self->unk15 & 0x40) {
        if (self->ext.main_6.armor_broken == 0) {
            self->x_speed = FIXED(0.5);
        } else {
            self->x_speed = FIXED(2);
        }
    } else {
        if (self->ext.main_6.armor_broken == 0) {
            self->x_speed = FIXED(-0.5);
        } else {
            self->x_speed = FIXED(-2);
        }
    }
    self->unk6 = 1;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void bulldozer_charge_move(struct MainObj* self)
{
    s16 x;
    s16 y;

    if (self->unk15 != 0) {
        x = self->x_pos.u.hi + (s8)(u8)self->terrain_box->unk0 + self->ext.main_6.ground_probe_distance;
    } else {
        x = (self->x_pos.u.hi - (s8)(u8)self->terrain_box->unk0) - self->ext.main_6.ground_probe_distance;
    }

    y = self->terrain_box->unk3 + (self->y_pos.u.hi + (s8)(u8)self->terrain_box->unk1);
    if (func_8002D724(PLAYER_OBJECT(self), x, y) == 0x38) {
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

void bulldozer_fall(struct MainObj* self)
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
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void bulldozer_check_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 1;
    }
}

struct Unk_unk68 bulldozer_terrain_box = { 1, -28, 47, 45 };

struct Unk_unk68 bulldozer_hurt_boxes[2] = {
    { -50, -69, 46, 86 },
    { -18, -18, 68, 34 },
};

struct Unk_unk68 D_800FA430 = { -15, -1, 34, 18 };

struct Unk_unk68 D_800FA434[2] = {
    { -18, -18, 68, 34 },
    { -18, -18, 68, 34 },
};

union AnimationStep D_800FA43C[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07F90003 },
};

union AnimationStep D_800FA45C[] = {
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0BFD0002 },
};

union AnimationStep D_800FA46C[] = {
    { 0x0C000001 },
};

union AnimationStep D_800FA470[] = {
    { 0x0D000001 },
};

union AnimationStep D_800FA474[] = {
    { 0x0E000001 },
};

union AnimationStep D_800FA478[] = {
    { 0x0F000001 },
};

union AnimationStep D_800FA47C[] = {
    { 0x10010003 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010003 },
    { 0x15010003 },
    { 0x16010003 },
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1BF50003 },
};

union AnimationStep D_800FA4AC[] = {
    { 0x1C000001 },
};

union AnimationStep D_800FA4B0[] = {
    { 0x1D000001 },
};

union AnimationStep D_800FA4B4[] = {
    { 0x1E000001 },
};

union AnimationStep D_800FA4B8[] = {
    { 0x1F000001 },
};

union AnimationStep D_800FA4BC[] = {
    { 0x20000001 },
};

union AnimationStep D_800FA4C0[] = {
    { 0x21000001 },
};

union AnimationStep D_800FA4C4[] = {
    { 0x22000001 },
};

union AnimationStep D_800FA4C8[] = {
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010003 },
    { 0x26FD0003 },
};

union AnimationStep D_800FA4D8[] = {
    { 0x27010003 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2AFD0003 },
};

union AnimationStep* D_800FA4E8[] = {
    D_800FA43C,
    D_800FA45C,
    D_800FA46C,
    D_800FA470,
    D_800FA474,
    D_800FA478,
    D_800FA47C,
    D_800FA4AC,
    D_800FA4B0,
    D_800FA4B4,
    D_800FA4B8,
    D_800FA4BC,
    D_800FA4C0,
    D_800FA4C4,
    D_800FA4C8,
    D_800FA4D8,
};

u8 bulldozer_debris[16] = {
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x0F,
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x00,
};

void (*bulldozer_state_funcs[])() = {
    func_80046B80,
    func_80046C8C,
    bulldozer_cleanup,
};

void (*bulldozer_step_funcs[])() = {
    enemy_hit_reaction,
    bulldozer_resume_step,
    bulldozer_rev,
    bulldozer_charge,
    bulldozer_fall,
};

void (*bulldozer_rev_funcs[])() = {
    bulldozer_rev_begin,
    bulldozer_rev_wait,
};

void (*bulldozer_charge_funcs[])() = {
    bulldozer_charge_start,
    bulldozer_charge_move,
};
