// MainObj, main_object_update_funcs[24]
// 80056788..80057100
#include "common.h"
#include "func_tables.h"

extern u8 jet_drone_debris[];

void jet_drone_update(struct MainObj* self)
{
    jet_drone_state_funcs[self->state](self);
}

// jet_drone_init
INCLUDE_ASM("main/nonmatchings/mains/main_24_jet_drone", func_800567C4);

void jet_drone_main(struct MainObj* self)
{
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    jet_drone_step_funcs[self->unk5](self);

    if (self->unk5 != 3) {
        func_8002D9BC(self);
        self->ext.main_24.saved_unk5 = self->unk5;

        hit = func_8002DD04(self);
        if (hit < 0) {
            spawn_explosion(self);
            spawn_debris(5, jet_drone_debris, self);
            drop_item(BASE_OBJECT(self), 0xC);
        } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
            return;
        }

        self->state = 2;
    }
}

void jet_drone_despawn(struct MainObj* self)
{
    self->unk7A = 0;
    self->ext.main_24.unk80 = 0;
    self->ext.main_24.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void jet_drone_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_24.saved_unk5;
}

void jet_drone_fly(struct MainObj* self)
{
    jet_drone_fly_funcs[self->unk6](self);
}

void jet_drone_fly_dash(struct MainObj* self)
{
    struct MiscObj* trail;

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (!(++self->ext.main_24.unk80 & 3)) {
        trail = find_free_misc_obj();
        if (trail != NULL) {
            trail->active = 0x41;
            trail->id = 7;
            trail->unk2 = 0;
            trail->unk40 = self->unk40;
            trail->unk42 = self->unk42 & 0x7FFF;
            trail->animation_table = (u32**)self->animation_table;
            trail->unk3C = (void*)self->sprite_frames;
            trail->bg_offset = self->bg_offset;
            trail->x_pos.val = self->x_pos.val;
            trail->y_pos.val = self->y_pos.val;
            trail->unk15 = self->unk15;
            trail->ext.misc_7.position = &self->x_pos;
            trail->state = 0;
        }
    }
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        self->unk6 = 1;
    }
}

void jet_drone_fly_arc(struct MainObj* self)
{

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed == 0) {
        if ((self->unk2 & 3) <= 1) {
            self->gravity = FIXED(0.1875);
        } else {
            self->gravity = FIXED(-0.1875);
        }
    }
    if (self->x_speed == 0) {
        self->x_accel >>= 2;
        self->unk7C = 0xA;
        set_animation(self, 2);
        self->unk6 = 2;
    }
}

void jet_drone_fly_turn(struct MainObj* self)
{
    struct MiscObj* trail;

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (!(++self->ext.main_24.unk80 & 3)) {
        trail = find_free_misc_obj();
        if (trail != NULL) {
            trail->active = 0x41;
            trail->id = 7;
            trail->unk2 = 1;
            trail->unk40 = self->unk40;
            trail->unk42 = self->unk42 & 0x7FFF;
            trail->animation_table = (u32**)self->animation_table;
            trail->unk3C = (void*)self->sprite_frames;
            trail->bg_offset = self->bg_offset;
            trail->x_pos.val = self->x_pos.val;
            trail->y_pos.val = self->y_pos.val;
            trail->unk15 = self->unk15 ^ 0x40;
            trail->ext.misc_7.position = &self->x_pos;
            trail->state = 0;
        }
    }
    if (--self->unk7C == 0) {
        self->gravity = 0;
        if ((self->unk2 & 3) <= 1) {
            self->y_speed = FIXED(-2);
        } else {
            self->y_speed = FIXED(2);
        }
        self->unk7C = 1;
        self->unk7E = 8;
        self->unk6 = 3;
    }
}

void jet_drone_fly_bomb(struct MainObj* self)
{
    struct MiscObj* trail;
    struct ShotObj* shot;

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (!(++self->ext.main_24.unk80 & 3)) {
        trail = find_free_misc_obj();
        if (trail != NULL) {
            trail->active = 0x41;
            trail->id = 7;
            trail->unk2 = 1;
            trail->unk40 = self->unk40;
            trail->unk42 = self->unk42 & 0x7FFF;
            trail->animation_table = (u32**)self->animation_table;
            trail->unk3C = (void*)self->sprite_frames;
            trail->bg_offset = self->bg_offset;
            trail->x_pos.val = self->x_pos.val;
            trail->y_pos.val = self->y_pos.val;
            trail->unk15 = self->unk15 ^ 0x40;
            trail->ext.misc_7.position = &self->x_pos;
            trail->state = 0;
        }
    }
    if (--self->unk7E == 0) {
        set_animation(self, 9);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0xD;
            shot->unk2 = 0;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk3C = (void*)self->sprite_frames;
            shot->bg_offset = self->bg_offset;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk15 = self->unk15;
            shot->state = 0;
        }
        if (--self->unk7C == 0) {
            self->unk7E = 0x7FFF;
        } else {
            self->unk7E = 8;
        }
    }
}

void jet_drone_wait_for_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0xA0) {
        func_8001540C(2, 0x50, self);
        self->unk7A = 0;
        self->unk5 = 2;
    }
}

struct Unk_unk68 jet_drone_hurt_box[] = {
    { -11, -12, 22, 22 },
};

struct Unk_unk68 jet_drone_terrain_box[] = {
    { -8, -11, 16, 20 },
};

union AnimationStep jet_drone_anim_0[] = {
    { 0x00010006 },
    { 0x07010005 },
    { 0x06010004 },
    { 0x05010005 },
    { 0x04010006 },
    { 0x03010005 },
    { 0x02010004 },
    { 0x01010005 },
    { 0x00F90106 },
};

union AnimationStep jet_drone_anim_1[] = {
    { 0x0C010003 },
    { 0x0D010005 },
    { 0x08010003 },
    { 0x09010004 },
    { 0x0A010005 },
    { 0x0B000101 },
};

union AnimationStep jet_drone_anim_2[] = {
    { 0x0B000101 },
};

union AnimationStep jet_drone_anim_3[] = {
    { 0x11010002 },
    { 0x15010002 },
    { 0x13010002 },
    { 0x15010002 },
    { 0x14010002 },
    { 0x12010002 },
    { 0x16010002 },
    { 0x15F90002 },
};

union AnimationStep jet_drone_anim_4[] = {
    { 0x17000101 },
};

union AnimationStep jet_drone_anim_5[] = {
    { 0x18000101 },
};

union AnimationStep jet_drone_anim_6[] = {
    { 0x19000101 },
};

union AnimationStep jet_drone_anim_7[] = {
    { 0x1A000101 },
};

union AnimationStep jet_drone_anim_8[] = {
    { 0x1B000101 },
};

union AnimationStep jet_drone_anim_9[] = {
    { 0x0E010004 },
    { 0x0F010005 },
    { 0x0E010004 },
    { 0x0B000101 },
};

union AnimationStep jet_drone_anim_10[] = {
    { 0x10010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1E000101 },
};

union AnimationStep* jet_drone_animations[] = {
    jet_drone_anim_0,
    jet_drone_anim_1,
    jet_drone_anim_2,
    jet_drone_anim_3,
    jet_drone_anim_4,
    jet_drone_anim_5,
    jet_drone_anim_6,
    jet_drone_anim_7,
    jet_drone_anim_8,
    jet_drone_anim_9,
    jet_drone_anim_10,
};

u8 jet_drone_debris[] = {
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x00,
    0x00,
    0x00,
};

void (*jet_drone_state_funcs[])(struct MainObj*) = {
    func_800567C4,
    jet_drone_main,
    jet_drone_despawn,
};

void (*jet_drone_step_funcs[])(struct MainObj*) = {
    (void (*)(struct MainObj*))enemy_hit_reaction,
    jet_drone_resume_step,
    jet_drone_fly,
    jet_drone_wait_for_player,
};

void (*jet_drone_fly_funcs[])() = {
    jet_drone_fly_dash,
    jet_drone_fly_arc,
    jet_drone_fly_turn,
    jet_drone_fly_bomb,
};
