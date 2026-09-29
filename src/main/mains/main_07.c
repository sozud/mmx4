// MainObj, main_object_update_funcs[7]
// 800473C8..80047C88
#include "common.h"
#include "func_tables.h"

void ambush_gunner_update(struct MainObj* self)
{
    ambush_gunner_state_funcs[self->state](self);
}

// ambush_gunner_init
INCLUDE_ASM("main/nonmatchings/mains/main_07", func_80047404);

void ambush_gunner_main(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    ambush_gunner_step_funcs[self->unk5](self);
    if (self->ext.main_7.unk90 != 0) {
        func_8002D9BC(self);
        self->ext.main_7.saved_unk5 = self->unk5;
        if (func_8002DD04(self) < 0) {
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(5, ambush_gunner_debris, self);
            if (!(self->unk2 & 1)) {
                func_800BF638(BASE_OBJECT(self), 0xE, self->x_pos.u.hi - 0xA, self->y_pos.i.hi);
            } else {
                func_800BF638(BASE_OBJECT(self), 0xE, self->x_pos.u.hi + 0xA, self->y_pos.i.hi);
            }
            self->state = 2;
            return;
        }
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        if (self->unk5 != 2 || self->unk6 != 0) {
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        }
    } else {
        self->state = 2;
    }
}

void ambush_gunner_despawn(struct MainObj* self)
{
    self->unk7A = 0;
    self->ext.main_7.unk80 = 0;
    self->ext.main_7.unk84 = 0;
    self->ext.main_7.saved_x_velocity = 0;
    self->ext.main_7.saved_y_velocity = 0;
    self->ext.main_7.unk90 = 0;
    self->ext.main_7.saved_unk5 = 0;
    self->invincibility_timer = 0;
    despawn_object(OBJECT_HEADER(self));
}

void ambush_gunner_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_7.saved_unk5;
}

void ambush_gunner_emerge(struct MainObj* self)
{
    ambush_gunner_emerge_funcs[self->unk6](self);
}

// ambush_gunner_emerge_wait
INCLUDE_ASM("main/nonmatchings/mains/main_07", func_80047818);

void ambush_gunner_emerge_burst(struct MainObj* self)
{
    self->invincibility_timer = 0;
    self->ext.main_7.unk90 = 1;
    spawn_rubble(8, ambush_gunner_emerge_particles, self,
        self->unk15 == 0 ? FIXED(-3) : FIXED(3));
    func_8001540C(2, 0x15, self);
    animate_object(ANIMATED_OBJECT(self));
    self->unk6 = 2;
}

void ambush_gunner_emerge_finish(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 0x16, self);
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void ambush_gunner_aim(struct MainObj* self)
{
    ambush_gunner_aim_funcs[self->unk6](self);
}

void ambush_gunner_aim_start(struct MainObj* self)
{
    self->unk7C = 0x28;
    self->unk6 = 1;
}

void ambush_gunner_aim_wait(struct MainObj* self)
{
    if (self->unk7C == 0) {
        set_velocity_from_angle(
            MOVING_OBJECT(self),
            angle_to_object(
                OBJECT_HEADER(self),
                OBJECT_HEADER(&g_Player))
                & 0xFF);

        if ((self->unk15 == 0 && self->x_speed < 0) || (self->unk15 != 0 && self->x_speed > 0)) {
            self->ext.main_7.saved_x_velocity = self->x_speed;
            self->ext.main_7.saved_y_velocity = self->y_speed;
            set_animation(self, 2);
            self->unk5 = 4;
            self->unk6 = 2;
        } else {
            self->unk7C = 0x3C;
        }

        self->x_speed = 0;
        self->y_speed = 0;
    } else {
        self->unk7C--;
    }
}

void ambush_gunner_fire(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        struct ShotObj* shot;

        func_8001540C(2, 0x17, self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 2;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk2 = (u8)self->unk2 & 1;
            shot->unk15 = self->unk15;
            shot->bg_offset = self->bg_offset;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            set_velocity_from_angle(MOVING_OBJECT(self),
                angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
            if ((self->unk15 == 0 && self->x_speed < 0) || (self->unk15 != 0 && self->x_speed > 0)) {
                shot->x_vel.val = self->x_speed;
                shot->y_vel.val = self->y_speed;
            } else {
                shot->x_vel.val = self->ext.main_7.saved_x_velocity;
                shot->y_vel.val = self->ext.main_7.saved_y_velocity;
            }
            self->x_speed = 0;
            self->y_speed = 0;
        }
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

struct Unk_unk68 ambush_gunner_terrain_box = { -13, -12, 25, 24 };

union AnimationStep ambush_gunner_anim_0[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010006 },
    { 0x04010006 },
    { 0x05010004 },
    { 0x06010005 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010201 },
    { 0x0E010005 },
    { 0x0F010003 },
    { 0x10010003 },
    { 0x11010003 },
    { 0x0E010006 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15010006 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010006 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010006 },
    { 0x1C010005 },
    { 0x1D010008 },
    { 0x1C010005 },
    { 0x1B010004 },
    { 0x1B000101 },
};

union AnimationStep ambush_gunner_anim_1[] = {
    { 0x1B000101 },
};

union AnimationStep ambush_gunner_anim_2[] = {
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22010001 },
    { 0x1B010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22010001 },
    { 0x1B010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x1C010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x28010201 },
    { 0x29010001 },
    { 0x2A010001 },
    { 0x2B010002 },
    { 0x2C010003 },
    { 0x2D010004 },
    { 0x2E010004 },
    { 0x2E000101 },
};

union AnimationStep ambush_gunner_anim_3[] = {
    { 0x34000101 },
};

union AnimationStep ambush_gunner_anim_4[] = {
    { 0x35000101 },
};

union AnimationStep ambush_gunner_anim_5[] = {
    { 0x36000101 },
};

union AnimationStep ambush_gunner_anim_6[] = {
    { 0x37010002 },
    { 0x38010003 },
    { 0x39010003 },
    { 0x3A010003 },
    { 0x3B010002 },
    { 0x3C010001 },
    { 0x3D010001 },
    { 0x3E000101 },
};

union AnimationStep ambush_gunner_anim_7[] = {
    { 0x3F000101 },
};

union AnimationStep ambush_gunner_anim_8[] = {
    { 0x2F010001 },
    { 0x30010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x33FC0101 },
};

union AnimationStep* ambush_gunner_animations[] = {
    ambush_gunner_anim_0,
    ambush_gunner_anim_1,
    ambush_gunner_anim_2,
    ambush_gunner_anim_3,
    ambush_gunner_anim_4,
    ambush_gunner_anim_5,
    ambush_gunner_anim_6,
    ambush_gunner_anim_7,
    ambush_gunner_anim_8,
};

u8 ambush_gunner_debris[] = {
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x00,
    0x00,
    0x00,
};

u8 ambush_gunner_emerge_particles[] = {
    0x01,
    0x02,
    0x03,
    0x04,
    0x01,
    0x02,
    0x03,
    0x04,
};

void (*ambush_gunner_state_funcs[])(struct MainObj*) = {
    func_80047404,
    ambush_gunner_main,
    ambush_gunner_despawn,
};

void (*ambush_gunner_step_funcs[5])() = {
    enemy_hit_reaction,
    ambush_gunner_resume_step,
    ambush_gunner_emerge,
    ambush_gunner_aim,
    ambush_gunner_fire,
};

void (*ambush_gunner_emerge_funcs[3])() = {
    func_80047818,
    ambush_gunner_emerge_burst,
    ambush_gunner_emerge_finish,
};

void (*ambush_gunner_aim_funcs[2])(struct MainObj*) = {
    ambush_gunner_aim_start,
    ambush_gunner_aim_wait,
};
