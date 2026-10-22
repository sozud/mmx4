// MainObj, main_object_update_funcs[24]
// 80056788..80057100
#include "common.h"
#include "main/mains/main_24_jet_drone.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"

extern u8 jet_drone_debris[];

void jet_drone_main(struct MainObj*);
void jet_drone_despawn(struct MainObj* arg0);

// jet_drone_step_funcs
extern void (*jet_drone_step_funcs[])(struct MainObj*);
void jet_drone_resume_step(struct MainObj* arg0);
void jet_drone_fly(struct MainObj* arg0);
void jet_drone_wait_for_player(struct MainObj* arg0);

void jet_drone_fly_arc(struct MainObj*);

extern void (*jet_drone_state_funcs[])(struct MainObj*);
extern void (*jet_drone_fly_funcs[])(struct MainObj*);

extern u8 jet_drone_debris[];

void jet_drone_update(struct MainObj* self)
{
    jet_drone_state_funcs[self->state](self);
}

// jet_drone_init
#ifdef MMX4_PC
void func_800567C4(struct MainObj* arg0);
extern struct Unk_unk68 D_80106E74[];
extern union AnimationStep* jet_drone_animations[];
extern struct Unk_unk68 jet_drone_hurt_box[];
extern struct Unk_unk68 jet_drone_terrain_box[];
#endif

#ifdef MMX4_PC
void func_800567C4(struct MainObj* arg0)
{
    static const s32 motion[4][3] = {
        { -0x4000, -0x1C000, 0x14 },
        { -0x2000, -0xC000, 0x24 },
        { 0x4000, 0x1C000, 0x14 },
        { 0x2000, 0xC000, 0x24 },
    };
    u8 subtype = arg0->unk2;

    arg0->hp = 2;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = (const u16*)D_80106E74;
    arg0->animation_table = (const u8* const*)jet_drone_animations;
    arg0->unk16 = 6;
    arg0->hurt_box = (const u8*)jet_drone_hurt_box;
    arg0->air_state = 0;
    arg0->terrain_box = NULL;
    arg0->attack_box = (const u8*)jet_drone_terrain_box;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (subtype < 8) {
        arg0->x_accel = -0x8000;
        arg0->gravity = motion[subtype & 3][0];
        arg0->y_speed = motion[subtype & 3][1];
        arg0->unk7C = motion[subtype & 3][2];
        if (subtype < 4) {
            arg0->x_speed = -0x50000;
            arg0->unk15 = 0;
            func_8001540C(2, 0x50, arg0);
            arg0->unk5 = 2;
        } else {
            arg0->unk7A = 1;
            arg0->unk15 = 0x40;
            arg0->x_speed = 0x50000;
            arg0->unk5 = 3;
        }
    }
    set_animation(arg0, 0);
    arg0->ext.main_24.unk80 = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_24_jet_drone", func_800567C4);
#endif

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
